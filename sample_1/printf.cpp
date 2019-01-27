/*
 * printf.cpp
 *
 */
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#define	RT_OK				(1)
#define	RT_NG				(0)

#define	mutex_create()		(0)
#define	mutex_lock(v)		(RT_OK)
#define	mutex_unlock(v)		(RT_OK)

#define	UART_BASE			(0x10013000)
//#define	UART_BASE		(0x10010000)
//#define	UART_BASE		(0x10000000)

#define	TXDATA_IDX			(0)
#define	RXDATA_IDX			(1)
#define	TXCTRL_IDX			(2)
#define	RXCTRL_IDX			(3)
#define	IE_IDX				(4)
#define	IP_IDX				(5)
#define	DIV_IDX				(6)

volatile auto uart_base = (volatile uint32_t*)(UART_BASE);

static void debug_print(const char* str)
{
	while ( *str ) {
		uart_base[TXDATA_IDX] = *str++;
	}
}

static int vtsprintf(char* buff,char* fmt,va_list arg);

static int tsprintf_string(char* ,char* );
static int tsprintf_char(int ,char* );
static int tsprintf_decimal(signed long,char* ,int ,int );
static int tsprintf_hexadecimal(unsigned long ,char* ,int ,int ,int );

static int vtsprintf(char* buff,const char* fmt,va_list arg){
	int len;
	int size;
	int zeroflag,width;

	size = 0;
	len = 0;

	while(*fmt){
		if(*fmt=='%'){		/* % �Ɋւ��鏈�� */
			zeroflag = width = 0;
			fmt++;

			if (*fmt == '0'){
				fmt++;
				zeroflag = 1;
			}
			if ((*fmt >= '0') && (*fmt <= '9')){
				width = *(fmt++) - '0';
			}

			/* printf ("zerof = %d,width = %d\n",zeroflag,width); */

			switch(*fmt){
			case 'd':		/* 10�i�� */
				size = tsprintf_decimal(va_arg(arg,signed long),buff,zeroflag,width);
				break;
			case 'x':		/* 16�i�� 0-f */
				size = tsprintf_hexadecimal(va_arg(arg,unsigned long),buff,0,zeroflag,width);
				break;
			case 'X':		/* 16�i�� 0-F */
				size = tsprintf_hexadecimal(va_arg(arg,unsigned long),buff,1,zeroflag,width);
				break;
			case 'c':		/* �L�����N�^�[ */
				size = tsprintf_char(va_arg(arg,int),buff);
				break;
			case 's':		/* ASCIIZ������ */
				size = tsprintf_string(va_arg(arg,char*),buff);
				break;
			default:		/* �R���g���[���R�[�h�ȊO�̕��� */
				/* %%(%�ɑΉ�)�͂����őΉ������ */
				len++;
				*(buff++) = *fmt;
				break;
			}
			len += size;
			buff += size;
			fmt++;
		} else {
			*(buff++) = *(fmt++);
			len++;
		}
	}

	*buff = '\0';		/* �I�[������ */

	va_end(arg);
	return (len);
}




/*
  ���l => 10�i������ϊ�
*/
static int tsprintf_decimal(signed long val,char* buff,int zf,int wd){
	int i;
	char tmp[10];
	char* ptmp = tmp + 10;
	int len = 0;
	int minus = 0;

	if (!val){		/* �w��l��0�̏ꍇ */
		*(ptmp--) = '0';
		len++;
	} else {
		/* �}�C�i�X�̒l�̏ꍇ�ɂ�2�̕␔����� */
		if (val < 0){
			val = ~val;
			val++;
			minus = 1;
		}
		while (val){
			/* �o�b�t�@�A���_�[�t���[�΍� */
			if (len >= 8){
				break;
			}

			*ptmp = (val % 10) + '0';
			val /= 10;
			ptmp--;
			len++;
		}

	}

	/* �����A�����킹�Ɋւ��鏈�� */
	if (zf){
		if (minus){
			wd--;
		}
		while (len < wd){
			*(ptmp--) =  '0';
			len++;
		}
		if (minus){
			*(ptmp--) = '-';
			len++;
		}
	} else {
		if (minus){
			*(ptmp--) = '-';
			len++;
		}
		while (len < wd){
			*(ptmp--) =  ' ';
			len++;
		}
	}

	/* ����������̃o�b�t�@�R�s�[ */
	for (i=0;i<len;i++){
		*(buff++) = *(++ptmp);
	}

	return (len);
}

/*
  ���l => 16�i������ϊ�
*/
static int tsprintf_hexadecimal(unsigned long val,char* buff,
								int capital,int zf,int wd){
	int i;
	char tmp[10];
	char* ptmp = tmp + 10;
	int len = 0;
	char str_a;

	/* A-F��啶���ɂ��邩�������ɂ��邩�؂�ւ��� */
	if (capital){
		str_a = 'A';
	} else {
		str_a = 'a';
	}

	if (!val){		/* �w��l��0�̏ꍇ */
		*(ptmp--) = '0';
		len++;
	} else {
		while (val){
			/* �o�b�t�@�A���_�[�t���[�΍� */
			if (len >= 8){
				break;
			}

			*ptmp = (val % 16);
			if (*ptmp > 9){
				*ptmp += str_a - 10;
			} else {
				*ptmp += '0';
			}

			val >>= 4;		/* 16�Ŋ��� */
			ptmp--;
			len++;
		}
	}
	while (len < wd){
		*(ptmp--) =  zf ? '0' : ' ';
		len++;
	}

	for (i=0;i<len;i++){
		*(buff++) = *(++ptmp);
	}

	return(len);
}

/*
  ���l => 1�����L�����N�^�ϊ�
*/
static int tsprintf_char(int ch,char* buff){
	*buff = (char)ch;
	return(1);
}

/*
  ���l => ASCIIZ������ϊ�
*/
static int tsprintf_string(char* str,char* buff){
	int count = 0;
	while(*str){
		*(buff++) = *str;
		str++;
		count++;
	}
	return(count);
}


/*
  Tiny sprintf�֐�
*/
int tsprintf(char* buff,const char* fmt, ...){
	va_list arg;
	int len;
	int size;
	int zeroflag,width;

	size = 0;
	len = 0;
	va_start(arg, fmt);

	vtsprintf(buff, fmt, arg);

	va_end(arg);
}

/*
  Tiny sprintf�֐�
*/
static int printf_mutex;

extern "C" {
void lprintf_init(void)
{
	printf_mutex = mutex_create();
	uart_base[TXCTRL_IDX] = 0x00010001;
	uart_base[RXCTRL_IDX] = 0x00010001;
	uart_base[DIV_IDX] = 17;
	uart_base[IE_IDX] = 0x3;
}
}

int tprintf(const char* fmt, ...)
{
static char		buff[1024];
	va_list arg;
	int len;
	int size;
	int zeroflag,width;

	size = 0;
	len = 0;
	va_start(arg, fmt);

	vtsprintf(buff,fmt,arg);

	va_end(arg);
	debug_print(buff);
	return 0;
}

volatile int lpr_counter = 0;

int lprintf(const char* fmt, ...)
{
static char		buff[1024];
	va_list arg;
	int len;
	int size;
	int zeroflag,width;

	size = 0;
	len = 0;
	va_start(arg, fmt);

	int ret;
	ret = mutex_lock(printf_mutex);
	if ( ret != RT_OK ) {
		for (;;) {
			tprintf("printf lock error:%08X\n", ret);
		}
	}
	if ( 0 < lpr_counter ) {
		for (;;) {
			tprintf("XX:%d:%08X:", 0, lpr_counter);
		}
	}
	lpr_counter++;
	vtsprintf(buff,fmt,arg);

	va_end(arg);
	debug_print(buff);
	lpr_counter--;
	ret = mutex_unlock(printf_mutex);
	if ( ret != RT_OK ) {
		for (;;) {
			tprintf("printf unlock error\n");
		}
	}
	
	return 0;
}

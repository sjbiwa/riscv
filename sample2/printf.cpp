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

#define	UART_BASE	(0x10013000)
//#define	UART_BASE	(0x10010000)
//#define	UART_BASE	(0x10000000)

volatile auto uart_base = (volatile uint32_t*)(UART_BASE);

static void debug_print(const char* str)
{
	while ( *str ) {
		uart_base[0] = *str++;
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
		if(*fmt=='%'){		/* % に関する処理 */
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
			case 'd':		/* 10進数 */
				size = tsprintf_decimal(va_arg(arg,signed long),buff,zeroflag,width);
				break;
			case 'x':		/* 16進数 0-f */
				size = tsprintf_hexadecimal(va_arg(arg,unsigned long),buff,0,zeroflag,width);
				break;
			case 'X':		/* 16進数 0-F */
				size = tsprintf_hexadecimal(va_arg(arg,unsigned long),buff,1,zeroflag,width);
				break;
			case 'c':		/* キャラクター */
				size = tsprintf_char(va_arg(arg,int),buff);
				break;
			case 's':		/* ASCIIZ文字列 */
				size = tsprintf_string(va_arg(arg,char*),buff);
				break;
			default:		/* コントロールコード以外の文字 */
				/* %%(%に対応)はここで対応される */
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

	*buff = '\0';		/* 終端を入れる */

	va_end(arg);
	return (len);
}




/*
  数値 => 10進文字列変換
*/
static int tsprintf_decimal(signed long val,char* buff,int zf,int wd){
	int i;
	char tmp[10];
	char* ptmp = tmp + 10;
	int len = 0;
	int minus = 0;

	if (!val){		/* 指定値が0の場合 */
		*(ptmp--) = '0';
		len++;
	} else {
		/* マイナスの値の場合には2の補数を取る */
		if (val < 0){
			val = ~val;
			val++;
			minus = 1;
		}
		while (val){
			/* バッファアンダーフロー対策 */
			if (len >= 8){
				break;
			}

			*ptmp = (val % 10) + '0';
			val /= 10;
			ptmp--;
			len++;
		}

	}

	/* 符号、桁合わせに関する処理 */
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

	/* 生成文字列のバッファコピー */
	for (i=0;i<len;i++){
		*(buff++) = *(++ptmp);
	}

	return (len);
}

/*
  数値 => 16進文字列変換
*/
static int tsprintf_hexadecimal(unsigned long val,char* buff,
								int capital,int zf,int wd){
	int i;
	char tmp[10];
	char* ptmp = tmp + 10;
	int len = 0;
	char str_a;

	/* A-Fを大文字にするか小文字にするか切り替える */
	if (capital){
		str_a = 'A';
	} else {
		str_a = 'a';
	}

	if (!val){		/* 指定値が0の場合 */
		*(ptmp--) = '0';
		len++;
	} else {
		while (val){
			/* バッファアンダーフロー対策 */
			if (len >= 8){
				break;
			}

			*ptmp = (val % 16);
			if (*ptmp > 9){
				*ptmp += str_a - 10;
			} else {
				*ptmp += '0';
			}

			val >>= 4;		/* 16で割る */
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
  数値 => 1文字キャラクタ変換
*/
static int tsprintf_char(int ch,char* buff){
	*buff = (char)ch;
	return(1);
}

/*
  数値 => ASCIIZ文字列変換
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
  Tiny sprintf関数
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
  Tiny sprintf関数
*/
static int printf_mutex;

extern "C" {
void lprintf_init(void)
{
	printf_mutex = mutex_create();
	uart_base[2] = 0x01;
	uart_base[3] = 0x01;
	uart_base[6] = 17;
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
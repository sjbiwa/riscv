#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(__ASSEMBLER__)
#else

#if defined(_LP64)
typedef	uint64_t CSRREGTYPE;
#else
typedef	uint32_t CSRREGTYPE;
#endif

#define	_CSRRW(reg,value)	({ CSRREGTYPE rvalue; __asm__ volatile ("csrrw  %0," #reg ",%1" :"=r"(rvalue):"r"(value):"memory"); rvalue; })
#define	_CSRRS(reg,value)	({ CSRREGTYPE rvalue; __asm__ volatile ("csrrs  %0," #reg ",%1" :"=r"(rvalue):"r"(value):"memory"); rvalue; })
#define	_CSRRC(reg,value)	({ CSRREGTYPE rvalue; __asm__ volatile ("csrrc  %0," #reg ",%1" :"=r"(rvalue):"r"(value):"memory"); rvalue; })
#define	_CSRRWI(reg,value)	({ CSRREGTYPE rvalue; __asm__ volatile ("csrrwi %0," #reg "," #value :"=r"(rvalue)::"memory"); rvalue; })
#define	_CSRRSI(reg,value)	({ CSRREGTYPE rvalue; __asm__ volatile ("csrrsi %0," #reg "," #value :"=r"(rvalue)::"memory"); rvalue; })
#define	_CSRRCI(reg,value)	({ CSRREGTYPE rvalue; __asm__ volatile ("csrrci %0," #reg "," #value :"=r"(rvalue)::"memory"); rvalue; })


#define	_CSRR(reg)			({ CSRREGTYPE rvalue; __asm__ volatile ("csrr %0," #reg :"=r"(rvalue)::"memory"); rvalue; })
#define	_CSRW(reg,value)	({ __asm__ volatile ("csrw " #reg ",%0" ::"r"(value):"memory"); value; })
#define	_CSRS(reg,value)	({ __asm__ volatile ("csrs " #reg ",%0" ::"r"(value):"memory"); value; })
#define	_CSRC(reg,value)	({ __asm__ volatile ("csrc " #reg ",%0" ::"r"(value):"memory"); value; })
#define	_CSRWI(reg,value)	({ __asm__ volatile ("csrwi " #reg ", " #value :::"memory"); value; })
#define	_CSRSI(reg,value)	({ __asm__ volatile ("csrsi " #reg ", " #value :::"memory"); value; })
#define	_CSRCI(reg,value)	({ __asm__ volatile ("csrci " #reg ", " #value :::"memory"); value; })

#endif

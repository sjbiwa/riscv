#
#
#

MAKEFILE = Makefile
CC = riscv64-unknown-elf-gcc
CXX = riscv64-unknown-elf-g++

CFLAGS += -march=rv64gc -mabi=lp64
#CFLAGS = -march=rv32gc -mabi=ilp32

CFLAGS += -mcmodel=medany

LDSCRIPT = link.ld

C_OBJ = main.o
S_OBJ = startup.o
CXX_OBJ = code.o
all:
	$(CC) $(CFLAGS) $(C_OBJ:.o=.c) $(S_OBJ:.o=.S) $(CXX_OBJ:.o=.cpp) -nostdlib -static -T$(LDSCRIPT) -Wl,-Ttext,0x80000000

.c.o:
	$(CC) $(CFLAGS) $<


#
#
#

CC = riscv-none-embed-gcc
CPP = riscv-none-embed-g++
LD = $(CC)

TARGET = sample.elf

CPP_SRCS = main.cpp
C_SRCS = handler.c
A_SRCS = start.S

.SUFFIXES: .cpp .cxx
 
OBJS = $(A_SRCS:%.S=%.o) $(C_SRCS:%.c=%.o) $(CPP_SRCS:%.cpp=%.o)

LDSCRIPT = ram.lds

$(TARGET): $(OBJS)
	$(LD) -ggdb -mcmodel=medany -mabi=lp64f -march=rv64imf -msmall-data-limit=0 -nostdlib -T $(LDSCRIPT) -Ttext 0x80000000 -o $(TARGET) $(OBJS)

.c.o:
	$(CC) -ggdb -mcmodel=medany -mabi=lp64f -march=rv64imf -msmall-data-limit=0 -c $<

.cpp.o:
	$(CPP) -ggdb -mcmodel=medany -mabi=lp64f -march=rv64imf -msmall-data-limit=0 -c $<

.S.o:
	$(CC) -ggdb -mcmodel=medany -mabi=lp64f -march=rv64imf -msmall-data-limit=0 -c $<

clean:
	rm $(TARGET)
	rm *.o

# medany medlow

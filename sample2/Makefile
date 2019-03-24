#
#
#

CC = riscv64-unknown-elf-g++
LDFLAGS += --specs=nano.specs -lc -lm -lnosys -lstdc++
SRC = *.S *.cpp

all:
	riscv64-unknown-elf-g++ -march=rv64imafdc -mabi=lp64d -g -o sample.elf $(SRC) -mcmodel=medany -nostdlib $(LDFLAGS) -Wl,-T,ld.script

run:
	qemu-system-riscv64 -nographic -machine sifive_u -kernel sample.elf
	
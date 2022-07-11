CHAINPATH=
CHAIN=$(CHAINPATH)arm-none-eabi
CFLAGS=-std=c99 -Wall -mfpu=neon -mhard-float -mcpu=cortex-a8
AFLAGS=-mfpu=neon
IPATH=-Iinc/
SRC=src/
OBJ=obj/
BIN=bin/

all: app

app: start.o timer.o auxiliarFunctions.o main.o
	$(CHAIN)-ld  $(IPATH) $(OBJ)start.o $(OBJ)main.o $(OBJ)auxiliarFunctions.o $(OBJ)timers.o -T $(SRC)memmap.ld -o $(OBJ)main.elf
	$(CHAIN)-objcopy $(OBJ)main.elf $(BIN)spl.boot -O binary
	cp $(BIN)spl.boot /tftpboot/app

start.o: $(SRC)start.s
	$(CHAIN)-as $(AFLAGS) $(SRC)start.s -o $(OBJ)start.o

main.o: $(SRC)main.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)main.c -o $(OBJ)main.o

timer.o: $(SRC)timers.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)timers.c -o $(OBJ)timers.o

auxiliarFunctions.o: $(SRC)auxiliarFunctions.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)auxiliarFunctions.c -o $(OBJ)auxiliarFunctions.o
                                        
copy:
	cp $(BIN)spl.boot /tftpboot/app

clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.elf
	rm -rf $(BIN)*.boot

dump:
	$(CHAIN)-objdump -D $(OBJ)main.elf

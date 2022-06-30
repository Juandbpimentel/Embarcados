CHAINPATH=
CHAIN=$(CHAINPATH)arm-none-eabi
CFLAGS=-std=c99 -Wall -mfpu=neon -mhard-float -mcpu=cortex-a8
AFLAGS=-mfpu=neon
IPATH=-Iinc/
SRC=src/
OBJ=obj/
BIN=bin/

all: app

app: start.o main.o timer.o auxiliarFunctions.o
	$(CHAIN)-ld $(OBJ)start.o $(OBJ)main.o $(OBJ)auxiliarFunctions.o $(OBJ)timer.o -T $(SRC)memmap.ld -o $(OBJ)main.elf
	$(CHAIN)-objcopy $(OBJ)main.elf $(BIN)spl.boot -O binary
	cp $(BIN)spl.boot /tftpboot/appTimer.bin

start.o: $(SRC)start.s
	$(CHAIN)-as $(AFLAGS) $(SRC)start.s -o $(OBJ)start.o

main.o: $(SRC)main.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)main.c -o $(OBJ)main.o

timer.o: $(SRC)timer.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)timer.c -o $(OBJ)timer.o

auxiliarFunctions.o: $(SRC)auxiliarFunctions.c
	$(CHAIN)-gcc $(CFLAGS) $(IPATH) -c $(SRC)auxiliarFunctions.c -o $(OBJ)auxiliarFunctions.o
                                        
copy:
	cp $(BIN)spl.boot /tftpboot/appTimer.bin

clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.elf
	rm -rf $(BIN)*.boot

dump:
	$(CHAIN)-objdump -D $(OBJ)main.elf

all: release

CC= arm-none-eabi-gcc

run:
	file ./bin/app

debug: funcoesD mainD
	$(CC) obj/funcoes.o obj/main.o -lc -lrdimon -o bin/app

release: funcoesR mainR
	$(CC)  obj/funcoes.o obj/main.o -lc -lrdimon -o bin/app

funcoesR: src/funcoes.c
	$(CC) -c src/funcoes.c -o obj/funcoes.o -Iinc

mainR: src/main.c
	$(CC) -c src/main.c -o obj/main.o -Iinc

funcoesD: src/funcoes.c
	$(CC) -c src/funcoes.c -o obj/funcoes.o -Iinc -DDEBUG

mainD: src/main.c
	$(CC) -c src/main.c -o obj/main.o -Iinc -DDEBUG

clear:
	rm -r bin/* obj/*
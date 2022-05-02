run:
	./bin/app.out

debug: funcoesD mainD
	gcc -o bin/app.out obj/funcoes.o obj/main.o

release: funcoesR mainR
	gcc -o bin/app.out obj/funcoes.o obj/main.o

funcoesR: src/funcoes.c
	gcc -c src/funcoes.c -o obj/funcoes.o -Iinc

mainR: src/main.c
	gcc -c src/main.c -o obj/main.o -Iinc

funcoesD: src/funcoes.c
	gcc -c src/funcoes.c -o obj/funcoes.o -Iinc -DDEBUG

mainD: src/main.c
	gcc -c src/main.c -o obj/main.o -Iinc -DDEBUG

clear:
	rm -r bin/* obj/*
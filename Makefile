CC=gcc
MKDIR = mkdir -p

app: mkbuild main.o libfifo.a 
	$(CC)  build/main.o -o app.out -L . archive/libfifo.a

mkbuild:
	$(MKDIR) ./build 
	$(MKDIR) ./archive

libfifo.a: fifo.o
	ar rs archive/libfifo.a build/fifo.o

fifo.o: fifo-lib/fifo.c
	$(CC)  -c -I fifo-lib fifo-lib/fifo.c -o build/fifo.o

main.o:	app/main.c
	$(CC)  -c -I fifo-lib/ app/main.c -o build/main.o

test:
	$(CC) -I test/ -I fifo-lib/ ut/*.c -o ut-fifo.out

clean:
	rm -rf build archive
	rm -f app.out ut-fifo.out

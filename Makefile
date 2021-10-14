CC=gcc
MKDIR = mkdir -p

app: mkbuild main.o libfifo.a 
	$(CC)  build/main.o -o app.out -L . libfifo.a

mkbuild:
	$(MKDIR) ./build 
	$(MKDIR) ./archive

libfifo.a: fifo.o
	ar rs archive/libfifo.a build/fifo.o

fifo.o: fifo-lib/fifo.c
	$(CC)  -c -I fifo-lib fifo-lib/fifo.c -o build/fifo.o

main.o:	app/main.c
	$(CC)  -c -I fifo-lib/ app/main.c -o build/main.o

clean:
	rm -rf build archive
	rm -f app.out

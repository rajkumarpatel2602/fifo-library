CC=gcc
MKDIR = mkdir -p

app: build-dirs main.o libfifo.a 
	$(CC) build/main.o -o app.out -L . archive/libfifo.a

build-dirs:
	$(MKDIR) ./build 
	$(MKDIR) ./archive

libfifo.a: fifo.o
	ar rs archive/libfifo.a build/fifo.o

fifo.o: fifo-lib/fifo.c
	$(CC)  -c -I fifo-lib fifo-lib/fifo.c -o build/fifo.o

main.o:	app/main.c
	$(CC)  -c -I fifo-lib/ app/main.c -o build/main.o

test: clean build-dirs 
	$(CC) -fprofile-arcs -ftest-coverage -I ut/ -I fifo-lib/ ut/*.c fifo-lib/fifo.c -o ut-fifo.out

test-coverage:
	lcov -c -d . -o coverage.info
	lcov -r coverage.info '*/AllTests*' '*/CuTest*' -o coverage-filtered.info
	genhtml -s coverage-filtered.info -o coverage

clean:
	rm -rf build archive
	rm -f app.out ut-fifo.out
	rm -rf coverage*
	rm -rf *.gc* 

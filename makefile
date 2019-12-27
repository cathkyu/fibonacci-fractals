CFLAGS=-Wall -O2 -ansi
fib: main_fib.o fib.o bmp.o timing.o
	$(CXX) -o fib $?
runall:
	./fib 7 10 10 10 100 100 fib7.bmp
	./fib 9 50 50 10 200 200 fib9.bmp
	./fib 25 500 500 2 3000 3000 fib25.bmp
	./fib 26 1000 1000 2 4000 4000 fib26.bmp
clean:
	@rm -rf fib *.o *bmp

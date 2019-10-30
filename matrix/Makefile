CC=gcc
DEBUG=-g

defaut: matrix.o linear_regression.o
	$(CC) $(DEBUG) -o linear_regression matrix.o linear_regression.o

%.o: %.c matrix.h
	$(CC) $< -c

clean:
	rm -f *.o linear_regression
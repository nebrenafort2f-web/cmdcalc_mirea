CC = cc
CFLAGS = -std=c11

cmdcalc: main.o calc.o
	$(CC) $(CFLAGS) -o cmdcalc main.o calc.o

main.o: main.c calc.h
	$(CC) $(CFLAGS) -c main.c -o main.o

calc.o: calc.c calc.h
	$(CC) $(CFLAGS) -c calc.c -o calc.o

clean:
	rm -f main.o calc.o cmdcalc

.PHONY: clean

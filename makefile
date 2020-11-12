all: *.c
	gcc -O1 -Wall -o main main.c -lpthread
zip: *.c makefile README.md
	zip lab4 main.c makefile README.md

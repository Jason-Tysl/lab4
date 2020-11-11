all: *.c
	gcc main.c -o main -pedantic
zip: *.c makefile README.md
	zip lab4 main.c makefile README.md

CC = gcc
CFLAGS = -g -ansi -pedantic -Wall -std=c99

all: StudentRegSystem

Student.o: Student.c Student.h
	$(CC) $(CFLAGS) -c Student.c

Course.o: Course.c Course.h
	$(CC) $(CFLAGS) -c Course.c

Register.o: Register.c Register.h
	$(CC) $(CFLAGS) -c Register.c

StudRegSystem.o: StudRegSystem.c Student.h Course.h Register.h
	$(CC) $(CFLAGS) -c StudRegSystem.c

StudentRegSystem: Student.o Course.o Register.o StudRegSystem.o 
	$(CC) $(CFLAGS) -o StudentRegSystem Student.o Course.o Register.o StudRegSystem.o

clean:
	rm -f *.o StudentRegSystem

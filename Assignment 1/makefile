# Makefile - Mert Ertugrul 
CC=g++
CFLAGS=-c -Wall
target: first
first: main.o Reservation.o Flight.o ReservationSystem.o
	$(CC) main.o Reservation.o Flight.o ReservationSystem.o -o hw1
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
Reservation.o: Reservation.cpp
	$(CC) $(CFLAGS) Reservation.cpp
Flight.o: Flight.cpp
	$(CC) $(CFLAGS) Flight.cpp
ReservationSystem.o: ReservationSystem.cpp
	$(CC) $(CFLAGS) ReservationSystem.cpp
clean:
	rm *o hw1
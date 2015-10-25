#Comms
CC=g++ -Wall -Wextra
#CFLAGS = -L/usr/local/lib
GMP=-lgmp -lgmpxx
FILES = ./Source.o ./menu.o ./stack.o

result: source  $(FILES)
	$(CC) $(FILES) $(GMP) -o result_unix

source: Source.cpp headers.h menu stack 
	$(CC) ./Source.cpp -c

menu: menu.h menu.cpp
	$(CC) ./menu.cpp -c
	
stack: stack.cpp stack.h headers.h
	$(CC) $(GMP) ./stack.cpp -c
	
clean:
	rm -rf $(FILES)


#project: Source.c  primes.txt
#	$(CC) Full_project.c -o result -lgmp 


#make_primes: make_primes.exe compile 
#	./make_primes.exe
	
#compile: make_primes.c
#	$(CC) make_primes.c -o make_primes

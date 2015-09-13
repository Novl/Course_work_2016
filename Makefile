#Comms
CC=g++
#CFLAGS = -L/usr/local/lib
GMP=-lgmp -lgmpxx
FILES = Source.o menu.o

result: source  $(FILES)
	$(CC) $(FILES) $(GMP) -o result_unix

source: Source.cpp menu
	$(CC) Source.cpp -c

menu: menu.h menu.cpp clean
	$(CC) menu.cpp -c

clean:
	rm -rf $(FILES)


#project: Source.c  primes.txt
#	$(CC) Full_project.c -o result -lgmp 


#make_primes: make_primes.exe compile 
#	./make_primes.exe
	
#compile: make_primes.c
#	$(CC) make_primes.c -o make_primes

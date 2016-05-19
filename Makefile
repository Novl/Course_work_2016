#Comms
CC=g++ -Wall -Wextra
FLAGS=-lgmp -lgmpxx -std=c99
BuildFILES = $(BuildDir)/Source $(BuildDir)/menu $(BuildDir)/stack $(BuildDir)/gen_prime $(BuildDir)/ord $(BuildDir)/KP
SrcDir = ./src
IncludeDir = ./include
BuildDir = ./build
Algos = $(SrcDir)/gen_prime.cpp $(SrcDir)/ord.cpp $(SrcDir)/KP.cpp

result: dir source menu stack algos $(BuildFILES)
	$(CC) $(BuildFILES) $(FLAGS) -o result_win

source: $(SrcDir)/Source.cpp
	$(CC) $(SrcDir)/Source.cpp -c -o $(BuildDir)/Source

menu: $(SrcDir)/menu.cpp $(IncludeDir)/menu.h $(IncludeDir)/headers.h
	$(CC) $(SrcDir)/menu.cpp -c -o $(BuildDir)/menu

stack: $(SrcDir)/stack.cpp $(IncludeDir)/stack.h
	$(CC) $(SrcDir)/stack.cpp -c -o $(BuildDir)/stack

algos: $(Algos)
	$(CC) $(SrcDir)/gen_prime.cpp -c -o $(BuildDir)/gen_prime
	$(CC) $(SrcDir)/ord.cpp -c -o $(BuildDir)/ord
	$(CC) $(SrcDir)/KP.cpp -c -o $(BuildDir)/KP

dir:
	@if [ ! -d $(BuildDir) ] ; then echo "MKDIR" ; mkdir $(BuildDir); fi
#	$(if [! -d $(BuildDir)], mkdir $(BuildDir), )
#	-mkdir $(BuildDir)
	
clean:
	rm -rf $(BuildFILES)
    
start: result_win
	result_win
all :   bin rshell 

bin: 
	mkdir -p bin 

rshell:
	g++ -Wall -Werror -ansi -pedantic src/rshell.cpp -o ./bin/rshell

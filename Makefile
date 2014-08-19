all : rshell rshell1 #rshell 1.cpp is for hw1 regrade
rshell:
	g++ -Wall -Werror -ansi -pedantic src/rshell.cpp -o ./bin/rshell
rshell1: 
	g++ -Wall -Werror -ansi -pedantic src/rshell1.cpp -o ./bin/rshell1

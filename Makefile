all : rshell	rshell1 #ls
rshell:
	g++ -Wall -Werror -ansi -pedantic src/rshell.cpp -o ./bin/rshell
rshell1:
	g++ -Wall -Werror -ansi -pedantic src/rshell1.cpp -o ./bin/rshell1



#ls:
#//	g++ -Wall -Werror -ansi -pedantic src/ls.cpp -o ./bin/ls


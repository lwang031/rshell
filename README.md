rshell
======
This is a program that execute the function of shell command. It uses getlin to take command. Then parse the command into to char** argv2. At last, execvp function helps to achieve the function as shell command. 

There are severl bugs in the programm:

1. The username and hostname are set up contain only 256 spaces, the content cannot exceed this; otherwise, it cannot show the information of a user.
2. The strtok function makes the parsed command ignore the "/" and treat it as a space so "-/l" will no work as "-l".
3. The program also cannot parse the command like "-l-a" it will treat then as only one part not "-l", "-a".
4. When parsing command "#", it will ignore all the stuff beyond it,but the "#" cannot stay near any command such as "#-l" or "-l#" these two command will not work. It can only work with "ls # -l".

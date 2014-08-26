rshell
======
This is a program that execute the function of shell command. It uses getlin to take command. Then parse the command into to char** argv2. At last, execvp function helps to achieve the function as shell command. 

#There are severl bugs in the programm:

* 1. The username and hostname are set up contain only 256 spaces, the content cannot exceed this; otherwise, it cannot show the information of a user.

*2. The getlogin_r does work in local computer, but doesn't work after start scripting

* 3. The strtok function cannot handle first argument perfectly, `bin/rshell` and `./a.out` will work since the path is work because they are in the same directry as the program. But it doesn't work if a wrong command was input such as `./b.out`, it will return instead of finding other paths.
* 4. The program also cannot parse the command like "-l-a" it will treat then as only one part not "-l", "-a".
* 5. When parsing command "#", it will ignore all the stuff beyond it,but the "#" cannot stay near any command such as "#-l" or "-l#" these two command will not work. It can only work with "ls # -l".
* 6. The `&` is not perfect, it can be taken from the middle of command, and ignore the rest behind. So a user has to put the `&` in the end of command, or it won't work as expect.
* 7. For signal `^C`, in the initial state, if a user type in `^C`, it does nothing but print out the `^C' in the same line, untill a command was type in.
* 8. For signal `^Z`, program will be stopped untill typing in `fg` or `bg`. If the command runs an app such as `gedit`, both `fg` and `bg` will work correctly, but if run command `cat`, `bg` won't work; however, `^Z` and `fg` still work.

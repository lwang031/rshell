#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
using namespace std;


  
int status;   
pid_t pid2;

void sig_handler (int signum){
   if (signal (SIGINT, SIG_IGN) == SIG_ERR) { perror("cannot SIG_IGN: ");}
 
    
}
void sig_stop(int signum){
   if ( kill (pid2, SIGSTOP) == -1 ){ perror("cannot SIGSTOP: ");}
    
}
void run_fg(){

    if (kill(pid2, SIGCONT) == -1){ perror ("cannot fg: ");}
}
void run_bg(){

    if (kill(pid2,SIGCONT) == -1 ){ perror ("cannot bg: ");}
}

int b = 0;

int main()
{
    while(1)
    {
start:
        b = 0;
        char usr[256]={0};
        char host[256] ={0};

        if (getlogin_r(usr,sizeof(usr)-1) != 0){perror("cannot getlogin: ");}
        if (gethostname(host,sizeof(host)-1) == -1){perror ("cannot gethostname: ");}
        cout<<usr<<"@"<<host<<"$ ";
        if (signal(SIGINT, sig_handler) == SIG_ERR){perror("cannot SIGINT: ");}
        if (signal(SIGTSTP, sig_stop) == SIG_ERR) { perror("cannot SIGTSTP: ");}
        string str;                  //start take cmd from user
        std::getline(std::cin, str);
        if (str.empty()) goto start;
        vector < char*> pathb;       //build the vector of path
        char *pa;                 //the path for strtok
        int i = 0;
        int j =0;
        int h = 0;
        if (getenv("PATH") == NULL){ perror("getenv: ");}
        
        string a = getenv("PATH");
        char *patha = new char [a.length()*sizeof(void*)];
        strcpy (patha, a.c_str() );//<<endl;
        pa = strtok (patha,":");
        while (pa != NULL){
            pathb.push_back(pa);
            pa = strtok(NULL, ":");
        }
        char* cmd = (char*)malloc(str.length()*sizeof(void*));
            //whole command line input by user
        strcpy (cmd,str.c_str());
//"-------------pre-parse-------------------------------"<<endl;        
         char * pch; //represent each part of cmd
         pch = strtok (cmd," ");
         char** argv2;//arguments or "&"
         i = 0;  //track the number of arguments
         while (pch != NULL){
            if (strcmp(pch, "exit")==0){
                exit(0);
            }
            if (h == 1){
                if (chdir(pch) == -1){
                    perror("cannot cd: ");
                }
                h = 0;
                goto start;
                
            }
            if (strcmp(pch, "cd") == 0){
                h = 1;
            }
            if(strcmp(pch, "#") == 0) break;
            
            if (strcmp(pch,"&") ==0){
                i--;
                b = 1;
            }
            pch = strtok(NULL," ");
            i++;
        }
        if (h == 1){
            if (getenv("HOME") == NULL){ perror("getenv: ");}

            string home = getenv("HOME");
            if (chdir(home.c_str()) == -1){
                perror("cannot cd: ");
            }
            goto start;
        }
        
//"--------------------parse-------------------------"<<endl;
        strcpy(cmd, str.c_str()); 
        argv2 = (char**)malloc(((i)*sizeof(void*))+1 ); 
        pch = strtok (cmd," ");
        j =0;
        while (pch != NULL){
            if(strcmp(pch, "#") == 0){
                break;
            }
            if(strcmp(pch,"&")!=0){
                if (b == 0 && strchr(pch, '&') != NULL){ 
                   int kyg = strlen(pch) - (strchr(pch, '&') - pch + 1);
                    if (kyg == 0){ 
                        // the staus of -----& can only be at the end, ignore the rest behind

                        b = 1;
                        char *pch_amp = new char[strlen(pch)-1];
                        strncpy(pch_amp, pch, strlen(pch)-1);
                        argv2[j] = new char[strlen(pch)-1];
                        strcpy(argv2[j], pch_amp);
                        j++;
                        break;
                    }    
                }
                argv2[j] = new char[strlen(pch)];
                strcpy(argv2[j], pch);
                
                pch = strtok(NULL, " ");
                j++;
            }
            else break;//"&" has to be put at last
         }   
        argv2[j] = 0;
        int run_program = 0;
        if (strchr(argv2[0], '/') != NULL){
            if( argv2[0][0] == '.' &&  argv2[0][1] == '/'){
                run_program = 1;
                char* new_argv0 = argv2[0] + 2;
                strcpy(argv2[0], new_argv0);
            }
            if (strcmp (argv2[0], "bin/rshell") == 0){
                run_program = 1;
cout<<"run bin/rshell"<<endl;
            }
            if (argv2[0][0] == '/'){
                run_program = 2;
            }
        }
        if(strcmp (argv2[0], "fg") == 0){
                run_fg();

                goto fg_stop;
        }
        if (strcmp (argv2[0], "bg") == 0){
                run_bg();
                b = 1;

                goto fg_stop;
                
        }
//"-----------------------execute-------------------------"<<endl;

        char cwd[1024];
        pid_t pid;
        pid = fork();
        pid2 = pid;
 cout<<"child pid: "<<getpid()<<endl;       
        if ( pid < 0){
            perror("fork failed: ");
        }

      
        else if (pid == 0){  //child process
            
            char *c;
            if (run_program == 1){
                char *pathc = getcwd(cwd, sizeof(cwd));
                c= new char[strlen(pathc)];
                strcpy(c, pathc);
                strcat(c,"/");
                strcat(c, argv2[0]);
                if (execv(c, (char *const*)argv2) == -1){perror("execv: ");}
            }    
            if (run_program == 2){
                if (execv(argv2[0], argv2) == -1){perror("execv: ");}
            }
            for(unsigned int k = 0; k < pathb.size(); k++){
                c = new char[strlen(pathb.at(k))];
                strcpy (c, pathb.at(k));
                strcat(c, "/");
                strcat(c, argv2[0]);
cout<<"present the location of finding command(or not): "<<k<<"  "<<c<<endl;
                execv(c, (char *const*)argv2);//will check error later                           

                
            }
            if (execv(c, (char *const*)argv2) == -1){
                
                cerr<<"execv: No such file or directory"<<endl;
                
                if (b== 1) {
                    cout<<usr<<"@"<<host<<"$ ";
                }
                return 1;
            }

           
                         
            
        }
        else {

fg_stop:
            if(b == 0){
                if (waitpid(pid, &status, WUNTRACED) != pid){
                    perror("wait ");
                }
            }

        }
    }
}
    

   

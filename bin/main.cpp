#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

#define lt 1;
#define gt 2;
#define dgt 4;
#define tlt 8;

int main()
{
    
    while(1)
    {

        char usr[256]={0};
        char host[256] ={0};
        getlogin_r(usr,(sizeof(usr)-1));
        gethostname(host,(sizeof(host)-1));
        cout<<usr<<"@"<<host<<"$ ";

         string str;
         std::getline(std::cin, str);
         char* cmd = (char*)malloc(str.length()*sizeof(void*));
            //whole command line input by user

         strcpy (cmd,str.c_str());
         int a = 0;
         int flag = 0;
cout<<"----------------------red-parse--------------------------------"<<endl;
        

cout<<"-------------pre-parse-------------------------------"<<endl;        
         char * pch; //represent each part of cmd
         pch = strtok (cmd," /");

         char** argv2;//arguments or "&"
         int i = 0;  //track the number of arguments
         while (pch != NULL){
            if (strcmp(pch, "exit")==0){
                exit(0);
            }
            //if (strcmp (pch, '<'
            if(strcmp(pch, "#") == 0) break;
            if (strcmp(pch,"&") ==0){
                i--;
                a = 1;
            }
            pch = strtok(NULL," /");
            i++;
        }
cout<<"--------------------parse-------------------------"<<endl;
        strcpy(cmd, str.c_str()); 
        argv2 = (char**)malloc(((i)*sizeof(void*))+1 ); 
        pch = strtok (cmd," /");
        char* cm =pch;//the command
        int j =0;
        while (pch != NULL){
            if(strcmp(pch, "#") == 0){
                break;
            }
            if(strcmp(pch,"&")!=0){
                argv2[j] = new char[strlen(pch)];
                strcpy(argv2[j], pch);
                
                pch = strtok(NULL, " /");
                j++;
            }
            else break;//"&" has to be put at last
         }   

        argv2[j] = 0;
cout<<"-----------------------execute-------------------------"<<endl;
        pid_t pid;
        int status;
        if((pid = fork())<0){    //fork failed
            perror("fork failed: ");
            exit(1);
        }
        else if (pid == 0){  //child process
            if( execvp(cm,(char *const*)argv2) < 0){
                perror("execute failed: ");
                free (argv2);
                exit(1);
            }
             
            
        }
        else {
            if(a == 0){
              while (wait(&status) != pid);
            }
           //     waitpid(getpid(), &status ,0);
            
           
        }
    }
}

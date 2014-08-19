#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
using namespace std;



#define NOFLAG 0
#define l 1
#define L 1
#define r 2
#define R 2
#define a 4
#define A 4

int main(int argc ,char** argv)
{

    
cout<<"------------------------readdir--------stat-----------------"<<endl;

    char *dirName = ".";
    DIR *dirp;
    
    
    if (!(dirp  = opendir(dirName)))
    {
        cerr << "Error(" << errno << ") opening " << dirName << endl;
        
        return errno;
    }
    struct dirent *direntp;
    struct stat buf;
    while ((direntp = readdir(dirp))!=NULL)
    {
        

        cout << direntp->d_name<<"  ";
        if((stat(direntp->d_name,&buf))==-1){
            cerr<<"Error("<<errno<<")opening "<<dirName<<endl;
            return errno;
        }
        cout<<buf.st_mode<<"    "<<buf.st_size<<"   "<<buf.st_atime<<endl;
        // use stat here to find attributes of file
    }
    closedir(dirp);
cout<<"--------------------bitwise------------------------------"<<endl;
    
    unsigned int flags = NOFLAG | a | L;
    cout<<"l: "<<l<<endl;
    cout<<"flags: "<<flags<<endl;
    cout<<"flags & l: "<<(flags&l)<<endl;
    
    if (flags & l){
        cout<< "flag -l was passed";
        cout<<endl;
    }
    if (flags & R){
        cout<< "flag -R was passed";
        cout<<endl;
    }
    if (flags & a){
        cout<< "flag -a was passed";
        cout<<endl;
    }
    else {cout<<"no flag was passed"<<endl;}



}
/*
int main (int argc, char**argv){
   

    unsigned int x = NOFLAG | l | R;
    unsigned int y = NOFLAG | R | a;
    cout<<"x: "<<x<<endl;
    cout<<"y: "<<y<<endl;
    cout<<(x&y)<<endl;
    cout<<(x|y)<<endl;
    cout<<(x^y)<<endl;
    cout<<(-y)<<endl;
    return 0;
}

*/

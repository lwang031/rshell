#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
using namespace std;


void runparse(vector<vector<string> > &);


int main(){
    int i, j, k;
    while(1){
        vector < vector <string> > parse;
        runparse(parse);
        for (i = 0; i < parse.size(); i++){
            for (j = 0; j < parse[i].size(); j++){
                cout<<"parse: "<< parse[i][j]<<" ";
        }
        cout<<endl;
                
    }
        cout<<"go to main: "<<endl;

        if (! parse.empty()){
    cout<<"------------------runcmd----------------------------"<<endl;
        //flag1 --- input redir, flag2 ---output redir
            int tpipe[2];
            int i = 0;  //parse[i]
            int fd, newfd;
            int flag1, flag2, back;
            int order = 1;
            char *infile;
            char *outfile;
            char **argv;
            
            pid_t pid;
            vector <pid_t> pidvec;
            if (parse.size() == 1) order = 0;
            else if (i == 0) order = 1;
            else if (i == parse.size()-1) order = 2;
            else { order = 3; }
cerr<< "---------------in run com---------------------------------"<<argv[1]<<endl;
            
            
            i = 0;
            while (i< parse.size()) {
               
////////////////////////////////////////////////////////////////////


cout<<"---------------------------parse vector--------------------  "<<endl;
                int h = 0;
                k = 0;
                j = 0;
                int q = 0;
                flag1 = 0;
                flag2 = 0;
                back = 0;
                infile = "";
                outfile = "";
           

                for (int h = 0; h < parse[i].size(); h++){ 

                    cout<<"order is: "<<order<<" parse[i].size: "
                        <<parse[i].size()<<" "<<parse[i][h]<<endl;

                //no two same symbol exist in one argument
                if (parse[i][h] == "<"){
                    if ( (order == 2) || (order == 3)){
                        cerr<<"< cannot be here!!\n";
                        exit(1);
                    }
                    flag1 == 11;
                    if (k != 0){
                        cerr<<"cannot put two redi symbol in one argument!!\n";
                        exit(1);
                    }
                    k = h;
                }
                
                
                
                
                
                if (parse[i][h] == ">"){
                    if ( (order == 1) || (order == 3)){
                        cerr<<"> cannot be here!!\n";
                        exit(1);
                    }

                    flag2 = 21;
                    if (j != 0){
                        cerr<<"cannot put two redi symbol in one argument!!\n";
                        exit(1);
                    }

                    j = h;
                }




                if (parse[i][h] == ">>"){
                    if ( (order == 1) || (order == 3)){
                        cerr<<">> cannot be here!!\n";
                        exit(1);
                    }
                    flag2 = 22;
                    if (j != 0){
                        cerr<<"cannot put two redi symbol in one argument!!\n";
                        exit(1);
                    }
                    j = h;
                }
            
            }




            if (parse[i].back() == " "){
                parse[i].pop_back();
            } 
               
            
            // handle " "in the end
            if (parse[i].back() == "&"){     //handle &&&&
                back = 1;
                parse[i].pop_back();
            }


           // cout<<"eee"<<endl;




            else if ( *(parse[i].back().end()) == '&'){
                back = 1;
                string astr = parse[i].back();
                astr.assign(astr.begin(), astr.end()-1);
                parse[i].back().assign(astr.begin(), astr.end());
            }






            if ((k == 0 ) && (j == 0) ){ //no < >
                //argv = (char**)malloc(((parse.size())*sizeof(void*))+1 );
                argv = new char* [parse[i].size()];
                
                for (int h = 0; h < parse[i].size(); h++){
                    argv[h] = new char [parse[i][h].size()];
                    
                    strcpy(argv[h], (parse[i][h]).c_str());
cout<<"------in parse vec_-----------------argv[h]: "<<argv[h]<<endl;
                }
            }




            if ( (k != 0) && (j != 0) ){// both < >
                
                
                
                if ( k < j) q = k;

                else { q = j;}
               
                    argv = new char* [q];
                    
                    for (int h = 0; h< q; h++){
                        
                        argv[h] = new char [parse[i][h].size()];
                    
                        strcpy(argv[h], (parse[i][h]).c_str());

                    }
                    infile = new char [parse[i][k+1].size()];
                    strcpy (infile, parse[i][k+1].c_str());
                    outfile = new char [parse[i][j+1].size()];
                    strcpy (outfile, parse[i][j+1].c_str());
            }

            else // one < or >
            {
                if (order == 1){ 
                    q = k;
                    infile = new char [parse[i][q+1].size()];
                    strcpy (infile, parse[i][q+1].c_str());
                }
                else if (order == 2)
                {
                    q = j;
                    outfile = new char [parse[i][q+1].size()];
                    strcpy (outfile, parse[i][q+1].c_str());
                }
                argv = new char* [q];
                for (int h = 0; h< q; h++){
                        
                    argv[h] = new char [parse[i][h].size()];
                    
                    strcpy(argv[h], (parse[i][h]).c_str());

                }
            }








 ///////////////////////////////////////////////////////////////////////////               

                if ((pid = fork()) == -1 ){
                    perror("cannot fork: ");
                    exit (1);
                }
                cout<<"pid: "<<pid<<endl;
                if (pid == 0){             
cout<<"----------------child----------"<<"i:  "<<i<<endl;

                    if (i != 0){// not first
        cout<<"not first"<<endl;
                        //close (tpipe[1]);
                        if (dup2(tpipe[0], 0) == -1 ){
                            perror("cannot pipe read: ");
                        }
                        //close (tpipe[0]);
                    }
                
                    if (i != (parse.size()-1)){ //not last
cout<<"not last"<<endl;
                        //clsoe (tpipe[0]);
                        if (pipe (tpipe) == -1 )
                        { 
                            perror ("cannot make pipe: ");
                        }

                        if (dup2(tpipe[1], 1) == -1 ){
                            perror("cannot pipe write: ");
                        }
                        //close (tpipe[1]);
                    }
                        
                    if (i == 0 && flag1 == 11) {              //handle I redi
    cout<<"first"<<endl;
                        if (( fd = open ( infile, O_RDONLY)) == -1){
                            perror("cannot Input redirect: ");
                        }
                        newfd = dup2 (fd, 0);
                        if (newfd == -1){
                            perror ("cannot Input2 redirect: ");
                        }
                        close (fd);
                    }
                    if (i == (parse.size()-1) && ( flag2 == 21 || flag2 ==22 )){
         cout<<"last"<<endl;               
                        //handl O redi
                        close(1);
                        if (flag2 == 21) { 
                            if (( fd = open ( outfile, O_RDWR 
                                            | O_CREAT, 0644)) == -1)                                          
                            {
                                perror ("cannot Output redirect: ");
                            }
                            if(( newfd = dup2(fd, 0)) == -1){
                                perror("cannot Output2 redirect: ");
                            }
                        
                        }
                        if (flag2 == 22) { 
                            if ((fd = open ( outfile, O_RDWR | O_CREAT 
                                | O_APPEND, 0644 )) == -1){
                                perror ("cannot Output redirect: ");
                            }
                            if(( newfd = dup2(fd, 0)) == -1){
                                perror("cannot Output2 redirect: ");
                            }

                        }

                    }
cout<<"go to execute: "<<argv[0]<<endl;
                    execvp(argv[0],argv) == -1;
                        perror("execute failed: ");
                        exit(1);
                    

                
                }            
                else {
    cout<<"------------------parent--------------------------"<<endl;
                    pidvec.push_back(pid);
                }

                    i++;// increment parse vector
            }



           
            for ( j = 0; j < pidvec.size(); j++){
cout<<"-------------------------wait -----------------------"<<endl;
                    waitpid( pidvec[j], NULL , 0 );
            }
         
            
            cout<<"--------------------free ------------------------"<<endl;
           // free(argv);    

            
        }
     
    
    
    
    
    }
    return 0;
}

    

    
void runparse(vector<vector<string> > &parse2 ){
cout<<"------------------run parse ------------------------"<<endl;
    char usr[256]={0}; //get user info
    char host[256] ={0};
    getlogin_r(usr,(sizeof(usr)-1));
    gethostname(host,(sizeof(host)-1));
    cout<<usr<<"@"<<host<<"$ ";
    string str;    //get input from user
    int l = 0;//three symbols for "< > |"
    int r = 0;
    int rr = 0;
    int p = 0;
    vector <string> parse;
    getline (cin, str);
    
    if (str == "exit") exit(0);   //end the program;
    if (str.at(0) == '#') {           //check # status
        parse2.clear();
        return;
    }
    for (int n = 1; n < str.size(); n++){
        
        if((str[n-1] == ' ') && (str[n] == '#')){
            str.assign(str.begin(), str.begin()+n-1);
        }
        

    }
    int i = 0;// i track the number of subs
    istringstream iss (str);

    while(1){
        string sub;
        iss >> sub;
        if (iss == 0) break;
        for(int j = 0; j < sub.size(); j++){

            stringstream ss;
            l = 0;
            r = 0;
            p = 0;
            rr = 0;
            if( ( sub[j] == '<') || ( sub[j] == '>') ||( sub[j] == '|') ){
                
                
                if((j == 0) &&( sub[j] == '|')){// symbol in the beginning

                    ++p;
                    string sub1; 
                    if ( rr > 0){
                        sub1 = ">>";
                    }
                    else{
                        ss << (sub[j]);
                        ss >> sub1;
                    }
                    parse.push_back(sub1);
                    i++;
                    sub.assign(sub.begin()+j+1, sub.end());
                    j = -1;                    
                    cout<<"first: "<<sub1<<" "<<j<<" "
                        <<sub<<r<<l<<p<<rr<<endl;
                
                }


                else if ((j == (sub.size()-1)) &&( sub[j] = '|'))  
                       
                {
                    ++p;

                    string sub1;
                    ss << (sub[j]);
                    ss >> sub1;
                    
                    sub.assign (sub.begin(), sub.end()-1);
                    parse.push_back(sub);
                    i++;
                    parse.push_back(sub1);
                    i++;
                    cout<<"end: "<<sub<<" "<<j<<" "<<sub1
                        <<" "<<l<<r<<p<<rr<<endl;
                
                }

            
                else if ( (j != 0) &&(j < (sub.size()-1))){
                    cout<<"mdidsfs: "<<rr<<" "<<j<<endl;  
                    //include >> in the end

                    string sub1;
                    sub1.assign (sub.begin(), sub.begin()+j);
                    if ( sub[j] == '<' ) ++l;
                    else if (sub[j] == '>' ){
                        if (sub[j+1] == '>'){
                            ++rr;
                            ++j;
                            cout<<">>: "<<rr<<" "<<j<<endl;
                        }                         
                        else {++r;}
                    }

                    else { ++p;};


                    string sub2;

                    if ( rr > 0){
                        sub2 = ">>";
                    }
                    else {
                        ss << (sub[j]);
                        ss >> sub2;
                    }
                    sub.assign(sub.begin()+(j+1), sub.end());
                    parse.push_back(sub1);
                    parse.push_back(sub2);
                    i++;
                    i++;
                    j = -1;
                    cout<<"middle: "<<sub1<<" "<<sub2<<" "<<sub
                        <<" "<<j<<" "<<r<<l<<p<<rr<<endl;
                }

            }    
            
            
        }
    
        if ( l== 0 && r== 0 && p == 0 & rr == 0){
            cout<<"no symbol occr: "<<sub<<endl;
            parse.push_back(sub); 

            i++; 
        }
       
        
        
    }
    cout<<"i: "<<i<<"   rlp: "<<r<<l<<p<<rr<<endl;
    
    int j = 0;
    int k = 0;
    int m = 0;
    int z = 0;

    vector <string> sub3;
    for ( i = 0; i < parse.size(); i++){
        if (parse[i] != "|"){
            sub3.push_back(parse[i]);       
            cout<<"sub3 parse: "<<parse[i]<<endl;

        }
        if (parse[i] == "|"){
            j++;
            m = i;
            parse2.push_back(sub3);
            z = 1;
            
            sub3.clear();

        }
    }
    vector<string>::iterator it;

    if (z == 0) { it = parse.begin() +m;}  
    if (z == 1)  { it = parse.begin()+ m + 1;}
    sub3.assign(it, parse.end());
    parse2.push_back(sub3);



    
    return;
}




   




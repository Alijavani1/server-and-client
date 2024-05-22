
#include <iostream>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <vector>

#define PORT 65432   
#define FORMAT "UTF-8" 
using namespace std;
vector<int>list;
 bool flag=true;
void handle_client(int client_socket) {

    std::cout << "[NEW CONNECTION] Client connected" << endl;
    cout<<"Enter the word back to disconnect"<<endl;
     while(true){
   char buffer[1024] = {0};
   char download[1024] = {0};
   char dataread[150]={0};
   string message="";
   string message2="";
   cout << "Enter message: ";
   getline(std::cin, message);
   if(message=="back"){
    break;
   }
   send(client_socket, message.c_str(), message.size(), 0);
    if(message[0]=='d'&&message[1]=='o'&& message[2]=='w'&&message[3]=='n'){
        char komaki[50] = {0};
        komaki[0]='c';komaki[1]='l';komaki[2]='i';komaki[3]='e';komaki[4]='n';
        komaki[5]='t';komaki[6]=' ';
        message2=message;
        int pos=message2.find(" ");
        string temp1=message2.substr(pos+1);
        for(int i=0;i<temp1.size();i++){
           komaki[i+7]=temp1[i];
       }
            recv(client_socket, download, 1024, 0);
            string text=download;
            if(text=="No such file exists"){
               printf("%s\n","No such file exists");
               memset(download,0, strlen(download));
                break;
            }
            else if(download!="") {
            FILE *temp;
            temp=fopen(komaki,"w");
            fputs(download,temp);
            printf("%s\n",download);
            cout<<"The download is Done"<<endl;
            memset(download,0, strlen(download));
            break;
            }
    }
   if(message[0]=='u'&&message[1]=='p'&& message[2]=='l'&&message[3]=='o'){
         char komaki[50] = {0};
         int pos;
         pos=message.find(" ");
         string temp=message.substr(pos+1);
         for(int i=0;i<temp.size();i++){
          komaki[i]=temp[i];
         }
         char x [10];
         recv(client_socket, x, 1024, 0);
         FILE *te;
         te=fopen(komaki,"r");
         if(te==NULL){
            message2="No such file exists";
            send(client_socket, message2.c_str(),message2.size(), 0);
            printf("%s\n","No such file exists");
            break;
         }
         while(fgets(dataread,150,te)!=NULL){
          message2+=dataread;
         }
         if(message2!=""){
          send(client_socket, message2.c_str(),message2.size(), 0);
          printf("%s\n","the Upload Done");
         }
          message2="";
          fflush(stdin);
          break;
    }
    // Receiving response from the server
    cout << "Received: ";
    recv(client_socket, buffer, 1024, 0);
    cout<< buffer << endl;
    fflush(stdin);
     memset(buffer,0, strlen(buffer));
     }
    close(client_socket);
    flag=true;
}
void list_connect(int server_socket){
 sockaddr_in client_addr;
          socklen_t client_len = sizeof(client_addr);
  while(1){
     list.push_back(accept(server_socket, (struct sockaddr *)&client_addr, &client_len)); 
       if(flag){
    for(int i=0;i<list.size();i++){
      if(list[i]!=-100)
        printf("%d-clien\n",i);
    }
       }

  }
           
}
int main() {
  avale:
    cout<<"1-Helpe\n2-login to the program"<<endl;
  int vorodi;
  cin>>vorodi;
  switch (vorodi)
  {
  case 1:
  cout<<"download name file\nupload name file"<<endl;
  goto avale;
    break;
  case 2:
  int client;
  int in_put;
    // Creating server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Socket creation error" << std::endl;
        return 1;
    }

    // Setting up server address
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Binding socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Binding error" << std::endl;
        return 1;
    }

    // Listening for connections
    if (listen(server_socket, 5) == -1) {
        std::cerr << "Listening error" << std::endl;
        return 1;
    }

    // Server started
    
   std::cout << "[STARTING] Server is starting..." << endl;
   std::cout << "[LISTENING] Server is listening on port " << PORT << endl;
    cout<<"1-connect client"<<endl<<"2-exsit"<<endl;
         scanf("%d",&in_put);
         if(in_put==1){
    thread(list_connect,server_socket).detach(); 
   
    while (true) {
       if(flag){
        cout<<"Exit thr program by entering -1"<<endl;
          cout<<"select the desired client"<<endl;
      scanf("%d",&client);
      if(client==-1)
      break;
      printf("%s\n","be khater moshkel scanf ye chise alki vard konid:");
      scanf("\n");
    thread(handle_client,list[client]).detach();   
    list[client]=-100;
      flag=false;
      }   
    }
         }

    close(server_socket);
  break;
  }
  return 0;
}

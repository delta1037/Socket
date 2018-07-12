#include <winsock2.h>
#include <windows.h>
#include <libintl.h>
#include <pthread.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include "log.h"
#include <thread>

#define BUFSIZE 1024
#define SERVERIP "127.0.0.1"
#define CLI_MAX_NUM 10


#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"x86/pthreadVC2.lib")

using namespace std;

int status=0;
int thread_count=0;

SOCKET cliSock;
SOCKET serSock;
SOCKADDR_IN cliAddr;
SOCKADDR_IN serAddr;

struct Client{
  short thread_tag; //1 待销毁
  short tag; //0 该位置可用
  int threadNum;
  SOCKET cli;
  SOCKADDR_IN cliAddr;
  pthread_t thread;
  pthread_rwlock_t c_lock;
};
Client* Aclient;
void serverInit(){
  //create sock
  serSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

  LOG_INFO("init all client")
  Aclient = (Client*)malloc(CLI_MAX_NUM*(sizeof(Client)));
  for(int i=0;i<CLI_MAX_NUM;i++){
    Aclient[i].tag=0;
    Aclient[i].thread_tag=0;
    pthread_rwlock_init(&Aclient[i].c_lock, nullptr);
  }

  //create & bind address
  serAddr.sin_family=AF_INET;
  serAddr.sin_port=htons(4321);
  serAddr.sin_addr.S_un.S_addr=inet_addr(SERVERIP);

  status=bind(serSock,(SOCKADDR*)&serAddr, sizeof(serAddr));

  LOG_INFO("Start to a new listen")
  status=listen(serSock,5);
}
void *messageHandler(void *Info){
  Client* cliInfo=(Client*)Info;
  cout<<"Client"<<cliInfo->threadNum<<" is online\n";
  int recvLength=0;

  char buf[BUFSIZE];
  while(true){
    recvLength=recv(cliInfo->cli,buf,BUFSIZE,0);
    if(recvLength>0){
      cout<<"[RECV LOG]recv from client:"<<cliInfo->threadNum<<"  message: "<<buf<<"\n";
      for(int i=0;i<CLI_MAX_NUM;i++){
        //pthread_rwlock_tryrdlock(&Aclient[i].c_lock);
        if(Aclient[i].tag==1&&i!=cliInfo->threadNum){
          //send bufin to this client
          char num[2];
          num[0]='0'+cliInfo->threadNum;
          num[1]=':';
          char t[BUFSIZE];
          t[0]='\0';
          strcat(t,"Client->");
          strcat(t,num);
          //strcat(t,buf);
          send(Aclient[i].cli,t,BUFSIZE,0);
          cout<<"[SEND LOG]from client:"<<cliInfo->threadNum<<"send to client:"<<i<<" message:"<<buf<<"\n";
        }
        //pthread_rwlock_unlock(&Aclient[cliInfo->threadNum].c_lock);
      }
      if(!strcmp(buf,"exit")){
        break;
      }
    }
  }
  //close client sock
  cout<<"Client"<<cliInfo->threadNum<<" is offline\n";

  //pthread_rwlock_trywrlock(&Aclient[cliInfo->threadNum].c_lock);
  Aclient[cliInfo->threadNum].tag=0;
  Aclient[cliInfo->threadNum].thread_tag=1;
  //pthread_rwlock_unlock(&Aclient[cliInfo->threadNum].c_lock);

  closesocket(cliSock);
  pthread_exit(nullptr);
}
void Server(){
  WSADATA wsa;
  WSAStartup(MAKEWORD(2,0),&wsa);

  //Init server
  serverInit();

  pthread_t* thread_handles;
  thread_handles=(pthread_t*)malloc(CLI_MAX_NUM* sizeof(pthread_t));

  int len= sizeof(SOCKADDR_IN);
  int maxnum=CLI_MAX_NUM;
  int i;
  while(maxnum>0){
    //LOG_INFO("Find a new location to accept...")
    //find a null client location
    for(i=0;i<CLI_MAX_NUM;i++){
      //pthread_rwlock_trywrlock(&Aclient[i].c_lock);
      if(Aclient[i].tag==0&&Aclient[i].thread_tag==0){
        Aclient[i].cli=accept(serSock, (SOCKADDR*)&Aclient[i].cliAddr,&len);
        cout<<"Accept in "<<i<<"\n";
        //pthread_rwlock_trywrlock(&Aclient[i].c_lock);
        Aclient[i].threadNum=i;
        Aclient[i].tag=1;
        Aclient[i].thread=thread_handles[i];
        //pthread_rwlock_unlock(&Aclient[i].c_lock);
        break;
      }
      else if(Aclient[i].thread_tag==1){
        Aclient[i].thread_tag=0;
        pthread_join(thread_handles[i], nullptr);
        cout<<"thread "<<i<<" is join\n";
      }
      //pthread_rwlock_unlock(&Aclient[i].c_lock);
    }
    if(i==CLI_MAX_NUM) {
      LOG_INFO("there is no blank index...")
      break;
    }
    //LOG_INFO("a new thread create for a new client...")
    //create a new thread for client
    pthread_create(&thread_handles[Aclient[i].threadNum], nullptr,messageHandler,&(Aclient[i]));
    pthread_detach(thread_handles[i]);
    maxnum--;
  }
  for(i=0;i<CLI_MAX_NUM;i++){
    pthread_rwlock_destroy(&Aclient[i].c_lock);
    if(Aclient[i].thread_tag==1){
      pthread_join(thread_handles[i], nullptr);
    }
  }
  //close ws2_32.dll
  WSACleanup();
  free(Aclient);
}

int main(){
  Server();
  return 0;
}
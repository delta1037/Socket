//
// Created by liubo on 2018/7/9.
//
#include <winsock2.h>
#include <stdio.h>
//#include <afxres.h>
#include <stdio.h>
#include <conio.h>
#include <io.h>
#include "log.h"
#include <windows.h>
//#include <pthread.h>

#pragma comment(lib,"ws2_32.lib")

#define BUFSIZE 1024
#define SERVERIP "127.0.0.1"

int status=0;
void Server(){
  SOCKET cliSock;
  SOCKET serSock;
  SOCKADDR_IN cliAddr;
  SOCKADDR_IN serAddr;
  char buf[BUFSIZE];

  WSADATA wsa;
  WSAStartup(MAKEWORD(2,0),&wsa);

  //create sock
  serSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);


  //create & bind address
  serAddr.sin_family=AF_INET;
  serAddr.sin_port=htons(4321);
  serAddr.sin_addr.S_un.S_addr=inet_addr(SERVERIP);

  status=bind(serSock,(SOCKADDR*)&serAddr, sizeof(serAddr));


  //listen
  status=listen(serSock,5);
  LOG_INFO("Start to listen")

  //accept
  int len= sizeof(SOCKADDR_IN);
  cliSock=accept(serSock, (SOCKADDR*)&cliAddr,&len);
  LOG_INFO("Accept one connect")

  //send & recv
  LOG_INFO("you can Start to recv & send,use 'exit' to exit")
  int recvLength=0;
  int tag=1;
  ioctlsocket(serSock,FIONBIO,(unsigned long*)&tag);
  ioctlsocket(cliSock,FIONBIO,(unsigned long*)&tag);
  while(1){
    recvLength=recv(cliSock,buf,BUFSIZE,0);
    if(recvLength>0){
      printf("recv:%s\n",buf);
      if(!strcmp(buf,"exit")){
        break;
      }
      recvLength=0;
    }

    //_sleep(500);
    if(kbhit()){
      gets(buf);
      send(cliSock,buf,BUFSIZE,0);
      printf("send->%s\n",buf);
    }
  }

  //close
  closesocket(serSock);
  closesocket(cliSock);
  //close ws2_32.dll
  WSACleanup();
}
int main(){
  //Server();

  //pthread_t* test;

  //pthread_create(test,Server(),0);
  //CreateThread()

  return 0;
}

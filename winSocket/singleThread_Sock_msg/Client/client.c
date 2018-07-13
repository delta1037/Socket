//
// Created by liubo on 2018/7/9.
//
#include <winsock2.h>
#include <stdio.h>
#include <conio.h>
#include "log.h"
#pragma comment(lib,"ws2_32.lib")

#define BUFSIZE 1024
#define other "192.168.1.102"
#define mine "127.0.0.1"
#define h "192.168.1.116"

int status=0;
int Client(int serPort,char* serIP){
  SOCKET cliSock;
  SOCKADDR_IN serAddr;
  char buf[BUFSIZE];

  WSADATA wsa;
  WSAStartup(MAKEWORD(2,2),&wsa);

  //create sock
  cliSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

  //create & bind address
  serAddr.sin_family=AF_INET;
  serAddr.sin_port=htons(serPort);
  serAddr.sin_addr.S_un.S_addr=inet_addr(serIP);

  //connect
  status=connect(cliSock,(SOCKADDR*)&serAddr, sizeof(serAddr));
  LOG_INFO("Connect success...")

  //send & recv
  LOG_INFO("you can Start to recv & send,use 'exit' to exit")
  int recvLengh=0;
  int tag=1;
  ioctlsocket(cliSock,FIONBIO,(unsigned long*)&tag);
  LOG_INFO("Ready in while.")

  while(1){
    if(kbhit()){
      memset(buf,0,BUFSIZE);
      gets(buf);
      send(cliSock,buf,BUFSIZE,0);
      //printf("send->%s\n",buf);
      if(!strcmp(buf,"exit")){
        break;
      }
    }
    _sleep(100);
    recvLengh=recv(cliSock,buf,BUFSIZE,0);
    if(recvLengh>0){
      //puts("Get from:");
      printf("recv:%s\n",buf);
    }
  }

  //close
  closesocket(cliSock);

  //close ws2_32.dll
  WSACleanup();
}
int main(){
    Client(4321,mine);
    return 0;
}
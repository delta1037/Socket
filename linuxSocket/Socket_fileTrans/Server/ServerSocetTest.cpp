//
// Created by geniusrabbit on 18-2-27.
//

#include <cstring>
#include <fstream>
#include "include/SocketServer.h"
#include "include/Log.h"

using namespace std;
using namespace GeniusNote;


typedef struct{
  int id;
  char name[10];
}ID_Name;

const char *serverPath="/home/geniusrabbit/";
char writePath[50]= "/home/geniusrabbit/TransHttp-C++/Server/\0";
char fileName[20];

const char *ClientIP="127.0.0.1";
int ClientPort=6666;
const char *ServerIP="127.0.0.1";
int ServerPort=6667;

const char *status="ok";

const int bufSize=1024*1024*2;
char buf[bufSize];

int recvFile(){
  int state=0;

  //init
  SocketServer server{};
  server.Init(ClientIP,ClientPort,ServerIP,ServerPort);

  bzero(fileName, sizeof(fileName));
  int recvSize=server.Recv((void*)fileName, 20);
  printf("file name is %s\n",fileName);

  server.Send((void*)status,10);
  LOG_INFO("write back ok is send")

  strcat(writePath,fileName);
  fstream out(writePath,ios::out);
  bzero(buf, sizeof(buf));
  int recvLength=server.Recv(buf, sizeof(buf));
  int sum=0;
  while(recvLength>100){
    out.write(buf,recvLength);
    sum+=recvLength;
    printf("recvLength---%d---",recvLength);

    bzero(buf, sizeof(buf));
    recvLength=server.Recv(buf, sizeof(buf));
  }

  printf("recvSize=%d\n",sum);
  //close socket & file
  server.Close();
  out.close();
  return 0;

}
int main(){
  int recvStatus=recvFile();
  if(recvStatus==0){
    LOG_INFO("recv is success~")
  }
  return 0;
}
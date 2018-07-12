#include <cstring>
#include <fstream>
#include <unistd.h>
#include "include/SocketClient.h"
#include "include/Log.h"

using namespace Socket;
using namespace std;

typedef struct{
  int id;
  char name[10];
}ID_Name;

const char *ClientIP="127.0.0.1";
int ClientPort=6666;
const char *ServerIP="127.0.0.1";
int ServerPort=6667;

char *filePath= const_cast<char *>("/home/geniusrabbit/TransHttp-C++/Client/test.mp4");
const char *fileName="test000.mp4";

char serverStatus[10];

int sendFile(){
  int state=Running;

  int BUFFER_SIZE=1024*1024;
  char buf[BUFFER_SIZE];

  //init
  SocketClient client{};
  client.Init(ClientIP,ClientPort,ServerIP,ServerPort);

  //send filename
  LOG_INFO("Send filename")
  int sendSize=client.Send((void*)fileName, strlen(fileName));
  CHECK(sendSize,SOCKET_ERROR,{LOG_ERROR("Send filename error") state=Error;})

  //send name is ok!
  bzero(serverStatus, sizeof(serverStatus));
  client.Recv((void*)serverStatus,5);
  printf("serverStatus is %s\n",serverStatus);

  // trans file
  fstream in(filePath,ios::in);
  LOG_INFO("Start to send file")
  while(!in.eof()){
    streamsize num_read=in.read(buf,BUFFER_SIZE).gcount();

    sendSize=client.Send(buf, (size_t)num_read);
    CHECK(sendSize,0,{LOG_ERROR("Send file error") state=Error;})
    bzero(buf, (size_t)BUFFER_SIZE);
  }

  //close socket & file
  client.Close();
  in.close();
  return 0;
}
int recvtest(){
  int BUFFER_SIZE=1024*5;
  char buf[BUFFER_SIZE];
  int readLength;

  fstream in(filePath,ios::in);
  while(!in.eof()){
    streamsize num_read=in.read(buf,BUFFER_SIZE).gcount();
    printf("%d--%s\n",(int)num_read,buf);
  }



  FILE *fp=fopen(filePath,"r");

  if(fp==NULL){
    LOG_ERROR("Can't read file")
  }

  readLength = (int)fread(buf, sizeof(char),(size_t)BUFFER_SIZE, fp);
  printf("buf is %s\n",buf);
  printf("readLength:%d\n",readLength);
}
int main(){
  int status=1;
  status=sendFile();
  if(status==0){
    LOG_INFO("Send file success")
  }
}

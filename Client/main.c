#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <zconf.h>

int main() {
    //创建套接字
    int sock=socket(AF_INET,SOCK_STREAM,0);

    //向特定的服务器发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));//用0填充每个字节
    serv_addr.sin_family=AF_INET; //使用ipv4
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");        //你将要连接的ip地址
    serv_addr.sin_port=htons(1234); //端口
    connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    //读取服务器传回的数据
    char buffer[40];
    read(sock,buffer,sizeof(buffer)-1);

    printf("Message from server:%s\n",buffer);

    //关闭套接字
    close(sock);

    return 0;
}

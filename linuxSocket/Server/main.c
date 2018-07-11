#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <zconf.h>

int main() {
    //创建
    int serv_sock =socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    //将套接字绑定ip,端口
    struct  sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr)); //填充每个字节用0
    serv_addr.sin_family=AF_INET; //使用ipv4
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1"); //本机(即服务器)IP地址
    serv_addr.sin_port=htons(1234); //使用的端口
    bind(serv_sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr));


    //开始监听
    listen(serv_sock,20);

    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size =sizeof(clnt_addr);
    int clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);

    //向客户端发送数据
    char str[]="hello world";
    write(clnt_sock,str,sizeof(str));

    //关闭套接字
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

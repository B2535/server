#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<ctype.h>
#define SERV_PORT 6666
#define SERV_IP "127.0.0.1"




int main(){
    int lfd,cfd;

    struct sockaddr_in serv_addr,clie_addr;//封装服务器和客户端 IP和端口
    socklen_t clie_addr_len;
    char buf[BUFSIZ];
    int n;

    serv_addr.sin_port=htons(SERV_PORT);
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);


    
    
    lfd=socket(AF_INET,SOCK_STREAM,0);//创建套接字

    bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)//绑定IP和端口
    );

    listen(lfd,32);
    clie_addr_len=sizeof(clie_addr);
    cfd=accept(lfd,(struct sockaddr*)&clie_addr,&clie_addr_len);

    n=read (cfd,buf,sizeof(buf));
    for(int i=0;i<n;i++){
        buf[i]=toupper(buf[i]);//小写转大写
    }
    write(cfd,buf,n);
    close(lfd);
    close(cfd);

    return 0;
}
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

void error(const char * errormessage);

int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_adr;
    struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;
    char message[1024];
    if(argc != 2)
    {
        cout<<"Usage : "<<argv[0]<<"<port>"<<endl;
        exit(1);
    }

    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1)
    {
        error("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error("bind() error");
	if(listen(serv_sock, 2)==-1)
		error("listen() error");

    clnt_addr_size=sizeof(clnt_addr);  
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)
    {
		error("accept() error");  
    }
    while(1)
    {
        int str_len=read(clnt_sock,message, 1024);
        if(str_len==-1)
            error("read() error!");
        cout<<message<<endl;
        write(clnt_sock,message, 1024);
    }
	close(clnt_sock);	
	close(serv_sock);
    return 0;
}

void error(const char * errormessage)
{
	fputs(errormessage, stderr);
	fputc('\n', stderr);
	exit(1);
}
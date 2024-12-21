#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

void error(const char *message);

int main(int argc, char* argv[])
{
	int sock;
    char msg[1024];
    int result[4];
	struct sockaddr_in serv_addr;
	
	if(argc!=3)
    {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
		
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) 
		error("connect() error!");
    else
		puts("Connected...........");
    while(1)
	{
		fputs("Your number : ", stdout);
		cin>>msg;
		if(msg[0] == 'q')
			break;
		write(sock,msg,1024);
		read(sock,msg,1024);
		cout<<msg<<endl;
	}
	close(sock);
	return 0;
}

void error(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
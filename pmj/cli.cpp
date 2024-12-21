#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;
class client
{
	private:
		int sock;
		char msg[1024];
		int result[4];
		struct sockaddr_in serv_addr;

	public:
		void create_socket(int * argc,char *argv[]) //소켓 생성 함수
		{
			if(*argc!=3)
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
		}
		void error(const char *message) // 소켓 생성중 에러문구 출력 함수
		{
			fputs(message, stderr);
			fputc('\n', stderr);
			exit(1);
		}
		void input() // 서버로 문자 전송 함수
		{
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
		}
		void client_close() //소켓 닫는 함수
		{
			close(sock);
		}
};
int main(int argc, char* argv[])
{
	client pmj;
	pmj.create_socket(&argc,argv);
	pmj.input();
	pmj.client_close();
	return 0;
}
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
		char msg_id[1024];
		char msg_pw[1024];
		char number;
		struct sockaddr_in serv_addr;
		string book[10];

	public:
		
		void book_inquiry()
        {
            fputs("도서 조회 : 1  장르별 검색 : 2  = ", stdout);
			cin>>number;
			if(number >= 1 && number <= 2)
			{
				fputs("다시 입력해 주세요 도서 조회 : 1  장르별 검색 : 2  = ", stdout);
				cin>>number;
			}
			write(sock,(void *)&number,1);
			if(number == '1')
			{
				for(int i = 0 ; i < 10 ; i++)
				{
					int len;
					read(sock,&len,sizeof(len));
					char *book = new char[len + 1]; 
					read(sock,book,len);
					book[len]= '\0';
					cout<<book;
					delete[] book;
				}
			}
			else if(number == '2')
			{
				fputs("작가 : 1 , 청구기호 : 2 , 제목 : 3 = ",stdout);
				cin>>number;
				if(number >= 1 && number <= 3)
				{
					fputs("다시 입력해 주세요 작가 : 1 , 청구기호 : 2 , 제목 : 3 = ", stdout);
					cin>>number;
				}
				write(sock,(void *)&number,1);
				if(number == '1')
				{
					fputs("작가 명을 입력해주세요.",stdout);
					cin>>msg;
					write(sock,msg,1024);
					for(int j = 0 ; j < 10 ; j++)
					{
						for(int i = 0 ; i < 10 ; i++)
						{
							int len;
							read(sock,&len,sizeof(len));
							char *book = new char[len + 1]; 
							read(sock,book,len);
							book[len]= '\0';
							cout<<book<<" ";
							delete[] book;
						}
						cout<<endl;
					}
				}
				else if(number == '2')
				{
					fputs("청구기호 명을 입력해주세요.",stdout);
					cin>>msg;
					write(sock,msg,1024);
					for(int j = 0 ; j < 10 ; j++)
					{
						for(int i = 0 ; i < 10 ; i++)
						{
							int len;
							read(sock,&len,sizeof(len));
							char *book = new char[len + 1]; 
							read(sock,book,len);
							book[len]= '\0';
							cout<<book<<" ";
							delete[] book;
						}
						cout<<endl;
					}
				}
				else if(number == '3')
				{
					fputs("제목 명을 입력해주세요.",stdout);
					cin>>msg;
					write(sock,msg,1024);
					for(int i = 0 ; i < 10 ; i++)
					{
						int len;
						read(sock,&len,sizeof(len));
						char *book = new char[len + 1]; 
						read(sock,book,len);
						book[len]= '\0';
						cout<<book<<endl;
						delete[] book;
					}
				}

			}
        }
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
		void login() // 서버로 문자 전송 함수
		{
			fputs("ID : ", stdout);
			cin>>msg_id;
			number = '9';
			write(sock,(void *)&number,1);
			write(sock,msg_id,1024);
			read(sock,msg_id,1024);

			fputs("PW : ", stdout);
			cin>>msg_pw;
			number = '8';
			write(sock,(void *)&number,1);
			write(sock,msg_pw,1024);
			read(sock,msg_pw,1024);

			fputs("Your ID : ", stdout);
			cout<<msg_id<<endl;
			fputs("Your PW : ", stdout);
			cout<<msg_pw<<endl;
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
	pmj.login();
	pmj.book_inquiry();
	pmj.client_close();
	return 0;
}
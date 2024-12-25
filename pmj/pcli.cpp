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
		char user_msg[1024];
		char number;
		struct sockaddr_in serv_addr;
		string book[10];

	public:
		bool readWithTimeout(int sock, char *buffer, int length, int timeoutSeconds) {
			fd_set readfds;
			struct timeval timeout;
			
			FD_ZERO(&readfds);
			FD_SET(sock, &readfds);
			
			timeout.tv_sec = timeoutSeconds;
			timeout.tv_usec = 0;
			
			int activity = select(sock + 1, &readfds, NULL, NULL, &timeout);
			if (activity < 0) {
				return false;
			}
			if (activity == 0) {
				return false;
			}

			// 데이터 수신
			int bytesRead = read(sock, buffer, length);
			return bytesRead > 0;
		}
		void book_inquiry()
        {
			while(1)
			{
				system("clear");
				while(1)
				{
					fputs("도서 기본 정보 보기 : 1  장르별 검색 : 2  = ", stdout);
					cin>>number;
					if(number < '1' || number > '2')
					{
						system("clear");
						fputs("다시 입력해 주세요", stdout);
						cout<<endl;
					}
					else
						break;
				}
				write(sock,(void *)&number,1);
				cout<<endl;
				if(number == '1')
				{
					system("clear");
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
					cout<<endl;
					fputs("끝내기  아무버튼",stdout);
					cin>>user_msg;
				}
				else if(number == '2')
				{
					system("clear");
					while(1)
					{
						fputs("작가 : 1 , 청구기호 : 2 , 제목 : 3 = ",stdout);
						cin>>number;
						if(number < '1' || number > '3')
						{
							system("clear");
							fputs("다시 입력해 주세요", stdout);
							cout<<endl;
						}
						else
							break;
					}
					write(sock,(void *)&number,1);
					if(number == '1')
					{
						fputs("작가 명을 입력해주세요.",stdout);
						cin>>msg;
						write(sock,msg,1024);
						int num = 0;
						while(1)
						{
							int endwhile = 0;
							system("clear");
							write(sock,(void*)&num,1);
							for(int j = 0 ; j < 10 ; j++)
							{
								for(int i = 0 ; i < 10 ; i++)
								{
									int len;
									if (!readWithTimeout(sock, (char*)&len, sizeof(len), 1)) {
										endwhile = -1;
										break;
									}
									char *book = new char[len + 1]; 
									read(sock,book,len);
									book[len]= '\0';
									cout<<book<<" ";
									delete[] book;
								}
								cout<<endl;
								if(endwhile == -1)
								{
									break;
								}
							}
							fputs("페이지 업 = q , 페이지 다운 = w ,끝내기  = e",stdout);
							cin>>user_msg;
							if(user_msg[0] == 'q')
							{
								num += 10;
							}
							else if(user_msg[0] == 'w')
							{
								num -= 10;
								if(num < 0)
								{
									num = 0;
								}
							}
							else if(user_msg[0] == 'e')
							{
								num = -1;
								write(sock,(void*)&num,1);
								break;
							}

						}
					}
					else if(number == '2')
					{
						fputs("청구기호 명을 입력해주세요.",stdout);
						cin>>msg;
						write(sock,msg,1024);
						int num = 0;
						while(1)
						{
							system("clear");
							int endwhile = 0;
							write(sock,(void*)&num,1);
							for(int j = 0 ; j < 10 ; j++)
							{
								
								for(int i = 0 ; i < 10 ; i++)
								{
									int len;
									if (!readWithTimeout(sock, (char*)&len, sizeof(len), 1)) {
										cout<<"마지막입니다."<<endl;
										endwhile = -1;
										break;
									}
									char *book = new char[len + 1]; 
									read(sock,book,len);
									book[len]= '\0';
									cout<<book<<" ";
									delete[] book;
								}
								cout<<endl;
								if(endwhile == -1)
								{
									break;
								}
							}
							fputs("페이지 업 = q , 페이지 다운 = w ,끝내기  = e",stdout);
							cin>>user_msg;
							if(user_msg[0] == 'q')
							{
								num += 10;
							}
							else if(user_msg[0] == 'w')
							{
								num -= 10;
								if(num < 0)
								{
									num = 0;
								}
							}
							else if(user_msg[0] == 'e')
							{
								num = -1;
								write(sock,(void*)&num,1);
								break;
							}

						}
					}
					else if(number == '3')
					{
						fputs("제목 명을 입력해주세요.",stdout);
						cin>>msg;
						write(sock,msg,1024);
						int num = 0;
						while(1)
						{
							system("clear");
							int endwhile = 0;
							write(sock,(void*)&num,1);
							for(int j = 0 ; j < 10 ; j++)
							{
								
								for(int i = 0 ; i < 10 ; i++)
								{
									int len;
									if (!readWithTimeout(sock, (char*)&len, sizeof(len), 1)) {
										cout<<"마지막입니다."<<endl;
										endwhile = -1;
										break;
									}
									char *book = new char[len + 1]; 
									read(sock,book,len);
									book[len]= '\0';
									cout<<book<<" ";
									delete[] book;
								}
								cout<<endl;
								if(endwhile == -1)
								{
									break;
								}
							}
							fputs("페이지 업 = q , 페이지 다운 = w ,끝내기  = e",stdout);
							cin>>user_msg;
							if(user_msg[0] == 'q')
							{
								num += 10;
							}
							else if(user_msg[0] == 'w')
							{
								num -= 10;
								if(num < 0)
								{
									num = 0;
								}
							}
							else if(user_msg[0] == 'e')
							{
								num = -1;
								write(sock,(void*)&num,1);
								break;
							}

						}
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
			
			while(1)
			{
				fputs("로그인 1번 회원가입 2번 = ",stdout);
				cin>>number;
				if(number < '1' || number > '2')
				{
					system("clear");
					fputs("다시 입력해 주세요", stdout);
					cout<<endl;
				}
				else
					break;
			}
			if(number == '1')
			{
				system("clear");
				while(1)
				{
					fputs("ID : ", stdout);
					cin>>msg_id;
					fputs("PW : ", stdout);
					cin>>msg_pw;
					while(1)
					{
						fputs("로그인 하기 1 ,돌아가기 2 ",stdout);
						cin>>number;
						if(number < '1' || number > '2')
						{
							system("clear");
							fputs("다시 입력해 주세요", stdout);
							cout<<endl;
						}
						else
							break;
					}
					if(number == '1')
					{
						number = '9';
						write(sock,(void *)&number,1);

						write(sock,msg_id,1024);
						write(sock,msg_pw,1024);


						read(sock,(void *)&number,1);
						if(number == '2')
						{	
							system("clear");
							fputs("다시 입력해주세요",stdout);
							cout<<endl;
						}
						else if(number == '1')
						{
							break;
						}
					}
					else if(number == '2')
					{
						system("clear");
						login();
						break;
					}
				}
			}
			else if(number == '2')
			{
				while(1)
				{
					char name[1024];
					char phone[1024];
					char addr[1024];
					fputs("ID : ", stdout);
					cin>>msg_id;
					fputs("PW : ", stdout);
					cin>>msg_pw;
					fputs("name : ", stdout);
					cin>>name;
					fputs("phone : ", stdout);
					cin>>phone;
					fputs("addr : ", stdout);
					cin>>addr;
					number = '8';
					write(sock,(void *)&number,1);

					write(sock,msg_id,1024);
					write(sock,msg_pw,1024);
					write(sock,name,1024);
					write(sock,phone,1024);
					write(sock,addr,1024);
					read(sock,(void *)&number,1);
					if(number == '1')
					{
						fputs("회원가입이 완료되었습니다.",stdout);
						cout<<endl;
						sleep(3);
						break;
					}
					fputs("중복된 아이디입니다 다시 입력해주세요",stdout);
					cout<<endl;
					sleep(3);
					system("clear");
				}
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
	pmj.login();
	pmj.book_inquiry();
	pmj.client_close();
	return 0;
}
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;
class server
{
    private:
        int serv_sock;
        int clnt_sock;
        int option;
        socklen_t optlen;
        struct sockaddr_in serv_adr;
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_size;
        char message[1024];
        char number;
        string book[10] = {" 도서"," 책"," 출판사"," 대여정보"," 기타"," 제목"," 작가"," 장르"," 기타"," 등"};

    public:
        void login()
        {
            while(1)
            {
                number = '0';
                int str_len=read(clnt_sock,(void *)&number,1);
                if(str_len==-1)
                    error("read() error!");
                cout<<number;
                if(number == '9')
                {
                    str_len=read(clnt_sock,message, 1024);
                    if(str_len==-1)
                        error("read() error!");
                    cout<<"Your ID : "<<endl;
                    cout<<message<<endl;
                    write(clnt_sock,message, 1024);
                }
                else if(number == '8')
                {
                    str_len=read(clnt_sock,message, 1024);
                    if(str_len==-1)
                        error("read() error!");
                    cout<<"Your PW : "<<endl;
                    cout<<message<<endl;
                    write(clnt_sock,message, 1024);
                }
                else if(number == '1')
                {
                    for(int i = 0 ; i < 10 ; i++)
                    {
                        int len = book[i].size();
                        write(clnt_sock,&len,sizeof(len));
                        write(clnt_sock,book[i].c_str(),len);
                    }  
                }
                else if(number == '2')
                {
                    cout<<"미완성";
                }
                else if(number == 0)
                {
                    sleep(1);
                }
            }
        }
        void create_socket(int * argc,char * argv[])
        {
            if(*argc != 2)
            {
                cout<<"Usage : "<<argv[0]<<"<port>"<<endl;
                exit(1);
            }

            serv_sock = socket(PF_INET,SOCK_STREAM,0);
            if(serv_sock == -1)
            {
                error("socket() error");
            }

            optlen = sizeof(option);
            option = 1;
            setsockopt(serv_sock, SOL_SOCKET,SO_REUSEADDR,(void*)&option,optlen);

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

        }
        void error(const char * errormessage)
        {
            fputs(errormessage, stderr);
            fputc('\n', stderr);
            exit(1);
        }
        void socket_close()
        {
            close(clnt_sock);	
	        close(serv_sock);
        }
};
int main(int argc, char *argv[])
{
    server pmj;
    pmj.create_socket(&argc,argv);
    pmj.login();
    cout<<"11";
    pmj.socket_close();
    return 0;
}
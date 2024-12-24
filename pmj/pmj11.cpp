#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <mariadb/conncpp.hpp>
using namespace std;
class database
{
    private:

    public:
        void select(std::unique_ptr<sql::Connection> &conn) 
        {
            try {
                // createStaemet 객체 생성
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                // 쿼리를 실행
                sql::ResultSet *res = stmnt->executeQuery("select * from KING");
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    std::cout << "SNB = " << res->getString(1);
                    std::cout << ",Library = " << res->getString(2);
                    std::cout << ",dataroom = "<< res->getString(3);
                    std::cout << ",Registration_number = "<< res->getString(4);
                    std::cout << ",name = "<< res->getString(5);
                    std::cout << ",Author = "<< res->getString(6);
                    std::cout << ",publisher = "<< res->getString(7);
                    std::cout << ",Publication_year = "<< res->getString(8);
                    std::cout << ",Call_number = "<< res->getString(9);
                    std::cout << ",Data_base_date = "<< res->getString(10);
                    break;
                }
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
            }
        }
        void nameselect(std::unique_ptr<sql::Connection> &conn,string userinput,string book[]) 
        {
            try {
                int i = 0;
                std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT * FROM KING where name = ?"));
                stmnt->setString(1, userinput);
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    std::cout << "SNB = " << res->getString(1);
                    book[0] = res->getString(1);
                    std::cout << ",Library = " << res->getString(2);
                    book[1] = res->getString(2);
                    std::cout << ",dataroom = "<< res->getString(3);
                    book[2] = res->getString(3);
                    std::cout << ",Registration_number = "<< res->getString(4);
                    book[3] = res->getString(4);
                    std::cout << ",name = "<< res->getString(5);
                    book[4] = res->getString(5);
                    std::cout << ",Author = "<< res->getString(6);
                    book[5] = res->getString(6);
                    std::cout << ",publisher = "<< res->getString(7);
                    book[6] = res->getString(7);
                    std::cout << ",Publication_year = "<< res->getString(8);
                    book[7] = res->getString(8);
                    std::cout << ",Call_number = "<< res->getString(9);
                    book[8] = res->getString(9);
                    std::cout << ",Data_base_date = "<< res->getString(10);
                    book[9] = res->getString(10);
                    break;
                }
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
            }
        }
        void Authorselect(std::unique_ptr<sql::Connection> &conn,string userinput,string book[],int  clnt_sock,int number) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "SELECT * FROM KING where author like '%" + userinput +"%'limit 10 offset "+ std::to_string(number);
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    //std::cout << "SNB = " << res->getString(1);
                    book[0] = res->getString(1);
                    //std::cout << ",Library = " << res->getString(2);
                    book[1] = res->getString(2);
                    // std::cout << ",dataroom = "<< res->getString(3);
                    book[2] = res->getString(3);
                    //std::cout << ",Registration_number = "<< res->getString(4);
                    book[3] = res->getString(4);
                    //std::cout << ",name = "<< res->getString(5);
                    book[4] = res->getString(5);
                    //std::cout << ",Author = "<< res->getString(6);
                    book[5] = res->getString(6);
                    //std::cout << ",publisher = "<< res->getString(7);
                    book[6] = res->getString(7);
                    //std::cout << ",Publication_year = "<< res->getString(8);
                    book[7] = res->getString(8);
                    //std::cout << ",Call_number = "<< res->getString(9);
                    book[8] = res->getString(9);
                   // std::cout << ",Data_base_date = "<< res->getString(10)<<endl;
                    book[9] = res->getString(10);
                    for(int i = 0 ; i < 10 ; i++)
                    {
                        int len = book[i].size();
                        write(clnt_sock,&len,sizeof(len));
                        write(clnt_sock,book[i].c_str(),len);
                    }
                }
                

            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
            }
        }
        void Call_numberselect(std::unique_ptr<sql::Connection> &conn,string userinput,string book[],int clnt_sock,int number) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "SELECT * FROM KING where find like '" + userinput + "%'limit 10 offset "+ std::to_string(number);

                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    std::cout << "SNB = " << res->getString(1);
                    book[0] = res->getString(1);
                    std::cout << ",Library = " << res->getString(2);
                    book[1] = res->getString(2);
                    std::cout << ",dataroom = "<< res->getString(3);
                    book[2] = res->getString(3);
                    std::cout << ",Registration_number = "<< res->getString(4);
                    book[3] = res->getString(4);
                    std::cout << ",name = "<< res->getString(5);
                    book[4] = res->getString(5);
                    std::cout << ",Author = "<< res->getString(6);
                    book[5] = res->getString(6);
                    std::cout << ",publisher = "<< res->getString(7);
                    book[6] = res->getString(7);
                    std::cout << ",Publication_year = "<< res->getString(8);
                    book[7] = res->getString(8);
                    std::cout << ",Call_number = "<< res->getString(9);
                    book[8] = res->getString(9);
                    std::cout << ",Data_base_date = "<< res->getString(10)<<endl;
                    book[9] = res->getString(10);
                    for(int i = 0 ; i < 10 ; i++)
                    {
                        int len = book[i].size();
                        write(clnt_sock,&len,sizeof(len));
                        write(clnt_sock,book[i].c_str(),len);
                    }
                }
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
            }
        }
};
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
        string book[10] = {"연변"," 소장도서관"," 자료실명"," 등록번호"," 도서명"," 저자"," 출판사"," 출판연도"," 청구기호"," 데이터기준일자"};
    public:
        void input()
        {
            for(int i = 0 ; i < 10 ; i++)
            {
                int len = book[i].size();
                write(clnt_sock,&len,sizeof(len));
                write(clnt_sock,book[i].c_str(),len);
            }  
        }
        void login(std::unique_ptr<sql::Connection> &conn,database dbpmj)
        {
            while(1)
            {
                number = '0';
                int str_len=read(clnt_sock,(void *)&number,1);
                if(str_len==-1)
                    error("read() error!");
                if(number == '9')
                {
                    str_len=read(clnt_sock,message, 1024);
                    if(str_len==-1)
                        error("read() error!");
                    cout<<"Your ID : "<<endl;
                    cout<<message<<endl;
                    write(clnt_sock,message, 1024);
                    cout<<'0';
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
                    read(clnt_sock,(void *)&number,1);
                    if(number == '1')
                    {
                        read(clnt_sock,message, 1024);
                        while(1)
                        {
                            read(clnt_sock,(void *)&number,1);
                            if(number == -1)
                            {
                                break;
                            }
                            dbpmj.Authorselect(conn,message,book,clnt_sock,number);
                        }
                    }
                    else if(number == '2')
                    {
                        read(clnt_sock,message, 1024);
                        while(1)
                        {
                            read(clnt_sock,(void *)&number,1);
                            if(number == -1)
                            {
                                break;
                            }
                            dbpmj.Call_numberselect(conn,message,book,clnt_sock,number);
                        }
                    }
                    else if(number == '3')
                    {
                        read(clnt_sock,message, 1024);
                        dbpmj.nameselect(conn,message,book);
                        input();
                    }
                }
                else if(number == '0')
                {
                    sleep(3);
                }
                cout<<'b';
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
     // DB연결 객체 생성
    sql::Driver* driver = sql::mariadb::get_driver_instance();
    // 연결할 DB의 특정 IP, DB를 정의
    sql::SQLString url("jdbc:mariadb://localhost:3306/KINGSEO");
    // 연결할 DB를 사용할 유저를 정의
    sql::Properties properties({{"user", "PMJ"}, {"password", "1234"}});
    // 객체에 값을 통하여 연결을 시도
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    server pmj;
    database dbpmj;
    pmj.create_socket(&argc,argv);
    pmj.login(conn,dbpmj);
    pmj.socket_close();
    return 0;
}
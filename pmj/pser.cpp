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
        void addMember(std::unique_ptr<sql::Connection> &conn, std::string id, std::string pw, std::string name, std::string phone, std::string addr) {
			try {
				// PreparedStatement 객체 생성
				std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into Member values (?, ?, ?, ?, ?, default,'1','0','0',NULL)"));
				// 객체에 값을 전달
				stmnt->setString(1, id);
				stmnt->setString(2, pw);
				stmnt->setString(3, name);
				stmnt->setString(4, phone);
				stmnt->setString(5, addr);
				// 객체의 내부 함수를 이용하여 쿼리를 실행
				stmnt->executeUpdate();
			// 실패시 오류 메세지 반환
			} catch(sql::SQLException& e){
			std::cerr << "Error inserting new Member: " << e.what() << std::endl;
			}
		}
        //로그인 아이디, 비번 비교
        int checkLogin(std::unique_ptr<sql::Connection> &conn, std::string id, std::string pw) {
            try {
                std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT M_id , M_pw FROM Member WHERE M_id = ? and M_pw =?"));
                stmnt->setString(1, id);
                stmnt->setString(2, pw);

                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
                if (res->next()) {
                    return 1; //맞으면 로그인 성공
                } else {
                    return 2; // 중복되지 않은 경우 빈 문자열 반환
                }

            } catch(sql::SQLException& e) {
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
                return 3;
            }
        }
		//회원가입 id 중복 체크 함수
		// std::string checkIDmember(std::unique_ptr<sql::Connection> &conn, std::string id) {
		// 	try {
		// 		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT M_id FROM Member WHERE M_id = ?"));
		// 		stmnt->setString(1, id);

		// 		std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
		// 		if (res->next()) {
		// 			return std::string(res->getString("M_id")); // 변환 추가
		// 		} else {
		// 			return ""; // 중복되지 않은 경우 빈 문자열 반환
		// 		}

		// 	} catch(sql::SQLException& e) {
		// 		std::cerr << "Error selecting tasks: " << e.what() << std::endl;
		// 		return "";
		// 	}
		// }
		//로그인 아이디 비교
		int checkLoginId(std::unique_ptr<sql::Connection> &conn, std::string id) {
			try {
				std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT M_id FROM Member WHERE M_id = ?"));
				stmnt->setString(1, id);

				std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
				if (res->next()) {
					return 1; //맞으면 로그인 성공
				} else {
					return 2; // 중복되지 않은 경우 빈 문자열 반환
				}

			} catch(sql::SQLException& e) {
				std::cerr << "Error selecting tasks: " << e.what() << std::endl;
				return 3;
			}
		}
        //로그인 비번 비교
		int checkLoginPw(std::unique_ptr<sql::Connection> &conn, std::string pw) {
			try {
				std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT  M_pw FROM Member WHERE  M_pw = ?"));
				stmnt->setString(1, pw);

				std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
				if (res->next()) {
					return 1; //맞으면 로그인 성공
				} else {
					return 2; // 중복되지 않은 경우 빈 문자열 반환
				}

			} catch(sql::SQLException& e) {
				std::cerr << "Error selecting tasks: " << e.what() << std::endl;
				return 3;
			}
		}
        // void select(std::unique_ptr<sql::Connection> &conn) 
        // {
        //     try {
        //         // createStaemet 객체 생성
        //         std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        //         // 쿼리를 실행
        //         sql::ResultSet *res = stmnt->executeQuery("select * from KING");
        //         // 반복문을 통해서 내부의 값을 반환
        //         while (res->next()) {
        //             std::cout << "SNB = " << res->getString(1);
        //             std::cout << ",Library = " << res->getString(2);
        //             std::cout << ",dataroom = "<< res->getString(3);
        //             std::cout << ",Registration_number = "<< res->getString(4);
        //             std::cout << ",name = "<< res->getString(5);
        //             std::cout << ",Author = "<< res->getString(6);
        //             std::cout << ",publisher = "<< res->getString(7);
        //             std::cout << ",Publication_year = "<< res->getString(8);
        //             std::cout << ",Call_number = "<< res->getString(9);
        //             std::cout << ",Data_base_date = "<< res->getString(10);
        //             break;
        //         }
        //     // 실패시 오류 메세지 반환
        //     } catch(sql::SQLException& e){
        //         std::cerr << "Error selecting tasks: " << e.what() << std::endl;
        //     }
        // }
        int rating(std::unique_ptr<sql::Connection> &conn,std::string id) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "select M_rating from Member where M_id = '"+id+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                if(res->next()) {
                    return res->getInt(1);
                }
                else
                    return 3;
                
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
                return 3;
            }
        }
        int abnormal_return(std::unique_ptr<sql::Connection> &conn,std::string id) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "select M_abnormal_return from Member where M_id = '"+id+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                if(res->next()) {
                    return res->getInt(1);
                }
                else
                    return -1;
                
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
                return -1;
            }
        }
        int Subscription_period(std::unique_ptr<sql::Connection> &conn,std::string id) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "select datediff(curdate(),(select M_join_date from Member where M_id = '"+id+"'))";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                if(res->next()) {
                    return res->getInt(1);
                }
                else
                    return -1;
                
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
                return -1;
            }
        }
        int Date_comparison(std::unique_ptr<sql::Connection> &conn,std::string id,std::string book) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "select datediff(curdate(),(select date from borrow where book_num = '"+book+"' and user_id = '"+id+"'))";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                if(res->next()) {
                    return res->getInt(1);
                }
                else
                    return -1;
                
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
                return -1;
            }
        }
        bool changemember(std::unique_ptr<sql::Connection> &conn,std::string id) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "select datediff(curdate(),(select black_date from Member where M_id = '"+id+"'))";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                if(res->next()) {
                    if(res->getInt(1) >= 30)
                    {
                        return 1;
                    }
                    else
                        return 0;
                }
                else
                    return 0;
                
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
                return 0;
            }
        }
        int Normal_return(std::unique_ptr<sql::Connection> &conn,std::string id) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "select M_normal_return from Member where M_id = '"+id+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                if(res->next()) {
                    return res->getInt(1);
                }
                else
                    return -1;
                

            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
                return -1;
            }
        }
        void Excellent_member(std::unique_ptr<sql::Connection> &conn,std::string id) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "update Member set M_rating = '2' where M_id = '"+id+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    
                }
            
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
            }
        }
        void Black_member(std::unique_ptr<sql::Connection> &conn,std::string id) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "update Member set M_rating = '0' where M_id = '"+id+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    
                }
            
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
            }
            updateabnormalzero(conn,id);
        }
        void normal_member(std::unique_ptr<sql::Connection> &conn,std::string id) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "update Member set M_rating = '1' where M_id = '"+id+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    
                }
            
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
            }
        }
        void updatenormal(std::unique_ptr<sql::Connection> &conn,std::string id) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "update Member set M_normal_return = M_normal_return +1 where M_id = '"+id+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    
                }
            
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
            }
        }
        void updateabnormal(std::unique_ptr<sql::Connection> &conn,std::string id) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "update Member set M_abnormal_return = M_abnoraml_return + 1 where M_id = '"+id+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    
                }
            
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
            }
        }
        void updateabnormalzero(std::unique_ptr<sql::Connection> &conn,std::string id) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "update Member set M_abnormal_return = 0 where M_id = '"+id+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    
                }
            
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
            }
        }
        void black_date(std::unique_ptr<sql::Connection> &conn,std::string id) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "update Member set black_date = default where M_id = '"+id+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    
                }
            
            // 실패시 오류 메세지 반환
            } catch(sql::SQLException& e){
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
            }
        }
        void nameselect(std::unique_ptr<sql::Connection> &conn,string userinput,string book[],int  clnt_sock,int number) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "SELECT * FROM KING where name like '%" + userinput +"%'limit 10 offset "+ std::to_string(number);
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    for(int i = 0 ; i < 10 ; i++)
                    {
                        book[i] = res->getString(i+1);
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
        void Authorselect(std::unique_ptr<sql::Connection> &conn,string userinput,string book[],int  clnt_sock,int number) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "SELECT * FROM KING where author like '%" + userinput +"%'limit 10 offset "+ std::to_string(number);
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                // 반복문을 통해서 내부의 값을 반환
                while (res->next()) {
                    for(int i = 0 ; i < 10 ; i++)
                    {
                        book[i] = res->getString(i+1);
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
                    for(int i = 0 ; i < 10 ; i++)
                    {
                        book[i] = res->getString(i+1);
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
        //대여함수
        void borrowBook(std::unique_ptr<sql::Connection> &conn, std::string id, std::string book) {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "insert into borrow value ('"+book+"','"+id+"',default)";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));

            } catch(sql::SQLException& e) {
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
            }
        }
        //대여함수
        bool borrowcheck(std::unique_ptr<sql::Connection> &conn, std::string book) {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "select book_num from borrow where book_num = '"+book+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                if(res->next()) {
                    return 1;
                }
                else
                    return 0;
            } catch(sql::SQLException& e) {
                std::cerr << "Error selecting tasks: " << e.what() << std::endl;
                return 0;
            }
        }
        //반납함수
        int returnBook(std::unique_ptr<sql::Connection> &conn, std::string id, std::string book) 
        {
            try {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "select * from borrow where book_num = '"+book+"' and user_id = '"+id+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
            if(res->next()) 
            {
                std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
                std::string str = "delete from borrow where book_num = '"+book+"' and user_id = '"+id+"'";
                std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery(str));
                return 1;
            }
            else 
                return 0;

            } catch(sql::SQLException& e) {
                std::cerr << "Error executing tasks: " << e.what() << std::endl;
                return 0;
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
        char id[1024];
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
                    char pw[1024];
                    while(1)
                    {
                        str_len=read(clnt_sock,id, 1024);
                        str_len=read(clnt_sock,pw, 1024);
                        if(str_len==-1)
                            error("read() error!");
                        int loginid = dbpmj.checkLoginId(conn, id);
                        int loginpw = dbpmj.checkLoginPw(conn, pw);
                        int login = dbpmj.checkLogin(conn,id, pw);
                        if (loginid == 1 && loginpw == 1 && login == 1) 
                        {
                            number = '1';
                            write(clnt_sock,(void *)&number, 1);
                            break;
                        } 
                        else 
                        {
                            number = '2';
                            write(clnt_sock,(void *)&number, 1);
                        }
                    }
                }
                else if(number == '8')
                {
                    char pw[1024];
                    char name[1024];
                    char phone[1024];
                    char addr[1024];
                    while(1)
                    {
                        str_len=read(clnt_sock,id, 1024);
                        str_len=read(clnt_sock,pw, 1024);
                        str_len=read(clnt_sock,name, 1024);
                        str_len=read(clnt_sock,phone, 1024);
                        str_len=read(clnt_sock,addr, 1024);
                        if(str_len==-1)
                            error("read() error!");
                        int loginid = dbpmj.checkLoginId(conn, id);
                        if(loginid == 1)
                        {
                            number = '1';
                            write(clnt_sock,(void *)&number, 1);
                        }
                        else
                        {
                            number = '9';
                            write(clnt_sock,(void *)&number, 1);
                            dbpmj.addMember(conn,id,pw,name,phone,addr);
                        }
                    }
                }
                // else if(number == '1')
                // {
                //     for(int i = 0 ; i < 10 ; i++)
                //     {
                //         int len = book[i].size();
                //         write(clnt_sock,&len,sizeof(len));
                //         write(clnt_sock,book[i].c_str(),len);
                //     }  
                // }
                else if(number == '1')
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
                        while(1)
                        {
                            read(clnt_sock,(void *)&number,1);
                            if(number == -1)
                            {
                                break;
                            }
                            dbpmj.nameselect(conn,message,book,clnt_sock,number);
                        }
                    }
                }
                else if(number == '2')
                {
                    int num = dbpmj.rating(conn,id);
                    if(num == 0)
                    {
                        number = '1';
                        write(clnt_sock,(void *)&number, 1);
                    }
                    else
                    {
                        number = '0';
                        write(clnt_sock,(void *)&number, 1);
                        read(clnt_sock,message, 1024);
                        if(dbpmj.borrowcheck(conn,message))
                        {
                            number ='1';
                            write(clnt_sock,(void *)&number, 1);
                        }
                        else
                        {
                            number ='0';
                            write(clnt_sock,(void *)&number, 1);
                            read(clnt_sock,(void *)&number,1);
                            if(number == '1')
                            {
                                dbpmj.borrowBook(conn,id,message);
                            }
                        }
                    }
                }
                else if(number == '3')
                {
                    read(clnt_sock,message, 1024);
                    if(dbpmj.borrowcheck(conn,message))
                    {
                        number ='1';
                        write(clnt_sock,(void *)&number, 1);
                        read(clnt_sock,(void *)&number,1);
                        if(number == '1')
                        {
                            int date =dbpmj.Date_comparison(conn,id,message);
                            int bools = dbpmj.returnBook(conn,id,message);
                            if(bools == 1)
                            {
                                number ='1';
                                write(clnt_sock,(void *)&number, 1);
                                int num = dbpmj.rating(conn,id);
                                if(num <= 1)
                                {
                                    if(date <= 4)
                                    {
                                        dbpmj.updatenormal(conn,id);
                                    }
                                    else if (date > 14)
                                    {
                                        dbpmj.Black_member(conn,id);
                                    }
                                    else if (date > 4)
                                    {
                                        dbpmj.updateabnormal(conn,id);
                                    }
                                }
                                else if(num == 2)
                                {
                                    if(date <= 7)
                                    {
                                        dbpmj.updatenormal(conn,id);
                                    }
                                    else if (date > 14)
                                    {
                                        dbpmj.Black_member(conn,id);
                                    }
                                    else if (date > 7)
                                    {
                                        dbpmj.updateabnormal(conn,id);
                                    }

                                }


                            }
                            else if(bools == 0)
                            {
                                number ='0';
                                write(clnt_sock,(void *)&number, 1);
                            }
                        }
                        else
                            number ='0';
                            write(clnt_sock,(void *)&number, 1);
                    }
                    else
                    {
                        number ='0';
                        write(clnt_sock,(void *)&number, 1);
                    }
                }
                else if(number == '0')
                {
                    sleep(3);
                }
                Membership_renewal(conn,dbpmj);
            }
        }
        void Membership_renewal(std::unique_ptr<sql::Connection> &conn,database dbpmj)
        {
            int Subscription = dbpmj.Subscription_period(conn,id);
            int normal_return = dbpmj.Normal_return(conn,id);
            if(Subscription >= 180 && normal_return >= 10)
            {
                dbpmj.Excellent_member(conn,id);
            }
            int abnormal_return = dbpmj.abnormal_return(conn,id);
            if(abnormal_return >= 3)
            {
                dbpmj.Black_member(conn,id);
                dbpmj.black_date(conn,id);
            }
            if(dbpmj.changemember(conn,id))
            {
                dbpmj.normal_member(conn,id);
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
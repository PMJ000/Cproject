#include <iostream>

#include "mdb.cpp"

using namespace std;

int main() {
    int input_num;
    string id, pw, name, phone_num, addr;
    cout<<"원하시는 번호를 입력해주세요 1. 회원가입 2 로그인 : "<<endl;
    cin>>input_num;

   
    try {
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://localhost:3306/LIBRARY");
        // 연결할 DB를 사용할 유저를 정의
        sql::Properties properties({{"user", "lib_admin"}, {"password", "1234"}});
        // 객체에 값을 통하여 연결을 시도
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
        if (input_num == 1) {
            
            while(1) {
                cout<<"사용하실 Id를 입력해주세요 : "<<endl;
                cin>>id;
                string existingID = checkIDmember(conn, id);
                if (!existingID.empty()) {
                     cout << "중복된 아이디 입니다. 다시 입력해주세요" << endl;
                } else {
                cout << "사용 가능한 아이디입니다." << endl;
                break;
                }
            }
            
            cout<<"사용하실 비밀번호를 입력해주세요 : "<<endl;
            cin>>pw;
            cout<<"이름을 입력해주세요 : "<<endl;
            cin>>name;
            cout<<"핸드폰 번호를 입력해주세요 : "<<endl;
            cin>>phone_num;
            cout<<"주소를 입력해주세요 : "<<endl;
            cin>>addr;
            addMember(conn, id, pw, name, phone_num, addr);
        }
        cout<<"회원가입이 완료되었습니다! 로그인해주세요"<<endl;
    
     
        std::cout << "-------------------------------" << std::endl;


    // 연결 실패시 오류 발생
    } catch(sql::SQLException& e) {
        std::cerr << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
        // 프로그램 비정상 종료
        return 1;
    }

    return 0;
}
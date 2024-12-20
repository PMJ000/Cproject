#include <iostream>

#include "mdb.cpp"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    try {
        // DB연결 객체 생성
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        // 연결할 DB의 특정 IP, DB를 정의
        sql::SQLString url("jdbc:mariadb://localhost:3306/KINGSEO");
        // 연결할 DB를 사용할 유저를 정의
        sql::Properties properties({{"user", "PMJ"}, {"password", "1234"}});
        // 객체에 값을 통하여 연결을 시도
        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

        showTasks(conn);
        addTask(conn, "Tom", 15, false);
        addTask(conn, "None", 0, false);
        updateTask(conn, "Tom", true);
        deleteTask(conn, "None");
        std::cout << "-------------------------------" << std::endl;
        showTasks(conn);


    // 연결 실패시 오류 발생
    } catch(sql::SQLException& e) {
        std::cerr << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
        // 프로그램 비정상 종료
        return 1;
    }

    return 0;
}
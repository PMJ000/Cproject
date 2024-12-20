// Includes
#include <iostream>
#include <mariadb/conncpp.hpp>

// DELETE문 실행 함수(이름을 이용한)
void deleteTask(std::unique_ptr<sql::Connection> &conn, std::string name) {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("delete from tasks where name = ?"));
        // 객체에 값을 전달
        stmnt->setString(1, name);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        stmnt->executeQuery();
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error deleting task: " << e.what() << std::endl;
   }
}

// UPDATE문 실행 함수(이름을 이용하여 성별을 바꿈)
void updateTask(std::unique_ptr<sql::Connection> &conn, std::string name, bool gender) {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("update tasks set gender = ? where name = ?"));
        // 객체에 값을 전달
        stmnt->setBoolean(1, gender);
        stmnt->setString(2, name);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        stmnt->executeQuery();
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error updating task status: " << e.what() << std::endl;
   }
}

// Insert문 실행 함수
// 인자로 값을 넣는다. (id값은 AUTO_INCEREMENT이기 때문에 없어도 상관 없다.)
void addTask(std::unique_ptr<sql::Connection> &conn, std::string name, int age, bool gender) {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into tasks values (default, ?, ?, ?)"));
        // 객체에 값을 전달
        stmnt->setString(1, name);
        stmnt->setInt(2, age);
        stmnt->setBoolean(3, gender);
        // 객체의 내부 함수를 이용하여 쿼리를 실행
        stmnt->executeQuery();
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: " << e.what() << std::endl;
   }
}

// SELECT문 실행 함수
void showTasks(std::unique_ptr<sql::Connection> &conn) {
    try {
        // createStaemet 객체 생성
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // 쿼리를 실행
        sql::ResultSet *res = stmnt->executeQuery("select * from tasks");
        // 반복문을 통해서 내부의 값을 반환
        while (res->next()) {
            std::cout << "id = " << res->getInt(1);
            std::cout << ", name = " << res->getString(2);
            std::cout << ", gender = ";
            if (res->getBoolean(4)) {
                std::cout << "Male" << std::endl;
            } else {
                std::cout << "Female" << std::endl;
            }
                
        }
    // 실패시 오류 메세지 반환
    } catch(sql::SQLException& e){
      std::cerr << "Error selecting tasks: " << e.what() << std::endl;
   }
}

//int main() {
//    try {
//        // DB연결 객체 생성
//        sql::Driver* driver = sql::mariadb::get_driver_instance();
//        // 연결할 DB의 특정 IP, DB를 정의
//        sql::SQLString url("jdbc:mariadb://localhost:3306/test");
//        // 연결할 DB를 사용할 유저를 정의
//        sql::Properties properties({{"user", "operator"}, {"password", "0000"}});
//        // 객체에 값을 통하여 연결을 시도
//        std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
//
//        showTasks(conn);
//        addTask(conn, "Tom", 15, false);
//        addTask(conn, "None", 0, false);
//        updateTask(conn, "Tom", true);
//        deleteTask(conn, "None");
//        std::cout << "-------------------------------" << std::endl;
//        showTasks(conn);
//
//
//    // 연결 실패시 오류 발생
//    } catch(sql::SQLException& e) {
//        std::cerr << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
//        // 프로그램 비정상 종료
//        return 1;
//    }
//
//    return 0;
//}

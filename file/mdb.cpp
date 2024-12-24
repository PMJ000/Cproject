#include <iostream>
#include <mariadb/conncpp.hpp>

// DELETE문 실행 함수(이름을 이용한)
// void deleteTask(std::unique_ptr<sql::Connection> &conn, std::string name) {
//     try {
//         // PreparedStatement 객체 생성
//         std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("delete from tasks where name = ?"));
//         // 객체에 값을 전달
//         stmnt->setString(1, name);
//         // 객체의 내부 함수를 이용하여 쿼리를 실행
//         stmnt->executeQuery();
//     // 실패시 오류 메세지 반환
//     } catch(sql::SQLException& e){
//       std::cerr << "Error deleting task: " << e.what() << std::endl;
//    }
// }

// UPDATE문 실행 함수(이름을 이용하여 성별을 바꿈)
// void updateTask(std::unique_ptr<sql::Connection> &conn, std::string name, bool gender) {
//     try {
//         // PreparedStatement 객체 생성
//         std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("update tasks set gender = ? where name = ?"));
//         // 객체에 값을 전달
//         stmnt->setBoolean(1, gender);
//         stmnt->setString(2, name);
//         // 객체의 내부 함수를 이용하여 쿼리를 실행
//         stmnt->executeQuery();
//     // 실패시 오류 메세지 반환
//     } catch(sql::SQLException& e){
//       std::cerr << "Error updating task status: " << e.what() << std::endl;
//    }
// }

// Insert문 실행 함수
// 인자로 값을 넣는다. (id값은 AUTO_INCEREMENT이기 때문에 없어도 상관 없다.)
void addMember(std::unique_ptr<sql::Connection> &conn, std::string id, std::string pw, std::string name, std::string phone, std::string addr) {
    try {
        // PreparedStatement 객체 생성
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into Member values (?, ?, ?, ?, ?, default)"));
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

// SELECT문 실행 함수 
// 회원정보 보여주는 기능
// void showTasks(std::unique_ptr<sql::Connection> &conn) {
//     try {
//         // createStaemet 객체 생성
//         std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
//         // 쿼리를 실행
//         sql::ResultSet *res = stmnt->executeQuery("select * from Member");
//         // 반복문을 통해서 내부의 값을 반환
    
//         while (res->next()) {
//             std::cout << "id = " << res->getString(1);
//             std::cout << ", name = " << res->getString(2);
//             std::cout << ", gender = ";
//             if (res->getBoolean(4)) {
//                 std::cout << "Male" << std::endl;
//             } else {
//                 std::cout << "Female" << std::endl;
//             }
                
//         }
//     // 실패시 오류 메세지 반환
//     } catch(sql::SQLException& e){
//       std::cerr << "Error selecting tasks: " << e.what() << std::endl;
//    }
// }
//회원가입 id 중복 체크 함수
std::string checkIDmember(std::unique_ptr<sql::Connection> &conn, std::string id) {
    try {
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT M_id FROM Member WHERE M_id = ?"));
        stmnt->setString(1, id);

        std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
        if (res->next()) {
            return std::string(res->getString("M_id")); // 변환 추가
        } else {
            return ""; // 중복되지 않은 경우 빈 문자열 반환
        }

    } catch(sql::SQLException& e) {
        std::cerr << "Error selecting tasks: " << e.what() << std::endl;
        return "";
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
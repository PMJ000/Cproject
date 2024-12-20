CREATE TABLE Student(
    stu_num int unsigned primary key, 
    stu_name varchar(15),
    stu_age tinyint unsigned,
    stu_major varchar(15),
    stu_grade tinyint unsigned,
    domitory bool
);

create table Professor (
    pro_num int unsigned primary key, 
    pro_name varchar(15), 
    pro_age tinyint unsigned,
    pro_major varchar(15),
    pro_roomNum tinyint unsigned
);

create table Class (
    class_num int unsigned primary key,
    class_name varchar(15), 
    class_pro_num int unsigned not null,
    class_room tinyint unsigned,
    class_day varchar(15),
    class_time varchar(15),
    CONSTRAINT FK_pro_num FOREIGN KEY(class_pro_num) REFERENCES Professor(pro_num)
    
);

create table Lesson(
    lesson_stu_num int unsigned,
    lesson_class_num int unsigned,
    CONSTRAINT FK_lsn FOREIGN KEY(lesson_stu_num) REFERENCES Student(stu_num),
    CONSTRAINT FK_lcn FOREIGN KEY(lesson_class_num) REFERENCES Class(class_num)

);

create table Library_info(
    lib_num int primary key, 
    lib_loca varchar(15),
    lib_data_room varchar(15),
    lib_regi_num int,
    lib_name varchar(30),
    lib_author varchar(30),
    lib_publ varchar (30),
    lib_publ_date varchar (10),
    lib_call_num varchar (30),
    lib_data_date varchar (10)
);

LOAD DATA LOCAL INFILE '/home/lms/바탕화면/output.csv' INTO TABLE Library_info CHARACTER SET 'UTF8' COLUMNS TERMINATED BY ',' ENCLOSED BY '"' LINES TERMINATED BY '\n' IGNORE 1 LINES;

create table Member (
    M_id varchar(30) primary key,
    M_pw varchar(30) not null,
    M_name varchar(30) not null,
    M_call_num varchar (30) not null,
    M_addr varchar (100) 
);

create user'lib_admin'@localhost IDENTIFIED BY'1234';
grant all on LIBRARY.*to 'lib_admin'@localhost;
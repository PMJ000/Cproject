create table STUDENT(
    s_id int primary key,
    s_name varchar(30),
    jender bool,
    age int,
    major varchar(15),
    grade int,
    domlitory bool
);
create table PROFESSOR(
    p_id int primary key,
    p_name varchar(30),
    jender bool,
    age int,
    major varchar(15),
    professor_office int
);
create table ATTEND_CLASS(
    attend_id int primary key,
    attend_name varchar(30),
    s_id int,
    p_id int,
    class_room int,
    class_time varchar(10),
    constraint FK_s_id  FOREIGN KEY(s_id) REFERENCES STUDENT(s_id),
    constraint FK_p_id  FOREIGN KEY(p_id) REFERENCES PROFESSOR(p_id)
);

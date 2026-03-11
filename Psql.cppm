///module:
//Description:模块用于辅助程序存储到数据库中以用于持久存储的操作
//this files is build by author: tangshengqing2024051604041 at 2026-03-11 11:56:54
//email address:2052448030@qq.com

module;
#include<libpq-fe.h>//导入postgresql的头文件
export module psql;


import std;


using std::print;
using std::string;
using std::vector;


//常用数据库sql语句

//=----------------------------------------创建表的sql语句

const string creaStudentTable = "create table IF NOT EXISTS student20240511604041 ("
        " id bigint primary key,"
        " name varchar(20) not null,"
        "account varchar(20) not null,"
        "password varchar(20) not null"
")";//学生表

const string creaCourseTable = "create table IF NOT EXISTS course20240511604041("
            "id bigint primary key,"
            "name varchar(20) not null"
            ")";//可选课程表

const string creaStudentCourseTable = "create table IF NOT EXISTS studentcourse20240511604041("
            "sid bigint,"
            "cid bigint ,"
            "grades   int check (grades<100 and grades>0),"
            "primary key(sid,cid)"
    ")";//学生课程关系表

const string createTeachertable = "create table IF NOT EXISTS teacher20240511604041("
        " id bigint primary key,"
        " name varchar(20) not null,"
        "account varchar(20) not null,"
        "password varchar(20) not null"
    ")";//教师表

const string createTeacherCourseTable ="create table IF NOT EXISTS teachercourse20240511604041("
            "tid bigint ,"
            "cid bigint ,"
            "primary key(tid,cid)"
    ")";//教师课程关系表



//------------------------------------学生类sql
const string showStudentTableStr="select * from student ";//sql查学生表

const string showStudentTableStrOrdeBy="select * from Student Order BY id ASC";//正序查询学生表

//------------------------------------教师类sql
const string showTeacherTableStr="select * from teacher ";//sql查教师

//-------------------------------------课程类sql
const string showCourseTableStr="select * from course ";//sql查课程

//-------------------------------------学生选课课程关系sql

const string showStudentRollCourseTableStr="select name from course where id in (select course_id from studentcourse where student_id = ";//查看关系表
const string deleteStudentControlCourseTableStr="delete from studentcourse where ";//删除选课的拼接语句
const string insertStudentControlCourseTableStr="insert into studentcourse (course_id,student_id) values ";//选课的拼接语句



//------------------------------------教师学生关系sql

const string showCourseHaveStudentTableStr="select * from teacherstudent";







//--------------------------------------------------------------接口类声明--------------------------------------------------------------------------------------------
//创建接口类
export class Psql{


public:
    //创建连接，反馈连接
    Psql();

    static Psql& getControlsql();//获取静态管理对象

    void selectTable(const char *input,vector<string> &fromSql);//查的接口
    void insertTable(const string &table,const string &date1,const string &date2);//插入接口
    void insertTeacherTable(const string &table,const string &date1,const string &date2,const string &date3);//插入接口2

    void InitleTable();//初始化创建表的操作，在计算机中创建表
    void creatTable(string sql);
private:
    const char *constr;//连接到的口
    PGconn* conclass;//连接端口对象

};

//------------------------------------------------------------------数据库和程序的命令接口实现----------------------------------------------

void Psql::creatTable(string sql){
    // 2. 执行 SQL
    PGresult* res = PQexec(conclass, sql.c_str());

    // 3. 获取执行状态
    ExecStatusType status = PQresultStatus(res);

    // 4. 判断是否成功
    if (status == PGRES_COMMAND_OK) {
        // CREATE TABLE 成功时返回 COMMAND_OK
        print("表创建成功 (或已存在)\n");
    }



}





//初始化连接
Psql::Psql():constr("host=localhost dbname=postgres user=postgres password= port=5432"),conclass(nullptr){
    conclass=PQconnectdb(constr);//连接到数据库，用管理员权限连接

if (PQstatus(conclass) == CONNECTION_OK) {
    printf("连接成功！\n");
    printf("数据库: %s\n", PQdb(conclass));
    printf("用户: %s\n", PQuser(conclass));
    printf("主机: %s\n", PQhost(conclass));
    printf("端口: %s\n", PQport(conclass));
} else {
    printf("连接失败: %s\n", PQerrorMessage(conclass));
}






}

Psql& Psql::getControlsql(){
    static Psql ps;

    return ps;
}//获取静态管理对象


//查询函数接口
void Psql::selectTable(const char *input,vector<string> &fromSql){
    PGresult *res=PQexec(conclass,input);//查询获取对象指针

    //查询成功则会输出信息
    if(PQresultStatus(res)==PGRES_TUPLES_OK)
    {
        int row=PQntuples(res);
        int cols = PQnfields(res);

        for(int i=0;i<row;i++){
            string aLine = {};
            for(int j=0;j<cols;j++)
            {
                aLine += " ";
                const char *va = PQgetvalue(res, i, j); //获取i行0列的信息
                aLine += va;//添加到一行中的string对象中
                //print("\t{} ",va);
            }
            //print("{}\n", aLine);
            fromSql.push_back(aLine);//将多行导入到vector<string>中，然后准备处理
        }

    }else{
       print("Query failed: {}\n", PQresultErrorMessage(res));//打印具体错误
    }


}


//控制函数接口--增-插入
void Psql::insertTable(const string &table,const string &date1,const string &date2){

     string isExist;
    if(table!="teachercourse"&&table!="studentcourse")//studentcourse和teachercourse的属性特殊性，单独分类
    {
        isExist = "select count(*) from " + table + " where id = " +date1;//先查看存在不再插入


    }else if(table=="teachercourse"){
         isExist = "select count(*) from " + table + " where teacher_id = " +date1+" AND course_id = "+date2;//先查看存在不再插入
    }else if(table=="studentcourse")
    {
         isExist = "select count(*) from " + table + " where student_id = " +date1+" AND course_id =" +date2;//先查看存在不再插入

    }




     PGresult *res=PQexec(conclass,isExist.c_str());//查询获取对象指针

     int count = std::atoi(PQgetvalue(res,0,0));

     //print("{}\n",isExist);

    if(count ==1)
    {
        print("已经插入到表\n",PQcmdTuples(res));
    }else{

        //不存在，插入
         string insert;
        if(table =="student")
        {
            insert = "INSERT INTO student (id, name) VALUES ("+date1+",'"+date2+"')";

        }else if(table=="course")
        {
            insert = "INSERT INTO course (id, name) VALUES ("+date1+",'"+date2+"')";

        }else if(table=="studentcourse")
        {
            insert = "INSERT INTO studentcourse (student_id,course_id) VALUES ("+date1+","+date2+")";

        }else if(table=="teachercourse")
        {
            insert = "INSERT INTO teachercourse (teacher_id,course_id) VALUES ("+date1+","+date2+")";

        }
      //print("{}\n",insert);
        PGresult *res1=PQexec(conclass,insert.c_str());

        if(PQresultStatus(res1)==PGRES_COMMAND_OK)
        {
            print("---sucessfully {}\n",PQcmdTuples(res));
        }else{
            print("insert {} error\n",table);
        }


    }
}//插入接口

void Psql::insertTeacherTable(const string &table,const string &date1,const string &date2,const string &date3){
    const string &findteacher="select count(*) from teacher where id = "+date1;

      PGresult *res=PQexec(conclass,findteacher.c_str());//查询获取对象指针

    int count = std::atoi(PQgetvalue(res,0,0));

    if(count ==1)
    {
        print("已经插入到表\n",PQcmdTuples(res));
    }else{
        const string &inserts="insert into teacher (id,name,course) VALUES ("+date1+", '"+date2+"','"+date3+"')";
        PGresult *isinsert = PQexec(conclass,inserts.c_str());

        //print("{}",inserts);

        if(PQresultStatus(isinsert)==PGRES_COMMAND_OK)
        {
            print("---sucessfully {}\n",PQcmdTuples(isinsert));
        }else{
            print("insert {} error\n",table);
        }
    }



}

//初始化创建表的操作，在计算机中创建表


void Psql::InitleTable(){
    const string studentTable="student";
    const string courseTable="course";
    const string studentCourseTable="studentcourse";


    const string teacherTable="teacher";
    const string teacherCourseTable="teachercourse";

    creatTable(creaStudentTable);
    creatTable(creaCourseTable);
    creatTable(creaStudentCourseTable);
    creatTable(createTeachertable);
    creatTable(createTeacherCourseTable);

 }


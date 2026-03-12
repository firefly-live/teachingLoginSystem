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
            "grades   int,"
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



//--------------------------------------------------------------接口类声明--------------------------------------------------------------------------------------------
//创建接口类
export class Psql{


public:
    //创建连接，反馈连接
    Psql();

    static Psql& getControlsql();//获取静态管理对象

    void itemInintilize(const char *input,vector<string> &fromSql);//协助初始化

    void insertTableStudentCourse(const string &table,const string &date1,const string &date2);//插入接口
    void updateTableStudentGrades(const string &table, const string &date1, const string &date2,const string& date3);//插入接口2,用于3参数实现

    void deleteCourseeStudent(const string &table, const string &Sid, const string &Cid);

    void InserteInformationToSystem();


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




void Psql::deleteCourseeStudent(const string &table, const string &Sid, const string &Cid){



    string deleteARow = "delete from studentcourse20240511604041 where sid = "+ Sid +" And  cid = "+Cid;//重复性检测，如果有了，那就忽略

    //print("{}\n",insert);
    PGresult *res1=PQexec(conclass,deleteARow.c_str());

    if(PQresultStatus(res1)==PGRES_COMMAND_OK)//执行成功，存在行会忽略的
    {
        print(" 从学生课程表同步删除成功--sucessfully {}\n",PQcmdTuples(res1));
    }else{
        print("delete {} error\n",PQerrorMessage(conclass));
    }


}





//初始化连接
Psql::Psql():constr("host=localhost dbname=postgres user=postgres password= port=5432"),conclass(nullptr){
    conclass=PQconnectdb(constr);//连接到数据库，用管理员权限连接

if (PQstatus(conclass) == CONNECTION_OK) {
    print("连接成功！\n");
    print("数据库: {}\n", PQdb(conclass));
    print("用户: {}\n", PQuser(conclass));
    print("主机: {}\n", PQhost(conclass));
    print("端口: {}\n", PQport(conclass));
} else {
    print("连接失败: {}\n", PQerrorMessage(conclass));
}


}

Psql& Psql::getControlsql(){
    static Psql ps;

    return ps;
}//获取静态管理对象


//辅助CenterControl：：initilize函数进行初始化
void Psql::itemInintilize(const char *input,vector<string> &fromSql){
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
void Psql::insertTableStudentCourse(const string &table,const string &date1,const string &date2){

       string insert = "INSERT INTO studentcourse20240511604041 (sid,cid) VALUES ("+date1+","+date2+")" + "ON CONFLICT (sid, cid) DO NOTHING;";//重复性检测，如果有了，那就忽略

      //print("{}\n",insert);
        PGresult *res1=PQexec(conclass,insert.c_str());

        if(PQresultStatus(res1)==PGRES_COMMAND_OK)//执行成功，存在行会忽略的
        {
            print("插入到学生课程表成功或者已经存在---successfully{}\n",PQcmdTuples(res1));
        }else{
            print("insert {} error\n",table);
        }

}//插入接口



void Psql::updateTableStudentGrades(const string &table, const string &date1, const string &date2, const string &date3)
{
    string insert{};
    if (table == "studentcourse20240511604041") {
        insert = "update studentcourse20240511604041 set grades= " + date3 + " where sid = " + date1
                 + " And  cid = " + date2;
    } //更新分数
    //print("{}\n",insert);
    PGresult *res1 = PQexec(conclass, insert.c_str());

    if (PQresultStatus(res1) == PGRES_COMMAND_OK) {
        print("更新学生课程分数---successfully {}\n", PQcmdTuples(res1));
    } else {
        fprintf(stderr, "数据库操作失败: %s\n", PQerrorMessage(conclass));

    } //插入接口
}

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

    InserteInformationToSystem();//插入到对象表


 }

 //将这些对象分别插入到表中，以便于读取,也可自定义
 void Psql::InserteInformationToSystem()
 {
     const string insertStudentSql = "INSERT INTO student20240511604041 (id, name, account, password) VALUES "
                                     "(2001, 'Qiong1', 'Qiong1', '2'),"
                                     "(2002, 'Qiong2', 'Qiong2', '2'),"
                                     "(2003, 'Qiong3', 'Qiong3', '2'),"
                                     "(2004, 'Qiong4', 'Qiong4', '2'),"
                                     "(2005, 'Qiong5', 'Qiong5', '2') "
                                     "ON CONFLICT (id) DO NOTHING;";

     // 教师表插入语句
     const string insertTeacherSql = "INSERT INTO teacher20240511604041 (id, name, account, password) VALUES "
                                     "(3001, 'Ji1', 'Ji1', '3'),"
                                     "(3002, 'Ji2', 'Ji2', '3'),"
                                     "(3003, 'Ji3', 'Ji3', '3'),"
                                     "(3004, 'Ji4', 'Ji4', '3'),"
                                     "(3005, 'Ji5', 'Ji5', '3') "
                                     "ON CONFLICT (id) DO NOTHING;";

     // 课程表插入语句
     const string insertCourseSql = "INSERT INTO course20240511604041 (id, name) VALUES "
                                    "(1001, 'math'),"
                                    "(1002, 'C++'),"
                                    "(1003, 'data_structure'),"
                                    "(1004, 'database'),"
                                    "(1005, 'operating system') "
                                    "ON CONFLICT (id) DO NOTHING;";

     // 教师课程关系表插入语句
     const string insertTeacherCourseSql = "INSERT INTO teachercourse20240511604041 (tid, cid) VALUES "
                                           "(3001, 1001),"
                                           "(3002, 1002),"
                                           "(3003, 1003),"
                                           "(3004, 1004),"
                                           "(3005, 1005) "
                                           "ON CONFLICT (tid, cid) DO NOTHING;";


     PGresult *res = PQexec(conclass, insertStudentSql.c_str());
     if (PQresultStatus(res) == PGRES_COMMAND_OK) {
         print("✅学生表初始化成功\n");
     } else {
          fprintf(stderr, "学生表 数据库操作失败: %s\n", PQerrorMessage(conclass));
     }
     PQclear(res);

     // 执行教师表插入
     res = PQexec(conclass, insertTeacherSql.c_str());
     if (PQresultStatus(res) == PGRES_COMMAND_OK) {
         print("✅ 教师表初始化成功\n");
     } else {
          fprintf(stderr, "教师表 数据库操作失败: %s\n", PQerrorMessage(conclass));
     }
     PQclear(res);

     // 执行课程表插入
     res = PQexec(conclass, insertCourseSql.c_str());
     if (PQresultStatus(res) == PGRES_COMMAND_OK) {
         print("✅ 课程表初始化成功\n");
     } else {
         fprintf(stderr, " 课程表数据库操作失败: %s\n", PQerrorMessage(conclass));
     }
     PQclear(res);

     // 执行教师课程关系表插入
     res = PQexec(conclass, insertTeacherCourseSql.c_str());
     if (PQresultStatus(res) == PGRES_COMMAND_OK) {
         print("✅ 教师课程关系表初始化成功\n");
     } else {
         fprintf(stderr, "教师课程关系表 数据库操作失败: %s\n", PQerrorMessage(conclass));
     }
     PQclear(res);



 }



///module: centrolControl
//Description:用于控制Student和Course的交互，Teacher和Student的交互，Student和Teacher，实现实例化对像的逻辑控制
//实现整个程序的逻辑运行框架，交互三类对象的实体数据
/*this files is build by author: tangshengqing2024051604041 at 2026-03-08*/
//email address:2052448030@qq.com
module;
#include <unistd.h>
#include <cstdio>
export module Objects:CenterControl;

import std;

import :Student;
import :Course;
import :Teacher;
import psql;
using std::cin;
using std::string;
using std::vector;
using std::stringstream;

export class CenterControl
{
public:
    //系统初始优化相关
    void initilize();                         //初始化
    static CenterControl getSystem();         //传出静态的管理对象
    void loginMethod();                       //选择登陆方式
    void loginStudent(Student* student);      //选择学生方式
    void loginTeacher(Teacher* teacher);      //选择老师登陆方式
    void teacherBindCourse(int TId, int cId); //老师绑定课程
    void saveEndIntoSql();

    void userAccTeacher();//教师账号密码登录
    void userAccStudent();//学生账号密码登录

    //学生
    void showCourseAll(); //展示所有课程+教师
    void showCourseOwnStudent(Student* student);
    void studentRollInCourse(Student* student);    //学生注册课程
    void studentNotRollInCourse(Student* student); //学生取消课程
    void showAllGradeOwnStudent(Student* student);//展示当前学生的所有分数

    //教师功能
    void showCourseOwn(Teacher* teacher); //展示所有课程+教师
    void scoreGrades(Teacher *teacher);   //目标查找老师，课程，学生对象，然后调用打分程序 //打分s
    void showStudentGrades(Teacher *teacher);



    //测试功能函数用于辅助其他1函数逻辑判断
    void studentRollInCourse(int Sid,int Cid);

private:
    vector<Student*> students; //存储学生类
    vector<Course*> courses;   //存储课程类
    vector<Teacher*> teachers; //存储老师类
    Psql ps;//数据库管理
};

//测试功能函数用于辅助其他1函数逻辑判断
void CenterControl::studentRollInCourse(int Sid, int Cid)
{
    for (auto &stu : students) {
        if(stu->hasId(Sid))
        {
            for(auto &cou:courses)
            {
                if(cou->hasId(Cid))
                {
                   stu->joinCourse(cou); //学生对象-》加入课程会判断是否已经有该对象
                    cou->joinStudents(stu); //课程对像->加入学生//会自动判断已经有无这个对象
                }
            }
        }
    }

}


//系统结束保存到sql
void CenterControl::saveEndIntoSql()
{
    print("正在保存信息到数据库中.....\n");


}






//系统初始优化相关
void CenterControl::initilize()
{
    //数据库初始化
    ps.InitleTable();

    print("正在从数据库中读取信息.....\n");
    vector<string> getAllfromSql; //存储数据库当中的字符串，一行作为一个vector的子对象


    //通过读取数据表自动化存储数据表的学生信息------读取数据表学生信息并且创建相应对象
    ps.selectTable("select * from student20240511604041", getAllfromSql); //将数据库的这些字符串存储到哦容器中
    for (auto aLine : getAllfromSql) {
        stringstream ss(aLine); //将获取的字符串作为了流依次赋值
        int Sid;
        string name, account, password;
        ss >> Sid >> name >> account >> password; //将获取到的包含信息的字符串依次赋值给对应类型
        students.push_back(new Student(Sid, name, account, password)); //将得到的信息依次构建到student容器中
        //print("{} {} {} {}\n",Sid,name,account,password);
    }

    getAllfromSql.clear(); //清除之前存储的信息

    //通过读取数据表自动化存储数据表的教师信息------读取数据表教师信息并且创建相应对象
    ps.selectTable("select * from teacher20240511604041", getAllfromSql); //将数据库的这些字符串存储到哦容器中
    for (auto aLine : getAllfromSql) {
        stringstream ss(aLine); //将获取的字符串作为了流依次赋值
        int Tid;
        string name, account, password;
        ss >> Tid >> name >> account >> password; //将获取到的包含信息的字符串依次赋值给对应类型
        teachers.push_back(new Teacher(Tid, name, account, password)); //将得到的信息依次构建到student容器中
        //print("{} {} {} {}\n",Tid,name,account,password);
    }

    getAllfromSql.clear(); //清除之前存储的信息

    //通过读取数据表自动化读取数据表的教师信息------读取数据表课程信息并且创建相应对象
    ps.selectTable("select * from course20240511604041", getAllfromSql); //将数据库的这些字符串存储到哦容器中
    for (auto aLine : getAllfromSql) {
        stringstream ss(aLine); //将获取的字符串作为了流依次赋值
        int Cid;
        string name;
        ss >> Cid >> name; //将获取到的包含信息的字符串依次赋值给对应类型
        courses.push_back(new Course(Cid, name)); //将得到的信息依次构建到student容器中
        //print("{} {}\n",Cid,name);
    }



    getAllfromSql.clear(); //清除之前存储的信息

    //通过读取数据表自动化读取数据表的教师课程信息------读取数据表课程信息并且调用teacherBindCourse();绑定教师和课程函数
    ps.selectTable("select * from teachercourse20240511604041", getAllfromSql); //将数据库的这些字符串存储到哦容器中
    for (auto aLine : getAllfromSql) {
        stringstream ss(aLine); //将获取的字符串作为了流依次赋值
        int Tid, Cid;
        ss >> Tid >> Cid; //将获取到的包含信息的字符串依次赋值给对应类型
        teacherBindCourse(Tid, Cid); //读取course和teacher表依次绑定课程
        //print("{} {}\n", Tid, Cid);
    }



    getAllfromSql.clear(); //清除之前存储的信息

    //通过读取数据表自动化读取数据表的学生课程信息------调用打分你程序，给对象赋值分数
    ps.selectTable("select * from studentcourse20240511604041", getAllfromSql); //将数据库的这些字符串存储到哦容器中
    for (auto aLine : getAllfromSql) {
        stringstream ss(aLine); //将获取的字符串作为了流依次赋值
        int Sid, Cid, grades;
        ss >> Sid >> Cid >> grades; //将获取到的包含信息的字符串依次赋值给对应类型
        for (auto stu : students) {
            if (stu->hasId(Sid)) {
                stu->scoreGrades(Cid, grades);//这里的Cid导入后进入执行函数打分操作，该接口也是教师打分函数的赋值主接口
                studentRollInCourse(Sid,Cid);//会自动绑定学生和课程信息
                break;//找到目标后自动退出，进行查看下一行的数据
            }

        }//遍历学生容器，找到目标对象，然后将分数依次赋值

        print("{} {} {}\n",Sid,Cid,grades);
    }
    //1开头：学生id
    //2开头：课程id
    //3开头：老师id
    //students.push_back(new Student(2001, "Qiong1","Qiong1","2")); //登入学生信息
    //students.push_back(new Student(2002, "Qiong2","Qiong2","2")); //登入学生信息
    //students.push_back(new Student(2003, "Qiong3","Qiong3","2")); //登入学生信息
    //students.push_back(new Student(2004, "Qiong4","Qiong4","2")); //登入学生信息

    //courses.push_back(new Course(1001, "math"));
    //courses.push_back(new Course(1002, "C++"));
    //courses.push_back(new Course(1003, "data_structure"));

    //teachers.push_back(new Teacher(3001, "Ji","Ji","3"));
    //teachers.push_back(new Teacher(3002, "wa","Wa","3"));

    //CenterControl::teacherBindCourse(3001, 1001);

    //CenterControl::teacherBindCourse(3002, 1003);


    print("读取成功\n");
    print("按回车键继续运行程序....\n");
    getchar();

    //测试函数，直接加入到里面，课程加入学生，学生加入课程，测试教师打分
    //studentRollInCourse(2001,1001);
    //studentRollInCourse(2001,1003);
    //studentRollInCourse(2003,1001);
    //studentRollInCourse(2004,1001);


} //初始化
CenterControl CenterControl::getSystem()
{
    static CenterControl LoginSys;
    LoginSys.initilize();
    return LoginSys;
} //传出静态的管理对象
void CenterControl::loginMethod()
{
    //后续在这可以添加登陆验证等方法
    char c;
    Student* stu = students[0]; //测试
    Teacher* tea = teachers[0]; //测试登陆
    bool running = true; //控制running
    string str;
    while (running) {
        std::cout << "\033[2J\033[1;1H"; // 清屏操作
        print("请选择你的登陆方式\n---1:选择学生登陆\n---2:选择教师登陆\n---3:退出系统\n");
        cin >> c;
        switch (c) {
        case '1':
            userAccStudent();
            print("按回车键继续....\n");
            getchar();
            getchar();
            break;
        case '2':
            userAccTeacher();
            print("按回车键继续....\n");
            getchar();
            getchar();
            break;
        case '3':
            running = false;
            break;
        default: {
            print("输入错误，请重新输入\n");
            getline(cin, str); //清除乱输入的
        }

        break;
        }
    }
    saveEndIntoSql();//保存
    print("感谢使用，按任意键推出\n");
    cin.get();
} //选择登陆方式
void CenterControl::loginStudent(Student* student)
{
    string str; //清除错误输入
    char c;
    bool running = true;
    char middle;
    while (running) {
        std::cout << "\033[2J\033[1;1H"; // 清屏操作
        print("----学生登陆----\n选择功能\n---1:查看已经选择过的课程\n---2:选课程\n---3退选课程\n---4:"
              "查看自己的选课的成绩\n---5:退出学生操作系统\n");
        cin >> c;
        switch (c) {
        case '1': {
            showCourseOwnStudent(student);
            print("按回车键继续....\n");
            getchar();
            getchar();
        } break;
        case '2': {
            studentRollInCourse(student);
            print("按回车键继续....\n");
            getchar();
            getchar();
        }
            print("test\n");
            break;
        case '3': {
            studentNotRollInCourse(student);
            print("按回车键继续....\n");
            getchar();
            getchar();
        }
            print("test\n");
            break;
        case '4': {
            showAllGradeOwnStudent(student);
            print("按回车键继续....\n");
            getchar();
            getchar();
        }

        break;
        case '5':
            running = false;
            break;
        default: {
            print("输入错误，请重新输入\n");
            getline(cin, str); //清除乱输入的
        } break;
        }
    }

} //选择教师方式
void CenterControl::loginTeacher(Teacher* teacher)
{
    string str; //清除错误输入
    char c;
    bool running = true;
    while (running) {
        std::cout << "\033[2J\033[1;1H"; // 清屏操作
        print("----教师登陆----\n选择功能\n---1:查看自己的课程\n---2:给学生成绩打分\n---3:查看学生成绩\n---4:"
              "退出教师操作系统\n");
        cin >> c;
        switch (c) {
        case '1': {
            showCourseOwn(teacher);
            print("按回车键继续....\n");
            getchar();
            getchar();

        } break;
        case '2': {
            scoreGrades(teacher);
            print("按回车键继续....\n");
            getchar();
            getchar();
        } break;
        case '3': {
            showStudentGrades(teacher);
            print("按回车键继续....\n");
            getchar();
            getchar();
        }
            break;
        case '4':
            running = false;
            break;
        default: {
            print("输入错误，请重新输入\n");
            getline(cin, str); //清除乱输入的
        } break;
        }
    }

} //选择教师方式

void CenterControl::teacherBindCourse(int TId, int cId)
{
    for (auto &tea : teachers) {
        if (tea->hasId(TId)) {
            for (auto &cou : courses) {
                if (cou->hasId(cId)) {
                    tea->bindCourse(cou); //老师绑定课程
                }
            }
        }
    }

} //老师绑定课程


void CenterControl::userAccTeacher()
{
    string Account;
    string Password;
    print("请输入账号...：");
    cin >> Account;
    print("请输入密码...:");
    cin >> Password;
    for (auto &tea : teachers) {
        if (tea->userAccountChargeIsRight(Account, Password)) {
            print("登录教师系统成功\n");
            loginTeacher(tea);
            return;
        }

    }
    print("输入账号或密码错误，请检查\n");


}//教师账号密码登录
void CenterControl::userAccStudent(){
    string Account;
    string Password;
    print("请输入账号...：");
    cin >> Account;
    print("请输入密码...:");
    cin >> Password;
    for (auto &stu :students) {
        if (stu->userAccountChargeIsRight(Account, Password)) {
            print("登录学生系统成功\n");
            loginStudent(stu);
            return;
        }

    }
    print("输入账号或密码错误，请检查\n");

}//学生账号密码登录




 //-------学生


void CenterControl::showCourseAll()
{
    print("教师\t课程\t课程id号\n");
    for (auto &tea : teachers) {
        tea->showCourse();
    }

} //展示所有课程+教师
void CenterControl::showCourseOwnStudent(Student* student)
{
    print("-------已经选择的课程有 ------ \n");
    student->showCourse();
    print("\n");

} //展示学生已经选择的课程信息
void CenterControl::studentRollInCourse(Student* student)
{
    showCourseAll();
    print("\n请输入课程id号.....\n");

    int Cid = 0;
    cin >> Cid;

    //遍历容器查找课程
    for (auto &cour : courses) {
        if (cour->hasId(Cid)) {
            student->joinCourse(cour); //学生对象-》加入课程
            cour->joinStudents(student); //课程对像->加入学生

            return;
        }
    }
    print("添加专业课失败，请检查输入课程id号是否正确\n");

} //学生注册课程
void CenterControl::studentNotRollInCourse(Student* student)
{
    showCourseOwnStudent(student);
    print("\n请要退选的输入课程id号.....\n");

    int Cid = 0;
    cin >> Cid;

    //遍历容器查找课程
    for (auto &cour : courses) {
        if (cour->hasId(Cid)) {
            student->popCourse(cour); //pop出去自己选的课程
            cour->popStudent(student); //课程pop学生对象
            return;
        }
    }
    print("退选专业课失败，请检查输入课程id号是否正确或者是否已选\n");

} //学生取消课程
void CenterControl::showAllGradeOwnStudent(Student* student){
    student->showMyAllGrade();
}//展示当前学生的所有分数





//----------------------------------------------------教师


void CenterControl::showCourseOwn(Teacher* teacher)
{
    print("我   教授课程   教授课程id\n");
    teacher->showCourse();
} //展示所有课程+教师
void CenterControl::scoreGrades(Teacher* teacher)
{
    //循环打分，输入2退出
    bool running = true;
    // --根据teacher->绑定的course->再对学生打分->学生->导入课程和分数
    char c;
    while (running) {
        while (getchar() != '\n');
        teacher->scoreGrades();
        print("输入1以退出打分，输入其他继续打分\n");
        cin >> c;
        if (c == '1') break;
    }

} //目标查找老师，课程，学生对象，然后调用打分程序 //打分
void CenterControl::showStudentGrades(Teacher* teacher)
{
    teacher->showStudentGrades();
} //查看学生的成绩






//------------------------------------Student访问course所需成员实现函数
void Student::showCourse()
{
    for (auto &cou : courses) {
        print("{}\n", cou->showInformation());
    }
}

void Student::showMyGrade(int Cid)
{
    //print("showMyGrade(int Cid)\n");
    for (auto &cou : Grades) // 遍历一系列课程id号，找到目标课程，然后输出分数
    {
        //print("showMyGrade(int Cid)\n");

        if (cou.first == Cid) {
            print("\t\t  {}  {}\n", name, cou.second); //找到目标课程，输出课程的分数
        }
    }
} //3：查看自己的对应课成绩



void Student::showMyAllGrade()
{
    //for (auto &grade : Grades) {
    //    print("\t{} {}\n", grade.first, grade.second); //接着输出课程对于的分数，break取消查找，准备输出下一个课程
    //}
    //print("\n\n");//测试


    for (auto &grade : Grades) {
        for (auto &cou : courses) {
            if( cou->useIdshowName(grade.first))//通过id查找课程名字然后输出但是要检测course容器中的id是否对应，否则就会多输出
                    print("\t{}\n", grade.second);//接着输出课程对于的分数，break取消查找，准备输出下一个课程
        }
    }
    print("\n");
}



//------------------------------------------course访问Student所需成员实现函数
void Course::showStudentGrades()
{
      //print("showStudentGrades()\n");
    for (auto &stu : students) {
        stu->showMyGrade(Cid);//传入当前课程号的id,用于学生进行查看自己的该课程的1成绩
    }
}//依次调用选了该课的学生，依次展示学生分数


void Course::showStudent()
{
    for (auto &stu : students) {
        print("\t\t\t{}\n", stu->showInformaton());
    }

} //展示选了课程的学生
void Course::scoreGrades()
{
    print("请输入要打分的目标学生id号\n");
    int Sid;
    cin >> Sid;
    for (auto &stu : students) {
        if (stu->hasId(Sid)) {
             int score=101;
            while(score>100||score<0)//检测输入分数1-100
            {
                print("请输入分数-0--100\n");
                cin >> score;
            }
            stu->scoreGrades(Cid, score);
            return;//传入自身的课程号和打的分数--pair容器中，然后push到容器中
        }
    }
}//由老师类传入，然后调用studet的打分，且调入自己的课程名字






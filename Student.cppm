//module:      Student.cppm
//Description: 作为Student的实例化模块，继承User类，用于实现老师对象的逻辑操作
/*this files is build by author: tangshengqing2024051604041 at 2026-03-08*/
//email address:2052448030@qq.com
export module Objects:Student;
import std;
import :User;
using std::string;
using std::vector;
using std::pair;
using std::print;
class Course;


export class Student:public User{

public:
    Student(){}
    Student(int Sid, string name)
        : Sid(Sid), name(name){}
    void showCourse(); //--对于学生来说，查看可选课程，对于老师来说，查看自己的教授课
    void operatingCourse();//2：选课--CRUD
    void showMyGrade();     //3：查看自己的选课成绩
    void scoreGrades(int Cid,int score);//由课程传入，课程的名字和老师选择打分传入


    //常用逻辑判断
    bool hasId();//查看是否有这个学生
    void joinCourse(Course* course);//添加课程信息
    void showInformaton();//展示学生信息

private:
    int Sid;
    string name;
    vector<Course*> courses;//存储选择的课程
    vector<pair<string, int>> Grades;//记录一系列课程的成绩

};

void Student::showCourse(){

    print("helllo\n");

}

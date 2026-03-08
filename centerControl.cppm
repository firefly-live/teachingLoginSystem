///module: centrolControl
//Description:用于控制Student和Course的交互，Teacher和Student的交互，Student和Teacher，实现实例化对像的逻辑控制
            //实现整个程序的逻辑运行框架，交互三类对象的实体数据
/*this files is build by author: tangshengqing2024051604041 at 2026-03-08*/
//email address:2052448030@qq.com
export module Objects:CenterControl;
import std;
import :Student;
using std::string;
using std::vector;


class CenterControl{
public:
         static CenterControl system();//传出静态的管理对象
         void initilize();//初始化
         void studentRollInCourse(int sId,int cId);//学生注册课程
         void studentNotRollInCourse(int sId,int cId);//学生取消课程


         void scoreGrades(int sId,int cId);//目标查找老师，课程，学生对象，然后调用打分程序 //打分
         void showStudentGrades(int sId,int cId);//查看学生的成绩
         void loginMethod();//选择登陆方式
         void loginStudent(Student* student);//选择学生方式
         void loginTeacher(Student* teacher);//选择老师登陆方式
private:
         vector<Student> *students;//存储学生类
         vector<Course> *courses;//存储课程类
         vector<Course> *teacher;//存储老师类



};

///module: centrolControl
//Description:用于控制Student和Course的交互，Teacher和Student的交互，Student和Teacher，实现实例化对像的逻辑控制
//实现整个程序的逻辑运行框架，交互三类对象的实体数据
/*this files is build by author: tangshengqing2024051604041 at 2026-03-08*/
//email address:2052448030@qq.com
module;
#include <unistd.h>
#include<cstdio>
export module Objects:CenterControl;

import std;

import :Student;
import :Course;
import :Teacher;
using std::string;
using std::vector;
using std::cin;


export class CenterControl{
public:
            static CenterControl getSystem();//传出静态的管理对象
            void initilize();//初始化
            void studentRollInCourse(int sId,int cId);//学生注册课程
            void studentNotRollInCourse(int sId,int cId);//学生取消课程

            void showCourseAll();//展示所有课程+教师
            void showCourseOwn(Teacher *teacher);//展示所有课程+教师

            void teacherBindCourse(int TId,int cId);//老师绑定课程


            void scoreGrades(int sId,int cId);//目标查找老师，课程，学生对象，然后调用打分程序 //打分
            void showStudentGrades(int sId,int cId);//查看学生的成绩

            void loginMethod();//选择登陆方式
            void loginStudent(Student* student);//选择学生方式
            void loginTeacher(Teacher* teacher);//选择老师登陆方式
private:
            vector<Student*> students;//存储学生类
            vector<Course*> courses;//存储课程类
            vector<Teacher*> teachers;//存储老师类



};



void CenterControl::showCourseAll(){

            print("教师\t课程\t课程id号\n");
            for(auto tea:teachers)
            {
                        tea->showCourse();

            }

}//展示所有课程+教师

void CenterControl::showCourseOwn(Teacher *teacher){
            print("我   教授课程   教授课程id\n");
            teacher->showCourse();
}//展示所有课程+教师




CenterControl CenterControl:: getSystem(){
            static CenterControl LoginSys;
            LoginSys.initilize();
            return LoginSys;
}//传出静态的管理对象
void CenterControl::initilize(){
            //1开头：学生id
            //2开头：课程id
            //3开头：老师id
            students.push_back(new Student(2001,"Qiong"));//登入学生信息

            courses.push_back(new Course(1001,"math"));
            courses.push_back(new Course(1002,"C++"));
            courses.push_back(new Course(1003,"data_structure"));

            teachers.push_back(new Teacher(3001,"JiZi"));
            teachers.push_back(new Teacher(3002,"waerte"));

            CenterControl::teacherBindCourse(3001,1001);
            CenterControl::teacherBindCourse(3001,1002);

             CenterControl::teacherBindCourse(3002,1003);


}
void CenterControl::studentRollInCourse(int sId,int cId){



}//学生注册课程
void CenterControl::studentNotRollInCourse(int sId,int cId){



}//学生取消课程


void CenterControl::teacherBindCourse(int TId,int cId){
            for(auto tea: teachers)
            {
                        if(tea->hasId(TId))
                        {
                                    for(auto cou: courses)
                                    {
                                                if(cou->hasId(cId))
                                                {
                                                            tea->bindCourse(cou);//老师绑定课程

                                                }

                                    }

                        }
            }



}//老师绑定课程






void CenterControl::scoreGrades(int sId,int cId){



}//目标查找老师，课程，学生对象，然后调用打分程序 //打分
void CenterControl::showStudentGrades(int sId,int cId){



}//查看学生的成绩
void CenterControl::loginMethod(){
            //后续在这可以添加登陆验证等方法
            char c;
            Student* stu=students[0];//测试
            Teacher* tea=teachers[0];//测试登陆
            bool running=true;//控制running
            string str;
            while(running)
            {

                        std::cout << "\033[2J\033[1;1H";// 清屏操作
                        print("请选择你的登陆方式\n---1:选择学生登陆\n---2:选择教师登陆\n---3:退出系统\n");
                        cin>>c;
                        switch (c) {
                        case '1':
                                    loginStudent(stu);

                                    break;
                        case '2':
                                    loginTeacher(tea);

                                    break;
                        case '3':
                                    running=false;
                                    break;
                        default:{
                                    print("输入错误，请重新输入\n");
                                    getline(cin, str);//清除乱输入的
                        }



                                    break;
                        }
            }
            print("感谢使用，按任意键推出\n");
            cin.get();
}//选择登陆方式
void CenterControl::loginStudent(Student* student){
            string str;//清除错误输入
            char c;
            bool running=true;
            char middle;
            while(running)
            {
                        std::cout << "\033[2J\033[1;1H";// 清屏操作
                        print("----学生登陆----\n选择功能\n---1:查看所有可选课程\n---2:选择课程\n---3退选课程\n---4:查看自己的选课的成绩\n---5:退出学生操作系统\n");
                        cin>>c;
                        switch(c){
                        case '1':{
                                    showCourseAll();
                                    print("按回车键继续....\n");
                                    getchar();
                                    getchar();
                        }
                                    break;
                        case '2':
                                    print("test\n");
                                    break;
                        case '3':
                                    print("test\n");
                                    break;
                        case '4':
                                    print("test\n");
                                    break;
                        case '5':
                                    running=false;
                                    break;
                        default:{
                                    print("输入错误，请重新输入\n");
                                    getline(cin, str);//清除乱输入的
                        }
                                    break;

                        }
            }


}//选择学生方式
void CenterControl::loginTeacher(Teacher* teacher){
            string str;//清除错误输入
            char c;
            bool running=true;
            while(running)
            {
                        std::cout << "\033[2J\033[1;1H";// 清屏操作
                        print("----教师登陆----\n选择功能\n---1:查看自己的课程\n---2:给学生成绩打分\n---3:查看学生成绩\n---4:退出学生操作系统\n");
                        cin>>c;
                        switch(c){
                        case '1':{
                                    showCourseOwn(teacher);
                                    print("按回车键继续....\n");
                                    getchar();
                                    getchar();

                        }
                                    break;
                        case '2':
                                    print("test\n");
                                    break;
                        case '3':
                                    print("test\n");
                                    break;
                        case '4':
                                    running=false;
                                    break;
                        default:{
                                    print("输入错误，请重新输入\n");
                                    getline(cin, str);//清除乱输入的
                        }
                                    break;

                        }
            }


}//选择学生方式








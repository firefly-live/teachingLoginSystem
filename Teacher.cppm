//module:      Teacher.cppm
//Description: 作为teacher的实例化模块，继承User类，用于实现老师对象的逻辑操作
/*this files is build by author: tangshengqing2024051604041 at 2026-03-08*/
//email address:2052448030@qq.com
export module Objects:Teacher;
import std;
import :User;
import :Course;
using std::string;
using std::vector;
using std::print;


export class Teacher :public User{

public:
    Teacher(){};
    Teacher(int Tid, string name)
        : Tid(Tid), name(name){}
    void showCourse(); //--对于学生来说，查看可选课程，对于老师来说，查看自己的教授课
    void scoreGrades(int score);//给学生打分，传入course
    const string showInformation();//展示老师的信息

    //展示学生分数
    void showStudentGrades();


    //常用逻辑判断
    bool hasId(int Ttid);
    void bindCourse(Course* couurse);//由传入的课程对象，然后推送到coursses容器
private:
    int Tid;
    string name;//名字
    vector<Course*> courses;//通过课程得出选了这个课程的进而改学生成绩
};


void Teacher::showStudentGrades(){

    for(auto cou: courses){
        print("\n课程    课程id\t|\n");
        print("{}\t|\n",cou->showInformation());
        print("\t\t|-->姓名  分数\n");
        cou->showStudentGrades();
    }

}//遍历课程容器然后进行遍历输出course保存你的student容器分数



 const string Teacher::showInformation(){
    return ("{} {}",Tid,name);
 }//展示老师的信息


void Teacher::showCourse(){

   for(auto cour:courses)
   {
       string getInformation=cour->showInformation();
       print("{}\t{}\n",name,getInformation);
   }
}//展示自己的课程

bool Teacher::hasId(int Ttid){
    return Ttid==Tid;
}

void Teacher::bindCourse(Course* couurse){
    courses.push_back(couurse);
}//由传入的课程对象，然后推送到coursses容器

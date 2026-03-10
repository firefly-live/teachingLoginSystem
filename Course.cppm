//module:      Course.cppm
//Description:  用于操作Course的相关对象的操作，
/*this files is build by author: tangshengqing2024051604041 at 2026-03-08*/
//email address:2052448030@qq.com
export module Objects:Course;
import std;
using std::string;
using std::vector;
class Student;
using std::print;

export  class Course{

public:
    Course(){}

    Course(int Cid, string name)
        : Cid(Cid), name(name){}
    bool hasId(int Ccid); // 查看是否有这个课程
    void joinStudents(Student* student);
   const string showInformation();//展示课程信息
    const void useIdshowName(int Cid);//通过课程id号展示课程名字

    void scoreGrades();//由老师类传入，然后调用studet的打分，且调入自己的课程名字

    bool operator==(Course* course);//检查course的两个对象是否相等
    void operator=(Course* course);//检查course的两个对象是否相等

    void popStudent(Student* student);//推出student的对象

    void showStudent();//展示选了课程的学生

    void showStudentGrades();//依次调用选课学生，依次展示学生分数
private:
    int Cid;
    string name;
    vector <Student*> students;
};



 const void Course::useIdshowName(int Cid){
    print("\n{}",name);
}//通过课程id号展示课程名字





bool Course::operator==(Course* course){

    return (Cid==course->Cid&&name==course->name);
}//检查course的两个对象是否相等

void Course::operator=(Course* course){
    Cid=course->Cid;
    name=course->name;
}//检查course的两个对象是否相等

void Course::popStudent(Student* student){
    for(int i=0;i<students.size();i++)
    {
        if(students[i]==student)
        {
            students[i]=students[students.size()-1];//将末尾的移动到前面，然后pop出去
            students.pop_back();
            print("课程推出学生对象\n");
            return;
        }

    }
      print("未找到学生对象\n");
}//退选课程信息





bool Course:: hasId(int Ccid){
    return Ccid==Cid;

} // 查看是否有这个课程
void Course:: joinStudents(Student* student){
    students.push_back(student);//导入学生信息到课程
}
const string Course:: showInformation(){
    return format("{}\t{}",name,Cid);
}//展示课程信息::

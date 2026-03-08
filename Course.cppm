//module:      Course.cppm
//Description:  用于操作Course的相关对象的操作，
/*this files is build by author: tangshengqing2024051604041 at 2026-03-08*/
//email address:2052448030@qq.com
export module Objects:Course;
import std;
using std::string;
using std::vector;
class Student;


class Course{

public:
    Course(){}

    Course(int Cid, string name)
        : Cid(Cid), name(name){}
    bool hasId(); // 查看是否有这个课程
    void joinStudents(Student* student);
    void showInformation();//展示课程信息

    void scoreGrades(int score);//由老师类传入，然后调用studet的打分，且调入自己的课程名字

private:
    int Cid;
    string name;
    vector <Student> *students;
};

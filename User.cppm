//module:      User.cppm
//Description: 作为teacher和student的基类模块，用于后续的密码保护措施
/*this files is build by author: tangshengqing2024051604041 at 2026-03-08*/
//email address:2052448030@qq.com
export module Objects:User;
import std;
using std::string;
using std::vector;

class User{
public:
    User(){};
    User(string userAccount, string userPasssword): userAccount(userAccount), userPasssword(userPasssword) {}
    virtual void showCourse() = 0; //--对于学生来说，查看可选课程，对于老师来说，查看自己的教授课
private:
    string userAccount;//后续优化完善实现
    string userPasssword;//后续完善实现
};

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <limits>
#include <iomanip>

#include "KeyManager.h"


//-------UserInformation实现--------
UserInformation::UserInformation(string name, string key, string role):UserName(name),UserKey(key),UserRole(role) {}

string UserInformation::getname() { return UserName; }
string UserInformation::getkey() { return UserKey; }
string UserInformation::getrole() { return UserRole; }
//用户信息打印
void UserInformation::display() {
    std::cout << "用户名：" << UserName << "，用户密码：" << UserKey << ",用户权限：" << UserRole << endl;
}
void UserInformation::setkey(const string& newKey) {
    UserKey = newKey;  // 更新密码
}
//----------UserInformationManager实现----------
//构造函数
UserInformationManager::UserInformationManager(){
    UserInformation* admin = new UserInformation("admin1" ,"123456",  "Admin");
    Users.push_back(admin);
    //记录用户数
    Count = 1;
    kk = 1;
    //当前登录用户名
    Current_name = "None";
    //当前登录用户密码
    Current_key = "None";
}
//构析函数
UserInformationManager::~UserInformationManager(){
    for (auto user : Users) {
        delete user;
    }
}

//************************判断函数************************

//判断用户名是否存在于user库中
bool UserInformationManager::InName(string name) {
    for (auto user : Users)
        if (name == user->getname())
            return 1;
    return 0;
}
//判断在User库中，名字和密码是否匹配
bool UserInformationManager::KeyMatchName(string name, string key) {
    for (auto user : Users)
        if (name == user->getname())
            if (user->getkey() == key)
                return 1;
    return 0;
}
//判断用户权限是否为“Admin”管理员
bool UserInformationManager::IsAdmin(string role) {
    if (role == "Admin")
        return 1;
    return 0;
}
//判断名字是否已经在User库中（名字是否重复）
bool UserInformationManager::IsSingle(string name) {
    for (auto user : Users)
        if (name == user->getname())
            return 0;
    return 1;
}
// 密码强度检测函数
string CheckPasswordStrength(const string& password) {
    bool hasLetter = false, hasDigit = false, hasSpecial = false;
    for (char c : password) {
        if (isalpha(c)) hasLetter = true;
        else if (isdigit(c)) hasDigit = true;
        else hasSpecial = true;
    }

    if (password.length() < 6)
        return "弱（长度小于6）";
    if ((hasLetter && hasDigit && hasSpecial) && password.length() >= 8)
        return "强";
    if (hasLetter && hasDigit)
        return "中";
    return "弱";
}

//************************打印函数****************************

//打印所有用户信息及管理员密码
void UserInformationManager::DisplayUsers() {
    std::cout << "用户信息" << endl;
    std::cout << "========================================================" << endl;
    cout << left << setw(15) << "用户名"
        << setw(15) << "用户密码"
        << setw(8) << "用户权限" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (auto user : Users) {
        cout << left << setw(15) << user->getname()
            << setw(15) << user->getkey()
            << setw(8) << user->getrole() << endl;
    }
    std::cout << "========================================================" << endl;

}
//查找用户权限
string UserInformationManager::Findrole(string name) {
    for (auto user : Users) {
        if (name == user->getname())
            return user->getrole();
    }
    return "NULL";
}
// 去除字符串首尾的空格
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}


//++++++++++++++++++++++++++++++++++         登录注册操作            +++++++++++++++++++++++++++++++++++
// 
//**************登录注册界面*************
int UserInformationManager::Login_Screem() {
    std::cout << "========================================================" << endl;
    std::cout << "|         欢迎使用上海海事大学学生档案管理系统         |" << endl;
    std::cout << "========================================================" << endl;
    std::cout << "|                        请登录                        |" << endl;
    std::cout << "========================================================" << endl;
    std::cout << "|                        1.登录                        |" << endl;
    std::cout << "|                        2.注册                        |" << endl;
    std::cout << "|                        3.退出                        |" << endl;
    std::cout << "========================================================" << endl;
    std::cout << "请选择功能>";
    int c = -1;
    cin >> c;

    if (cin.fail()) {
        cin.clear(); // 清除错误状态
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 丢弃错误输入
        system("cls");
        cout << "!!!!! 请输入数字选项（1-3） !!!!!" << endl;
    }
    else if (c < 1 || c > 3) {
        system("cls");
        cout << "!!!!! 请输入数字选项（1-3） !!!!!" << endl;
    }
    return c;
}

//登录输入提示界面
void UserInformationManager::InputkeyScreem(string &name, string &key) {
    std::cout << "=============================" << endl;
    std::cout << "  用户名：";
    cin >> name;
    std::cout << "--------------------------------" << endl;
    std::cout << "  密码：";
    cin >> key;
    std::cout << "=============================" << endl;
}

//*****************************************注册功能*******************************************
//--------------添加用户，并放到文件中备份-------------
void UserInformationManager::AddUsers(string Username, string Userkey, string role) {
    // 检查用户名是否已存在，防止重复添加
    if (InName(Username)) {
        std::cout << "用户名已存在，添加失败！" << endl;
        return;
    }
    // 创建新的用户对象并添加到用户列表
    UserInformation* newUser = new UserInformation(Username, Userkey, role);
    Users.push_back(newUser);
    Count++;  // 更新用户计数
    // 追加到 CSV 文件
    ofstream file("users.csv", ios::app);
    if (file.is_open()) {
        file << Username << "," << Userkey << "," << role << endl;
        file.close();
    }
    //添加成功提示
    std::cout << "用户 " << Username << " 添加成功，角色：" << role << endl;
}
//------------------注册服务------------------
void UserInformationManager::RegisterScreem(string& name, string& key1) {
    //退出主循环标志
    bool flag = true;
    //选择（管理员/学生）标志
    int c = 0;
    string key2, AdminKey;
    while (flag) {
        // *******注册界面********
        std::cout << "==============================" << endl;
        std::cout << "|           请注册           |" << endl;
        std::cout << "==============================" << endl;
        std::cout << "|        1. 管理员用户       |" << endl;
        std::cout << "|        2. 学生用户         |" << endl;
        std::cout << "==============================" << endl;
        std::cout << "请选择用户类型：";
        cin >> c;
        while (true) {
            std::cout << "请输入您的真实姓名 ：";
            cin >> name;
            //判断输入名字是否已存在
            if (!IsSingle(name)) {
                std::cout << "用户名已存在，请更换姓名！" << endl;
                continue;  // 继续循环，要求重新输入
            }
            break;  // 用户名合法，跳出循环
        }
        //跳出循环，进行输入密码
        while (true) {
            std::cout << "请输入用户密码：";
            cin >> key1;
            string strength = CheckPasswordStrength(key1);
            std::cout << "密码强度：" << strength << endl;
            if (strength == "弱" || strength.find("弱") != string::npos) {
                std::cout << "密码太弱，请设置更强的密码（至少6位，包含字母和数字）！" << endl;
                continue;
            }
            std::cout << "--------------------------------" << endl;
            std::cout << "再次输入确认密码：";
            cin >> key2;
            if (key1 != key2) {
                std::cout << "两次密码输入不一致，请重新输入！" << endl;
                continue;
            }
            break; // 密码强度合格，且输入一致，退出循环
        }
         // **管理员注册**
         if (c == 1) {  
             std::cout << "请输入管理员密码：";
             cin >> AdminKey;
             if (AdminKey == Admin_Key) {
                 system("cls");
                 std::cout << "注册成功！请登录" << endl;
                 //给与管理员权限
                 AddUsers(name, key1, "Admin");
                 //跳出循环
                 flag = false;
             }
             else {
                 system("cls");
                 std::cout << "！！！管理员密码错误！！！请重新输入" << endl;
             }
         }
         // **学生注册**
         else { 
             system("cls");
             std::cout << "注册成功！请登录" << endl;
             //给予学生权限
             AddUsers(name, key1, "Stu");
             //跳出循环
             flag = false;
         }
    }
}

//*******************************************************主登录注册界面***********************************************************
string UserInformationManager::Login() {
    string n, k, c;
    bool flag_1 = true;

    // 重置当前登录状态
    Current_name = "None";
    Current_key = "None";

    while (flag_1) {
        int choice = Login_Screem();
        // ... 原有输入检查代码 ...

        switch (choice) {
        case 1: // 登录
            InputkeyScreem(n, k);
            if (InName(n) && KeyMatchName(n, k)) {
                Current_name = n;
                Current_key = k;
                system("cls");

                string role = Findrole(n);
                if (role == "Admin") {
                    std::cout << "========================================================" << endl;
                    std::cout << "                  欢迎！" << n << "管理员                     " << endl;
                    c = "Admin";
                }
                else {
                    std::cout << "========================================================" << endl;
                    std::cout << "                     欢迎！" << n << "同学                    " << endl;
                    c = "Stu";
                }
                flag_1 = false;
                return c;
            }
            else if (!InName(n)) {
                system("cls");
                std::cout << "!!!!! 用户名不存在，请重新输入或注册 !!!!!" << endl;
            }
            else {
                system("cls");
                std::cout << "!!!!! 密码错误，请重新输入 !!!!!" << endl;
            }
            break;
            //注册
        case 2:
            system("cls");
            RegisterScreem(n, k);
            break;
            //退出
        case 3:
            char s;
            while (1) {
                std::cout << "确认退出？（y/n）";
                cin >> s;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除剩余输入

                if (s == 'y') {
                    system("cls");
                    std::cout << "感谢使用该系统~~再见！" << endl;
                    exit(0);
                }
                else if (s == 'n') {
                    // 无事发生
                    system("cls");
                    break;
                }
                else {
                    std::cout << "请输入正确选项" << endl;
                }
            }
        }
    }
}

//++++++++++++++++++++++++++++++++            开机自启动读取             +++++++++++++++++++++++++++++

void UserInformationManager::Load_Users() {
    //打开文件
    ifstream file("users.csv");
    //文件打开失败提示
    if (!file.is_open()) {
        std::cout << "用户数据文件不存在，将创建新文件。" << endl;
        return;
    }
    // 清空当前用户数据，防止重复加载
    for (auto user : Users)
        delete user;
    Users.clear();

    string line;
    bool isFirstLine = true;
    //对文件每行进行遍历读取
    while (getline(file, line)) {
        stringstream ss(line);
        string username, userkey, userrole;
        // 第一行是管理员密码
        if (isFirstLine) {
            //读取管理员密码
            getline(ss, username, ',');
            if (username == "AdminKey") {
                getline(ss, Admin_Key,',');
                //Admin_Key = trim(Admin_Key);
                isFirstLine = false;
                continue;
            }
        }
        // 读取用户数据
        if (getline(ss, username, ',') && getline(ss, userkey, ',') && getline(ss, userrole)) {
            Users.push_back(new UserInformation(username, userkey, userrole));
        }
    }
    //关闭文件
    file.close();
}


//++++++++++++++++++++++++++++++                       管理员操作                     ++++++++++++++++++++++++++++++
// 
//*************************************功能九：用户密码管理**************************************
//--------判断用户是否在User库中存在------
bool UserInformationManager::In_User(string Username) {
    for (auto& users : Users)
        if (Username == users->getname())
            return 1;
    return 0;
}

//---------备份用户信息--------
void UserInformationManager::Backup_Users() {
    //打开文件
    ofstream file("users.csv", ios::trunc);
    //进行备份
    if (file.is_open()) {
        // 备份管理员密码
        file << "AdminKey," << Admin_Key << endl; 
        //遍历备份用户信息
        for(auto& users:Users)
            file << users->getname() << "," << users->getkey() << "," << users->getrole() << endl;
        file.close();
    }
    //成功提示
    std::cout << "备份成功！" << endl;
}

//---------删除用户----------
void UserInformationManager::Delete_Users() {
    string Uname;
    char c;
    while (1) {
        DisplayUsers();
        std::cout << "输入要删除的用户名或按q退出>" ;
        cin >> Uname;
        //User库中是否存在
        if (!In_User(Uname)) {
            std::cout << "用户不存在" << endl;
            return;
        }
        break;
     }
     //打印这行用户信息
     for (auto& users : Users) {
         if (users-> getname() == Uname) {
             users->display();
             //确认
             std::cout << "确认删除？（y/n）";
             cin >> c;
             if (c == 'y') {
                 delete(users);
                 Count--;
                 std::cout << "删除成功" << endl;
                 Backup_Users();
                 break;
             }
             else {
                 std::cout << "取消删除" << endl;
                 break;
             }
         }
     }
}

//-----------更换管理员密码------------
void UserInformationManager::Replace_Admin_Key() {
    string checked_admin_key,checked_new_admin_key,new_admin_key;
    while(1){
        std::cout << "输入原管理员密码或按q退出：";
        cin >> checked_admin_key;
        if (checked_admin_key == "q") return;
        if (checked_admin_key != Admin_Key) {
            std::cout << "原密码错误，请重试" << endl;
            continue;
        }
        break;
    }
    while (1) {
        std::cout << "输入新的管理员密码：";
        cin >> new_admin_key;
        std::cout << "再次输入以确认：";
        cin >> checked_new_admin_key;
        if (new_admin_key != checked_new_admin_key) {
            std::cout << "两次密码不一致，重新输入" << endl;
            continue;
        }
        break;
    }
    Admin_Key = new_admin_key;
    std::cout << "管理员密码修改成功！" << endl;
    // 立即备份到文件
    Backup_Users(); 
}

//-----------打印管理员密码-----------
void UserInformationManager::Display_Admin_Key() {
    std::cout << "管理员密码：" << Admin_Key << endl;
}

//------------------------------------密码管理主界面------------------------------------
void UserInformationManager::Key_Manage_Screem() {
    DisplayUsers();
    char s;
    while (1) {
        system("cls");
        std::cout << "==============================" << endl;
        std::cout << "|           选择功能         |" << endl;
        std::cout << "==============================" << endl;
        std::cout << "|        1. 删除用户         |" << endl;
        std::cout << "|        2. 备份用户信息     |" << endl;
        std::cout << "|        3. 更新管理员密码   |" << endl;
        std::cout << "|        4. 打印管理员密码   |" << endl;
        std::cout << "|        按 q 退出           |" << endl;
        std::cout << "==============================" << endl;
        std::cout << ">> ";
        cin >> s;

        switch (s) {
        case '1':
            Delete_Users();
            break;
        case '2':
            Backup_Users();
            system("pause");
            break;
        case '3':
            Replace_Admin_Key();
            system("pause");
            break;
        case '4':
            Display_Admin_Key();
            system("pause");
            break;
        case 'q':
            return;
        default:
            std::cout << "\n无效输入！请输入有效选项（1-4 或 q）" << endl;
            system("pause");
        }
    }
}   


//*******************************************功能零：退出登录******************************************
char UserInformationManager::Exit_Screem() {
    char s;
    while (1) {
        std::cout << "确认退出？（y/n）";
        cin >> s;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除剩余输入

        if (s == 'y') {
            Current_name = "None";
            Current_key = "None";
            return 'y';
        }
        else if (s == 'n') {
            return 'n';
            break;
        }
        else {
            std::cout << "请输入正确选项" << endl;
            return 'y';
        }
        return 'y';
    }
}


//+++++++++++++++++++++++++++                          学生查看操作                        ++++++++++++++++++++++++++
//
//************************************功能五：修改学生密码********************************************
void UserInformationManager::Replace_Student_Key() {
    string checked_student_key, new_student_key, checked_new_student_key;
    while (1) {
        std::cout << "输入原密码,按q返回：";
        cin >> checked_student_key;
        if (checked_student_key == "q")  
            return;
        if (checked_student_key !=Current_key) {
            std::cout << "原密码错误，请重试" << endl;
            continue;
        }
        break;
    }
    while (1) {
        std::cout << "输入新的密码：";
        cin >> new_student_key;

        string strength = CheckPasswordStrength(new_student_key);
        std::cout << "密码强度：" << strength << endl;

        if (strength == "弱" || strength.find("弱") != string::npos) {
            std::cout << "密码太弱，请设置更强的密码（至少6位，包含字母和数字）！" << endl;
            continue;
        }

        std::cout << "--------------------------------" << endl;
        std::cout << "再次输入确认密码：";
        cin >> checked_new_student_key;

        if (new_student_key != checked_new_student_key) {
            std::cout << "两次密码输入不一致，请重新输入！" << endl;
            continue;
        }

        break; // 密码强度合格，且输入一致，退出循环
    }

    for (auto& users : Users) {
        if (users->getname() == Current_name) {
            users->setkey(new_student_key);
        }
    }
    // 更新当前登录状态的密码
    Current_key = new_student_key;
    std::cout << "密码修改成功！" << endl;
    cout << "当前用户登录信息：\n登录名：" << Current_name 
        << "\n登录密码：" << Current_key << endl;
    // 立即备份到文件
    Backup_Users(); 
}

//************************************功能六：注销账户********************************************
char UserInformationManager::Log_Off() {
    char s;
    while (1) {
        std::cout << "当前用户为："<<Current_name << endl;
        std::cout << "确认注销当前账户？(y/n)";
        cin >> s;
        if (s == 'y') {
            for (auto it = Users.begin(); it != Users.end(); ++it) {
                if ((*it)->getname() == Current_name) {
                    delete* it;
                    Users.erase(it);
                    Backup_Users();
                    std::cout << "用户 " << Current_name << " 已成功注销！" << endl;
                    break;
                }
            }
            // 清除当前登录状态
            Current_name = "None";
            Current_key = "None";
            system("cls");
            Login(); // 返回登录界面
            return 'y';
        }
        else if (s == 'n') {
            return 'n';
        }
        else {
            std::cout << "请输入正确选项" << endl;
            return 'y';
        }
        return 'y';
    }
}

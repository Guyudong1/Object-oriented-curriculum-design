#include <iostream>
using namespace std;
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

#include "AdminManager.h"


//----------Student实现-----------
Student::Student(string Id, string Name, string Birth, string Sex, string Class) :Sid(Id), Sname(Name), Sbirth(Birth), Ssex(Sex), Sclass(Class) {}
string Student::GetId() { return Sid; }
string Student::GetName() { return Sname; }
string Student::GetBirth() { return Sbirth; }
string Student::GetSex() { return Ssex; }
string Student::GetClass() { return Sclass; }
//学生信息打印
void Student::StuDisplay() const {
    cout << left << setw(18) << "学号"
        << setw(10) << "姓名"
        << setw(15) << "生日"
        << setw(8) << "性别"
        << setw(10) << "所在班级" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << left << setw(18) << Sid
        << setw(10) << Sname
        << setw(15) << Sbirth
        << setw(8) << Ssex
        << setw(10) << Sclass << endl;
}
//学生成绩打印
void Student::GradesDisplay() const {
    cout << Sname << " (" << Sid << ")的成绩：" << endl;
    cout << left << setw(18) << "课程名"
        << setw(10) << "课程学分"
        << setw(10) << "课程绩点"<<endl;
    cout << "-------------------------------------------------------" << endl;
    for (const auto& g : grades) {
        g.GradeDisplay();
    }
}

//----------Grade实现------------
Grade::Grade() : Cname("无"), Credit(0.0), GPA(0.0) {}
Grade::Grade(string name, float credit, float gpa) :Cname(name), Credit(credit), GPA(gpa) {}
Grade::~Grade() {}
string Grade::GetCname() const { return Cname; }
float Grade::GetCredit() const { return Credit; }
float Grade::GetGPA() const { return GPA; }
//成绩打印
void Grade::GradeDisplay() const {
    cout <<left<<setw(18)<< Cname <<setw(10)<< Credit <<setw(10) <<  GPA << endl;
}

//----------StudentManager实现-----------

// ++++++++++++++++++++++++++++管理员操作++++++++++++++++++++++++++++++++++

//**********************************************主系统菜单**************************************************
int AdminManager::Admin_Menu() {
    int s = -1;
    int unreadCount = MessageManager::GetUnreadCount("admin");
    while (true) {


        cout << "========================================================" << endl;
        cout << "|             上海海事大学学生档案管理系统             |" << endl;
        cout << "========================================================" << endl;
        cout << "|                    请选择功能：                      |" << endl;
        cout << "========================================================" << endl;
        cout << "|                    1.录入学生信息                    |" << endl;
        cout << "|                    2.打印学生信息                    |" << endl;
        cout << "|                    3.备份学生信息                    |" << endl;
        cout << "|                    4.读取学生信息                    |" << endl;
        cout << "|                    5.增加学生信息                    |" << endl;
        cout << "|                    6.删除学生信息                    |" << endl;
        cout << "|                    7.修改学生信息                    |" << endl;
        cout << "|                    8.查询学生信息                    |" << endl;
        cout << "|                    9.用户密码管理                    |" << endl;
        cout << "|                    10.邮箱"
            << (unreadCount > 0 ? ("(新消息" + to_string(unreadCount) + "条)") : "")
            << string(20 - 6 - (unreadCount > 0 ? (6 + to_string(unreadCount).length()) : 0), ' ') << "              " << endl;
        cout << "|                    0.退出该系统                      |" << endl;
        cout << "========================================================" << endl;
        cout << "请选择功能>";


        cin >> s;

        if (cin.fail()) {
            cin.clear(); // 清除错误状态
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 丢弃错误输入
            system("cls");
            cout << "!!!!! 请输入正确数字选项（0-9）!!!!!" << endl;
        }
        else if (s < 0 || s > 10) {
            system("cls");
            cout << "!!!!! 请输入正确数字选项（0-9）!!!!!" << endl;
        }
        else {
            break;
        }
    }

    return s;
}


//********************************************功能一：录入学生信息***********************************************
//录入学生信息
string AdminManager::Add_Student_Information() {
    string id, name, birth, sex, sclass;
    cout << "=============================" << endl;
    cout << "        录入系统,按q退出            " << endl;
    cout << "=============================" << endl;
    cout << "学号： ";
    cin >> id;
    if (id == "q")
        return "ERROR";
    cout << "姓名: ";
    cin >> name;
    if (name == "q")
        return "ERROR";
    cout << "生日(YYYY-MM-DD): ";
    cin >> birth;
    if (birth == "q")
        return "ERROR";
    cout << "性别(男/女): ";
    cin >> sex;
    if (sex == "q")
        return "ERROR";
    cout << "所在班级: ";
    cin >> sclass;

    cout << "=============================" << endl;
    for (const auto& student : students) {
        if (student.Sid == id) {
            cout << "录入失败！已有该学号学生，添加重复！" << endl;
            return "ERROR";
        }
    }
    students.emplace_back(id, name, birth, sex, sclass);
    cout << "学生录入成功！！！" << endl;
    cout << "学号: " << id << ", 姓名: " << name << ", 生日: " << birth << ", 性别: " << sex << ", 所在班级: " << sclass << endl;
    cout << "=============================" << endl;
    return id;
}
//录入学生成绩
void AdminManager::Add_Student_Grade(string studentID, const Grade& grade) {
    for (auto& student : students)
        if (student.Sid == studentID) {
            student.grades.push_back(grade);
            cout << "录入成绩的学生：" << student.Sname << endl;
            return;
        }
    cout << "录入失败!该学生未找到!" << endl;
}
//录入学生信息界面
void AdminManager::Add_Student_Screem() {
    char k;
    string id;
    while (1) {
        system("cls");
        char c2;
        id = Add_Student_Information();
        if (id == "ERROR") {
            break;
        }
        cout << "是否输入学生成绩？（y/n）";
        cin >> k;
        if (k == 'y') {
            string name;
            float credit;
            float gpa;

            while (1) {
                char c1;
                cout << "=============================" << endl;
                cout << "课程名：";
                cin >> name;
                cout << "学分：";
                cin >> credit;
                cout << "绩点：";
                cin >> gpa;
                cout << "=============================" << endl;
                Add_Student_Grade(id, Grade(name, credit, gpa));
                cout << "继续输入成绩?（y/n）";
                cin >> c1;
                if (c1 == 'y')
                    cout << "继续输入：" << endl;
                else if (c1 == 'n')
                    break;
            }
        }
        else if (k == 'n')
            Add_Student_Grade(id, Grade());
        cout << "继续输入学生信息？（y/n）";
        cin >> c2;
        if (c2 == 'y')
            cout << "继续输入学生信息：" << endl;
        else if (c2 == 'n') {
            break;
        }
    }
}

//****************************************功能二：打印学生信息*********************************************
//------------表格实现---------------
//学生信息表
void AdminManager::Table_Student_Information_Display() {
    cout << left << setw(18) << "学号"
        << setw(10) << "姓名"
        << setw(15) << "生日"
        << setw(8) << "性别"
        << setw(10) << "所在班级" << endl;
    cout << "-----------------------------------------------------------" << endl;
    for (auto& student : students)
        cout << left << setw(18) << student.Sid
        << setw(10) << student.Sname
        << setw(15) << student.Sbirth
        << setw(8) << student.Ssex
        << setw(10) << student.Sclass << endl;
}
//学生成绩表
void AdminManager::Table_Student_Grade_Display(string id) {
    
    cout << left << setw(15) << "课程名称"
        << setw(15) << "课程学分"
        << setw(8) << "课程绩点" << endl;
    cout << "--------------------------------------------------------" << endl;

    for (auto& student : students) {
        if (student.Sid == id) {
            for (auto& grades : student.grades) {
                cout << left << setw(15) << grades.Cname
                    << setw(15) << grades.Credit
                    << setw(8) << grades.GPA << endl;
            }
            break;
        }
    }
}
//判断ID是否在User库中
bool AdminManager::In_Id(string id) {
    for (auto& student : students)
        if (student.Sid == id)
            return 1;
    return 0;
}
//打印所有学生的基本信息
string AdminManager::Student_Information_Display() {
    string s;
    system("cls");
    Table_Student_Information_Display();
    cout << "输入学号查看对应成绩,按q退出：";
    cin >> s;
    return s;
}
//打印指定学生的所有成绩
void AdminManager::Student_Grade_Display(string id) {
    cout << "id为" << id << "的成绩为：" << endl;
    Table_Student_Grade_Display(id);

}
//打印界面
void AdminManager::Display_Student_Screem() {
    string s;
    s = Student_Information_Display();
    while (1) {
        if (s == "q") {
            break;
        }
        else if (In_Id(s)) {
            Student_Grade_Display(s);
            cout << "输入学号查看对应成绩,按q退出：";
            cin >> s;

        }
        else {
            cout << "该学号的学生不存在。" << endl;
            cout << "输入学号查看对应成绩,按q退出：";
            cin >> s;
        }
    }
}

//***********************************************功能三：备份学生信息***********************************************

//备份界面
void AdminManager::Backup_Student_Screem() {
    //打开文件
    std::string filename = "students_data.csv";
    std::ofstream outFile(filename, std::ios::out);
    //打开失败提示
    if (!outFile) {
        std::cerr << "无法打开文件进行写入！" << std::endl;
        return;
    }
    // 写入表头
    outFile << "学生ID,姓名,生日,性别,班级,课程名,学分,GPA\n";
    // 遍历所有学生打印
    for (const auto& student : students) {
        for (const auto& grade : student.grades) {
            outFile << student.Sid << ","
                << student.Sname << ","
                << student.Sbirth << ","
                << student.Ssex << ","
                << student.Sclass << ","
                << grade.Cname << ","
                << grade.Credit << ","
                << grade.GPA << "\n";
        }
    }
    //关闭文件
    outFile.close();
    //成功提示
    std::cout << "学生信息已成功备份到 " << filename << std::endl;
}

//********************************功能四：读取学生信息***********************************

//读取界面
void AdminManager::Read_Student_Screem() {
    //打开文件
    std::string filename = "students_data.csv";
    std::ifstream inFile(filename, std::ios::in);
    //文件打开失败提示
    if (!inFile) {
        std::cerr << "无法打开文件进行读取！" << std::endl;
        return;
    }

    std::string line;
    // 读取表头，丢弃
    std::getline(inFile, line);
    //遍历所有学生读取
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        //读取表头
        std::string sid, sname, sbirth, ssex, sclass, cname, credit, gpa;
        //读取数据
        std::getline(ss, sid, ',');
        std::getline(ss, sname, ',');
        std::getline(ss, sbirth, ',');
        std::getline(ss, ssex, ',');
        std::getline(ss, sclass, ',');
        std::getline(ss, cname, ',');
        std::getline(ss, credit, ',');
        std::getline(ss, gpa, ',');
        //将读取到的数据存入Student和Grade类中
        Grade grade(cname, std::stof(credit), std::stof(gpa));
        //判断是否为新学生的参数
        bool found = false;
        // 查找已有学生
        for (auto& student : students) {
            if (student.Sid == sid) {
                student.grades.push_back(grade);
                found = true;
                break;
            }
        }
        // 如果是新学生，创建新的 Student 对象
        if (!found) {
            Student student(sid, sname, sbirth, ssex, sclass);
            student.grades.push_back(grade);
            students.push_back(student);
        }
    }
    //关闭文件
    inFile.close();
    //成功读取提示
    std::cout << "学生信息已成功从 " << filename << " 读取！" << std::endl;
}

//*********************************修改版功能五：为已有学生添加成绩**********************************
// 为已有学生添加成绩界面
void AdminManager::Add_Student_Grades_Screem() {
    system("cls");// 清屏
    cout << "=============================" << endl;
    cout << "      为已有学生添加成绩       " << endl;
    cout << "=============================" << endl;

    if (students.empty()) {
        cout << "当前没有学生信息，请先录入学生！" << endl;
        return;
    }

    // 显示所有学生列表供选择
    Table_Student_Information_Display();

    string id;
    cout << "请输入要添加成绩的学生学号（按q返回）: ";
    cin >> id;

    if (id == "q") return; // 用户取消操作

    // 查找学生
    auto it = find_if(students.begin(), students.end(),
        [&id](const Student& s) { return s.Sid == id; });

    if (it != students.end()) {
        // 循环添加多门课程成绩
        char addMore;
        do {
            string name;
            float credit, gpa;

            cout << "=============================" << endl;
            cout << "课程名: ";
            cin >> name;
            cout << "学分: ";
            cin >> credit;
            cout << "绩点: ";
            cin >> gpa;

            // 添加成绩到学生对象
            it->grades.emplace_back(name, credit, gpa);
            cout << "成绩添加成功！" << endl;

            // 询问是否继续添加
            cout << "继续为该学生添加成绩？(y/n): ";
            cin >> addMore;
        } while (tolower(addMore) == 'y');

        // 显示更新后的成绩单
        cout << "当前学生成绩列表：" << endl;
        Table_Student_Grade_Display(id);
    }
    else {
        cout << "未找到学号为 " << id << " 的学生！" << endl;
    }
}


//*********************************功能六：删除学生信息**********************************
// 删除学生信息界面
void AdminManager::Delete_Student_Screem() {
    bool flag = 1; // 控制循环标志
    while (flag) {
        system("cls");
        cout << "===========================================================" << endl;
        cout << "|                      删除学生信息                       |" << endl;
        cout << "|                         按q退出                         |" << endl;
        cout << "===========================================================" << endl;

        // 检查学生列表是否为空
        if (students.empty()) {
            cout << "当前没有学生信息可删除！" << endl;
            return;
        }

        // 显示学生列表
        Table_Student_Information_Display();
        cout << "===========================================================" << endl;

        string id;
        cout << "请输入要删除的学生学号/按q退出> ";
        cin >> id;

        if (id == "q") {
            break;
        }// 用户取消操作

         // 查找目标学生
        auto it = find_if(students.begin(), students.end(), [&id](const Student& s) { return s.Sid == id; });
        if (it != students.end()) {
            char confirm, c;
            system("cls");
            while (1) {
                cout << "======================================================" << endl;
                cout << "|                   1.删除学生                       |" << endl;
                cout << "|                   2.删除学生成绩                   |" << endl;
                cout << "|                   3.退出                           |" << endl;
                cout << "======================================================" << endl;
                cout << "请选择>";
                cin >> c;
                if (c == '1') {
                    cout << "确定要删除学号为 " << id << " 的学生信息吗？(y/n): ";
                    cin >> confirm;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除剩余输入

                    // 确认删除操作
                    if (tolower(confirm) == 'y') {
                        students.erase(it);// 从容器中删除学生
                        cout << "学生信息删除成功！" << endl;
                        break;
                    }
                    else if (tolower(confirm) == 'n') {
                        cout << "已取消删除操作。" << endl;
                        break;
                    }
                }
                else if (c == '2') {
                    string courseName;
                    cout << "======================================================" << endl;
                    it->GradesDisplay();
                    cout << "======================================================" << endl;
                    cout << "请输入要删除的成绩所属课程名>";
                    cin >> courseName;

                    // 检查课程是否存在
                    auto gradeIt = find_if(
                        it->grades.begin(),
                        it->grades.end(),
                        [&courseName](const Grade& grade) {
                            return grade.Cname == courseName;
                        }
                    );
                    if (gradeIt != it->grades.end()) {
                        cout << "确定要删除学号为 " << id << " 的课程 " << courseName << " 的成绩吗？(y/n): ";
                        cin >> confirm;
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (tolower(confirm) == 'y') {
                            it->grades.erase(gradeIt); // 删除该课程成绩
                            cout << "课程 " << courseName << " 成绩删除成功！" << endl;
                        }
                        else {
                            cout << "已取消删除操作。" << endl;
                        }
                    }
                    else {
                        system("cls");
                        cout << "请输入正确选项" << endl;
                    }
                }
                else if (c == '3') break;
            }
        }
        else {
            cout << "未找到学号为 " << id << " 的学生！" << endl;
        }
    }
}



//*********************************功能七：修改学生信息**********************************
// 修改学生信息界面
void AdminManager::Modify_Student_Screem() {
    bool flag1 = 1;// 外层循环标志
    while (flag1) {
        system("cls");
        cout << "===========================================================" << endl;
        cout << "|                      修改学生信息                       |" << endl;
        cout << "|                         按q退出                         |" << endl;
        cout << "===========================================================" << endl;

        // 检查学生列表是否为空
        if (students.empty()) {
            cout << "当前没有学生信息可修改！" << endl;
            return;
        }

        // 显示学生列表
        Table_Student_Information_Display();
        cout << "===========================================================" << endl;

        string id;
        cout << "请输入要修改的学生学号/按q退出>";
        cin >> id;

        if (id == "q") {
            break;
        }

        // 查找目标学生
        auto it = find_if(students.begin(), students.end(),
            [&id](const Student& s) { return s.Sid == id; });

        if (it != students.end()) {
            bool flag2 = 1;// 内层循环标志
            while (flag2) {
                system("cls");
                cout << "当前学生信息如下：" << endl;
                cout << "===========================================================" << endl;
                it->StuDisplay();
                cout << "===========================================================" << endl;
                cout << "|                     请选择要修改的内容：                |" << endl;
                cout << "|                        1. 姓名                          |" << endl;
                cout << "|                        2. 生日                          |" << endl;
                cout << "|                        3. 性别                          |" << endl;
                cout << "|                        4. 班级                          |" << endl;
                cout << "|                        5. 成绩信息                      |" << endl;
                cout << "|                         按q返回                         |" << endl;
                cout << "===========================================================" << endl;
                cout << "请选择>";

                char choice;
                cin >> choice;

                // 根据选择修改不同字段
                switch (choice) {
                case '1': {
                    string newName;
                    cout << "请输入新的姓名: ";
                    cin >> newName;
                    it->Sname = newName;
                    break;
                }// 修改姓名

                case '2': {
                    string newBirth;
                    cout << "请输入新的生日(YYYY-MM-DD): ";
                    cin >> newBirth;
                    it->Sbirth = newBirth;
                    break;
                }// 修改生日

                case '3': {
                    string newSex;
                    cout << "请输入新的性别(男/女): ";
                    cin >> newSex;
                    it->Ssex = newSex;
                    break;
                }// 修改性别

                case '4': {
                    string newClass;
                    cout << "请输入新的班级: ";
                    cin >> newClass;
                    it->Sclass = newClass;
                    break;
                }// 修改班级

                case '5': {
                    Modify_Student_Grades(*it);
                    system("cls");
                    break;
                }// 通过调用子函数修改成绩

                case 'q':// 返回上级
                    flag2 = 0;
                    break;
                default:
                    cout << "无效的选择！" << endl;
                }

                cout << "学生信息修改成功！" << endl;
            }
        }
        else {
            cout << "未找到学号为 " << id << " 的学生！" << endl;
            system("pause");
        }
    }
}

// 修改学生成绩子函数
void AdminManager::Modify_Student_Grades(Student& student) {
    bool flag3 = 1;// 循环标志
    if (student.grades.empty()) {
        cout << "该学生暂无成绩信息！" << endl;
        return;
    }
    while (flag3) {
        system("cls");
        cout << student.Sname << "的成绩信息：" << endl;
        cout << "========================================================" << endl;
        Table_Student_Grade_Display(student.Sid);// 显示当前成绩
        cout << "========================================================" << endl;
        cout << "|                      请选择操作                      |" << endl;
        cout << "|                      1. 添加成绩                     |" << endl;
        cout << "|                      2. 修改成绩                     |" << endl;
        cout << "|                      3. 删除成绩                     |" << endl;
        cout << "|                        按q返回                       |" << endl;
        cout << "========================================================" << endl;
        cout << "请选择> ";

        char choice;
        cin >> choice;

        switch (choice) {
        case '1': {
            string name;
            float credit, gpa;
            cout << "课程名: ";
            cin >> name;
            cout << "学分: ";
            cin >> credit;
            cout << "绩点: ";
            cin >> gpa;
            student.grades.emplace_back(name, credit, gpa);
            cout << "成绩添加成功！" << endl;
            break;
        }// 添加成绩

        case '2': {
            string courseName;
            cout << "请输入要修改的课程名: ";
            cin >> courseName;

            auto it = find_if(student.grades.begin(), student.grades.end(),
                [&courseName](const Grade& g) { return g.Cname == courseName; });

            if (it != student.grades.end()) {
                cout << "请输入新的学分: ";
                cin >> it->Credit;
                cout << "请输入新的绩点: ";
                cin >> it->GPA;
                cout << "成绩修改成功！" << endl;
            }
            else {
                cout << "未找到课程名为 " << courseName << " 的成绩记录！" << endl;
            }
            break;
        }// 修改已有成绩

        case '3': {
            string courseName;
            cout << "请输入要删除的课程名: ";
            cin >> courseName;

            auto it = find_if(student.grades.begin(), student.grades.end(),
                [&courseName](const Grade& g) { return g.Cname == courseName; });

            if (it != student.grades.end()) {
                student.grades.erase(it);
                cout << "成绩删除成功！" << endl;
            }
            else {
                cout << "未找到课程名为 " << courseName << " 的成绩记录！" << endl;
            }
            break;
        }// 删除成绩

        case 'q':// 返回上级
            flag3 = 0;
        default:
            cout << "！！！请选择正确的选项！！！" << endl;
        }
    }
}

//*********************************功能八：查询学生信息**********************************
// 查询学生信息界面
void AdminManager::Search_Student_Screem() {
    bool flag = 1;// 循环标志
    while (flag) {
        system("cls");
        cout << "=============================" << endl;
        cout << "|        查询学生信息       |" << endl;
        cout << "=============================" << endl;
        cout << "|      请选择查询方式：     |" << endl;
        cout << "=============================" << endl;
        cout << "|       1. 按学号查询       |" << endl;
        cout << "|       2. 按姓名查询       |" << endl;
        cout << "|       3. 按班级查询       |" << endl;
        cout << "|          按q返回          |" << endl;
        cout << "=============================" << endl;
        cout << "请选择查询方式/按q退出>";

        char choice;
        cin >> choice;

        switch (choice) {
        case '1': {
            system("cls");
            string id;
            cout << "请输入学号: ";
            cin >> id;
            cout << "===========================================================" << endl;

            bool found = false;
            for (const auto& student : students) {
                if (student.Sid == id) {
                    student.StuDisplay();// 显示学生信息
                    cout << "===========================================================" << endl;

                    if (!student.grades.empty()) {
                        cout << "|                       成绩信息                       |" << endl;
                        cout << "========================================================" << endl;
                        Table_Student_Grade_Display(id);// 显示成绩
                        cout << "========================================================" << endl;
                    }
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "未找到学号为 " << id << " 的学生！" << endl;
            system("pause");
            break;
        }// 按学号查询

        case '2': {
            system("cls");
            string name;
            cout << "请输入姓名: ";
            cin >> name;
            cout << "===========================================================" << endl;
            bool found = false;
            // 遍历查找学生
            for (const auto& student : students) {
                if (student.Sname == name) {
                    student.StuDisplay();
                    cout << "===========================================================" << endl;
                    if (!student.grades.empty()) {
                        cout << "|                       成绩信息                       |" << endl;
                        cout << "========================================================" << endl;
                        Table_Student_Grade_Display(student.Sid);
                        cout << "========================================================" << endl;
                    }
                    found = true;
                }
            }

            if (!found)
                cout << "未找到姓名为 " << name << " 的学生！" << endl;
            system("pause");
            break;
        }// 按姓名查询（逻辑同按学号）

        case '3': {
            system("cls");
            string className;
            cout << "请输入班级: ";
            cin >> className;
            cout << "===========================================================" << endl;
            bool found = false;
            for (const auto& student : students) {
                if (student.Sclass == className) {
                    student.StuDisplay();
                    cout << "===========================================================" << endl;
                    if (!student.grades.empty()) {
                        cout << "|                       成绩信息                       |" << endl;
                        cout << "========================================================" << endl;
                        Table_Student_Grade_Display(student.Sid);
                        cout << "========================================================" << endl;
                    }
                    found = true;
                }
            }

            if (!found)
                cout << "未找到班级为 " << className << " 的学生！" << endl;
            system("pause");
            break;
        }// 按班级查询（显示该班级所有学生）

        case 'q':
            flag = 0;
            break;
        default:
            cout << "！！！请选择正确的选项！！！" << endl;
        }
    }
}

//-------------------------------------------开机自启动---------------------------------------------
//读取界面
void AdminManager::Load_Students() {
    //打开文件
    std::string filename = "students_data.csv";
    std::ifstream inFile(filename, std::ios::in);
    //文件打开失败提示
    if (!inFile) {
        std::cerr << "无法打开文件进行读取！" << std::endl;
        return;
    }

    std::string line;
    // 读取表头，丢弃
    std::getline(inFile, line);
    //遍历所有学生读取
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        //读取表头
        std::string sid, sname, sbirth, ssex, sclass, cname, credit, gpa;
        //读取数据
        std::getline(ss, sid, ',');
        std::getline(ss, sname, ',');
        std::getline(ss, sbirth, ',');
        std::getline(ss, ssex, ',');
        std::getline(ss, sclass, ',');
        std::getline(ss, cname, ',');
        std::getline(ss, credit, ',');
        std::getline(ss, gpa, ',');
        //将读取到的数据存入Student和Grade类中
        Grade grade(cname, std::stof(credit), std::stof(gpa));
        //判断是否为新学生的参数
        bool found = false;
        // 查找已有学生
        for (auto& student : students) {
            if (student.Sid == sid) {
                student.grades.push_back(grade);
                found = true;
                break;
            }
        }
        // 如果是新学生，创建新的 Student 对象
        if (!found) {
            Student student(sid, sname, sbirth, ssex, sclass);
            student.grades.push_back(grade);
            students.push_back(student);
        }
    }
    //关闭文件
    inFile.close();
}
// ---------------------------------------------------发送信息---------------------------------------------------------
void AdminManager::MailboxMenu() {
    while (true) {
        system("cls");
        int unreadCount = MessageManager::GetUnreadCount("admin");

        cout << "========================================================" << endl;
        cout << "|                     管理员邮箱系统                    |" << endl;
        cout << "========================================================" << endl;
        cout << "|                    请选择操作：                      |" << endl;
        cout << "========================================================" << endl;
        cout << "|                    1.查看消息"
            << (unreadCount > 0 ? "(" + to_string(unreadCount) + "条未读)" : "")
            << string(20 - 8 - (unreadCount > 0 ? (4 + to_string(unreadCount).length()) : 0), ' ') << endl;
        cout << "|                    2.发送消息给学生                  |" << endl;
        cout << "|                    0.返回上级菜单                    |" << endl;
        cout << "========================================================" << endl;
        cout << "请选择操作>";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            MessageManager::ViewMessages("admin");
            system("pause");
            break;
        case 2:
            ReplyToStudentScreen();
            system("pause");
            break;
        case 0:
            return;
        default:
            cout << "无效的选择，请重新输入！" << endl;
            system("pause");
        }
    }
}

void AdminManager::ReplyToStudentScreen() {
    // 先显示所有学生
    Table_Student_Information_Display();

    string studentName;
    cout << "请输入要回复的学生姓名: ";
    cin >> studentName;

    // 检查学生是否存在
    bool studentExists = false;
    for (const auto& student : students) {
        if (student.Sname == studentName) {
            studentExists = true;
            break;
        }
    }

    if (!studentExists) {
        cout << "学生不存在！\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "请输入回复内容（输入空行结束）:\n";
    string content;
    string line;

    while (getline(cin, line) && !line.empty()) {
        content += line + "\n";
    }

    if (!content.empty()) {
        MessageManager::SendMessage("admin", studentName, content, Message::RESPONSE);
        cout << "回复已发送给学生 " << studentName << "！\n";
    }
    else {
        cout << "回复内容为空，未发送。\n";
    }
}
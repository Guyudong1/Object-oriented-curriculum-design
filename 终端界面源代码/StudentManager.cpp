#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

using namespace std;

#include "StudentManager.h"
#include "AdminManager.h"
#include "KeyManager.h"
#include "MessageManager.h"


//*********************************************学生查看系统菜单******************************************************

int StudentManager::Student_Menu() {
    int unreadCount = MessageManager::GetUnreadCount(Current_name);

    cout << "========================================================" << endl;
    cout << "|             上海海事大学学生档案管理系统             |" << endl;
    cout << "========================================================" << endl;
    cout << "|                    请选择功能：                      |" << endl;
    cout << "========================================================" << endl;
    cout << "|                    1.查看个人信息                    |" << endl;
    cout << "|                    2.查看成绩                        |" << endl;
    cout << "|                    3.查询课程平均绩点                |" << endl;
    cout << "|                    4.查询所在班级的总排名            |" << endl;
    cout << "|                    5.修改密码                        |" << endl;
    cout << "|                    6.注销账户                        |" << endl;
    cout << "|                    7.邮箱"
        << (unreadCount > 0 ? ("(新消息" + to_string(unreadCount) + "条)") : "")
        << string(20 - 6 - (unreadCount > 0 ? (6 + to_string(unreadCount).length()) : 0), ' ') << "              " << endl;
    cout << "|                    0.退出系统                        |" << endl;
    cout << "========================================================" << endl;
    cout << "请选择功能>";
    int s = -1;
    cin >> s;
    return s;
}

// StudentManager 构造函数
StudentManager::StudentManager(const vector<Student>& allStudents, const string& studentname)
    : students(allStudents), Current_name(studentname) {
    //// 调试输出
    //cout << "StudentManager 初始化: " << Current_name << endl;
    //cout << "学生数量: " << students.size() << endl;
}
void StudentManager::ViewPersonalInfo()//查看个人信息
{
    for (const auto& student : students)
    {
        if (student.Sname == Current_name)
        {
            student.StuDisplay();
            return;
        }
    }
    std::cout << "未找到该学生信息。" << std::endl;
}

void StudentManager::ViewGrades()//查看成绩
{
    for (const auto& student : students)
    {
        if (student.Sname == Current_name)
        {
            cout << left << setw(15) << "课程名称"
                << setw(15) << "课程学分"
                << setw(8) << "课程绩点" << endl;
            cout << "--------------------------------------------------------" << endl;
            for (auto& grades : student.grades)
                cout << left << setw(15) << grades.Cname
                 << setw(15) << grades.Credit
                 << setw(8) << grades.GPA << endl;
            return;
        }
    }
    std::cout << "未找到该学生信息。" << std::endl;
}

//*******************************************查询学生所有的课程的平均绩点和最高绩点*********************************************
void StudentManager::QueryCourseAverageGPA() {
    // 1. 找到当前学生
    const Student* currentStudent = nullptr;
    for (const auto& student : students) {
        if (student.Sname == Current_name) {
            currentStudent = &student;
            break;
        }
    }

    if (!currentStudent) {
        cout << "未找到该学生信息。" << endl;
        return;
    }

    if (currentStudent->grades.empty()) {
        cout << "该学生暂无成绩信息。" << endl;
        return;
    }

    // 2. 获取当前学生的班级
    string currentClass = currentStudent->Sclass;

    // 3. 打印表头
    cout << "--------------------------------------------------------" << endl;
    cout << left << setw(15) << "课程名称"
        << setw(15) << "我的绩点"
        << setw(15) << "班级平均"
        << setw(15) << "班级最高" << endl;
    cout << "--------------------------------------------------------" << endl;

    // 4. 遍历当前学生的每门课程
    for (const auto& myGrade : currentStudent->grades) {
        string courseName = myGrade.Cname;
        float myGPA = myGrade.GPA;

        // 计算该课程的全班数据
        float totalGPA = 0.0f;
        float maxGPA = 0.0f;
        int studentCount = 0;

        for (const auto& student : students) {
            if (student.Sclass == currentClass) {
                for (const auto& grade : student.grades) {
                    if (grade.Cname == courseName) {
                        totalGPA += grade.GPA;
                        if (grade.GPA > maxGPA) {
                            maxGPA = grade.GPA;
                        }
                        studentCount++;
                        break; // 每个学生只计算一次该课程
                    }
                }
            }
        }

        float averageGPA = studentCount > 0 ? totalGPA / studentCount : 0.0f;

        // 输出该课程的信息
        cout << left << setw(15) << courseName
            << setw(15) << fixed << setprecision(2) << myGPA
            << setw(15) << averageGPA
            << setw(15) << maxGPA << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}
//*****************************************************查询排名*********************************************************
// 计算加权GPA
float StudentManager::CalculateWeightedGPA(const Student& student) const {
    if (student.grades.empty()) return 0.0f;

    float totalWeighted = 0.0f;
    float totalCredits = 0.0f;

    for (const auto& grade : student.grades) {
        totalWeighted += grade.GetGPA() * grade.GetCredit();
        totalCredits += grade.GetCredit();
    }

    return totalCredits > 0 ? totalWeighted / totalCredits : 0.0f;
}

// 班级排名
int StudentManager::GetClassRank() {
    // 1. 获取当前学生信息
    const Student* currentStudent = nullptr;
    for (const auto& student : students) {
        if (student.Sname == Current_name) {
            currentStudent = &student;
            break;
        }
    }
    if (!currentStudent) return -1;

    // 2. 收集同班级学生
    vector<pair<string, float>> classStudents;
    for (const auto& student : students) {
        if (student.Sclass == currentStudent->Sclass) {
            classStudents.emplace_back(student.Sname, CalculateWeightedGPA(student));
        }
    }

    // 3. 排序并查找排名
    sort(classStudents.begin(), classStudents.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    for (int i = 0; i < classStudents.size(); ++i) {
        if (classStudents[i].first == Current_name) {
            return i + 1;
        }
    }
    return -1;
}

// 全校排名
int StudentManager::GetTotalRank() {
    vector<pair<string, float>> allStudents;
    for (const auto& student : students) {
        allStudents.emplace_back(student.Sname, CalculateWeightedGPA(student));
    }

    sort(allStudents.begin(), allStudents.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    for (int i = 0; i < allStudents.size(); ++i) {
        if (allStudents[i].first == Current_name) {
            return i + 1;
        }
    }
    return -1;
}

// 排名查询界面
void StudentManager::QueryGradeRanking() {
    // 获取当前学生信息
    const Student* currentStudent = nullptr;
    for (const auto& student : students) {
        if (student.Sname == Current_name) {
            currentStudent = &student;
            break;
        }
    }

    if (!currentStudent) {
        cout << "无法获取学生信息。" << endl;
        return;
    }

    // 计算加权GPA
    float weightedGPA = CalculateWeightedGPA(*currentStudent);

    // 获取排名
    int classRank = GetClassRank();
    int totalRank = GetTotalRank();

    if (classRank == -1 || totalRank == -1) {
        cout << "无法获取排名信息，请确认成绩数据已录入。" << endl;
        return;
    }

    cout << fixed << setprecision(2);
    cout << "--------------------- 排名信息 ------------------------" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << left << setw(15) << "平均绩点"
        << setw(15) << "班级排名"
        << setw(8) << "全校排名" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << left << setw(15) << weightedGPA
        << setw(15) << classRank
        << setw(8) << totalRank << endl;
    cout << "--------------------------------------------------------" << endl;
}

//**********************************************************信息*****************************************************
void StudentManager::MailboxMenu() {
    while (true) {
        system("cls");
        int unreadCount = MessageManager::GetUnreadCount(Current_name);

        cout << "========================================================" << endl;
        cout << "|                     学生邮箱系统                     |" << endl;
        cout << "========================================================" << endl;
        cout << "|                    请选择操作：                      |" << endl;
        cout << "========================================================" << endl;
        cout << "|                    1.查看消息"
            << (unreadCount > 0 ? "(" + to_string(unreadCount) + "条未读)" : "")
            << string(20 - 8 - (unreadCount > 0 ? (4 + to_string(unreadCount).length()) : 0), ' ')<< endl;
        cout << "|                    2.发送消息给管理员                |" << endl;
        cout << "|                    0.返回上级菜单                    |" << endl;
        cout << "========================================================" << endl;
        cout << "请选择操作>";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            MessageManager::ViewMessages(Current_name);
            system("pause");
            break;
        case 2:
            ContactAdminScreen();
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

void StudentManager::ContactAdminScreen() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "请输入要发送给管理员的消息内容（输入空行结束）:\n";
    string content;
    string line;

    // 收集多行输入，直到输入空行
    while (getline(cin, line)) {
        if (line.empty()) {
            break;
        }
        content += line + "\n";
    }

    if (!content.empty()) {
        // 显示预览
        cout << "\n===== 回复预览 =====\n";
        cout << content;
        cout << "===================\n";

        // 确认发送
        cout << "确认发送？(y/n): ";
        char confirm;
        cin >> confirm;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (tolower(confirm) == 'y') {
            MessageManager::SendMessage(Current_name, "admin", content, Message::REQUEST);
            cout << "消息已发送给管理员！\n";
        }
        else
            cout << "消息内容为空，未发送。\n";
    }
}
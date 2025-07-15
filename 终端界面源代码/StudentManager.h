#pragma once

#include "AdminManager.h"
#include "KeyManager.h"
#include "MessageManager.h"
#include <vector>

class StudentManager {
private:

    std::vector<Student> students;

    std::string Current_name;  // 当前登录学生的name

public:
    StudentManager(const std::vector<Student>& allStudents, const std::string& studentname);

    // 学生菜单
    int Student_Menu();

    // 查看个人信息
    void ViewPersonalInfo();

    // 查看成绩
    void ViewGrades();

    // 查询课程平均绩点
    void QueryCourseAverageGPA();

    // 查询班级排名
    void QueryGradeRanking();

    void MailboxMenu();

    void ContactAdminScreen();
private:
    // 计算加权GPA（内部使用）
    float CalculateWeightedGPA(const Student& student) const;

    // 排名计算
    int GetClassRank();    // 班级内排名

    int GetTotalRank();    // 全校总排名



};
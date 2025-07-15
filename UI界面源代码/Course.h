#pragma once
#include <string>

class Course {
public:
    std::string cname;  // 课程名
    std::string credit; // 学分
    std::string gpa;    // 绩点

    Course() = default;
    Course(const std::string& cname, const std::string& credit, const std::string& gpa)
        : cname(cname), credit(credit), gpa(gpa) {}

    // 用于显示课程信息
    std::string formatInfo() const {
        return cname + " " + credit + " " + gpa;
    }
};


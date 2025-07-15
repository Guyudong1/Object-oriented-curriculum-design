#pragma once
#include <string>

class Course {
public:
    std::string cname;  // �γ���
    std::string credit; // ѧ��
    std::string gpa;    // ����

    Course() = default;
    Course(const std::string& cname, const std::string& credit, const std::string& gpa)
        : cname(cname), credit(credit), gpa(gpa) {}

    // ������ʾ�γ���Ϣ
    std::string formatInfo() const {
        return cname + " " + credit + " " + gpa;
    }
};


#pragma once
#include <string>
#include <sstream>
#include "Course.h"
#include<vector>

class Stu_data {
public:
    std::string sid;
    std::string sname;
    std::string sbirth;
    std::string ssex;
    std::string sclass;
    std::string cname;
    std::string credit;
    std::string gpa;
    std::vector<Course> courses;  // �洢�γ���Ϣ

    Stu_data() = default;
    Stu_data(const std::string& sid, const std::string& sname, const std::string& sbirth, const std::string& ssex, const std::string& sclass, const std::string& cname, const std::string& credit, const std::string& gpa)
        : sid(sid), sname(sname), sbirth(sbirth), ssex(ssex),sclass(sclass),cname(cname),credit(credit), gpa(gpa){}

    std::string formatInfo() const {
        std::stringstream ss;
        ss << sid << "," << sname << "," << sbirth << "," << ssex <<"," << sclass << "," << cname << "," << credit << "," << gpa;
        // �����пγ���Ϣ��ӵ��ַ�����
        for (const auto& course : courses) {
            ss << "," << course.cname << "," << course.credit << "," << course.gpa;
        }
        return ss.str();
    }

    void formatwrite(const std::string& str) {
        std::stringstream ss(str);
        getline(ss, sid, ',');
        getline(ss, sname, ',');
        getline(ss, sbirth, ',');
        getline(ss, ssex, ',');
        getline(ss, sclass, ',');
        getline(ss, cname, ',');
        getline(ss, credit, ',');
        getline(ss, gpa, ',');

        // ��ȡ�γ���Ϣ
        std::string courseName, courseCredit, courseGPA;
        while (getline(ss, courseName, ',') && getline(ss, courseCredit, ',') && getline(ss, courseGPA, ',')) {
            courses.push_back(Course(courseName, courseCredit, courseGPA));  // ���γ���Ϣ��ӵ� courses ����
        }
    }
    // ��������������ѧ����Ϣ
    void setStudentInfo(const std::string& sid, const std::string& sname, const std::string& sbirth, const std::string& ssex, const std::string& sclass) {
        this->sid = sid;
        this->sname = sname;
        this->sbirth = sbirth;
        this->ssex = ssex;
        this->sclass = sclass;
    }
    void setStudentInfo1(const std::string& sid, const std::string& sname, const std::string& sbirth, const std::string& ssex, const std::string& sclass,
        const std::string& cname, const std::string& credit, const std::string& gpa) {
        this->sid = sid;
        this->sname = sname;
        this->sbirth = sbirth;
        this->ssex = ssex;
        this->sclass = sclass;
        this->cname = cname;  // ���ÿγ���
        this->credit = credit;  // ����ѧ��
        this->gpa = gpa;  // ���ü���
        addCourse(cname, credit, gpa);  // ��ӿγ�
    }
    void addCourse(const std::string& cname, const std::string& credit, const std::string& gpa) {
        courses.push_back(Course(cname, credit, gpa));  // ʹ�� Course ��Ĺ��캯����ӿγ�
    }
};

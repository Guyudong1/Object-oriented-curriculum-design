#pragma once

#include "AdminManager.h"
#include "KeyManager.h"
#include "MessageManager.h"
#include <vector>

class StudentManager {
private:

    std::vector<Student> students;

    std::string Current_name;  // ��ǰ��¼ѧ����name

public:
    StudentManager(const std::vector<Student>& allStudents, const std::string& studentname);

    // ѧ���˵�
    int Student_Menu();

    // �鿴������Ϣ
    void ViewPersonalInfo();

    // �鿴�ɼ�
    void ViewGrades();

    // ��ѯ�γ�ƽ������
    void QueryCourseAverageGPA();

    // ��ѯ�༶����
    void QueryGradeRanking();

    void MailboxMenu();

    void ContactAdminScreen();
private:
    // �����ȨGPA���ڲ�ʹ�ã�
    float CalculateWeightedGPA(const Student& student) const;

    // ��������
    int GetClassRank();    // �༶������

    int GetTotalRank();    // ȫУ������



};
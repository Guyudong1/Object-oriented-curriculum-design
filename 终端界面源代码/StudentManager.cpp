#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

using namespace std;

#include "StudentManager.h"
#include "AdminManager.h"
#include "KeyManager.h"
#include "MessageManager.h"


//*********************************************ѧ���鿴ϵͳ�˵�******************************************************

int StudentManager::Student_Menu() {
    int unreadCount = MessageManager::GetUnreadCount(Current_name);

    cout << "========================================================" << endl;
    cout << "|             �Ϻ����´�ѧѧ����������ϵͳ             |" << endl;
    cout << "========================================================" << endl;
    cout << "|                    ��ѡ���ܣ�                      |" << endl;
    cout << "========================================================" << endl;
    cout << "|                    1.�鿴������Ϣ                    |" << endl;
    cout << "|                    2.�鿴�ɼ�                        |" << endl;
    cout << "|                    3.��ѯ�γ�ƽ������                |" << endl;
    cout << "|                    4.��ѯ���ڰ༶��������            |" << endl;
    cout << "|                    5.�޸�����                        |" << endl;
    cout << "|                    6.ע���˻�                        |" << endl;
    cout << "|                    7.����"
        << (unreadCount > 0 ? ("(����Ϣ" + to_string(unreadCount) + "��)") : "")
        << string(20 - 6 - (unreadCount > 0 ? (6 + to_string(unreadCount).length()) : 0), ' ') << "              " << endl;
    cout << "|                    0.�˳�ϵͳ                        |" << endl;
    cout << "========================================================" << endl;
    cout << "��ѡ����>";
    int s = -1;
    cin >> s;
    return s;
}

// StudentManager ���캯��
StudentManager::StudentManager(const vector<Student>& allStudents, const string& studentname)
    : students(allStudents), Current_name(studentname) {
    //// �������
    //cout << "StudentManager ��ʼ��: " << Current_name << endl;
    //cout << "ѧ������: " << students.size() << endl;
}
void StudentManager::ViewPersonalInfo()//�鿴������Ϣ
{
    for (const auto& student : students)
    {
        if (student.Sname == Current_name)
        {
            student.StuDisplay();
            return;
        }
    }
    std::cout << "δ�ҵ���ѧ����Ϣ��" << std::endl;
}

void StudentManager::ViewGrades()//�鿴�ɼ�
{
    for (const auto& student : students)
    {
        if (student.Sname == Current_name)
        {
            cout << left << setw(15) << "�γ�����"
                << setw(15) << "�γ�ѧ��"
                << setw(8) << "�γ̼���" << endl;
            cout << "--------------------------------------------------------" << endl;
            for (auto& grades : student.grades)
                cout << left << setw(15) << grades.Cname
                 << setw(15) << grades.Credit
                 << setw(8) << grades.GPA << endl;
            return;
        }
    }
    std::cout << "δ�ҵ���ѧ����Ϣ��" << std::endl;
}

//*******************************************��ѯѧ�����еĿγ̵�ƽ���������߼���*********************************************
void StudentManager::QueryCourseAverageGPA() {
    // 1. �ҵ���ǰѧ��
    const Student* currentStudent = nullptr;
    for (const auto& student : students) {
        if (student.Sname == Current_name) {
            currentStudent = &student;
            break;
        }
    }

    if (!currentStudent) {
        cout << "δ�ҵ���ѧ����Ϣ��" << endl;
        return;
    }

    if (currentStudent->grades.empty()) {
        cout << "��ѧ�����޳ɼ���Ϣ��" << endl;
        return;
    }

    // 2. ��ȡ��ǰѧ���İ༶
    string currentClass = currentStudent->Sclass;

    // 3. ��ӡ��ͷ
    cout << "--------------------------------------------------------" << endl;
    cout << left << setw(15) << "�γ�����"
        << setw(15) << "�ҵļ���"
        << setw(15) << "�༶ƽ��"
        << setw(15) << "�༶���" << endl;
    cout << "--------------------------------------------------------" << endl;

    // 4. ������ǰѧ����ÿ�ſγ�
    for (const auto& myGrade : currentStudent->grades) {
        string courseName = myGrade.Cname;
        float myGPA = myGrade.GPA;

        // ����ÿγ̵�ȫ������
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
                        break; // ÿ��ѧ��ֻ����һ�θÿγ�
                    }
                }
            }
        }

        float averageGPA = studentCount > 0 ? totalGPA / studentCount : 0.0f;

        // ����ÿγ̵���Ϣ
        cout << left << setw(15) << courseName
            << setw(15) << fixed << setprecision(2) << myGPA
            << setw(15) << averageGPA
            << setw(15) << maxGPA << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}
//*****************************************************��ѯ����*********************************************************
// �����ȨGPA
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

// �༶����
int StudentManager::GetClassRank() {
    // 1. ��ȡ��ǰѧ����Ϣ
    const Student* currentStudent = nullptr;
    for (const auto& student : students) {
        if (student.Sname == Current_name) {
            currentStudent = &student;
            break;
        }
    }
    if (!currentStudent) return -1;

    // 2. �ռ�ͬ�༶ѧ��
    vector<pair<string, float>> classStudents;
    for (const auto& student : students) {
        if (student.Sclass == currentStudent->Sclass) {
            classStudents.emplace_back(student.Sname, CalculateWeightedGPA(student));
        }
    }

    // 3. ���򲢲�������
    sort(classStudents.begin(), classStudents.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    for (int i = 0; i < classStudents.size(); ++i) {
        if (classStudents[i].first == Current_name) {
            return i + 1;
        }
    }
    return -1;
}

// ȫУ����
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

// ������ѯ����
void StudentManager::QueryGradeRanking() {
    // ��ȡ��ǰѧ����Ϣ
    const Student* currentStudent = nullptr;
    for (const auto& student : students) {
        if (student.Sname == Current_name) {
            currentStudent = &student;
            break;
        }
    }

    if (!currentStudent) {
        cout << "�޷���ȡѧ����Ϣ��" << endl;
        return;
    }

    // �����ȨGPA
    float weightedGPA = CalculateWeightedGPA(*currentStudent);

    // ��ȡ����
    int classRank = GetClassRank();
    int totalRank = GetTotalRank();

    if (classRank == -1 || totalRank == -1) {
        cout << "�޷���ȡ������Ϣ����ȷ�ϳɼ�������¼�롣" << endl;
        return;
    }

    cout << fixed << setprecision(2);
    cout << "--------------------- ������Ϣ ------------------------" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << left << setw(15) << "ƽ������"
        << setw(15) << "�༶����"
        << setw(8) << "ȫУ����" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << left << setw(15) << weightedGPA
        << setw(15) << classRank
        << setw(8) << totalRank << endl;
    cout << "--------------------------------------------------------" << endl;
}

//**********************************************************��Ϣ*****************************************************
void StudentManager::MailboxMenu() {
    while (true) {
        system("cls");
        int unreadCount = MessageManager::GetUnreadCount(Current_name);

        cout << "========================================================" << endl;
        cout << "|                     ѧ������ϵͳ                     |" << endl;
        cout << "========================================================" << endl;
        cout << "|                    ��ѡ�������                      |" << endl;
        cout << "========================================================" << endl;
        cout << "|                    1.�鿴��Ϣ"
            << (unreadCount > 0 ? "(" + to_string(unreadCount) + "��δ��)" : "")
            << string(20 - 8 - (unreadCount > 0 ? (4 + to_string(unreadCount).length()) : 0), ' ')<< endl;
        cout << "|                    2.������Ϣ������Ա                |" << endl;
        cout << "|                    0.�����ϼ��˵�                    |" << endl;
        cout << "========================================================" << endl;
        cout << "��ѡ�����>";

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
            cout << "��Ч��ѡ�����������룡" << endl;
            system("pause");
        }
    }
}

void StudentManager::ContactAdminScreen() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "������Ҫ���͸�����Ա����Ϣ���ݣ�������н�����:\n";
    string content;
    string line;

    // �ռ��������룬ֱ���������
    while (getline(cin, line)) {
        if (line.empty()) {
            break;
        }
        content += line + "\n";
    }

    if (!content.empty()) {
        // ��ʾԤ��
        cout << "\n===== �ظ�Ԥ�� =====\n";
        cout << content;
        cout << "===================\n";

        // ȷ�Ϸ���
        cout << "ȷ�Ϸ��ͣ�(y/n): ";
        char confirm;
        cin >> confirm;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (tolower(confirm) == 'y') {
            MessageManager::SendMessage(Current_name, "admin", content, Message::REQUEST);
            cout << "��Ϣ�ѷ��͸�����Ա��\n";
        }
        else
            cout << "��Ϣ����Ϊ�գ�δ���͡�\n";
    }
}
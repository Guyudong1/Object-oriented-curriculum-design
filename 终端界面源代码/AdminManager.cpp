#include <iostream>
using namespace std;
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

#include "AdminManager.h"


//----------Studentʵ��-----------
Student::Student(string Id, string Name, string Birth, string Sex, string Class) :Sid(Id), Sname(Name), Sbirth(Birth), Ssex(Sex), Sclass(Class) {}
string Student::GetId() { return Sid; }
string Student::GetName() { return Sname; }
string Student::GetBirth() { return Sbirth; }
string Student::GetSex() { return Ssex; }
string Student::GetClass() { return Sclass; }
//ѧ����Ϣ��ӡ
void Student::StuDisplay() const {
    cout << left << setw(18) << "ѧ��"
        << setw(10) << "����"
        << setw(15) << "����"
        << setw(8) << "�Ա�"
        << setw(10) << "���ڰ༶" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << left << setw(18) << Sid
        << setw(10) << Sname
        << setw(15) << Sbirth
        << setw(8) << Ssex
        << setw(10) << Sclass << endl;
}
//ѧ���ɼ���ӡ
void Student::GradesDisplay() const {
    cout << Sname << " (" << Sid << ")�ĳɼ���" << endl;
    cout << left << setw(18) << "�γ���"
        << setw(10) << "�γ�ѧ��"
        << setw(10) << "�γ̼���"<<endl;
    cout << "-------------------------------------------------------" << endl;
    for (const auto& g : grades) {
        g.GradeDisplay();
    }
}

//----------Gradeʵ��------------
Grade::Grade() : Cname("��"), Credit(0.0), GPA(0.0) {}
Grade::Grade(string name, float credit, float gpa) :Cname(name), Credit(credit), GPA(gpa) {}
Grade::~Grade() {}
string Grade::GetCname() const { return Cname; }
float Grade::GetCredit() const { return Credit; }
float Grade::GetGPA() const { return GPA; }
//�ɼ���ӡ
void Grade::GradeDisplay() const {
    cout <<left<<setw(18)<< Cname <<setw(10)<< Credit <<setw(10) <<  GPA << endl;
}

//----------StudentManagerʵ��-----------

// ++++++++++++++++++++++++++++����Ա����++++++++++++++++++++++++++++++++++

//**********************************************��ϵͳ�˵�**************************************************
int AdminManager::Admin_Menu() {
    int s = -1;
    int unreadCount = MessageManager::GetUnreadCount("admin");
    while (true) {


        cout << "========================================================" << endl;
        cout << "|             �Ϻ����´�ѧѧ����������ϵͳ             |" << endl;
        cout << "========================================================" << endl;
        cout << "|                    ��ѡ���ܣ�                      |" << endl;
        cout << "========================================================" << endl;
        cout << "|                    1.¼��ѧ����Ϣ                    |" << endl;
        cout << "|                    2.��ӡѧ����Ϣ                    |" << endl;
        cout << "|                    3.����ѧ����Ϣ                    |" << endl;
        cout << "|                    4.��ȡѧ����Ϣ                    |" << endl;
        cout << "|                    5.����ѧ����Ϣ                    |" << endl;
        cout << "|                    6.ɾ��ѧ����Ϣ                    |" << endl;
        cout << "|                    7.�޸�ѧ����Ϣ                    |" << endl;
        cout << "|                    8.��ѯѧ����Ϣ                    |" << endl;
        cout << "|                    9.�û��������                    |" << endl;
        cout << "|                    10.����"
            << (unreadCount > 0 ? ("(����Ϣ" + to_string(unreadCount) + "��)") : "")
            << string(20 - 6 - (unreadCount > 0 ? (6 + to_string(unreadCount).length()) : 0), ' ') << "              " << endl;
        cout << "|                    0.�˳���ϵͳ                      |" << endl;
        cout << "========================================================" << endl;
        cout << "��ѡ����>";


        cin >> s;

        if (cin.fail()) {
            cin.clear(); // �������״̬
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������������
            system("cls");
            cout << "!!!!! ��������ȷ����ѡ�0-9��!!!!!" << endl;
        }
        else if (s < 0 || s > 10) {
            system("cls");
            cout << "!!!!! ��������ȷ����ѡ�0-9��!!!!!" << endl;
        }
        else {
            break;
        }
    }

    return s;
}


//********************************************����һ��¼��ѧ����Ϣ***********************************************
//¼��ѧ����Ϣ
string AdminManager::Add_Student_Information() {
    string id, name, birth, sex, sclass;
    cout << "=============================" << endl;
    cout << "        ¼��ϵͳ,��q�˳�            " << endl;
    cout << "=============================" << endl;
    cout << "ѧ�ţ� ";
    cin >> id;
    if (id == "q")
        return "ERROR";
    cout << "����: ";
    cin >> name;
    if (name == "q")
        return "ERROR";
    cout << "����(YYYY-MM-DD): ";
    cin >> birth;
    if (birth == "q")
        return "ERROR";
    cout << "�Ա�(��/Ů): ";
    cin >> sex;
    if (sex == "q")
        return "ERROR";
    cout << "���ڰ༶: ";
    cin >> sclass;

    cout << "=============================" << endl;
    for (const auto& student : students) {
        if (student.Sid == id) {
            cout << "¼��ʧ�ܣ����и�ѧ��ѧ��������ظ���" << endl;
            return "ERROR";
        }
    }
    students.emplace_back(id, name, birth, sex, sclass);
    cout << "ѧ��¼��ɹ�������" << endl;
    cout << "ѧ��: " << id << ", ����: " << name << ", ����: " << birth << ", �Ա�: " << sex << ", ���ڰ༶: " << sclass << endl;
    cout << "=============================" << endl;
    return id;
}
//¼��ѧ���ɼ�
void AdminManager::Add_Student_Grade(string studentID, const Grade& grade) {
    for (auto& student : students)
        if (student.Sid == studentID) {
            student.grades.push_back(grade);
            cout << "¼��ɼ���ѧ����" << student.Sname << endl;
            return;
        }
    cout << "¼��ʧ��!��ѧ��δ�ҵ�!" << endl;
}
//¼��ѧ����Ϣ����
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
        cout << "�Ƿ�����ѧ���ɼ�����y/n��";
        cin >> k;
        if (k == 'y') {
            string name;
            float credit;
            float gpa;

            while (1) {
                char c1;
                cout << "=============================" << endl;
                cout << "�γ�����";
                cin >> name;
                cout << "ѧ�֣�";
                cin >> credit;
                cout << "���㣺";
                cin >> gpa;
                cout << "=============================" << endl;
                Add_Student_Grade(id, Grade(name, credit, gpa));
                cout << "��������ɼ�?��y/n��";
                cin >> c1;
                if (c1 == 'y')
                    cout << "�������룺" << endl;
                else if (c1 == 'n')
                    break;
            }
        }
        else if (k == 'n')
            Add_Student_Grade(id, Grade());
        cout << "��������ѧ����Ϣ����y/n��";
        cin >> c2;
        if (c2 == 'y')
            cout << "��������ѧ����Ϣ��" << endl;
        else if (c2 == 'n') {
            break;
        }
    }
}

//****************************************���ܶ�����ӡѧ����Ϣ*********************************************
//------------���ʵ��---------------
//ѧ����Ϣ��
void AdminManager::Table_Student_Information_Display() {
    cout << left << setw(18) << "ѧ��"
        << setw(10) << "����"
        << setw(15) << "����"
        << setw(8) << "�Ա�"
        << setw(10) << "���ڰ༶" << endl;
    cout << "-----------------------------------------------------------" << endl;
    for (auto& student : students)
        cout << left << setw(18) << student.Sid
        << setw(10) << student.Sname
        << setw(15) << student.Sbirth
        << setw(8) << student.Ssex
        << setw(10) << student.Sclass << endl;
}
//ѧ���ɼ���
void AdminManager::Table_Student_Grade_Display(string id) {
    
    cout << left << setw(15) << "�γ�����"
        << setw(15) << "�γ�ѧ��"
        << setw(8) << "�γ̼���" << endl;
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
//�ж�ID�Ƿ���User����
bool AdminManager::In_Id(string id) {
    for (auto& student : students)
        if (student.Sid == id)
            return 1;
    return 0;
}
//��ӡ����ѧ���Ļ�����Ϣ
string AdminManager::Student_Information_Display() {
    string s;
    system("cls");
    Table_Student_Information_Display();
    cout << "����ѧ�Ų鿴��Ӧ�ɼ�,��q�˳���";
    cin >> s;
    return s;
}
//��ӡָ��ѧ�������гɼ�
void AdminManager::Student_Grade_Display(string id) {
    cout << "idΪ" << id << "�ĳɼ�Ϊ��" << endl;
    Table_Student_Grade_Display(id);

}
//��ӡ����
void AdminManager::Display_Student_Screem() {
    string s;
    s = Student_Information_Display();
    while (1) {
        if (s == "q") {
            break;
        }
        else if (In_Id(s)) {
            Student_Grade_Display(s);
            cout << "����ѧ�Ų鿴��Ӧ�ɼ�,��q�˳���";
            cin >> s;

        }
        else {
            cout << "��ѧ�ŵ�ѧ�������ڡ�" << endl;
            cout << "����ѧ�Ų鿴��Ӧ�ɼ�,��q�˳���";
            cin >> s;
        }
    }
}

//***********************************************������������ѧ����Ϣ***********************************************

//���ݽ���
void AdminManager::Backup_Student_Screem() {
    //���ļ�
    std::string filename = "students_data.csv";
    std::ofstream outFile(filename, std::ios::out);
    //��ʧ����ʾ
    if (!outFile) {
        std::cerr << "�޷����ļ�����д�룡" << std::endl;
        return;
    }
    // д���ͷ
    outFile << "ѧ��ID,����,����,�Ա�,�༶,�γ���,ѧ��,GPA\n";
    // ��������ѧ����ӡ
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
    //�ر��ļ�
    outFile.close();
    //�ɹ���ʾ
    std::cout << "ѧ����Ϣ�ѳɹ����ݵ� " << filename << std::endl;
}

//********************************�����ģ���ȡѧ����Ϣ***********************************

//��ȡ����
void AdminManager::Read_Student_Screem() {
    //���ļ�
    std::string filename = "students_data.csv";
    std::ifstream inFile(filename, std::ios::in);
    //�ļ���ʧ����ʾ
    if (!inFile) {
        std::cerr << "�޷����ļ����ж�ȡ��" << std::endl;
        return;
    }

    std::string line;
    // ��ȡ��ͷ������
    std::getline(inFile, line);
    //��������ѧ����ȡ
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        //��ȡ��ͷ
        std::string sid, sname, sbirth, ssex, sclass, cname, credit, gpa;
        //��ȡ����
        std::getline(ss, sid, ',');
        std::getline(ss, sname, ',');
        std::getline(ss, sbirth, ',');
        std::getline(ss, ssex, ',');
        std::getline(ss, sclass, ',');
        std::getline(ss, cname, ',');
        std::getline(ss, credit, ',');
        std::getline(ss, gpa, ',');
        //����ȡ�������ݴ���Student��Grade����
        Grade grade(cname, std::stof(credit), std::stof(gpa));
        //�ж��Ƿ�Ϊ��ѧ���Ĳ���
        bool found = false;
        // ��������ѧ��
        for (auto& student : students) {
            if (student.Sid == sid) {
                student.grades.push_back(grade);
                found = true;
                break;
            }
        }
        // �������ѧ���������µ� Student ����
        if (!found) {
            Student student(sid, sname, sbirth, ssex, sclass);
            student.grades.push_back(grade);
            students.push_back(student);
        }
    }
    //�ر��ļ�
    inFile.close();
    //�ɹ���ȡ��ʾ
    std::cout << "ѧ����Ϣ�ѳɹ��� " << filename << " ��ȡ��" << std::endl;
}

//*********************************�޸İ湦���壺Ϊ����ѧ����ӳɼ�**********************************
// Ϊ����ѧ����ӳɼ�����
void AdminManager::Add_Student_Grades_Screem() {
    system("cls");// ����
    cout << "=============================" << endl;
    cout << "      Ϊ����ѧ����ӳɼ�       " << endl;
    cout << "=============================" << endl;

    if (students.empty()) {
        cout << "��ǰû��ѧ����Ϣ������¼��ѧ����" << endl;
        return;
    }

    // ��ʾ����ѧ���б�ѡ��
    Table_Student_Information_Display();

    string id;
    cout << "������Ҫ��ӳɼ���ѧ��ѧ�ţ���q���أ�: ";
    cin >> id;

    if (id == "q") return; // �û�ȡ������

    // ����ѧ��
    auto it = find_if(students.begin(), students.end(),
        [&id](const Student& s) { return s.Sid == id; });

    if (it != students.end()) {
        // ѭ����Ӷ��ſγ̳ɼ�
        char addMore;
        do {
            string name;
            float credit, gpa;

            cout << "=============================" << endl;
            cout << "�γ���: ";
            cin >> name;
            cout << "ѧ��: ";
            cin >> credit;
            cout << "����: ";
            cin >> gpa;

            // ��ӳɼ���ѧ������
            it->grades.emplace_back(name, credit, gpa);
            cout << "�ɼ���ӳɹ���" << endl;

            // ѯ���Ƿ�������
            cout << "����Ϊ��ѧ����ӳɼ���(y/n): ";
            cin >> addMore;
        } while (tolower(addMore) == 'y');

        // ��ʾ���º�ĳɼ���
        cout << "��ǰѧ���ɼ��б�" << endl;
        Table_Student_Grade_Display(id);
    }
    else {
        cout << "δ�ҵ�ѧ��Ϊ " << id << " ��ѧ����" << endl;
    }
}


//*********************************��������ɾ��ѧ����Ϣ**********************************
// ɾ��ѧ����Ϣ����
void AdminManager::Delete_Student_Screem() {
    bool flag = 1; // ����ѭ����־
    while (flag) {
        system("cls");
        cout << "===========================================================" << endl;
        cout << "|                      ɾ��ѧ����Ϣ                       |" << endl;
        cout << "|                         ��q�˳�                         |" << endl;
        cout << "===========================================================" << endl;

        // ���ѧ���б��Ƿ�Ϊ��
        if (students.empty()) {
            cout << "��ǰû��ѧ����Ϣ��ɾ����" << endl;
            return;
        }

        // ��ʾѧ���б�
        Table_Student_Information_Display();
        cout << "===========================================================" << endl;

        string id;
        cout << "������Ҫɾ����ѧ��ѧ��/��q�˳�> ";
        cin >> id;

        if (id == "q") {
            break;
        }// �û�ȡ������

         // ����Ŀ��ѧ��
        auto it = find_if(students.begin(), students.end(), [&id](const Student& s) { return s.Sid == id; });
        if (it != students.end()) {
            char confirm, c;
            system("cls");
            while (1) {
                cout << "======================================================" << endl;
                cout << "|                   1.ɾ��ѧ��                       |" << endl;
                cout << "|                   2.ɾ��ѧ���ɼ�                   |" << endl;
                cout << "|                   3.�˳�                           |" << endl;
                cout << "======================================================" << endl;
                cout << "��ѡ��>";
                cin >> c;
                if (c == '1') {
                    cout << "ȷ��Ҫɾ��ѧ��Ϊ " << id << " ��ѧ����Ϣ��(y/n): ";
                    cin >> confirm;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���ʣ������

                    // ȷ��ɾ������
                    if (tolower(confirm) == 'y') {
                        students.erase(it);// ��������ɾ��ѧ��
                        cout << "ѧ����Ϣɾ���ɹ���" << endl;
                        break;
                    }
                    else if (tolower(confirm) == 'n') {
                        cout << "��ȡ��ɾ��������" << endl;
                        break;
                    }
                }
                else if (c == '2') {
                    string courseName;
                    cout << "======================================================" << endl;
                    it->GradesDisplay();
                    cout << "======================================================" << endl;
                    cout << "������Ҫɾ���ĳɼ������γ���>";
                    cin >> courseName;

                    // ���γ��Ƿ����
                    auto gradeIt = find_if(
                        it->grades.begin(),
                        it->grades.end(),
                        [&courseName](const Grade& grade) {
                            return grade.Cname == courseName;
                        }
                    );
                    if (gradeIt != it->grades.end()) {
                        cout << "ȷ��Ҫɾ��ѧ��Ϊ " << id << " �Ŀγ� " << courseName << " �ĳɼ���(y/n): ";
                        cin >> confirm;
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (tolower(confirm) == 'y') {
                            it->grades.erase(gradeIt); // ɾ���ÿγ̳ɼ�
                            cout << "�γ� " << courseName << " �ɼ�ɾ���ɹ���" << endl;
                        }
                        else {
                            cout << "��ȡ��ɾ��������" << endl;
                        }
                    }
                    else {
                        system("cls");
                        cout << "��������ȷѡ��" << endl;
                    }
                }
                else if (c == '3') break;
            }
        }
        else {
            cout << "δ�ҵ�ѧ��Ϊ " << id << " ��ѧ����" << endl;
        }
    }
}



//*********************************�����ߣ��޸�ѧ����Ϣ**********************************
// �޸�ѧ����Ϣ����
void AdminManager::Modify_Student_Screem() {
    bool flag1 = 1;// ���ѭ����־
    while (flag1) {
        system("cls");
        cout << "===========================================================" << endl;
        cout << "|                      �޸�ѧ����Ϣ                       |" << endl;
        cout << "|                         ��q�˳�                         |" << endl;
        cout << "===========================================================" << endl;

        // ���ѧ���б��Ƿ�Ϊ��
        if (students.empty()) {
            cout << "��ǰû��ѧ����Ϣ���޸ģ�" << endl;
            return;
        }

        // ��ʾѧ���б�
        Table_Student_Information_Display();
        cout << "===========================================================" << endl;

        string id;
        cout << "������Ҫ�޸ĵ�ѧ��ѧ��/��q�˳�>";
        cin >> id;

        if (id == "q") {
            break;
        }

        // ����Ŀ��ѧ��
        auto it = find_if(students.begin(), students.end(),
            [&id](const Student& s) { return s.Sid == id; });

        if (it != students.end()) {
            bool flag2 = 1;// �ڲ�ѭ����־
            while (flag2) {
                system("cls");
                cout << "��ǰѧ����Ϣ���£�" << endl;
                cout << "===========================================================" << endl;
                it->StuDisplay();
                cout << "===========================================================" << endl;
                cout << "|                     ��ѡ��Ҫ�޸ĵ����ݣ�                |" << endl;
                cout << "|                        1. ����                          |" << endl;
                cout << "|                        2. ����                          |" << endl;
                cout << "|                        3. �Ա�                          |" << endl;
                cout << "|                        4. �༶                          |" << endl;
                cout << "|                        5. �ɼ���Ϣ                      |" << endl;
                cout << "|                         ��q����                         |" << endl;
                cout << "===========================================================" << endl;
                cout << "��ѡ��>";

                char choice;
                cin >> choice;

                // ����ѡ���޸Ĳ�ͬ�ֶ�
                switch (choice) {
                case '1': {
                    string newName;
                    cout << "�������µ�����: ";
                    cin >> newName;
                    it->Sname = newName;
                    break;
                }// �޸�����

                case '2': {
                    string newBirth;
                    cout << "�������µ�����(YYYY-MM-DD): ";
                    cin >> newBirth;
                    it->Sbirth = newBirth;
                    break;
                }// �޸�����

                case '3': {
                    string newSex;
                    cout << "�������µ��Ա�(��/Ů): ";
                    cin >> newSex;
                    it->Ssex = newSex;
                    break;
                }// �޸��Ա�

                case '4': {
                    string newClass;
                    cout << "�������µİ༶: ";
                    cin >> newClass;
                    it->Sclass = newClass;
                    break;
                }// �޸İ༶

                case '5': {
                    Modify_Student_Grades(*it);
                    system("cls");
                    break;
                }// ͨ�������Ӻ����޸ĳɼ�

                case 'q':// �����ϼ�
                    flag2 = 0;
                    break;
                default:
                    cout << "��Ч��ѡ��" << endl;
                }

                cout << "ѧ����Ϣ�޸ĳɹ���" << endl;
            }
        }
        else {
            cout << "δ�ҵ�ѧ��Ϊ " << id << " ��ѧ����" << endl;
            system("pause");
        }
    }
}

// �޸�ѧ���ɼ��Ӻ���
void AdminManager::Modify_Student_Grades(Student& student) {
    bool flag3 = 1;// ѭ����־
    if (student.grades.empty()) {
        cout << "��ѧ�����޳ɼ���Ϣ��" << endl;
        return;
    }
    while (flag3) {
        system("cls");
        cout << student.Sname << "�ĳɼ���Ϣ��" << endl;
        cout << "========================================================" << endl;
        Table_Student_Grade_Display(student.Sid);// ��ʾ��ǰ�ɼ�
        cout << "========================================================" << endl;
        cout << "|                      ��ѡ�����                      |" << endl;
        cout << "|                      1. ��ӳɼ�                     |" << endl;
        cout << "|                      2. �޸ĳɼ�                     |" << endl;
        cout << "|                      3. ɾ���ɼ�                     |" << endl;
        cout << "|                        ��q����                       |" << endl;
        cout << "========================================================" << endl;
        cout << "��ѡ��> ";

        char choice;
        cin >> choice;

        switch (choice) {
        case '1': {
            string name;
            float credit, gpa;
            cout << "�γ���: ";
            cin >> name;
            cout << "ѧ��: ";
            cin >> credit;
            cout << "����: ";
            cin >> gpa;
            student.grades.emplace_back(name, credit, gpa);
            cout << "�ɼ���ӳɹ���" << endl;
            break;
        }// ��ӳɼ�

        case '2': {
            string courseName;
            cout << "������Ҫ�޸ĵĿγ���: ";
            cin >> courseName;

            auto it = find_if(student.grades.begin(), student.grades.end(),
                [&courseName](const Grade& g) { return g.Cname == courseName; });

            if (it != student.grades.end()) {
                cout << "�������µ�ѧ��: ";
                cin >> it->Credit;
                cout << "�������µļ���: ";
                cin >> it->GPA;
                cout << "�ɼ��޸ĳɹ���" << endl;
            }
            else {
                cout << "δ�ҵ��γ���Ϊ " << courseName << " �ĳɼ���¼��" << endl;
            }
            break;
        }// �޸����гɼ�

        case '3': {
            string courseName;
            cout << "������Ҫɾ���Ŀγ���: ";
            cin >> courseName;

            auto it = find_if(student.grades.begin(), student.grades.end(),
                [&courseName](const Grade& g) { return g.Cname == courseName; });

            if (it != student.grades.end()) {
                student.grades.erase(it);
                cout << "�ɼ�ɾ���ɹ���" << endl;
            }
            else {
                cout << "δ�ҵ��γ���Ϊ " << courseName << " �ĳɼ���¼��" << endl;
            }
            break;
        }// ɾ���ɼ�

        case 'q':// �����ϼ�
            flag3 = 0;
        default:
            cout << "��������ѡ����ȷ��ѡ�����" << endl;
        }
    }
}

//*********************************���ܰˣ���ѯѧ����Ϣ**********************************
// ��ѯѧ����Ϣ����
void AdminManager::Search_Student_Screem() {
    bool flag = 1;// ѭ����־
    while (flag) {
        system("cls");
        cout << "=============================" << endl;
        cout << "|        ��ѯѧ����Ϣ       |" << endl;
        cout << "=============================" << endl;
        cout << "|      ��ѡ���ѯ��ʽ��     |" << endl;
        cout << "=============================" << endl;
        cout << "|       1. ��ѧ�Ų�ѯ       |" << endl;
        cout << "|       2. ��������ѯ       |" << endl;
        cout << "|       3. ���༶��ѯ       |" << endl;
        cout << "|          ��q����          |" << endl;
        cout << "=============================" << endl;
        cout << "��ѡ���ѯ��ʽ/��q�˳�>";

        char choice;
        cin >> choice;

        switch (choice) {
        case '1': {
            system("cls");
            string id;
            cout << "������ѧ��: ";
            cin >> id;
            cout << "===========================================================" << endl;

            bool found = false;
            for (const auto& student : students) {
                if (student.Sid == id) {
                    student.StuDisplay();// ��ʾѧ����Ϣ
                    cout << "===========================================================" << endl;

                    if (!student.grades.empty()) {
                        cout << "|                       �ɼ���Ϣ                       |" << endl;
                        cout << "========================================================" << endl;
                        Table_Student_Grade_Display(id);// ��ʾ�ɼ�
                        cout << "========================================================" << endl;
                    }
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "δ�ҵ�ѧ��Ϊ " << id << " ��ѧ����" << endl;
            system("pause");
            break;
        }// ��ѧ�Ų�ѯ

        case '2': {
            system("cls");
            string name;
            cout << "����������: ";
            cin >> name;
            cout << "===========================================================" << endl;
            bool found = false;
            // ��������ѧ��
            for (const auto& student : students) {
                if (student.Sname == name) {
                    student.StuDisplay();
                    cout << "===========================================================" << endl;
                    if (!student.grades.empty()) {
                        cout << "|                       �ɼ���Ϣ                       |" << endl;
                        cout << "========================================================" << endl;
                        Table_Student_Grade_Display(student.Sid);
                        cout << "========================================================" << endl;
                    }
                    found = true;
                }
            }

            if (!found)
                cout << "δ�ҵ�����Ϊ " << name << " ��ѧ����" << endl;
            system("pause");
            break;
        }// ��������ѯ���߼�ͬ��ѧ�ţ�

        case '3': {
            system("cls");
            string className;
            cout << "������༶: ";
            cin >> className;
            cout << "===========================================================" << endl;
            bool found = false;
            for (const auto& student : students) {
                if (student.Sclass == className) {
                    student.StuDisplay();
                    cout << "===========================================================" << endl;
                    if (!student.grades.empty()) {
                        cout << "|                       �ɼ���Ϣ                       |" << endl;
                        cout << "========================================================" << endl;
                        Table_Student_Grade_Display(student.Sid);
                        cout << "========================================================" << endl;
                    }
                    found = true;
                }
            }

            if (!found)
                cout << "δ�ҵ��༶Ϊ " << className << " ��ѧ����" << endl;
            system("pause");
            break;
        }// ���༶��ѯ����ʾ�ð༶����ѧ����

        case 'q':
            flag = 0;
            break;
        default:
            cout << "��������ѡ����ȷ��ѡ�����" << endl;
        }
    }
}

//-------------------------------------------����������---------------------------------------------
//��ȡ����
void AdminManager::Load_Students() {
    //���ļ�
    std::string filename = "students_data.csv";
    std::ifstream inFile(filename, std::ios::in);
    //�ļ���ʧ����ʾ
    if (!inFile) {
        std::cerr << "�޷����ļ����ж�ȡ��" << std::endl;
        return;
    }

    std::string line;
    // ��ȡ��ͷ������
    std::getline(inFile, line);
    //��������ѧ����ȡ
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        //��ȡ��ͷ
        std::string sid, sname, sbirth, ssex, sclass, cname, credit, gpa;
        //��ȡ����
        std::getline(ss, sid, ',');
        std::getline(ss, sname, ',');
        std::getline(ss, sbirth, ',');
        std::getline(ss, ssex, ',');
        std::getline(ss, sclass, ',');
        std::getline(ss, cname, ',');
        std::getline(ss, credit, ',');
        std::getline(ss, gpa, ',');
        //����ȡ�������ݴ���Student��Grade����
        Grade grade(cname, std::stof(credit), std::stof(gpa));
        //�ж��Ƿ�Ϊ��ѧ���Ĳ���
        bool found = false;
        // ��������ѧ��
        for (auto& student : students) {
            if (student.Sid == sid) {
                student.grades.push_back(grade);
                found = true;
                break;
            }
        }
        // �������ѧ���������µ� Student ����
        if (!found) {
            Student student(sid, sname, sbirth, ssex, sclass);
            student.grades.push_back(grade);
            students.push_back(student);
        }
    }
    //�ر��ļ�
    inFile.close();
}
// ---------------------------------------------------������Ϣ---------------------------------------------------------
void AdminManager::MailboxMenu() {
    while (true) {
        system("cls");
        int unreadCount = MessageManager::GetUnreadCount("admin");

        cout << "========================================================" << endl;
        cout << "|                     ����Ա����ϵͳ                    |" << endl;
        cout << "========================================================" << endl;
        cout << "|                    ��ѡ�������                      |" << endl;
        cout << "========================================================" << endl;
        cout << "|                    1.�鿴��Ϣ"
            << (unreadCount > 0 ? "(" + to_string(unreadCount) + "��δ��)" : "")
            << string(20 - 8 - (unreadCount > 0 ? (4 + to_string(unreadCount).length()) : 0), ' ') << endl;
        cout << "|                    2.������Ϣ��ѧ��                  |" << endl;
        cout << "|                    0.�����ϼ��˵�                    |" << endl;
        cout << "========================================================" << endl;
        cout << "��ѡ�����>";

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
            cout << "��Ч��ѡ�����������룡" << endl;
            system("pause");
        }
    }
}

void AdminManager::ReplyToStudentScreen() {
    // ����ʾ����ѧ��
    Table_Student_Information_Display();

    string studentName;
    cout << "������Ҫ�ظ���ѧ������: ";
    cin >> studentName;

    // ���ѧ���Ƿ����
    bool studentExists = false;
    for (const auto& student : students) {
        if (student.Sname == studentName) {
            studentExists = true;
            break;
        }
    }

    if (!studentExists) {
        cout << "ѧ�������ڣ�\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "������ظ����ݣ�������н�����:\n";
    string content;
    string line;

    while (getline(cin, line) && !line.empty()) {
        content += line + "\n";
    }

    if (!content.empty()) {
        MessageManager::SendMessage("admin", studentName, content, Message::RESPONSE);
        cout << "�ظ��ѷ��͸�ѧ�� " << studentName << "��\n";
    }
    else {
        cout << "�ظ�����Ϊ�գ�δ���͡�\n";
    }
}
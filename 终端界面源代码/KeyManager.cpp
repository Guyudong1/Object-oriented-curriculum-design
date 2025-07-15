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


//-------UserInformationʵ��--------
UserInformation::UserInformation(string name, string key, string role):UserName(name),UserKey(key),UserRole(role) {}

string UserInformation::getname() { return UserName; }
string UserInformation::getkey() { return UserKey; }
string UserInformation::getrole() { return UserRole; }
//�û���Ϣ��ӡ
void UserInformation::display() {
    std::cout << "�û�����" << UserName << "���û����룺" << UserKey << ",�û�Ȩ�ޣ�" << UserRole << endl;
}
void UserInformation::setkey(const string& newKey) {
    UserKey = newKey;  // ��������
}
//----------UserInformationManagerʵ��----------
//���캯��
UserInformationManager::UserInformationManager(){
    UserInformation* admin = new UserInformation("admin1" ,"123456",  "Admin");
    Users.push_back(admin);
    //��¼�û���
    Count = 1;
    kk = 1;
    //��ǰ��¼�û���
    Current_name = "None";
    //��ǰ��¼�û�����
    Current_key = "None";
}
//��������
UserInformationManager::~UserInformationManager(){
    for (auto user : Users) {
        delete user;
    }
}

//************************�жϺ���************************

//�ж��û����Ƿ������user����
bool UserInformationManager::InName(string name) {
    for (auto user : Users)
        if (name == user->getname())
            return 1;
    return 0;
}
//�ж���User���У����ֺ������Ƿ�ƥ��
bool UserInformationManager::KeyMatchName(string name, string key) {
    for (auto user : Users)
        if (name == user->getname())
            if (user->getkey() == key)
                return 1;
    return 0;
}
//�ж��û�Ȩ���Ƿ�Ϊ��Admin������Ա
bool UserInformationManager::IsAdmin(string role) {
    if (role == "Admin")
        return 1;
    return 0;
}
//�ж������Ƿ��Ѿ���User���У������Ƿ��ظ���
bool UserInformationManager::IsSingle(string name) {
    for (auto user : Users)
        if (name == user->getname())
            return 0;
    return 1;
}
// ����ǿ�ȼ�⺯��
string CheckPasswordStrength(const string& password) {
    bool hasLetter = false, hasDigit = false, hasSpecial = false;
    for (char c : password) {
        if (isalpha(c)) hasLetter = true;
        else if (isdigit(c)) hasDigit = true;
        else hasSpecial = true;
    }

    if (password.length() < 6)
        return "��������С��6��";
    if ((hasLetter && hasDigit && hasSpecial) && password.length() >= 8)
        return "ǿ";
    if (hasLetter && hasDigit)
        return "��";
    return "��";
}

//************************��ӡ����****************************

//��ӡ�����û���Ϣ������Ա����
void UserInformationManager::DisplayUsers() {
    std::cout << "�û���Ϣ" << endl;
    std::cout << "========================================================" << endl;
    cout << left << setw(15) << "�û���"
        << setw(15) << "�û�����"
        << setw(8) << "�û�Ȩ��" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (auto user : Users) {
        cout << left << setw(15) << user->getname()
            << setw(15) << user->getkey()
            << setw(8) << user->getrole() << endl;
    }
    std::cout << "========================================================" << endl;

}
//�����û�Ȩ��
string UserInformationManager::Findrole(string name) {
    for (auto user : Users) {
        if (name == user->getname())
            return user->getrole();
    }
    return "NULL";
}
// ȥ���ַ�����β�Ŀո�
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}


//++++++++++++++++++++++++++++++++++         ��¼ע�����            +++++++++++++++++++++++++++++++++++
// 
//**************��¼ע�����*************
int UserInformationManager::Login_Screem() {
    std::cout << "========================================================" << endl;
    std::cout << "|         ��ӭʹ���Ϻ����´�ѧѧ����������ϵͳ         |" << endl;
    std::cout << "========================================================" << endl;
    std::cout << "|                        ���¼                        |" << endl;
    std::cout << "========================================================" << endl;
    std::cout << "|                        1.��¼                        |" << endl;
    std::cout << "|                        2.ע��                        |" << endl;
    std::cout << "|                        3.�˳�                        |" << endl;
    std::cout << "========================================================" << endl;
    std::cout << "��ѡ����>";
    int c = -1;
    cin >> c;

    if (cin.fail()) {
        cin.clear(); // �������״̬
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������������
        system("cls");
        cout << "!!!!! ����������ѡ�1-3�� !!!!!" << endl;
    }
    else if (c < 1 || c > 3) {
        system("cls");
        cout << "!!!!! ����������ѡ�1-3�� !!!!!" << endl;
    }
    return c;
}

//��¼������ʾ����
void UserInformationManager::InputkeyScreem(string &name, string &key) {
    std::cout << "=============================" << endl;
    std::cout << "  �û�����";
    cin >> name;
    std::cout << "--------------------------------" << endl;
    std::cout << "  ���룺";
    cin >> key;
    std::cout << "=============================" << endl;
}

//*****************************************ע�Ṧ��*******************************************
//--------------����û������ŵ��ļ��б���-------------
void UserInformationManager::AddUsers(string Username, string Userkey, string role) {
    // ����û����Ƿ��Ѵ��ڣ���ֹ�ظ����
    if (InName(Username)) {
        std::cout << "�û����Ѵ��ڣ����ʧ�ܣ�" << endl;
        return;
    }
    // �����µ��û�������ӵ��û��б�
    UserInformation* newUser = new UserInformation(Username, Userkey, role);
    Users.push_back(newUser);
    Count++;  // �����û�����
    // ׷�ӵ� CSV �ļ�
    ofstream file("users.csv", ios::app);
    if (file.is_open()) {
        file << Username << "," << Userkey << "," << role << endl;
        file.close();
    }
    //��ӳɹ���ʾ
    std::cout << "�û� " << Username << " ��ӳɹ�����ɫ��" << role << endl;
}
//------------------ע�����------------------
void UserInformationManager::RegisterScreem(string& name, string& key1) {
    //�˳���ѭ����־
    bool flag = true;
    //ѡ�񣨹���Ա/ѧ������־
    int c = 0;
    string key2, AdminKey;
    while (flag) {
        // *******ע�����********
        std::cout << "==============================" << endl;
        std::cout << "|           ��ע��           |" << endl;
        std::cout << "==============================" << endl;
        std::cout << "|        1. ����Ա�û�       |" << endl;
        std::cout << "|        2. ѧ���û�         |" << endl;
        std::cout << "==============================" << endl;
        std::cout << "��ѡ���û����ͣ�";
        cin >> c;
        while (true) {
            std::cout << "������������ʵ���� ��";
            cin >> name;
            //�ж����������Ƿ��Ѵ���
            if (!IsSingle(name)) {
                std::cout << "�û����Ѵ��ڣ������������" << endl;
                continue;  // ����ѭ����Ҫ����������
            }
            break;  // �û����Ϸ�������ѭ��
        }
        //����ѭ����������������
        while (true) {
            std::cout << "�������û����룺";
            cin >> key1;
            string strength = CheckPasswordStrength(key1);
            std::cout << "����ǿ�ȣ�" << strength << endl;
            if (strength == "��" || strength.find("��") != string::npos) {
                std::cout << "����̫���������ø�ǿ�����루����6λ��������ĸ�����֣���" << endl;
                continue;
            }
            std::cout << "--------------------------------" << endl;
            std::cout << "�ٴ�����ȷ�����룺";
            cin >> key2;
            if (key1 != key2) {
                std::cout << "�����������벻һ�£����������룡" << endl;
                continue;
            }
            break; // ����ǿ�Ⱥϸ�������һ�£��˳�ѭ��
        }
         // **����Աע��**
         if (c == 1) {  
             std::cout << "���������Ա���룺";
             cin >> AdminKey;
             if (AdminKey == Admin_Key) {
                 system("cls");
                 std::cout << "ע��ɹ������¼" << endl;
                 //�������ԱȨ��
                 AddUsers(name, key1, "Admin");
                 //����ѭ��
                 flag = false;
             }
             else {
                 system("cls");
                 std::cout << "����������Ա������󣡣�������������" << endl;
             }
         }
         // **ѧ��ע��**
         else { 
             system("cls");
             std::cout << "ע��ɹ������¼" << endl;
             //����ѧ��Ȩ��
             AddUsers(name, key1, "Stu");
             //����ѭ��
             flag = false;
         }
    }
}

//*******************************************************����¼ע�����***********************************************************
string UserInformationManager::Login() {
    string n, k, c;
    bool flag_1 = true;

    // ���õ�ǰ��¼״̬
    Current_name = "None";
    Current_key = "None";

    while (flag_1) {
        int choice = Login_Screem();
        // ... ԭ����������� ...

        switch (choice) {
        case 1: // ��¼
            InputkeyScreem(n, k);
            if (InName(n) && KeyMatchName(n, k)) {
                Current_name = n;
                Current_key = k;
                system("cls");

                string role = Findrole(n);
                if (role == "Admin") {
                    std::cout << "========================================================" << endl;
                    std::cout << "                  ��ӭ��" << n << "����Ա                     " << endl;
                    c = "Admin";
                }
                else {
                    std::cout << "========================================================" << endl;
                    std::cout << "                     ��ӭ��" << n << "ͬѧ                    " << endl;
                    c = "Stu";
                }
                flag_1 = false;
                return c;
            }
            else if (!InName(n)) {
                system("cls");
                std::cout << "!!!!! �û��������ڣ������������ע�� !!!!!" << endl;
            }
            else {
                system("cls");
                std::cout << "!!!!! ����������������� !!!!!" << endl;
            }
            break;
            //ע��
        case 2:
            system("cls");
            RegisterScreem(n, k);
            break;
            //�˳�
        case 3:
            char s;
            while (1) {
                std::cout << "ȷ���˳�����y/n��";
                cin >> s;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���ʣ������

                if (s == 'y') {
                    system("cls");
                    std::cout << "��лʹ�ø�ϵͳ~~�ټ���" << endl;
                    exit(0);
                }
                else if (s == 'n') {
                    // ���·���
                    system("cls");
                    break;
                }
                else {
                    std::cout << "��������ȷѡ��" << endl;
                }
            }
        }
    }
}

//++++++++++++++++++++++++++++++++            ������������ȡ             +++++++++++++++++++++++++++++

void UserInformationManager::Load_Users() {
    //���ļ�
    ifstream file("users.csv");
    //�ļ���ʧ����ʾ
    if (!file.is_open()) {
        std::cout << "�û������ļ������ڣ����������ļ���" << endl;
        return;
    }
    // ��յ�ǰ�û����ݣ���ֹ�ظ�����
    for (auto user : Users)
        delete user;
    Users.clear();

    string line;
    bool isFirstLine = true;
    //���ļ�ÿ�н��б�����ȡ
    while (getline(file, line)) {
        stringstream ss(line);
        string username, userkey, userrole;
        // ��һ���ǹ���Ա����
        if (isFirstLine) {
            //��ȡ����Ա����
            getline(ss, username, ',');
            if (username == "AdminKey") {
                getline(ss, Admin_Key,',');
                //Admin_Key = trim(Admin_Key);
                isFirstLine = false;
                continue;
            }
        }
        // ��ȡ�û�����
        if (getline(ss, username, ',') && getline(ss, userkey, ',') && getline(ss, userrole)) {
            Users.push_back(new UserInformation(username, userkey, userrole));
        }
    }
    //�ر��ļ�
    file.close();
}


//++++++++++++++++++++++++++++++                       ����Ա����                     ++++++++++++++++++++++++++++++
// 
//*************************************���ܾţ��û��������**************************************
//--------�ж��û��Ƿ���User���д���------
bool UserInformationManager::In_User(string Username) {
    for (auto& users : Users)
        if (Username == users->getname())
            return 1;
    return 0;
}

//---------�����û���Ϣ--------
void UserInformationManager::Backup_Users() {
    //���ļ�
    ofstream file("users.csv", ios::trunc);
    //���б���
    if (file.is_open()) {
        // ���ݹ���Ա����
        file << "AdminKey," << Admin_Key << endl; 
        //���������û���Ϣ
        for(auto& users:Users)
            file << users->getname() << "," << users->getkey() << "," << users->getrole() << endl;
        file.close();
    }
    //�ɹ���ʾ
    std::cout << "���ݳɹ���" << endl;
}

//---------ɾ���û�----------
void UserInformationManager::Delete_Users() {
    string Uname;
    char c;
    while (1) {
        DisplayUsers();
        std::cout << "����Ҫɾ�����û�����q�˳�>" ;
        cin >> Uname;
        //User�����Ƿ����
        if (!In_User(Uname)) {
            std::cout << "�û�������" << endl;
            return;
        }
        break;
     }
     //��ӡ�����û���Ϣ
     for (auto& users : Users) {
         if (users-> getname() == Uname) {
             users->display();
             //ȷ��
             std::cout << "ȷ��ɾ������y/n��";
             cin >> c;
             if (c == 'y') {
                 delete(users);
                 Count--;
                 std::cout << "ɾ���ɹ�" << endl;
                 Backup_Users();
                 break;
             }
             else {
                 std::cout << "ȡ��ɾ��" << endl;
                 break;
             }
         }
     }
}

//-----------��������Ա����------------
void UserInformationManager::Replace_Admin_Key() {
    string checked_admin_key,checked_new_admin_key,new_admin_key;
    while(1){
        std::cout << "����ԭ����Ա�����q�˳���";
        cin >> checked_admin_key;
        if (checked_admin_key == "q") return;
        if (checked_admin_key != Admin_Key) {
            std::cout << "ԭ�������������" << endl;
            continue;
        }
        break;
    }
    while (1) {
        std::cout << "�����µĹ���Ա���룺";
        cin >> new_admin_key;
        std::cout << "�ٴ�������ȷ�ϣ�";
        cin >> checked_new_admin_key;
        if (new_admin_key != checked_new_admin_key) {
            std::cout << "�������벻һ�£���������" << endl;
            continue;
        }
        break;
    }
    Admin_Key = new_admin_key;
    std::cout << "����Ա�����޸ĳɹ���" << endl;
    // �������ݵ��ļ�
    Backup_Users(); 
}

//-----------��ӡ����Ա����-----------
void UserInformationManager::Display_Admin_Key() {
    std::cout << "����Ա���룺" << Admin_Key << endl;
}

//------------------------------------�������������------------------------------------
void UserInformationManager::Key_Manage_Screem() {
    DisplayUsers();
    char s;
    while (1) {
        system("cls");
        std::cout << "==============================" << endl;
        std::cout << "|           ѡ����         |" << endl;
        std::cout << "==============================" << endl;
        std::cout << "|        1. ɾ���û�         |" << endl;
        std::cout << "|        2. �����û���Ϣ     |" << endl;
        std::cout << "|        3. ���¹���Ա����   |" << endl;
        std::cout << "|        4. ��ӡ����Ա����   |" << endl;
        std::cout << "|        �� q �˳�           |" << endl;
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
            std::cout << "\n��Ч���룡��������Чѡ�1-4 �� q��" << endl;
            system("pause");
        }
    }
}   


//*******************************************�����㣺�˳���¼******************************************
char UserInformationManager::Exit_Screem() {
    char s;
    while (1) {
        std::cout << "ȷ���˳�����y/n��";
        cin >> s;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���ʣ������

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
            std::cout << "��������ȷѡ��" << endl;
            return 'y';
        }
        return 'y';
    }
}


//+++++++++++++++++++++++++++                          ѧ���鿴����                        ++++++++++++++++++++++++++
//
//************************************�����壺�޸�ѧ������********************************************
void UserInformationManager::Replace_Student_Key() {
    string checked_student_key, new_student_key, checked_new_student_key;
    while (1) {
        std::cout << "����ԭ����,��q���أ�";
        cin >> checked_student_key;
        if (checked_student_key == "q")  
            return;
        if (checked_student_key !=Current_key) {
            std::cout << "ԭ�������������" << endl;
            continue;
        }
        break;
    }
    while (1) {
        std::cout << "�����µ����룺";
        cin >> new_student_key;

        string strength = CheckPasswordStrength(new_student_key);
        std::cout << "����ǿ�ȣ�" << strength << endl;

        if (strength == "��" || strength.find("��") != string::npos) {
            std::cout << "����̫���������ø�ǿ�����루����6λ��������ĸ�����֣���" << endl;
            continue;
        }

        std::cout << "--------------------------------" << endl;
        std::cout << "�ٴ�����ȷ�����룺";
        cin >> checked_new_student_key;

        if (new_student_key != checked_new_student_key) {
            std::cout << "�����������벻һ�£����������룡" << endl;
            continue;
        }

        break; // ����ǿ�Ⱥϸ�������һ�£��˳�ѭ��
    }

    for (auto& users : Users) {
        if (users->getname() == Current_name) {
            users->setkey(new_student_key);
        }
    }
    // ���µ�ǰ��¼״̬������
    Current_key = new_student_key;
    std::cout << "�����޸ĳɹ���" << endl;
    cout << "��ǰ�û���¼��Ϣ��\n��¼����" << Current_name 
        << "\n��¼���룺" << Current_key << endl;
    // �������ݵ��ļ�
    Backup_Users(); 
}

//************************************��������ע���˻�********************************************
char UserInformationManager::Log_Off() {
    char s;
    while (1) {
        std::cout << "��ǰ�û�Ϊ��"<<Current_name << endl;
        std::cout << "ȷ��ע����ǰ�˻���(y/n)";
        cin >> s;
        if (s == 'y') {
            for (auto it = Users.begin(); it != Users.end(); ++it) {
                if ((*it)->getname() == Current_name) {
                    delete* it;
                    Users.erase(it);
                    Backup_Users();
                    std::cout << "�û� " << Current_name << " �ѳɹ�ע����" << endl;
                    break;
                }
            }
            // �����ǰ��¼״̬
            Current_name = "None";
            Current_key = "None";
            system("cls");
            Login(); // ���ص�¼����
            return 'y';
        }
        else if (s == 'n') {
            return 'n';
        }
        else {
            std::cout << "��������ȷѡ��" << endl;
            return 'y';
        }
        return 'y';
    }
}

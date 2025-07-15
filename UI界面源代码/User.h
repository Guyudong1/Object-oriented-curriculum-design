#pragma once
#include"configure.h"
#include<vector>

class User
{
    User() = default;  // Ĭ�Ϲ��캯�������ã���ֹ��Чʵ����
public:
    std::string getName() const;
    std::string getKey() const;
    std::string getRole() const;
    std::string UserName;        // �û���
    std::string UserKey;         // �û�����
    std::string UserRole;        // �û�Ȩ��
    std::string Admin_Key;       // ����Ա����

    User(const std::string UserName, const std::string UserKey, const std::string UserRole);
    std::string formatInfo();
    void formatwrite(const std::string& str);  // д����Ϣ

    // ��� setKey �������޸�����
    void setKey(const std::string& newKey);
};



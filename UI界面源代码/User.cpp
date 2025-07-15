#include "User.h"
#include<string>
#include<sstream>
#include<iostream>
using namespace std;

std::string User::getName() const
{
    return this->UserName;
}

std::string User::getKey() const
{
    return this->UserKey;
}

std::string User::getRole() const
{
    return this->UserRole;
}

User::User(const std::string UserName, const std::string UserKey, const std::string UserRole)
    : UserName(UserName), UserKey(UserKey), UserRole(UserRole)
{
}

std::string User::formatInfo()
{
    stringstream ss;
    ss << this->UserName << "," << this->UserKey << "," << this->UserRole;
    return ss.str();
}

void User::formatwrite(const std::string& str)
{
    stringstream ss(str);
    ss >> this->UserName >> this->UserKey >> this->UserRole;
}

// 实现 setKey 方法来设置新密码
void User::setKey(const std::string& newKey) {
    this->UserKey = newKey;
}


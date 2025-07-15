#pragma once
#include"configure.h"
#include<vector>

class User
{
    User() = default;  // 默认构造函数不可用，防止无效实例化
public:
    std::string getName() const;
    std::string getKey() const;
    std::string getRole() const;
    std::string UserName;        // 用户名
    std::string UserKey;         // 用户密码
    std::string UserRole;        // 用户权限
    std::string Admin_Key;       // 管理员密码

    User(const std::string UserName, const std::string UserKey, const std::string UserRole);
    std::string formatInfo();
    void formatwrite(const std::string& str);  // 写入信息

    // 添加 setKey 方法来修改密码
    void setKey(const std::string& newKey);
};



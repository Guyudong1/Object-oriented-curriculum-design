#include <iostream>
using namespace std;
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "MessageManager.h"
vector<Message> MessageManager::messages; // 静态向量，存储所有消息

//----------------------------------------Message实现------------------------------------------
// 构造函数
Message::Message(const std::string& sender, const std::string& receiver,const std::string& content, MessageType type)
    : sender(sender), receiver(receiver), content(content), type(type) {
    read = false; // 初始化为未读状态
}

// Message类的getter方法
std::string Message::GetSender() const { return sender; }
std::string Message::GetReceiver() const { return receiver; }
std::string Message::GetContent() const { return content; }
Message::MessageType Message::GetType() const { return type; }
bool Message::IsRead() const { return read; }
void Message::MarkAsRead() { read = true; } // 将消息标记为已读

// 显示消息详情
void Message::Display() const {
    std::cout << (type == REQUEST ? "请求" : "响应") << " - ";
    std::cout << (read ? "已读" : "未读") << "\n";
    std::cout << "发送者: " << sender << "\n";
    std::cout << "内容: " << content << "\n";
    std::cout << "----------------------------------------\n";
}

//------------------------------------------MessageManager实现------------------------------------------
// 向管理器添加新消息
void MessageManager::AddMessage(const Message& msg) {
    messages.push_back(msg);
}

// 统计特定用户的未读消息数量
int MessageManager::GetUnreadCount(const std::string& username) {
    int count = 0;
    for (const auto& msg : messages)
        if (msg.GetReceiver() == username && !msg.IsRead()) 
            count++;
    return count;
}

// 查看特定用户的所有消息（会将消息标记为已读）
void MessageManager::ViewMessages(const std::string& username) {
    if (messages.empty()) {
        std::cout << "没有消息！\n";
        return;
    }
    int unreadCount = GetUnreadCount(username);
    std::cout << "=============== 消息列表 (" << unreadCount << "条未读) ===============\n";
    // 显示用户作为发送者或接收者的所有消息
    for (auto& msg : messages) {
        if (msg.GetReceiver() == username || msg.GetSender() == username) {
            msg.Display();
            msg.MarkAsRead(); // 将显示的消息标记为已读
        }
    }
    std::cout << "====================================================\n";
}

// 创建并发送新消息
void MessageManager::SendMessage(const std::string& sender,
    const std::string& receiver,
    const std::string& content,
    Message::MessageType type) {
    messages.emplace_back(sender, receiver, content, type);
}

// 将所有消息保存到CSV文件
void MessageManager::SaveMessages() {
    ofstream outFile("messages.csv");
    if (!outFile) {
        cerr << "无法打开消息文件进行保存！" << endl;
        return;
    }
    // 写入CSV表头
    outFile << "Sender,Receiver,Content,Type,Read\n";
    // 将每条消息写入文件
    for (const auto& msg : messages) {
        // 转义内容中的逗号和换行符
        string content = msg.GetContent();
        replace(content.begin(), content.end(), ',', ';');
        replace(content.begin(), content.end(), '\n', ' ');
        outFile << msg.GetSender() << ","
            << msg.GetReceiver() << ","
            << "\"" << content << "\","
            << (msg.GetType() == Message::REQUEST ? "REQUEST" : "RESPONSE") << ","
            << (msg.IsRead() ? "true" : "false") << "\n";
    }
    outFile.close();
}

// 从CSV文件加载消息
void MessageManager::LoadMessages() {
    ifstream inFile("messages.csv");
    if (!inFile) 
        return; // 文件不存在则忽略
    messages.clear(); // 清空现有消息
    string line;
    getline(inFile, line); // 跳过表头行
    // 读取每条消息行
    while (getline(inFile, line)) {
        stringstream ss(line);
        string sender, receiver, content, typeStr, readStr;
        // 解析CSV字段
        getline(ss, sender, ',');
        getline(ss, receiver, ',');
        // 处理被引号包围的内容
        if (ss.peek() == '"') {
            ss.get(); // 跳过开头的引号
            getline(ss, content, '"');
            ss.get(); // 跳过逗号
        }
        else
            getline(ss, content, ',');
        getline(ss, typeStr, ',');
        getline(ss, readStr);
        // 还原内容中的特殊字符
        replace(content.begin(), content.end(), ';', ',');
        // 将字符串值转换为适当类型
        Message::MessageType type = (typeStr == "REQUEST") ? Message::REQUEST : Message::RESPONSE;
        bool read = (readStr == "true");
        // 创建并存储消息
        Message msg(sender, receiver, content, type);
        if (read)
            msg.MarkAsRead();
        messages.push_back(msg);
    }
    inFile.close();
}
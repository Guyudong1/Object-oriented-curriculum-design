#pragma once

#include <string>
#include <vector>

// 消息类，用于封装一个请求或响应类型的消息信息
class Message {
public:

    enum MessageType {
        REQUEST,    // 请求消息
        RESPONSE    // 响应消息
    };

    // 构造函数：初始化一条消息
    // sender：发送者用户名
    // receiver：接收者用户名
    // content：消息内容
    // type：消息类型（请求或响应）
    Message(const std::string& sender, const std::string& receiver, const std::string& content, MessageType type);

    // 获取发送者用户名
    std::string GetSender() const;

    // 获取接收者用户名
    std::string GetReceiver() const;

    // 获取消息内容
    std::string GetContent() const;

    // 获取消息类型（REQUEST 或 RESPONSE）
    MessageType GetType() const;

    // 判断消息是否已读
    bool IsRead() const;

    // 将消息标记为“已读”
    void MarkAsRead();

    // 显示消息的详细信息
    void Display() const;

private:
    std::string sender;      // 发送者用户名
    std::string receiver;    // 接收者用户名
    std::string content;     // 消息的文本内容
    MessageType type;        // 消息类型（请求或响应）
    bool read;               // 标志位：表示该消息是否已读
};


class MessageManager {
public:
    // 存储所有消息的静态向量
    static std::vector<Message> messages;  

    // 添加消息到管理器
    static void AddMessage(const Message& msg);

    // 获取指定用户的未读消息数量
    static int GetUnreadCount(const std::string& username);

    // 查看指定用户的消息（会自动标记为已读）
    static void ViewMessages(const std::string& username);

    // 发送新消息
    static void SendMessage(const std::string& sender,const std::string& receiver,const std::string& content,Message::MessageType type);

    // 保存所有消息到文件
    static void SaveMessages();

    // 从文件加载消息
    static void LoadMessages();
};
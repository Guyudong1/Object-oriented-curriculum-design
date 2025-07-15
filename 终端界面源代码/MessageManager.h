#pragma once

#include <string>
#include <vector>

// ��Ϣ�࣬���ڷ�װһ���������Ӧ���͵���Ϣ��Ϣ
class Message {
public:

    enum MessageType {
        REQUEST,    // ������Ϣ
        RESPONSE    // ��Ӧ��Ϣ
    };

    // ���캯������ʼ��һ����Ϣ
    // sender���������û���
    // receiver���������û���
    // content����Ϣ����
    // type����Ϣ���ͣ��������Ӧ��
    Message(const std::string& sender, const std::string& receiver, const std::string& content, MessageType type);

    // ��ȡ�������û���
    std::string GetSender() const;

    // ��ȡ�������û���
    std::string GetReceiver() const;

    // ��ȡ��Ϣ����
    std::string GetContent() const;

    // ��ȡ��Ϣ���ͣ�REQUEST �� RESPONSE��
    MessageType GetType() const;

    // �ж���Ϣ�Ƿ��Ѷ�
    bool IsRead() const;

    // ����Ϣ���Ϊ���Ѷ���
    void MarkAsRead();

    // ��ʾ��Ϣ����ϸ��Ϣ
    void Display() const;

private:
    std::string sender;      // �������û���
    std::string receiver;    // �������û���
    std::string content;     // ��Ϣ���ı�����
    MessageType type;        // ��Ϣ���ͣ��������Ӧ��
    bool read;               // ��־λ����ʾ����Ϣ�Ƿ��Ѷ�
};


class MessageManager {
public:
    // �洢������Ϣ�ľ�̬����
    static std::vector<Message> messages;  

    // �����Ϣ��������
    static void AddMessage(const Message& msg);

    // ��ȡָ���û���δ����Ϣ����
    static int GetUnreadCount(const std::string& username);

    // �鿴ָ���û�����Ϣ�����Զ����Ϊ�Ѷ���
    static void ViewMessages(const std::string& username);

    // ��������Ϣ
    static void SendMessage(const std::string& sender,const std::string& receiver,const std::string& content,Message::MessageType type);

    // ����������Ϣ���ļ�
    static void SaveMessages();

    // ���ļ�������Ϣ
    static void LoadMessages();
};
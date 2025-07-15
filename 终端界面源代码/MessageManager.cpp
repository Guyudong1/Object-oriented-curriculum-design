#include <iostream>
using namespace std;
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "MessageManager.h"
vector<Message> MessageManager::messages; // ��̬�������洢������Ϣ

//----------------------------------------Messageʵ��------------------------------------------
// ���캯��
Message::Message(const std::string& sender, const std::string& receiver,const std::string& content, MessageType type)
    : sender(sender), receiver(receiver), content(content), type(type) {
    read = false; // ��ʼ��Ϊδ��״̬
}

// Message���getter����
std::string Message::GetSender() const { return sender; }
std::string Message::GetReceiver() const { return receiver; }
std::string Message::GetContent() const { return content; }
Message::MessageType Message::GetType() const { return type; }
bool Message::IsRead() const { return read; }
void Message::MarkAsRead() { read = true; } // ����Ϣ���Ϊ�Ѷ�

// ��ʾ��Ϣ����
void Message::Display() const {
    std::cout << (type == REQUEST ? "����" : "��Ӧ") << " - ";
    std::cout << (read ? "�Ѷ�" : "δ��") << "\n";
    std::cout << "������: " << sender << "\n";
    std::cout << "����: " << content << "\n";
    std::cout << "----------------------------------------\n";
}

//------------------------------------------MessageManagerʵ��------------------------------------------
// ��������������Ϣ
void MessageManager::AddMessage(const Message& msg) {
    messages.push_back(msg);
}

// ͳ���ض��û���δ����Ϣ����
int MessageManager::GetUnreadCount(const std::string& username) {
    int count = 0;
    for (const auto& msg : messages)
        if (msg.GetReceiver() == username && !msg.IsRead()) 
            count++;
    return count;
}

// �鿴�ض��û���������Ϣ���Ὣ��Ϣ���Ϊ�Ѷ���
void MessageManager::ViewMessages(const std::string& username) {
    if (messages.empty()) {
        std::cout << "û����Ϣ��\n";
        return;
    }
    int unreadCount = GetUnreadCount(username);
    std::cout << "=============== ��Ϣ�б� (" << unreadCount << "��δ��) ===============\n";
    // ��ʾ�û���Ϊ�����߻�����ߵ�������Ϣ
    for (auto& msg : messages) {
        if (msg.GetReceiver() == username || msg.GetSender() == username) {
            msg.Display();
            msg.MarkAsRead(); // ����ʾ����Ϣ���Ϊ�Ѷ�
        }
    }
    std::cout << "====================================================\n";
}

// ��������������Ϣ
void MessageManager::SendMessage(const std::string& sender,
    const std::string& receiver,
    const std::string& content,
    Message::MessageType type) {
    messages.emplace_back(sender, receiver, content, type);
}

// ��������Ϣ���浽CSV�ļ�
void MessageManager::SaveMessages() {
    ofstream outFile("messages.csv");
    if (!outFile) {
        cerr << "�޷�����Ϣ�ļ����б��棡" << endl;
        return;
    }
    // д��CSV��ͷ
    outFile << "Sender,Receiver,Content,Type,Read\n";
    // ��ÿ����Ϣд���ļ�
    for (const auto& msg : messages) {
        // ת�������еĶ��źͻ��з�
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

// ��CSV�ļ�������Ϣ
void MessageManager::LoadMessages() {
    ifstream inFile("messages.csv");
    if (!inFile) 
        return; // �ļ������������
    messages.clear(); // ���������Ϣ
    string line;
    getline(inFile, line); // ������ͷ��
    // ��ȡÿ����Ϣ��
    while (getline(inFile, line)) {
        stringstream ss(line);
        string sender, receiver, content, typeStr, readStr;
        // ����CSV�ֶ�
        getline(ss, sender, ',');
        getline(ss, receiver, ',');
        // �������Ű�Χ������
        if (ss.peek() == '"') {
            ss.get(); // ������ͷ������
            getline(ss, content, '"');
            ss.get(); // ��������
        }
        else
            getline(ss, content, ',');
        getline(ss, typeStr, ',');
        getline(ss, readStr);
        // ��ԭ�����е������ַ�
        replace(content.begin(), content.end(), ';', ',');
        // ���ַ���ֵת��Ϊ�ʵ�����
        Message::MessageType type = (typeStr == "REQUEST") ? Message::REQUEST : Message::RESPONSE;
        bool read = (readStr == "true");
        // �������洢��Ϣ
        Message msg(sender, receiver, content, type);
        if (read)
            msg.MarkAsRead();
        messages.push_back(msg);
    }
    inFile.close();
}
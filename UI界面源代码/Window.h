#pragma once
#include"configure.h"
class Window
{
public:
	Window(int w, int h, int flag);
	void setWindowTitle(const std::string& tilte);//���ô�����
	int exec();

	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();
	

	//����������������
	//�ж�������Ϣ
	inline static bool hasMsg() { return ::peekmessage(&m_msg); }//��ȡ����Լ�������Ϣ
	inline static ExMessage& getMsg() { return m_msg; }

private:
	HWND m_handle; //���ھ��
	inline static ExMessage m_msg;//��Ϣ
};
  
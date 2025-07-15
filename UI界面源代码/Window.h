#pragma once
#include"configure.h"
class Window
{
public:
	Window(int w, int h, int flag);
	void setWindowTitle(const std::string& tilte);//设置窗口名
	int exec();

	static int width();
	static int height();
	static void clear();
	static void beginDraw();
	static void flushDraw();
	static void endDraw();
	

	//按键操作及鼠标操作
	//判断有无消息
	inline static bool hasMsg() { return ::peekmessage(&m_msg); }//获取鼠标以及按键消息
	inline static ExMessage& getMsg() { return m_msg; }

private:
	HWND m_handle; //窗口句柄
	inline static ExMessage m_msg;//消息
};
  
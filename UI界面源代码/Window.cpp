#include "Window.h"
#include<iostream>
Window::Window(int w, int h, int flag)
{
	m_handle = ::initgraph(w,h,flag);
}

void Window::setWindowTitle(const std::string& title)
{
	::SetWindowText(m_handle, title.c_str());
	::setbkmode(TRANSPARENT);
}

int Window::exec()
{
	return getchar();
}

int Window::width()
{
	return ::getwidth();
}

int Window::height()
{
	return ::getheight();
}

void Window::clear()
{
	::cleardevice();
}

void Window::beginDraw()
{
	::BeginBatchDraw();
}

void Window::flushDraw()
{
	::FlushBatchDraw();
}

void Window::endDraw()
{
	::EndBatchDraw();
}

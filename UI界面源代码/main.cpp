#include"Window.h"
#include"Management.h"



int main()
{

	Window w(960, 640, EX_SHOWCONSOLE);
	w.setWindowTitle("学生管理系统");

	
	Management m;
	m.run();
	 
	return w.exec();
}
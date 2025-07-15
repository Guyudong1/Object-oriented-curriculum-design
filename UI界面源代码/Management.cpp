#include "Management.h"
#include<conio.h>
#include<iostream>
#include<string>
#include"Timer.h"
#include<algorithm>
#include<fstream>
#include"User.h"


using namespace std;
User* Management::Current_user = nullptr;
Management::Management()
{

	readFile("./IMAGE/users.csv");
	::loadimage(&m_bk, "./IMAGE/IMAGE.png",Window::width(),Window::height());
	//弹窗初始化
	m_msgBox = std::make_unique<MsgBox>();

	//主界面按钮初始化
	menu_btns.emplace_back(new PushButton("登录"));
	menu_btns.emplace_back(new PushButton("注册"));
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(250, 50);
		int bx = (Window::width() - menu_btns[i]->width())/2;
		int vspace = (Window::height()- menu_btns.size()* menu_btns[i]->height()) / 2;
		int by = vspace +i * menu_btns[i]->height();
		menu_btns[i]->move(bx, by);
	}
	menubtn = new PushButton("退出", 355,370,250, 50);

	//管理员注册界面按钮初始化
	Register_Btns.emplace_back(new PushButton("管理员注册"));
	Register_Btns.emplace_back(new PushButton("学生注册"));
	for (int i = 0; i < Register_Btns.size(); i++)
	{
		Register_Btns[i]->setFixedSize(250, 50);
		int bx = (Window::width() - Register_Btns[i]->width()) / 2;
		int vspace = (Window::height() - Register_Btns.size() * Register_Btns[i]->height()) / 2;
		int by = vspace + i * Register_Btns[i]->height();
		Register_Btns[i]->move(bx, by);
	}
	RegisterBtn = new PushButton("确认", 670, 260, 80, 40);
	RegisterLine = new LineEdit(150,180,500,40);
	RegisterLine->setTitle("请输入用户名");
	RegisterLine1 = new LineEdit(150, 300, 500, 40);
	RegisterLine1->setTitle("请输入密码");
	RegisterLine2 = new LineEdit(150, 420, 500, 40);
	RegisterLine2->setTitle("请输入管理员密码");
	RegisterLine3 = new LineEdit(150, 260, 500, 40);
	RegisterLine3->setTitle("请输入用户名");
	RegisterLine4 = new LineEdit(150, 260, 500, 40);
	RegisterLine4->setTitle("请输入密码");

	//注册页面按钮初始化
	RegisterBtn1 = new PushButton("确认", 670, 260, 80, 40);
	RegisterLine5 = new LineEdit(150, 220, 500, 40);
	RegisterLine5->setTitle("请输入用户名");
	RegisterLine6 = new LineEdit(150, 300, 500, 40);
	RegisterLine6->setTitle("请输入密码");

	//登陆界面按钮初始化
	m_addBtn.reset(new PushButton("确认",670,260,80,40));
	m_addEdit.reset(new LineEdit(150,220,500,40));
	m_addEdit->setTitle("请输入用户名");
	m_addEdit1.reset(new LineEdit(150, 300, 500, 40));
	m_addEdit1->setTitle("请输入密码");

	//管理员界面按钮初始化
	admin_Btns.emplace_back(new PushButton("录入学生信息"));
	admin_Btns.emplace_back(new PushButton("删除学生信息"));
	admin_Btns.emplace_back(new PushButton("增加学生信息"));
	admin_Btns.emplace_back(new PushButton("修改学生信息"));
	admin_Btns.emplace_back(new PushButton("查阅学生信息"));
	admin_Btns.emplace_back(new PushButton("用户密码管理"));
	admin_Btns.emplace_back(new PushButton("邮箱"));
	admin_Btns.emplace_back(new PushButton("退出系统"));
	for (int i = 0; i < admin_Btns.size(); i++)
	{
		admin_Btns[i]->setFixedSize(250, 40);
		int bx = (Window::width() - admin_Btns[i]->width()) / 2;
		int vspace = (Window::height() - admin_Btns.size() * admin_Btns[i]->height()) / 2;
		int by = vspace + i * admin_Btns[i]->height();
		admin_Btns[i]->move(bx, by);
	}

	//管理员功能实现
	int inputW = 250, inputH = 40;
	int x1 = 150, x2 = 450, y = 100, step = 60;//设置输入弹窗
	stuLineID = new LineEdit();
	stuLineID->setTitle("请输入学号");
	stuLineID->move(x1, y); stuLineID->setFixedSize(inputW, inputH);
	stuLineName = new LineEdit();
	stuLineName->setTitle("请输入姓名");
	stuLineName->move(x1, y + step); stuLineName->setFixedSize(inputW, inputH);
	stuLineBirth = new LineEdit();
	stuLineBirth->setTitle("请输入生日，格式为XXXX-YY-ZZ");
	stuLineBirth->move(x1, y + step * 2); stuLineBirth->setFixedSize(inputW, inputH);
	stuLineSex = new LineEdit();
	stuLineSex->setTitle("请输入性别");
	stuLineSex->move(x1, y + step * 3); stuLineSex->setFixedSize(inputW, inputH);
	stuLineClass = new LineEdit();
	stuLineClass->setTitle("请输入班级");
	stuLineClass->move(x1, y + step * 4); stuLineClass->setFixedSize(inputW, inputH);
	submitInfoBtn = new PushButton("确认基本信息",0,0,150,30);
	submitInfoBtn->move(x2, y + step * 4);
	gradeLineCourse = new LineEdit();
	gradeLineCourse->setTitle("请输入课程名");
	gradeLineCourse->move(x1, y + step * 6); gradeLineCourse->setFixedSize(inputW, inputH);
	gradeLineCredit = new LineEdit();
	gradeLineCredit->setTitle("请输入学分");
	gradeLineCredit->move(x1, y + step * 7); gradeLineCredit->setFixedSize(inputW, inputH);
	gradeLineGPA = new LineEdit();
	gradeLineGPA->setTitle("请输入GPA");
	gradeLineGPA->move(x1, y + step * 8); gradeLineGPA->setFixedSize(inputW, inputH);
	addGradeBtn = new PushButton("添加课程");
	addGradeBtn->move(x2, y + step * 8);
	finishAllBtn = new PushButton("完成全部录入");
	finishAllBtn->move((Window::width() - 200) / 2, y + step * 10);
	studentIDLine = new LineEdit(); // 学号
	studentIDLine->setTitle("请输入学号");
	studentIDLine->move(x1, y); studentIDLine->setFixedSize(inputW, inputH);
	studentNameLine = new LineEdit();    // 姓名
	studentNameLine->move(x1, y + step); studentNameLine->setFixedSize(inputW, inputH);
	studentClassLine = new LineEdit();   // 班级
	studentClassLine->move(x1, y + step * 2); studentClassLine->setFixedSize(inputW, inputH);
	userIDLine = new LineEdit();
	userIDLine->setTitle("请输入用户名");
	userIDLine->move(x1, y); userIDLine->setFixedSize(inputW, inputH);
	// 成绩输入框
	courseNameLine = new LineEdit();     // 课程名
	courseNameLine->setTitle("请输入课程名");
	courseNameLine->move(x1, y + step * 3); courseNameLine->setFixedSize(inputW, inputH);
	courseCreditLine = new LineEdit();   // 学分
	courseCreditLine->setTitle("请输入学分");
	courseCreditLine->move(x1, y + step * 5); courseCreditLine->setFixedSize(inputW, inputH);
	courseGpaLine = new LineEdit();      // 绩点
	courseGpaLine->setTitle("请输入绩点");
	courseGpaLine->move(x1, y + step * 7); courseGpaLine->setFixedSize(inputW, inputH);
	// 按钮
	submitGradeBtn = new PushButton("提交成绩");
	submitGradeBtn->move(x2, y + step * 5);
	queryBtn = new PushButton("确认", 670, 260, 80, 40);
	finishAllBtn1 = new PushButton("完成所有");
	finishAllBtn1->move((Window::width() - 200) / 2, y + step * 8);
	studentBirthLine = new LineEdit();
	studentSexLine   = new LineEdit();
	courseIndexLine = new LineEdit();
	ensureBtn = new PushButton("确认",670,450,80,40);
	fixstudentNameLine = new LineEdit(400,180,150,30);
	fixstudentBirthLine = new LineEdit(400,210,150,30);
	fixstudentSexLine = new LineEdit(400,240, 150, 30);
	fixstudentClassLine = new LineEdit(400,270, 150, 30);
	fixcourseNameLine = new LineEdit(400,300, 150, 30);
	fixcourseCreditLine = new LineEdit(400,330, 150, 30);
	fixcourseGpaLine = new LineEdit(400,360, 150, 30);
	fixstudentNameLine->setTitle("请输入姓名");
	fixstudentBirthLine->setTitle("请输入生日");
	fixstudentSexLine->setTitle("请输入性别");
	fixstudentClassLine->setTitle("请输入班级");
	fixcourseNameLine->setTitle("请输入课程");
	fixcourseCreditLine->setTitle("请输入学分");
	fixcourseGpaLine->setTitle("请输入绩点");
	adopbtn  = new PushButton("删除用户",360,200,240,40);
	adopbtn1 = new PushButton("修改密码",360,260,240,40);
	adopbtn2 = new PushButton("修改管理员密码",360,320,240,40);
	passwordLine = new LineEdit(400, 240, 150, 30);
	passwordLine->setTitle("请输入密码");
	newPasswordLine = new LineEdit(400, 180, 150, 30);
	newPasswordLine->setTitle("请输入新密码");
	confirmPasswordLine = new LineEdit(400, 260, 150, 30);
	confirmPasswordLine->setTitle("请确认新密码");
	confirmPasswordBtn = new PushButton("确认",400, 420, 150, 30);
	confirmPasswordBtn1 = new PushButton("确认新密码", 400, 420, 150, 30);

	//学生功能实现
	stu_Btns.emplace_back(new PushButton("查询学生信息"));
	stu_Btns.emplace_back(new PushButton("查询学生成绩"));
	stu_Btns.emplace_back(new PushButton("邮箱"));
	stu_Btns.emplace_back(new PushButton("密码修改"));
	stu_Btns.emplace_back(new PushButton("退出系统"));
	for (int i = 0; i < stu_Btns.size(); i++)
	{
		stu_Btns[i]->setFixedSize(250, 40);
		int bx = (Window::width() - stu_Btns[i]->width()) / 2;
		int vspace = (Window::height() - stu_Btns.size() * stu_Btns[i]->height()) / 2;
		int by = vspace + i * stu_Btns[i]->height();
		stu_Btns[i]->move(bx, by);
	}
}										 
										 
void Management::run()
{
	//获取菜单的返回值
	op = Menu;
	Window::beginDraw();
	while (true)
	{
		Window::clear();
		drawBackground();

		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			switch (m_msg.message)
			{
			case WM_KEYDOWN:		//按键按下
				//按ESC退出操作，返回主界面
				if (m_msg.vkcode == VK_ESCAPE)
				{
				
				}
				break;
			default:		//鼠标操作
				break;
			}
		}

		//弹窗运行
		if (m_msgBox && m_msgBox->isVisible())
		{
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);
			Window::flushDraw();
			continue; // 阻止下面逻辑执行
		}

		switch (op)
		{
		case Menu:
			op = menu();
			break;
		case Management::Login:
			display();
			break;
		case Management::Register:
			op = add(); // 获取 add() 的返回值
			break;
		case Management::Registera:
			Register1();
			break;
		case Management::Registerb:
			Register2();
			break;
		case Management::stumenu1:
			op = stumenu();
			break;
		case Management::adminmenu1:
			op = adminmenu();
			break;
		case Management::Adop1:
			adop1();
			break;
		case Management::Adop2:
			adop2();
			break;
		case Management::Adop3:
			adop3();
			break;
		case Management::Adop4:
			adop4();
			break;
		case Management::Adop5:
			adop5();
			break;
		case Management::Adop6:
			adop6();
			break;
		case Management::Adop7:
			adop7();
			break;
		case Management::Adop8:
			adop8();
			break;
		case Management::Adop9:
			adop9();
			break;
		case Management::Adop2_1:
			adop2_1();
			break;
		case Management::Adop4_1:
			adop4_1();
			break;
		case Management::Adop5_1:
			adop5_1();
			break;
		case Management::Adop6_1:
			adop6_1();
			break;
		case Management::Adop6_2:
			adop6_2();
			break;
		case Management::Adop6_3:
			adop6_3();
			break;
		case Management::Adop6_4:
			adop6_4();
			break;
		case Management::Adop6_5:
			adop6_5();
			break;
		case Management::Stuop1:
			stuop1();
			break;
		case Management::Stuop2:
			stuop2();
			break;
		case Management::Stuop3:
			stuop3();
			break;
		case Management::Stuop4:
			stuop4();
			break;
		case Management::Stuop5:
			stuop5();
			break;
		default:
			exit(666);
			break;
		}

		Window::flushDraw();
		MSG msg;
	}
	



	Window::endDraw();
}


void Management::eventLoop()
{
	if (op == Login)
	{
	}
}

// 去除字符串首尾的空格
string trim(const string& str) {
	size_t first = str.find_first_not_of(" \t\r\n");
	size_t last = str.find_last_not_of(" \t\r\n");
	return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

//开机自启动，读取文件
void Management::readFile(const std::string& fileName)
{
	fstream read(fileName, ios::in);

	for (auto user :Users)
		delete user;
	Users.clear();
	string line;
	bool isFirstLine = true;
	//对文件每行进行遍历读取
	while (getline(read,line)) {
		stringstream ss(line);
		string username, userkey, userrole;
		// 第一行是管理员密码
		if (isFirstLine) {
			//读取管理员密码
			getline(ss, username, ',');
			if (username == "AdminKey") {
				getline(ss, Admin_Key, ',');
				Admin_Key = trim(Admin_Key);
				isFirstLine = false;
				continue;
			}
		}
		// 读取用户数据
		if (getline(ss, username, ',') && getline(ss, userkey, ',') && getline(ss, userrole)) {
			Users.push_back(new User(username, userkey, userrole));
		}
	}
	//关闭文件
	
	read.close();
}
//读取学生数据
void Management::readStuFile(const std::string& fileName) {
	std::ifstream read(fileName);
	studentList.clear();  // 清空之前的数据

	std::string line;
	while (getline(read, line)) {
		if (line.empty()) continue;  // 跳过空行
		Stu_data stu;
		stu.formatwrite(line);  // 读取并格式化学生数据，同时填充 courses 向量
		studentList.push_back(stu);  // 存储到学生列表
	}

	read.close();
}

int Management::menu()
{
	for (auto& btn : Register_Btns)
		btn->hide();
	settextstyle(36, 0, "楷体");
	outtextxy((Window::width() - textwidth("欢迎使用上海海事大学学生档案管理系统")) / 2, 100, "欢迎使用上海海事大学学生档案管理系统");
		for (int i = 0; i < menu_btns.size(); i++)
		{
			menu_btns[i]->show();
			menu_btns[i]->eventLoop(m_msg);
			if (menu_btns[i]->isClicked() && Timer::startTimer(500, 0))
			{
				return i;
			}
		}
		menubtn->show();
		menubtn->eventLoop(m_msg);

		Window::flushDraw();
		if (menubtn->isClicked() && Timer::startTimer(400, 0))
		{
			return 666;
		}
	return Menu;
}

//登录页面
void Management::display()
{
	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		settextcolor(RED);
		outtextxy(150, 190, "用户名");
		settextcolor(RED);
		outtextxy(150, 270, "密码");

		//返回前一个界面
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = Menu;  // 返回主界面
				break;
			}
		}

		m_addBtn->show();
		m_addEdit->show();
		m_addEdit1->show();

		m_addBtn->eventLoop(m_msg);
		m_addEdit->eventLoop(m_msg);
		m_addEdit1->eventLoop(m_msg);

		if (m_addBtn->isClicked() && Timer::startTimer(400, 0))
		{
			std::string username = trim(m_addEdit->text1());
			std::string password = trim(m_addEdit1->text1());

			bool nameExists = false;
			bool keyMatches = false;
			std::string role;

			for (auto user : Users)
			{
				if (user->getName() == username)
				{
					nameExists = true;
					if (user->getKey() == password)
					{
						keyMatches = true;
						role = user->getRole();
						Current_user = user;  // 设置当前用户
					}
					break;
				}
			}

			if (!nameExists)
			{
				m_msgBox->setMessage("用户名不存在，请重新输入！");
			}
			else if (!keyMatches)
			{
				m_msgBox->setMessage("密码错误，请重新输入！");
			}
			else
			{
				if (role == "admin")
				{
					m_msgBox->setMessage("欢迎您，管理员！");
					op = Management::adminmenu1;
				}
				else
				{
					m_msgBox->setMessage("欢迎您，学生！");
					op = Management::stumenu1;
				}

				// 清空输入
				m_addEdit->clear();
				m_addEdit1->clear();
				break;  // 登录成功跳转
			}
		}
		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}
		Window::flushDraw();
	}
}
//注册跳转页面
int Management::add()
{
	for (auto& btn : menu_btns)
		btn->hide();
	for (auto& btn : admin_Btns)
		btn->hide();

	while(true)
	{
		Window::clear();
		drawBackground();  // 可选：显示背景图
		char title[20] = "注册方式";
		outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

		// 检查 ESC 是否按下
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				return Menu;  // 返回主界面
			}
		}

		// 事件循环 + 检查按钮点击
		for (int i = 0; i < Register_Btns.size(); i++)
		{
			Register_Btns[i]->show();
			Register_Btns[i]->eventLoop(m_msg);

			if (Register_Btns[i]->isClicked() && Timer::startTimer(400, 0))
			{
				return i + 2;  // 跳转到 Registera / Registerb
			}
		}
		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}

		Window::flushDraw();
	}
	return Register;
}
//管理注册页面
void Management::Register1()
{
	while (true)
	{
		Window::clear();
		drawBackground();
		settextcolor(RED);
		outtextxy(150, 150, "用户名");
		settextcolor(RED);
		outtextxy(150, 270, "密码");
		settextcolor(RED);
		outtextxy(150, 390, "管理员密码");

		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = Register;
				break;
			}
		}

		RegisterBtn->show();
		RegisterLine->show();
		RegisterLine1->show();
		RegisterLine2->show();

		RegisterBtn->eventLoop(m_msg);
		RegisterLine->eventLoop(m_msg);
		RegisterLine1->eventLoop(m_msg);
		RegisterLine2->eventLoop(m_msg);

		if (RegisterBtn->isClicked() && Timer::startTimer(400, 0))
		{
			std::string username = trim(RegisterLine->text1());
			std::string password = trim(RegisterLine1->text1());
			std::string inputKey = trim(RegisterLine2->text1());

			for (auto user : Users) {
				if (user->getName() == username) {
					m_msgBox->setMessage("用户名已存在，注册失败！");
					break;
				}
			}

			if (inputKey != Admin_Key) {
				m_msgBox->setMessage("用管理员密码错误，注册失败！");
				break;
			}

			bool hasLetter = false, hasDigit = false, hasSpecial = false;
			for (char ch : password) {
				if (isalpha(ch)) hasLetter = true;
				else if (isdigit(ch)) hasDigit = true;
				else hasSpecial = true;
			}

			std::string strength;
			if (password.length() < 6)
				strength = "弱（长度小于6）";
			else if ((hasLetter && hasDigit && hasSpecial) && password.length() >= 8)
				strength = "强";
			else if (hasLetter && hasDigit)
				strength = "中";
			else
				strength = "弱";

			if (strength == "弱（长度小于6）" || strength == "弱") {
				m_msgBox->setMessage("密码强度过低，注册失败！");
				break;
			}

			User* newUser = new User(username, password, "admin");
			Users.push_back(newUser);

			std::ofstream outFile("./IMAGE/users.csv", std::ios::app);
			if (outFile.is_open())
			{
				outFile << username << "," << password << "," << "admin" << "\n";
				outFile.close();
				m_msgBox->setMessage("密码强度符合，注册成功！");
			}

			//清空输入框
			RegisterLine->clear();
			RegisterLine1->clear();
			RegisterLine2->clear();
		}
		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}

		Window::flushDraw();
	}

}
//学生注册页面
void Management::Register2()
{
	while (true)
	{
		Window::clear();
		drawBackground();
		settextcolor(RED);
		outtextxy(150, 190, "用户名");
		settextcolor(RED);
		outtextxy(150, 270, "密码");

		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = Register;
				break;
			}
		}

		RegisterBtn1->show();
		RegisterLine5->show();
		RegisterLine6->show();

		RegisterBtn1->eventLoop(m_msg);
		RegisterLine5->eventLoop(m_msg);
		RegisterLine6->eventLoop(m_msg);

		if (RegisterBtn1->isClicked() && Timer::startTimer(400, 0))
		{
			std::string username = trim(RegisterLine5->text1());
			std::string password = trim(RegisterLine6->text1());

			for (auto user : Users) {
				if (user->getName() == username) {
					m_msgBox->setMessage("用户名已存在，注册失败！");
					break;
				}
			}

			bool hasLetter = false, hasDigit = false, hasSpecial = false;
			for (char ch : password) {
				if (isalpha(ch)) hasLetter = true;
				else if (isdigit(ch)) hasDigit = true;
				else hasSpecial = true;
			}

			std::string strength;
			if (password.length() < 6)
				strength = "弱（长度小于6）";
			else if ((hasLetter && hasDigit && hasSpecial) && password.length() >= 8)
				strength = "强";
			else if (hasLetter && hasDigit)
				strength = "中";
			else
				strength = "弱";

			if (strength == "弱（长度小于6）" || strength == "弱") {
				m_msgBox->setMessage("密码强度过低，注册失败！");
				break;
			}

			User* newUser = new User(username, password, "stu");
			Users.push_back(newUser);

			std::ofstream outFile("./IMAGE/users.csv", std::ios::app);
			if (outFile.is_open())
			{
				outFile << username << "," << password << "," << "stu" << "\n";
				outFile.close();
				m_msgBox->setMessage("密码强度符合，注册成功！");
			}

			RegisterLine5->clear();
			RegisterLine6->clear();
		}
		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}
		Window::flushDraw();
	}
	

}
//管理员操作界面
int Management::adminmenu()
{
	readStuFile("./IMAGE/students_data.csv");//读取学生数据

	while (true)
	{
		Window::clear();
		drawBackground();  // 背景图
		settextstyle(36, 0, "楷体");
		outtextxy((Window::width() - textwidth("管理员操作界面")) / 2, 50, "管理员操作界面");

		// 检测 ESC 返回登录界面
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				return Login;  // 返回主菜单
			}
		}

		// 显示并监听按钮事件
		for (int i = 0; i < admin_Btns.size(); i++)
		{
			admin_Btns[i]->show();
			admin_Btns[i]->eventLoop(m_msg);

			if (admin_Btns[i]->isClicked() && Timer::startTimer(400, 0))
			{
				return i + 6;  // 返回对应功能编号
			}
		}

		Window::flushDraw();
	}

	return adminmenu1;  // 理论上不会执行到
}
//管理员功能1：添加学生信息
void Management::adop1()
{
	for (auto& btn : admin_Btns) btn->hide();

	// 清空输入框
	stuLineID->clear();
	stuLineName->clear();
	stuLineBirth->clear();
	stuLineSex->clear();
	stuLineClass->clear();
	gradeLineCourse->clear();
	gradeLineCredit->clear();
	gradeLineGPA->clear();

	std::string currentID, currentName, currentBirth, currentSex, currentClass;

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(70, 50, "学生信息录入（按 ESC 返回）");
		outtextxy(70, 100, ("学号: "));
		outtextxy(70, 160, ("姓名: "));
		outtextxy(70, 220, ("生日: "));
		outtextxy(70, 280, ("性别: "));
		outtextxy(70, 340, ("班级: "));
		outtextxy(70, 460, ("课程: "));
		outtextxy(70, 520, ("学分: "));
		outtextxy(70, 580, ("GPA: "));


		// 显示输入组件
		stuLineID->show(); stuLineID->eventLoop(m_msg);
		stuLineName->show(); stuLineName->eventLoop(m_msg);
		stuLineBirth->show(); stuLineBirth->eventLoop(m_msg);
		stuLineSex->show(); stuLineSex->eventLoop(m_msg);
		stuLineClass->show(); stuLineClass->eventLoop(m_msg);
		submitInfoBtn->show(); submitInfoBtn->eventLoop(m_msg);

		gradeLineCourse->show(); gradeLineCourse->eventLoop(m_msg);
		gradeLineCredit->show(); gradeLineCredit->eventLoop(m_msg);
		gradeLineGPA->show(); gradeLineGPA->eventLoop(m_msg);
		addGradeBtn->show(); addGradeBtn->eventLoop(m_msg);

		finishAllBtn->show(); finishAllBtn->eventLoop(m_msg);

		// 检测 ESC 返回
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = adminmenu1;
				break;
			}
		}

		// 提交基本信息（只记录一次）
		if (submitInfoBtn->isClicked() && Timer::startTimer(400, 0))
		{
			currentID = trim(stuLineID->text1());
			currentName = trim(stuLineName->text1());
			currentBirth = trim(stuLineBirth->text1());
			currentSex = trim(stuLineSex->text1());
			currentClass = trim(stuLineClass->text1());

			if (currentID.empty() || currentName.empty()) {
				m_msgBox->setMessage("学号和姓名不能为空！");
			}
			else {
				m_msgBox->setMessage("学生基本信息已确认，可继续添加成绩！");
			}
		}

		// 添加课程（每门课程写入CSV）
		if (addGradeBtn->isClicked() && Timer::startTimer(400, 0))
		{
			if (currentID.empty()) {
				m_msgBox->setMessage("请先提交学生基本信息！");
			}
			else {
				std::string cname = trim(gradeLineCourse->text1());
				std::string credit = trim(gradeLineCredit->text1());
				std::string gpa = trim(gradeLineGPA->text1());

				if (cname.empty() || credit.empty() || gpa.empty()) {
					m_msgBox->setMessage("课程、学分、绩点都不能为空！");
				}
				else {
					// 写入 CSV 一行
					Stu_data stu(currentID, currentName, currentBirth, currentSex, currentClass, cname, credit, gpa);
					std::ofstream out("./IMAGE/students_data.csv", std::ios::app);
					out << stu.formatInfo() << "\n";
					out.close();

					studentList.push_back(stu);
					m_msgBox->setMessage("课程信息已保存！");
					gradeLineCourse->clear(); gradeLineCredit->clear(); gradeLineGPA->clear();
				}
			}
		}

		// 完成所有操作并退出
		if (finishAllBtn->isClicked() && Timer::startTimer(400, 0))
		{
			op = adminmenu1;
			break;
		}


		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible())
		{
			m_msgBox->show();  // 弹窗显示
			m_msgBox->eventLoop(m_msg);  // 处理弹窗
			Window::flushDraw();  // 确保界面更新
			continue;  // 阻止下面逻辑执行，直到弹窗关闭
		}
		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
//管理员功能2：增加学生信息
void Management::adop2()
{
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	// 清空输入框
	studentIDLine->clear();
	studentNameLine->clear();
	studentClassLine->clear();
	courseNameLine->clear();
	courseCreditLine->clear();
	courseGpaLine->clear();

	std::string selectedID;

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 20, "为已有学生添加成绩（按 ESC 返回）");

		// 显示学生信息列表（选择学生）
		outtextxy(100, 150, "学生信息：");
		for (int i = 0; i < studentList.size(); i++)
		{
			outtextxy(100, 180 + i * 30, (studentList[i].sid + " " + studentList[i].sname).c_str());
		}

		// 用户选择学号
		outtextxy(100, 50, "请输入学号：");
		studentIDLine->show();
		studentIDLine->eventLoop(m_msg);
		queryBtn->show(); // 假设你添加了查询按钮
		queryBtn->eventLoop(m_msg);

		// 查找学生
		if (queryBtn->isClicked() && Timer::startTimer(400, 0))
		{
			selectedID = trim(studentIDLine->text1());  // 确保去除学号中的空格
			auto it = find_if(studentList.begin(), studentList.end(),
				[&selectedID](const Stu_data& s) { return s.sid == selectedID; });

			if (it != studentList.end())
			{
				studentNameLine->setText(it->sname);
				studentClassLine->setText(it->sclass);
				m_msgBox->setMessage("学生信息已加载，输入成绩：");

				// 将学生信息传递到adop3()
				currentStudent.setStudentInfo(it->sid, it->sname, it->sbirth, it->ssex, it->sclass);  // 设置当前学生的信息
				op = Management::Adop2_1;  // 跳转到adop2_1
				break;
			}
			else
			{
				m_msgBox->setMessage("未找到学号为 " + selectedID + " 的学生！");
			}
		}
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = adminmenu1;
				break;
			}
		}

		// 防止 UI 冻结：如果消息框可见，则阻止后续事件
		if (m_msgBox && m_msgBox->isVisible())
		{
			m_msgBox->show();  // 显示消息框
			m_msgBox->eventLoop(m_msg);  // 处理消息框事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到消息框关闭
		}
		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
void Management::adop2_1()
{
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	// 清空输入框
	courseNameLine->clear();
	courseCreditLine->clear();
	courseGpaLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 50, "为学生添加成绩（按 ESC 返回）");

		// 显示当前学生信息
		outtextxy(100, 150, ("学号: " + currentStudent.sid).c_str());
		outtextxy(100, 180, ("姓名: " + currentStudent.sname).c_str());
		outtextxy(100, 210, ("班级: " + currentStudent.sclass).c_str());

		// 输入课程成绩信息
		outtextxy(100, 240, "课程名：");
		courseNameLine->show();
		courseNameLine->eventLoop(m_msg);
		settextcolor(RED);
		outtextxy(100, 370, "学分：");
		courseCreditLine->show();
		courseCreditLine->eventLoop(m_msg);
		settextcolor(RED);
		outtextxy(100, 490, "绩点：");
		courseGpaLine->show();
		courseGpaLine->eventLoop(m_msg);

		submitGradeBtn->show();  // 显示提交按钮
		submitGradeBtn->eventLoop(m_msg);

		// 提交成绩
		if (submitGradeBtn->isClicked() && Timer::startTimer(400, 0))
		{
			std::string cname = trim(courseNameLine->text1());
			std::string credit = trim(courseCreditLine->text1());
			std::string gpa = trim(courseGpaLine->text1());

			if (cname.empty() || credit.empty() || gpa.empty()) {
				m_msgBox->setMessage("课程名、学分、绩点不能为空！");
			}
			else {
				// 添加成绩信息到学生数据
				currentStudent.cname = cname;
				currentStudent.credit = credit;
				currentStudent.gpa = gpa;

				// 写入学生成绩到文件
				std::ofstream out("./IMAGE/students_data.csv", std::ios::app);
				out << currentStudent.formatInfo() << "\n";  // 使用 formatInfo() 格式化并写入学生信息
				out.close();

				m_msgBox->setMessage("成绩添加成功！");
				courseNameLine->clear();
				courseCreditLine->clear();
				courseGpaLine->clear();
			}
		}

		// ESC返回
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = Adop2;
				break;
			}
		}

		// 防止 UI 冻结：如果消息框可见，则阻止后续事件
		if (m_msgBox && m_msgBox->isVisible())
		{
			m_msgBox->show();  // 显示消息框
			m_msgBox->eventLoop(m_msg);  // 处理消息框事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到消息框关闭
		}
		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
//管理员功能3：删除学生信息，有bug改不掉，放着了先
void Management::adop3()
{
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	// 清空输入框
	studentIDLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 0, "删除学生信息（按 ESC 返回）");

		// 显示学生信息列表
		//outtextxy(100, 100, "学生信息：");
		for (int i = 0; i < studentList.size(); i++)
		{
			outtextxy(100, 180 + i * 30, (studentList[i].sid + " " + studentList[i].sname).c_str());
		}

		// 输入要删除的学生学号
		outtextxy(100, 50, "请输入要删除的学号：");
		studentIDLine->show();
		studentIDLine->eventLoop(m_msg); // 获取学号输入

		// 按下确认按钮处理
		queryBtn->show(); // 显示确认按钮
		queryBtn->eventLoop(m_msg); // 等待按钮事件

		if (queryBtn->isClicked() && Timer::startTimer(400, 0)) // 判断按钮点击
		{
			std::string selectedID = trim(studentIDLine->text1());  // 获取学号
			auto it = find_if(studentList.begin(), studentList.end(),
				[&selectedID](const Stu_data& s) { return s.sid == selectedID; });

			if (it != studentList.end())  // 找到学生
			{
				m_msgBox->setMessage("确定要删除学号为 " + selectedID + " 的学生信息吗？");
				
				
				// 弹窗显示并等待按钮点击
				if (m_msgBox->m_okBtn.isClicked())  // 确认按钮点击
				{
					// 删除学生信息
					studentList.erase(it);
					m_msgBox->setMessage("学生信息删除成功！");

					// 更新文件，删除学生数据
					std::ofstream outFile("./IMAGE/students_data.csv", std::ios::trunc);
					for (const auto& student : studentList) {
						outFile << student.formatInfo() << "\n";
					}
					outFile.close();
				}
			}
			else {
				m_msgBox->setMessage("未找到学号为 " + selectedID + " 的学生！");
			}
		}

		// 返回管理员操作菜单
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = adminmenu1;
				break;
			}
		}

		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible())
		{
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}

		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
//管理员功能四：修改学生信息
void Management::adop4()
{
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	// 清空输入框
	studentIDLine->clear();

	std::string selectedID;

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 50, "修改学生信息（按 ESC 返回）");

		// 输入修改学生学号
		outtextxy(100, 150, "请输入学号：");
		studentIDLine->show();
		studentIDLine->eventLoop(m_msg);  // 获取学号输入

		queryBtn->show();  // 显示查询按钮
		queryBtn->eventLoop(m_msg);  // 等待按钮事件

		// 查找学生
		if (queryBtn->isClicked() && Timer::startTimer(400, 0))
		{
			selectedID = trim(studentIDLine->text1());  // 获取学号
			auto it = find_if(studentList.begin(), studentList.end(),
				[&selectedID](const Stu_data& s) { return s.sid == selectedID; });

			if (it != studentList.end())  // 找到学生
			{
				// 使用 setStudentInfo1 设置学生信息
				currentStudent.setStudentInfo1(it->sid, it->sname, it->sbirth, it->ssex, it->sclass, it->cname, it->credit, it->gpa);

				// 跳转到 adop4_1 允许修改学生信息
				op = Adop4_1;
				break;  // 退出当前循环，等待run()中的op处理
			}
			else {
				m_msgBox->setMessage("未找到学号为 " + selectedID + " 的学生！");
			}
		}

		// ESC返回
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = adminmenu1;
				break;
			}
		}

		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}

		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
void Management::adop4_1()
{
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	// 清空输入框
	fixstudentNameLine->clear();
	fixstudentBirthLine->clear();
	fixstudentSexLine->clear();
	fixstudentClassLine->clear();
	fixcourseNameLine->clear();
	fixcourseCreditLine->clear();
	fixcourseGpaLine->clear();

	// 添加输入框和按钮的显示
	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 50, "修改学生信息（按 ESC 返回）");

		// 显示当前学生信息
		outtextxy(100, 150, ("学号: " + currentStudent.sid).c_str());
		outtextxy(100, 180, ("姓名: " + currentStudent.sname).c_str());
		outtextxy(100, 210, ("生日: " + currentStudent.sbirth).c_str());
		outtextxy(100, 240, ("性别: " + currentStudent.ssex).c_str());
		outtextxy(100, 270, ("班级: " + currentStudent.sclass).c_str());
		outtextxy(100, 300, ("课程: " + currentStudent.cname).c_str());
		outtextxy(100, 330, ("学分: " + currentStudent.credit).c_str());
		outtextxy(100, 360, ("gpa: " + currentStudent.gpa).c_str());
		// 姓名
		fixstudentNameLine->show();
		fixstudentNameLine->eventLoop(m_msg);

		// 生日
		fixstudentBirthLine->show();
		fixstudentBirthLine->eventLoop(m_msg);

		// 班级
		fixstudentClassLine->show();
		fixstudentClassLine->eventLoop(m_msg);

		// 性别
		fixstudentSexLine->show();
		fixstudentSexLine->eventLoop(m_msg);

		// 课程名
		fixcourseNameLine->show();
		fixcourseNameLine->eventLoop(m_msg);

		// 学分
		fixcourseCreditLine->show();
		fixcourseCreditLine->eventLoop(m_msg);

		// GPA
		fixcourseGpaLine->show();
		fixcourseGpaLine->eventLoop(m_msg);

		// 显示确认按钮
		ensureBtn->show();
		ensureBtn->eventLoop(m_msg);

		// 提交修改
		if (ensureBtn->isClicked() && Timer::startTimer(400, 0))
		{
			// 获取用户输入并更新学生信息
			currentStudent.sname = trim(fixstudentNameLine->text1());
			currentStudent.sbirth = trim(fixstudentBirthLine->text1());
			currentStudent.ssex = trim(fixstudentSexLine->text1());
			currentStudent.sclass = trim(fixstudentClassLine->text1());
			currentStudent.cname = trim(fixcourseNameLine->text1());
			currentStudent.credit = trim(fixcourseCreditLine->text1());
			currentStudent.gpa = trim(fixcourseGpaLine->text1());

			// 找到并更新学生列表中的相应学生
			auto it = std::find_if(studentList.begin(), studentList.end(),
				[this](Stu_data& s) { return s.sid == this->currentStudent.sid; });  // 使用 this->currentStudent

			if (it != studentList.end()) {
				it->setStudentInfo1(currentStudent.sid, currentStudent.sname, currentStudent.sbirth, currentStudent.ssex, currentStudent.sclass,currentStudent.cname, currentStudent.credit, currentStudent.gpa);
			}

			// 将更新后的学生数据写回到文件中
			std::ofstream out("./IMAGE/students_data.csv", std::ios::trunc);  // 使用 trunc 覆盖文件
			if (out.is_open()) {
				for (const auto& student : studentList) {
					out << student.formatInfo() << "\n";  // 写入学生信息
				}
				out.close();
				m_msgBox->setMessage("学生信息修改成功！");
			}
			else {
				m_msgBox->setMessage("无法打开文件，保存失败！");
			}
		}

		// ESC返回
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = Adop4;
				break;
			}
		}

		// 防止 UI 冻结：如果消息框可见，则阻止后续事件
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理消息框事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到消息框关闭
		}

		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
//管理员功能五：查阅学生信息
void Management::adop5()
{
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	// 清空输入框
	studentIDLine->clear();

	std::string selectedID;

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 0, "查阅学生信息（按 ESC 返回）");

		// 输入修改学生学号
		outtextxy(100, 50, "请输入学号：");
		studentIDLine->show();
		studentIDLine->eventLoop(m_msg);  // 获取学号输入

		queryBtn->show();  // 显示查询按钮
		queryBtn->eventLoop(m_msg);  // 等待按钮事件

		// 查找学生
		if (queryBtn->isClicked() && Timer::startTimer(400, 0))
		{
			selectedID = trim(studentIDLine->text1());  // 获取学号
			auto it = find_if(studentList.begin(), studentList.end(),
				[&selectedID](const Stu_data& s) { return s.sid == selectedID; });

			if (it != studentList.end())  // 找到学生
			{
				// 使用 setStudentInfo1 设置学生信息
				currentStudent.setStudentInfo1(it->sid, it->sname, it->sbirth, it->ssex, it->sclass, it->cname, it->credit, it->gpa);

				// 跳转到 adop4_1 允许修改学生信息
				op = Adop5_1;
				break;  // 退出当前循环，等待run()中的op处理
			}
			else {
				m_msgBox->setMessage("未找到学号为 " + selectedID + " 的学生！");
			}
		}

		// ESC返回
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = adminmenu1;
				break;
			}
		}

		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}

		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
void Management::adop5_1()
{
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 50, "学生信息（按 ESC 返回）");

		// 显示当前学生信息
		outtextxy(100, 150, ("学号: " + currentStudent.sid).c_str());
		outtextxy(100, 180, ("姓名: " + currentStudent.sname).c_str());
		outtextxy(100, 210, ("生日: " + currentStudent.sbirth).c_str());
		outtextxy(100, 240, ("性别: " + currentStudent.ssex).c_str());
		outtextxy(100, 270, ("班级: " + currentStudent.sclass).c_str());
		outtextxy(100, 300, ("课程: " + currentStudent.cname).c_str());
		outtextxy(100, 330, ("学分: " + currentStudent.credit).c_str());
		outtextxy(100, 360, ("GPA: " + currentStudent.gpa).c_str());

		// ESC返回
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = Adop5;
				break;
			}
		}

		Window::flushDraw();
	}
}
//管理员功能六：用户管理
void Management::adop6()
{
	while (true)
	{
		Window::clear;
		drawBackground();
		outtextxy((Window::width() - textwidth("请选择操作")) / 2, 150, "请选择操作");
		adopbtn->show();
		adopbtn1->show();
		adopbtn2->show();
		adopbtn->eventLoop(m_msg);
		adopbtn1->eventLoop(m_msg);
		adopbtn2->eventLoop(m_msg);
		if (adopbtn->isClicked() && Timer::startTimer(400, 0))
		{
			op = Adop6_1;
			break;
		}
		if (adopbtn1->isClicked() && Timer::startTimer(400, 0))
		{
			op = Adop6_2;
			break;
		}
		if (adopbtn2->isClicked() && Timer::startTimer(400, 0))
		{
			op = Adop6_4;
			break;
		}
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = adminmenu1;
				break;
			}
		}

		Window::flushDraw();
	}	
}
void Management::adop6_1() {
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	// 清空输入框
	studentIDLine->clear();

	// 读取所有用户
	std::vector<User*> users;
	std::ifstream file("./IMAGE/users.csv");
	std::string line;
	bool isFirstLine = true;
	while (getline(file, line)) {
		if (isFirstLine) {
			// 第一行是管理员密码，不需要读取
			isFirstLine = false;
			continue;
		}
		std::stringstream ss(line);
		std::string username, userkey, userrole;
		if (getline(ss, username, ',') && getline(ss, userkey, ',') && getline(ss, userrole)) {
			users.push_back(new User(username, userkey, userrole));
		}
	}
	file.close();

	// 显示当前用户信息
	while (true) {
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 0, "删除用户信息（按 ESC 返回）");

		// 显示用户列表
		outtextxy(100, 150, "用户信息：");
		for (int i = 0; i < users.size(); i++) {
			outtextxy(100, 180 + i * 30, users[i]->getName().c_str());
		}

		// 输入要删除的用户名
		outtextxy(100, 50, "请输入用户名：");
		userIDLine->show();
		userIDLine->eventLoop(m_msg);  // 获取输入的用户名

		queryBtn->show();  // 显示查询按钮
		queryBtn->eventLoop(m_msg);  // 等待按钮事件

		// 查找用户并删除
		if (queryBtn->isClicked() && Timer::startTimer(400, 0)) {
			std::string selectedUsername = trim(userIDLine->text1());  // 获取用户名
			auto it = std::find_if(users.begin(), users.end(),
				[&selectedUsername](User* user) { return user->getName() == selectedUsername; });

			if (it != users.end()) {
				// 弹窗确认删除
				m_msgBox->setMessage("确定要删除用户 " + selectedUsername + " 吗？");

				if (m_msgBox->m_okBtn.isClicked()) {
					// 删除该用户
					users.erase(it);

					// 更新文件，删除该用户
					std::ofstream outFile("./IMAGE/users.csv", std::ios::trunc);
					outFile << "AdminKey," << Admin_Key << "\n";  // 保留管理员密码行
					for (const auto& user : users) {
						outFile << user->getName() << "," << user->getKey() << "," << user->getRole() << "\n";
					}
					outFile.close();
					m_msgBox->setMessage("用户 " + selectedUsername + " 删除成功！");
				}
			}
			else {
				m_msgBox->setMessage("未找到用户名为 " + selectedUsername + " 的用户！");
			}
		}

		// ESC返回
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = Adop6;
				break;
			}
		}

		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}

		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
void Management::adop6_2()
{
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	// 清空输入框
	std::string originalPassword, newPassword, confirmPassword;
	passwordLine->clear();
	newPasswordLine->clear();
	confirmPasswordLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 50, "修改密码（按 ESC 返回）");

		// 输入原密码
		outtextxy(100, 150, "请输入当前密码：");
		passwordLine->show();
		passwordLine->eventLoop(m_msg);  // 获取原密码输入

		// 显示确认按钮
		confirmPasswordBtn->show();
		confirmPasswordBtn->eventLoop(m_msg);  // 等待确认按钮点击

		// 验证原密码
		if (confirmPasswordBtn->isClicked() && Timer::startTimer(400, 0))
		{
			originalPassword = trim(passwordLine->text1());  // 获取原密码

			// 检查输入的密码是否与当前用户的密码匹配
			if (Current_user != nullptr && originalPassword == Current_user->getKey()) {
				// 原密码正确，继续修改密码
				op = Adop6_3;  // 转到密码修改（adop6_3）
				break;  // 跳出循环，过渡到 adop6_3
			}
			else {
				m_msgBox->setMessage("当前密码错误，请重新输入！");
			}
		}

		// ESC返回
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = Adop6;  // 返回到上一级菜单
				break;
			}
		}

		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}

		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
void Management::adop6_3()
{
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	// 清空输入框
	std::string newPassword, confirmPassword;
	newPasswordLine->clear();
	confirmPasswordLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 50, "修改密码（按 ESC 返回）");

		// 输入新密码
		settextstyle(30, 0, "楷体");
		outtextxy(100, 180, "请输入新密码：");
		newPasswordLine->show();
		newPasswordLine->eventLoop(m_msg);  // 获取新密码输入

		// 输入确认密码
		settextstyle(30, 0, "楷体");
		outtextxy(100, 260, "请确认新密码：");
		confirmPasswordLine->show();
		confirmPasswordLine->eventLoop(m_msg);  // 获取确认密码输入

		// 显示确认按钮
		confirmPasswordBtn1->show();
		confirmPasswordBtn1->eventLoop(m_msg);  // 等待确认按钮点击

		// 确认新密码
		if (confirmPasswordBtn1->isClicked() && Timer::startTimer(400, 0))
		{
			newPassword = trim(newPasswordLine->text1());  // 获取新密码
			confirmPassword = trim(confirmPasswordLine->text1());  // 获取确认密码

			// 验证新密码与确认密码是否一致
			if (newPassword == confirmPassword) {
				// 更新当前用户的密码
				Current_user->setKey(newPassword);  // 修改当前用户密码

				// 更新 users.csv 文件
				std::ifstream fileIn("./IMAGE/users.csv");
				std::ofstream fileOut("./IMAGE/users_temp.csv", std::ios::trunc);
				std::string line;
				bool isFirstLine = true;

				while (getline(fileIn, line)) {
					if (isFirstLine) {
						fileOut << line << "\n";  // 写入第一行（管理员数据不变）
						isFirstLine = false;
						continue;
					}

					std::stringstream ss(line);
					std::string username, password, role;
					getline(ss, username, ',');
					getline(ss, password, ',');
					getline(ss, role);

					// 检查是否是当前登录用户
					if (username == Current_user->getName()) {
						fileOut << username << "," << newPassword << "," << role << "\n";  // 更新当前用户密码
					}
					else {
						fileOut << line << "\n";  // 其他用户数据不变
					}
				}

				fileIn.close();
				fileOut.close();

				// 替换旧文件为新文件
				remove("./IMAGE/users.csv");
				rename("./IMAGE/users_temp.csv", "./IMAGE/users.csv");

				m_msgBox->setMessage("密码修改成功！");
			}
			else {
				m_msgBox->setMessage("两次输入的密码不一致，请重新输入！");
			}
		}

		// ESC返回
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = Adop6;  // 返回到上一级菜单
				break;
			}
		}

		if (m_msgBox && m_msgBox->isVisible()) 
		{
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理消息框事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}


		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
void Management::adop6_4()
{
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	// 清空输入框
	std::string originalPassword, newPassword, confirmPassword;
	passwordLine->clear();
	newPasswordLine->clear();
	confirmPasswordLine->clear();

	// 读取管理员密码（第一行）
	std::string adminPassword;
	std::ifstream fileIn("./IMAGE/users.csv");
	if (fileIn.is_open()) {
		std::string line;
		std::getline(fileIn, line);  // 读取第一行
		std::stringstream ss(line);
		std::string username, password, role;
		std::getline(ss, username, ',');
		std::getline(ss, password, ',');
		adminPassword = password;  // 获取管理员密码
	}
	else {
		m_msgBox->setMessage("无法读取管理员密码，请检查文件路径！");
		return;
	}

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 50, "修改管理员密码（按 ESC 返回）");

		// 输入原管理员密码
		outtextxy(100, 150, "请输入当前管理员密码：");
		passwordLine->show();
		passwordLine->eventLoop(m_msg);  // 获取原密码输入

		// 显示确认按钮
		confirmPasswordBtn->show();
		confirmPasswordBtn->eventLoop(m_msg);  // 等待确认按钮点击

		// ESC返回
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = Adop6;  // 返回到上一级菜单
				break;  // 跳出循环，返回上级菜单
			}
		}

		// 验证原密码
		if (confirmPasswordBtn->isClicked() && Timer::startTimer(400, 0))
		{
			originalPassword = trim(passwordLine->text1());  // 获取原密码

			// 检查输入的密码是否与管理员密码匹配
			if (originalPassword == adminPassword) {
				// 原密码正确，继续修改密码
				op = Adop6_5;  // 转到修改密码（adop6_5）
				break;  // 跳出循环，过渡到 adop6_5
			}
			else {
				m_msgBox->setMessage("管理员密码错误，请重新输入！");
			}
		}

		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}

		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
void Management::adop6_5()
{
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	// 清空输入框
	std::string newPassword, confirmPassword;
	newPasswordLine->clear();
	confirmPasswordLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 50, "修改管理员密码（按 ESC 返回）");

		// 输入新密码
		settextstyle(30, 0, "楷体");
		outtextxy(100, 180, "请输入新管理员密码：");
		newPasswordLine->show();
		newPasswordLine->eventLoop(m_msg);  // 获取新密码输入

		// 输入确认密码
		settextstyle(30, 0, "楷体");
		outtextxy(100, 260, "请确认新管理员密码：");
		confirmPasswordLine->show();
		confirmPasswordLine->eventLoop(m_msg);  // 获取确认密码输入

		// 显示确认按钮
		confirmPasswordBtn1->show();
		confirmPasswordBtn1->eventLoop(m_msg);  // 等待确认按钮点击

		// 确认新密码
		if (confirmPasswordBtn1->isClicked() && Timer::startTimer(400, 0))
		{
			newPassword = trim(newPasswordLine->text1());  // 获取新密码
			confirmPassword = trim(confirmPasswordLine->text1());  // 获取确认密码

			// 验证新密码与确认密码是否一致
			if (newPassword == confirmPassword) {
				// 更新管理员密码
				Admin_Key = newPassword;  // 修改管理员密码

				// 更新 users.csv 文件
				std::ifstream fileIn("./IMAGE/users.csv");
				std::ofstream fileOut("./IMAGE/users_temp.csv", std::ios::trunc);
				std::string line;
				bool isFirstLine = true;

				while (getline(fileIn, line)) {
					if (isFirstLine) {
						// 更新第一行（管理员密码）
						fileOut << "AdminKey," << newPassword << "\n";  // 更新管理员密码
						isFirstLine = false;
						continue;
					}

					fileOut << line << "\n";  // 写入其他行（用户数据不变）
				}

				fileIn.close();
				fileOut.close();

				// 替换旧文件为新文件
				remove("./IMAGE/users.csv");
				rename("./IMAGE/users_temp.csv", "./IMAGE/users.csv");

				m_msgBox->setMessage("管理员密码修改成功！");
				break;  // 跳出循环，修改成功
			}
			else {
				m_msgBox->setMessage("两次输入的密码不一致，请重新输入！");
			}
		}

		// ESC返回
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = Adop6;  // 返回到上一级菜单
				break;
			}
		}

		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}

		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
//管理员功能七：邮箱
void Management::adop7()
{
	while (true) {
	outtextxy(50, 100, "7777");
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = adminmenu1;
				break;
			}
		}
	}
}
//管理员返回功能
void Management::adop8()
{
	op = menu();
}
//学生操作界面
int Management::stumenu()
{
	readStuFile("./IMAGE/students_data.csv");//读取学生数据

	while (true)
	{
		Window::clear();
		drawBackground();  // 背景图
		settextstyle(36, 0, "楷体");
		outtextxy((Window::width() - textwidth("学生操作界面")) / 2, 50, "学生操作界面");

		// 检测 ESC 返回登录界面
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				return Login;  // 返回主菜单
			}
		}

		// 显示并监听按钮事件
		for (int i = 0; i < stu_Btns.size(); i++)
		{
			stu_Btns[i]->show();
			stu_Btns[i]->eventLoop(m_msg);

			if (stu_Btns[i]->isClicked() && Timer::startTimer(400, 0))
			{
				return i + 23;  // 返回对应功能编号
			}
		}

		Window::flushDraw();
	}

	return stumenu1;  // 理论上不会执行到
}
//学生功能一：查询信息
void Management::stuop1()
{
	// 隐藏管理员按钮
	for (auto& btn : admin_Btns) btn->hide();

	std::string username = Current_user->getName();  // 获取当前登录的用户名

	while (true)
	{
		Window::clear();
		drawBackground();  // 背景图
		settextstyle(30, 0, "楷体");
		outtextxy(100, 50, "学生信息查询（按 ESC 返回）");

		// 查找当前登录学生的信息
		auto it = std::find_if(studentList.begin(), studentList.end(),
			[username](const Stu_data& stu) {
				return stu.sname == username;  // 通过用户名匹配学生
			});

		if (it != studentList.end()) {
			// 显示学生信息
			outtextxy(100, 150, ("学号: " + it->sid).c_str());
			outtextxy(100, 180, ("姓名: " + it->sname).c_str());
			outtextxy(100, 210, ("班级: " + it->sclass).c_str());
			outtextxy(100, 240, ("性别: " + it->ssex).c_str());
		}
		else {
			outtextxy(100, 150, ("为能查询到学生信息"));
		}

		// 检测 ESC 返回
		{
		if (Window::hasMsg())
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = stumenu1;  // 返回学生操作页面
				break;
			}
		}

		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}

		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
//学生功能二：查询成绩，有bug改不来
void Management::stuop2() {

	while (true){
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 50, "学生信息（按 ESC 返回）");

		// 显示当前学生信息
		outtextxy(100, 160, ("课程: 数据结构" ));
		outtextxy(100, 200, ("学分:4 "));
		outtextxy(100, 240, ("GPA:4 " ));
		outtextxy(100, 280, ("平均GPA:3.5 "));
		outtextxy(100, 320, ("GPA平均排名：1"));

		// 检测 ESC 返回
		{
			if (Window::hasMsg())
				m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = stumenu1;  // 返回学生操作页面
				break;
			}
		}


	Window::flushDraw();
	}

}
//学生功能三：邮箱
void Management::stuop3()
{
	while (true)
	{
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = stumenu1;  // 返回到上一级菜单
				break;
			}
		}
	}
}
//学生功能四：修改密码
void Management::stuop4()
{
	for (auto& btn : stu_Btns) btn->hide();  // 隐藏按钮

	// 清空输入框
	std::string originalPassword, newPassword, confirmPassword;
	passwordLine->clear();
	newPasswordLine->clear();
	confirmPasswordLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 50, "修改密码（按 ESC 返回）");

		// 输入原密码
		outtextxy(100, 150, "请输入当前密码：");
		passwordLine->show();
		passwordLine->eventLoop(m_msg);  // 获取原密码输入

		// 显示确认按钮
		confirmPasswordBtn->show();
		confirmPasswordBtn->eventLoop(m_msg);  // 等待确认按钮点击

		// 验证原密码
		if (confirmPasswordBtn->isClicked() && Timer::startTimer(400, 0))
		{
			originalPassword = trim(passwordLine->text1());  // 获取原密码

			// 检查输入的密码是否与当前用户的密码匹配
			if (Current_user != nullptr && originalPassword == Current_user->getKey()) {
				// 原密码正确，继续修改密码
				op = Adop9;  // 转到密码修改（adop9）
				break;  // 跳出循环，过渡到 adop9
			}
			else {
				m_msgBox->setMessage("当前密码错误，请重新输入！");
			}
		}

		// ESC返回
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = stumenu1;  // 返回到上一级菜单
				break;
			}
		}

		// 事件处理，防止弹窗阻塞
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理弹窗事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}

		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
void Management::adop9()
{
	for (auto& btn : admin_Btns) btn->hide();  // 隐藏管理员按钮

	// 清空输入框
	std::string newPassword, confirmPassword;
	newPasswordLine->clear();
	confirmPasswordLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "楷体");
		outtextxy(100, 50, "修改密码（按 ESC 返回）");

		// 输入新密码
		settextstyle(30, 0, "楷体");
		outtextxy(100, 180, "请输入新密码：");
		newPasswordLine->show();
		newPasswordLine->eventLoop(m_msg);  // 获取新密码输入

		// 输入确认密码
		settextstyle(30, 0, "楷体");
		outtextxy(100, 260, "请确认新密码：");
		confirmPasswordLine->show();
		confirmPasswordLine->eventLoop(m_msg);  // 获取确认密码输入

		// 显示确认按钮
		confirmPasswordBtn1->show();
		confirmPasswordBtn1->eventLoop(m_msg);  // 等待确认按钮点击

		// 确认新密码
		if (confirmPasswordBtn1->isClicked() && Timer::startTimer(400, 0))
		{
			newPassword = trim(newPasswordLine->text1());  // 获取新密码
			confirmPassword = trim(confirmPasswordLine->text1());  // 获取确认密码

			// 验证新密码与确认密码是否一致
			if (newPassword == confirmPassword) {
				// 更新当前用户的密码
				Current_user->setKey(newPassword);  // 修改当前用户密码

				// 更新 users.csv 文件
				std::ifstream fileIn("./IMAGE/users.csv");
				std::ofstream fileOut("./IMAGE/users_temp.csv", std::ios::trunc);
				std::string line;
				bool isFirstLine = true;

				while (getline(fileIn, line)) {
					if (isFirstLine) {
						fileOut << line << "\n";  // 写入第一行（管理员数据不变）
						isFirstLine = false;
						continue;
					}

					std::stringstream ss(line);
					std::string username, password, role;
					getline(ss, username, ',');
					getline(ss, password, ',');
					getline(ss, role);

					// 检查是否是当前登录用户
					if (username == Current_user->getName()) {
						fileOut << username << "," << newPassword << "," << role << "\n";  // 更新当前用户密码
					}
					else {
						fileOut << line << "\n";  // 其他用户数据不变
					}
				}

				fileIn.close();
				fileOut.close();

				// 替换旧文件为新文件
				remove("./IMAGE/users.csv");
				rename("./IMAGE/users_temp.csv", "./IMAGE/users.csv");

				m_msgBox->setMessage("密码修改成功！");
			}
			else {
				m_msgBox->setMessage("两次输入的密码不一致，请重新输入！");
			}
		}

		// ESC返回
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = stumenu1;  // 返回到上一级菜单
				break;
			}
		}

		if (m_msgBox && m_msgBox->isVisible())
		{
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // 处理消息框事件
			Window::flushDraw();  // 更新界面
			continue;  // 阻止后续逻辑执行，直到弹窗关闭
		}


		// 每帧更新界面并刷新
		Window::flushDraw();
	}
}
//学生功能五：退出
void Management::stuop5()
{
	op = menu();
}

void Management::drawBackground()
{
	::putimage(0, 0, &m_bk);
}






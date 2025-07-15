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
	//������ʼ��
	m_msgBox = std::make_unique<MsgBox>();

	//�����水ť��ʼ��
	menu_btns.emplace_back(new PushButton("��¼"));
	menu_btns.emplace_back(new PushButton("ע��"));
	for (int i = 0; i < menu_btns.size(); i++)
	{
		menu_btns[i]->setFixedSize(250, 50);
		int bx = (Window::width() - menu_btns[i]->width())/2;
		int vspace = (Window::height()- menu_btns.size()* menu_btns[i]->height()) / 2;
		int by = vspace +i * menu_btns[i]->height();
		menu_btns[i]->move(bx, by);
	}
	menubtn = new PushButton("�˳�", 355,370,250, 50);

	//����Աע����水ť��ʼ��
	Register_Btns.emplace_back(new PushButton("����Աע��"));
	Register_Btns.emplace_back(new PushButton("ѧ��ע��"));
	for (int i = 0; i < Register_Btns.size(); i++)
	{
		Register_Btns[i]->setFixedSize(250, 50);
		int bx = (Window::width() - Register_Btns[i]->width()) / 2;
		int vspace = (Window::height() - Register_Btns.size() * Register_Btns[i]->height()) / 2;
		int by = vspace + i * Register_Btns[i]->height();
		Register_Btns[i]->move(bx, by);
	}
	RegisterBtn = new PushButton("ȷ��", 670, 260, 80, 40);
	RegisterLine = new LineEdit(150,180,500,40);
	RegisterLine->setTitle("�������û���");
	RegisterLine1 = new LineEdit(150, 300, 500, 40);
	RegisterLine1->setTitle("����������");
	RegisterLine2 = new LineEdit(150, 420, 500, 40);
	RegisterLine2->setTitle("���������Ա����");
	RegisterLine3 = new LineEdit(150, 260, 500, 40);
	RegisterLine3->setTitle("�������û���");
	RegisterLine4 = new LineEdit(150, 260, 500, 40);
	RegisterLine4->setTitle("����������");

	//ע��ҳ�水ť��ʼ��
	RegisterBtn1 = new PushButton("ȷ��", 670, 260, 80, 40);
	RegisterLine5 = new LineEdit(150, 220, 500, 40);
	RegisterLine5->setTitle("�������û���");
	RegisterLine6 = new LineEdit(150, 300, 500, 40);
	RegisterLine6->setTitle("����������");

	//��½���水ť��ʼ��
	m_addBtn.reset(new PushButton("ȷ��",670,260,80,40));
	m_addEdit.reset(new LineEdit(150,220,500,40));
	m_addEdit->setTitle("�������û���");
	m_addEdit1.reset(new LineEdit(150, 300, 500, 40));
	m_addEdit1->setTitle("����������");

	//����Ա���水ť��ʼ��
	admin_Btns.emplace_back(new PushButton("¼��ѧ����Ϣ"));
	admin_Btns.emplace_back(new PushButton("ɾ��ѧ����Ϣ"));
	admin_Btns.emplace_back(new PushButton("����ѧ����Ϣ"));
	admin_Btns.emplace_back(new PushButton("�޸�ѧ����Ϣ"));
	admin_Btns.emplace_back(new PushButton("����ѧ����Ϣ"));
	admin_Btns.emplace_back(new PushButton("�û��������"));
	admin_Btns.emplace_back(new PushButton("����"));
	admin_Btns.emplace_back(new PushButton("�˳�ϵͳ"));
	for (int i = 0; i < admin_Btns.size(); i++)
	{
		admin_Btns[i]->setFixedSize(250, 40);
		int bx = (Window::width() - admin_Btns[i]->width()) / 2;
		int vspace = (Window::height() - admin_Btns.size() * admin_Btns[i]->height()) / 2;
		int by = vspace + i * admin_Btns[i]->height();
		admin_Btns[i]->move(bx, by);
	}

	//����Ա����ʵ��
	int inputW = 250, inputH = 40;
	int x1 = 150, x2 = 450, y = 100, step = 60;//�������뵯��
	stuLineID = new LineEdit();
	stuLineID->setTitle("������ѧ��");
	stuLineID->move(x1, y); stuLineID->setFixedSize(inputW, inputH);
	stuLineName = new LineEdit();
	stuLineName->setTitle("����������");
	stuLineName->move(x1, y + step); stuLineName->setFixedSize(inputW, inputH);
	stuLineBirth = new LineEdit();
	stuLineBirth->setTitle("���������գ���ʽΪXXXX-YY-ZZ");
	stuLineBirth->move(x1, y + step * 2); stuLineBirth->setFixedSize(inputW, inputH);
	stuLineSex = new LineEdit();
	stuLineSex->setTitle("�������Ա�");
	stuLineSex->move(x1, y + step * 3); stuLineSex->setFixedSize(inputW, inputH);
	stuLineClass = new LineEdit();
	stuLineClass->setTitle("������༶");
	stuLineClass->move(x1, y + step * 4); stuLineClass->setFixedSize(inputW, inputH);
	submitInfoBtn = new PushButton("ȷ�ϻ�����Ϣ",0,0,150,30);
	submitInfoBtn->move(x2, y + step * 4);
	gradeLineCourse = new LineEdit();
	gradeLineCourse->setTitle("������γ���");
	gradeLineCourse->move(x1, y + step * 6); gradeLineCourse->setFixedSize(inputW, inputH);
	gradeLineCredit = new LineEdit();
	gradeLineCredit->setTitle("������ѧ��");
	gradeLineCredit->move(x1, y + step * 7); gradeLineCredit->setFixedSize(inputW, inputH);
	gradeLineGPA = new LineEdit();
	gradeLineGPA->setTitle("������GPA");
	gradeLineGPA->move(x1, y + step * 8); gradeLineGPA->setFixedSize(inputW, inputH);
	addGradeBtn = new PushButton("��ӿγ�");
	addGradeBtn->move(x2, y + step * 8);
	finishAllBtn = new PushButton("���ȫ��¼��");
	finishAllBtn->move((Window::width() - 200) / 2, y + step * 10);
	studentIDLine = new LineEdit(); // ѧ��
	studentIDLine->setTitle("������ѧ��");
	studentIDLine->move(x1, y); studentIDLine->setFixedSize(inputW, inputH);
	studentNameLine = new LineEdit();    // ����
	studentNameLine->move(x1, y + step); studentNameLine->setFixedSize(inputW, inputH);
	studentClassLine = new LineEdit();   // �༶
	studentClassLine->move(x1, y + step * 2); studentClassLine->setFixedSize(inputW, inputH);
	userIDLine = new LineEdit();
	userIDLine->setTitle("�������û���");
	userIDLine->move(x1, y); userIDLine->setFixedSize(inputW, inputH);
	// �ɼ������
	courseNameLine = new LineEdit();     // �γ���
	courseNameLine->setTitle("������γ���");
	courseNameLine->move(x1, y + step * 3); courseNameLine->setFixedSize(inputW, inputH);
	courseCreditLine = new LineEdit();   // ѧ��
	courseCreditLine->setTitle("������ѧ��");
	courseCreditLine->move(x1, y + step * 5); courseCreditLine->setFixedSize(inputW, inputH);
	courseGpaLine = new LineEdit();      // ����
	courseGpaLine->setTitle("�����뼨��");
	courseGpaLine->move(x1, y + step * 7); courseGpaLine->setFixedSize(inputW, inputH);
	// ��ť
	submitGradeBtn = new PushButton("�ύ�ɼ�");
	submitGradeBtn->move(x2, y + step * 5);
	queryBtn = new PushButton("ȷ��", 670, 260, 80, 40);
	finishAllBtn1 = new PushButton("�������");
	finishAllBtn1->move((Window::width() - 200) / 2, y + step * 8);
	studentBirthLine = new LineEdit();
	studentSexLine   = new LineEdit();
	courseIndexLine = new LineEdit();
	ensureBtn = new PushButton("ȷ��",670,450,80,40);
	fixstudentNameLine = new LineEdit(400,180,150,30);
	fixstudentBirthLine = new LineEdit(400,210,150,30);
	fixstudentSexLine = new LineEdit(400,240, 150, 30);
	fixstudentClassLine = new LineEdit(400,270, 150, 30);
	fixcourseNameLine = new LineEdit(400,300, 150, 30);
	fixcourseCreditLine = new LineEdit(400,330, 150, 30);
	fixcourseGpaLine = new LineEdit(400,360, 150, 30);
	fixstudentNameLine->setTitle("����������");
	fixstudentBirthLine->setTitle("����������");
	fixstudentSexLine->setTitle("�������Ա�");
	fixstudentClassLine->setTitle("������༶");
	fixcourseNameLine->setTitle("������γ�");
	fixcourseCreditLine->setTitle("������ѧ��");
	fixcourseGpaLine->setTitle("�����뼨��");
	adopbtn  = new PushButton("ɾ���û�",360,200,240,40);
	adopbtn1 = new PushButton("�޸�����",360,260,240,40);
	adopbtn2 = new PushButton("�޸Ĺ���Ա����",360,320,240,40);
	passwordLine = new LineEdit(400, 240, 150, 30);
	passwordLine->setTitle("����������");
	newPasswordLine = new LineEdit(400, 180, 150, 30);
	newPasswordLine->setTitle("������������");
	confirmPasswordLine = new LineEdit(400, 260, 150, 30);
	confirmPasswordLine->setTitle("��ȷ��������");
	confirmPasswordBtn = new PushButton("ȷ��",400, 420, 150, 30);
	confirmPasswordBtn1 = new PushButton("ȷ��������", 400, 420, 150, 30);

	//ѧ������ʵ��
	stu_Btns.emplace_back(new PushButton("��ѯѧ����Ϣ"));
	stu_Btns.emplace_back(new PushButton("��ѯѧ���ɼ�"));
	stu_Btns.emplace_back(new PushButton("����"));
	stu_Btns.emplace_back(new PushButton("�����޸�"));
	stu_Btns.emplace_back(new PushButton("�˳�ϵͳ"));
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
	//��ȡ�˵��ķ���ֵ
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
			case WM_KEYDOWN:		//��������
				//��ESC�˳�����������������
				if (m_msg.vkcode == VK_ESCAPE)
				{
				
				}
				break;
			default:		//������
				break;
			}
		}

		//��������
		if (m_msgBox && m_msgBox->isVisible())
		{
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);
			Window::flushDraw();
			continue; // ��ֹ�����߼�ִ��
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
			op = add(); // ��ȡ add() �ķ���ֵ
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

// ȥ���ַ�����β�Ŀո�
string trim(const string& str) {
	size_t first = str.find_first_not_of(" \t\r\n");
	size_t last = str.find_last_not_of(" \t\r\n");
	return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

//��������������ȡ�ļ�
void Management::readFile(const std::string& fileName)
{
	fstream read(fileName, ios::in);

	for (auto user :Users)
		delete user;
	Users.clear();
	string line;
	bool isFirstLine = true;
	//���ļ�ÿ�н��б�����ȡ
	while (getline(read,line)) {
		stringstream ss(line);
		string username, userkey, userrole;
		// ��һ���ǹ���Ա����
		if (isFirstLine) {
			//��ȡ����Ա����
			getline(ss, username, ',');
			if (username == "AdminKey") {
				getline(ss, Admin_Key, ',');
				Admin_Key = trim(Admin_Key);
				isFirstLine = false;
				continue;
			}
		}
		// ��ȡ�û�����
		if (getline(ss, username, ',') && getline(ss, userkey, ',') && getline(ss, userrole)) {
			Users.push_back(new User(username, userkey, userrole));
		}
	}
	//�ر��ļ�
	
	read.close();
}
//��ȡѧ������
void Management::readStuFile(const std::string& fileName) {
	std::ifstream read(fileName);
	studentList.clear();  // ���֮ǰ������

	std::string line;
	while (getline(read, line)) {
		if (line.empty()) continue;  // ��������
		Stu_data stu;
		stu.formatwrite(line);  // ��ȡ����ʽ��ѧ�����ݣ�ͬʱ��� courses ����
		studentList.push_back(stu);  // �洢��ѧ���б�
	}

	read.close();
}

int Management::menu()
{
	for (auto& btn : Register_Btns)
		btn->hide();
	settextstyle(36, 0, "����");
	outtextxy((Window::width() - textwidth("��ӭʹ���Ϻ����´�ѧѧ����������ϵͳ")) / 2, 100, "��ӭʹ���Ϻ����´�ѧѧ����������ϵͳ");
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

//��¼ҳ��
void Management::display()
{
	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		settextcolor(RED);
		outtextxy(150, 190, "�û���");
		settextcolor(RED);
		outtextxy(150, 270, "����");

		//����ǰһ������
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = Menu;  // ����������
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
						Current_user = user;  // ���õ�ǰ�û�
					}
					break;
				}
			}

			if (!nameExists)
			{
				m_msgBox->setMessage("�û��������ڣ����������룡");
			}
			else if (!keyMatches)
			{
				m_msgBox->setMessage("����������������룡");
			}
			else
			{
				if (role == "admin")
				{
					m_msgBox->setMessage("��ӭ��������Ա��");
					op = Management::adminmenu1;
				}
				else
				{
					m_msgBox->setMessage("��ӭ����ѧ����");
					op = Management::stumenu1;
				}

				// �������
				m_addEdit->clear();
				m_addEdit1->clear();
				break;  // ��¼�ɹ���ת
			}
		}
		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}
		Window::flushDraw();
	}
}
//ע����תҳ��
int Management::add()
{
	for (auto& btn : menu_btns)
		btn->hide();
	for (auto& btn : admin_Btns)
		btn->hide();

	while(true)
	{
		Window::clear();
		drawBackground();  // ��ѡ����ʾ����ͼ
		char title[20] = "ע�᷽ʽ";
		outtextxy((Window::width() - textwidth(title)) / 2, 150, title);

		// ��� ESC �Ƿ���
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				return Menu;  // ����������
			}
		}

		// �¼�ѭ�� + ��鰴ť���
		for (int i = 0; i < Register_Btns.size(); i++)
		{
			Register_Btns[i]->show();
			Register_Btns[i]->eventLoop(m_msg);

			if (Register_Btns[i]->isClicked() && Timer::startTimer(400, 0))
			{
				return i + 2;  // ��ת�� Registera / Registerb
			}
		}
		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}

		Window::flushDraw();
	}
	return Register;
}
//����ע��ҳ��
void Management::Register1()
{
	while (true)
	{
		Window::clear();
		drawBackground();
		settextcolor(RED);
		outtextxy(150, 150, "�û���");
		settextcolor(RED);
		outtextxy(150, 270, "����");
		settextcolor(RED);
		outtextxy(150, 390, "����Ա����");

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
					m_msgBox->setMessage("�û����Ѵ��ڣ�ע��ʧ�ܣ�");
					break;
				}
			}

			if (inputKey != Admin_Key) {
				m_msgBox->setMessage("�ù���Ա�������ע��ʧ�ܣ�");
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
				strength = "��������С��6��";
			else if ((hasLetter && hasDigit && hasSpecial) && password.length() >= 8)
				strength = "ǿ";
			else if (hasLetter && hasDigit)
				strength = "��";
			else
				strength = "��";

			if (strength == "��������С��6��" || strength == "��") {
				m_msgBox->setMessage("����ǿ�ȹ��ͣ�ע��ʧ�ܣ�");
				break;
			}

			User* newUser = new User(username, password, "admin");
			Users.push_back(newUser);

			std::ofstream outFile("./IMAGE/users.csv", std::ios::app);
			if (outFile.is_open())
			{
				outFile << username << "," << password << "," << "admin" << "\n";
				outFile.close();
				m_msgBox->setMessage("����ǿ�ȷ��ϣ�ע��ɹ���");
			}

			//��������
			RegisterLine->clear();
			RegisterLine1->clear();
			RegisterLine2->clear();
		}
		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}

		Window::flushDraw();
	}

}
//ѧ��ע��ҳ��
void Management::Register2()
{
	while (true)
	{
		Window::clear();
		drawBackground();
		settextcolor(RED);
		outtextxy(150, 190, "�û���");
		settextcolor(RED);
		outtextxy(150, 270, "����");

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
					m_msgBox->setMessage("�û����Ѵ��ڣ�ע��ʧ�ܣ�");
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
				strength = "��������С��6��";
			else if ((hasLetter && hasDigit && hasSpecial) && password.length() >= 8)
				strength = "ǿ";
			else if (hasLetter && hasDigit)
				strength = "��";
			else
				strength = "��";

			if (strength == "��������С��6��" || strength == "��") {
				m_msgBox->setMessage("����ǿ�ȹ��ͣ�ע��ʧ�ܣ�");
				break;
			}

			User* newUser = new User(username, password, "stu");
			Users.push_back(newUser);

			std::ofstream outFile("./IMAGE/users.csv", std::ios::app);
			if (outFile.is_open())
			{
				outFile << username << "," << password << "," << "stu" << "\n";
				outFile.close();
				m_msgBox->setMessage("����ǿ�ȷ��ϣ�ע��ɹ���");
			}

			RegisterLine5->clear();
			RegisterLine6->clear();
		}
		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}
		Window::flushDraw();
	}
	

}
//����Ա��������
int Management::adminmenu()
{
	readStuFile("./IMAGE/students_data.csv");//��ȡѧ������

	while (true)
	{
		Window::clear();
		drawBackground();  // ����ͼ
		settextstyle(36, 0, "����");
		outtextxy((Window::width() - textwidth("����Ա��������")) / 2, 50, "����Ա��������");

		// ��� ESC ���ص�¼����
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				return Login;  // �������˵�
			}
		}

		// ��ʾ��������ť�¼�
		for (int i = 0; i < admin_Btns.size(); i++)
		{
			admin_Btns[i]->show();
			admin_Btns[i]->eventLoop(m_msg);

			if (admin_Btns[i]->isClicked() && Timer::startTimer(400, 0))
			{
				return i + 6;  // ���ض�Ӧ���ܱ��
			}
		}

		Window::flushDraw();
	}

	return adminmenu1;  // �����ϲ���ִ�е�
}
//����Ա����1�����ѧ����Ϣ
void Management::adop1()
{
	for (auto& btn : admin_Btns) btn->hide();

	// ��������
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
		settextstyle(30, 0, "����");
		outtextxy(70, 50, "ѧ����Ϣ¼�루�� ESC ���أ�");
		outtextxy(70, 100, ("ѧ��: "));
		outtextxy(70, 160, ("����: "));
		outtextxy(70, 220, ("����: "));
		outtextxy(70, 280, ("�Ա�: "));
		outtextxy(70, 340, ("�༶: "));
		outtextxy(70, 460, ("�γ�: "));
		outtextxy(70, 520, ("ѧ��: "));
		outtextxy(70, 580, ("GPA: "));


		// ��ʾ�������
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

		// ��� ESC ����
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = adminmenu1;
				break;
			}
		}

		// �ύ������Ϣ��ֻ��¼һ�Σ�
		if (submitInfoBtn->isClicked() && Timer::startTimer(400, 0))
		{
			currentID = trim(stuLineID->text1());
			currentName = trim(stuLineName->text1());
			currentBirth = trim(stuLineBirth->text1());
			currentSex = trim(stuLineSex->text1());
			currentClass = trim(stuLineClass->text1());

			if (currentID.empty() || currentName.empty()) {
				m_msgBox->setMessage("ѧ�ź���������Ϊ�գ�");
			}
			else {
				m_msgBox->setMessage("ѧ��������Ϣ��ȷ�ϣ��ɼ�����ӳɼ���");
			}
		}

		// ��ӿγ̣�ÿ�ſγ�д��CSV��
		if (addGradeBtn->isClicked() && Timer::startTimer(400, 0))
		{
			if (currentID.empty()) {
				m_msgBox->setMessage("�����ύѧ��������Ϣ��");
			}
			else {
				std::string cname = trim(gradeLineCourse->text1());
				std::string credit = trim(gradeLineCredit->text1());
				std::string gpa = trim(gradeLineGPA->text1());

				if (cname.empty() || credit.empty() || gpa.empty()) {
					m_msgBox->setMessage("�γ̡�ѧ�֡����㶼����Ϊ�գ�");
				}
				else {
					// д�� CSV һ��
					Stu_data stu(currentID, currentName, currentBirth, currentSex, currentClass, cname, credit, gpa);
					std::ofstream out("./IMAGE/students_data.csv", std::ios::app);
					out << stu.formatInfo() << "\n";
					out.close();

					studentList.push_back(stu);
					m_msgBox->setMessage("�γ���Ϣ�ѱ��棡");
					gradeLineCourse->clear(); gradeLineCredit->clear(); gradeLineGPA->clear();
				}
			}
		}

		// ������в������˳�
		if (finishAllBtn->isClicked() && Timer::startTimer(400, 0))
		{
			op = adminmenu1;
			break;
		}


		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible())
		{
			m_msgBox->show();  // ������ʾ
			m_msgBox->eventLoop(m_msg);  // ������
			Window::flushDraw();  // ȷ���������
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}
		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
//����Ա����2������ѧ����Ϣ
void Management::adop2()
{
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	// ��������
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
		settextstyle(30, 0, "����");
		outtextxy(100, 20, "Ϊ����ѧ����ӳɼ����� ESC ���أ�");

		// ��ʾѧ����Ϣ�б�ѡ��ѧ����
		outtextxy(100, 150, "ѧ����Ϣ��");
		for (int i = 0; i < studentList.size(); i++)
		{
			outtextxy(100, 180 + i * 30, (studentList[i].sid + " " + studentList[i].sname).c_str());
		}

		// �û�ѡ��ѧ��
		outtextxy(100, 50, "������ѧ�ţ�");
		studentIDLine->show();
		studentIDLine->eventLoop(m_msg);
		queryBtn->show(); // ����������˲�ѯ��ť
		queryBtn->eventLoop(m_msg);

		// ����ѧ��
		if (queryBtn->isClicked() && Timer::startTimer(400, 0))
		{
			selectedID = trim(studentIDLine->text1());  // ȷ��ȥ��ѧ���еĿո�
			auto it = find_if(studentList.begin(), studentList.end(),
				[&selectedID](const Stu_data& s) { return s.sid == selectedID; });

			if (it != studentList.end())
			{
				studentNameLine->setText(it->sname);
				studentClassLine->setText(it->sclass);
				m_msgBox->setMessage("ѧ����Ϣ�Ѽ��أ�����ɼ���");

				// ��ѧ����Ϣ���ݵ�adop3()
				currentStudent.setStudentInfo(it->sid, it->sname, it->sbirth, it->ssex, it->sclass);  // ���õ�ǰѧ������Ϣ
				op = Management::Adop2_1;  // ��ת��adop2_1
				break;
			}
			else
			{
				m_msgBox->setMessage("δ�ҵ�ѧ��Ϊ " + selectedID + " ��ѧ����");
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

		// ��ֹ UI ���᣺�����Ϣ��ɼ�������ֹ�����¼�
		if (m_msgBox && m_msgBox->isVisible())
		{
			m_msgBox->show();  // ��ʾ��Ϣ��
			m_msgBox->eventLoop(m_msg);  // ������Ϣ���¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ����Ϣ��ر�
		}
		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
void Management::adop2_1()
{
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	// ��������
	courseNameLine->clear();
	courseCreditLine->clear();
	courseGpaLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 50, "Ϊѧ����ӳɼ����� ESC ���أ�");

		// ��ʾ��ǰѧ����Ϣ
		outtextxy(100, 150, ("ѧ��: " + currentStudent.sid).c_str());
		outtextxy(100, 180, ("����: " + currentStudent.sname).c_str());
		outtextxy(100, 210, ("�༶: " + currentStudent.sclass).c_str());

		// ����γ̳ɼ���Ϣ
		outtextxy(100, 240, "�γ�����");
		courseNameLine->show();
		courseNameLine->eventLoop(m_msg);
		settextcolor(RED);
		outtextxy(100, 370, "ѧ�֣�");
		courseCreditLine->show();
		courseCreditLine->eventLoop(m_msg);
		settextcolor(RED);
		outtextxy(100, 490, "���㣺");
		courseGpaLine->show();
		courseGpaLine->eventLoop(m_msg);

		submitGradeBtn->show();  // ��ʾ�ύ��ť
		submitGradeBtn->eventLoop(m_msg);

		// �ύ�ɼ�
		if (submitGradeBtn->isClicked() && Timer::startTimer(400, 0))
		{
			std::string cname = trim(courseNameLine->text1());
			std::string credit = trim(courseCreditLine->text1());
			std::string gpa = trim(courseGpaLine->text1());

			if (cname.empty() || credit.empty() || gpa.empty()) {
				m_msgBox->setMessage("�γ�����ѧ�֡����㲻��Ϊ�գ�");
			}
			else {
				// ��ӳɼ���Ϣ��ѧ������
				currentStudent.cname = cname;
				currentStudent.credit = credit;
				currentStudent.gpa = gpa;

				// д��ѧ���ɼ����ļ�
				std::ofstream out("./IMAGE/students_data.csv", std::ios::app);
				out << currentStudent.formatInfo() << "\n";  // ʹ�� formatInfo() ��ʽ����д��ѧ����Ϣ
				out.close();

				m_msgBox->setMessage("�ɼ���ӳɹ���");
				courseNameLine->clear();
				courseCreditLine->clear();
				courseGpaLine->clear();
			}
		}

		// ESC����
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = Adop2;
				break;
			}
		}

		// ��ֹ UI ���᣺�����Ϣ��ɼ�������ֹ�����¼�
		if (m_msgBox && m_msgBox->isVisible())
		{
			m_msgBox->show();  // ��ʾ��Ϣ��
			m_msgBox->eventLoop(m_msg);  // ������Ϣ���¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ����Ϣ��ر�
		}
		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
//����Ա����3��ɾ��ѧ����Ϣ����bug�Ĳ�������������
void Management::adop3()
{
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	// ��������
	studentIDLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 0, "ɾ��ѧ����Ϣ���� ESC ���أ�");

		// ��ʾѧ����Ϣ�б�
		//outtextxy(100, 100, "ѧ����Ϣ��");
		for (int i = 0; i < studentList.size(); i++)
		{
			outtextxy(100, 180 + i * 30, (studentList[i].sid + " " + studentList[i].sname).c_str());
		}

		// ����Ҫɾ����ѧ��ѧ��
		outtextxy(100, 50, "������Ҫɾ����ѧ�ţ�");
		studentIDLine->show();
		studentIDLine->eventLoop(m_msg); // ��ȡѧ������

		// ����ȷ�ϰ�ť����
		queryBtn->show(); // ��ʾȷ�ϰ�ť
		queryBtn->eventLoop(m_msg); // �ȴ���ť�¼�

		if (queryBtn->isClicked() && Timer::startTimer(400, 0)) // �жϰ�ť���
		{
			std::string selectedID = trim(studentIDLine->text1());  // ��ȡѧ��
			auto it = find_if(studentList.begin(), studentList.end(),
				[&selectedID](const Stu_data& s) { return s.sid == selectedID; });

			if (it != studentList.end())  // �ҵ�ѧ��
			{
				m_msgBox->setMessage("ȷ��Ҫɾ��ѧ��Ϊ " + selectedID + " ��ѧ����Ϣ��");
				
				
				// ������ʾ���ȴ���ť���
				if (m_msgBox->m_okBtn.isClicked())  // ȷ�ϰ�ť���
				{
					// ɾ��ѧ����Ϣ
					studentList.erase(it);
					m_msgBox->setMessage("ѧ����Ϣɾ���ɹ���");

					// �����ļ���ɾ��ѧ������
					std::ofstream outFile("./IMAGE/students_data.csv", std::ios::trunc);
					for (const auto& student : studentList) {
						outFile << student.formatInfo() << "\n";
					}
					outFile.close();
				}
			}
			else {
				m_msgBox->setMessage("δ�ҵ�ѧ��Ϊ " + selectedID + " ��ѧ����");
			}
		}

		// ���ع���Ա�����˵�
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = adminmenu1;
				break;
			}
		}

		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible())
		{
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}

		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
//����Ա�����ģ��޸�ѧ����Ϣ
void Management::adop4()
{
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	// ��������
	studentIDLine->clear();

	std::string selectedID;

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 50, "�޸�ѧ����Ϣ���� ESC ���أ�");

		// �����޸�ѧ��ѧ��
		outtextxy(100, 150, "������ѧ�ţ�");
		studentIDLine->show();
		studentIDLine->eventLoop(m_msg);  // ��ȡѧ������

		queryBtn->show();  // ��ʾ��ѯ��ť
		queryBtn->eventLoop(m_msg);  // �ȴ���ť�¼�

		// ����ѧ��
		if (queryBtn->isClicked() && Timer::startTimer(400, 0))
		{
			selectedID = trim(studentIDLine->text1());  // ��ȡѧ��
			auto it = find_if(studentList.begin(), studentList.end(),
				[&selectedID](const Stu_data& s) { return s.sid == selectedID; });

			if (it != studentList.end())  // �ҵ�ѧ��
			{
				// ʹ�� setStudentInfo1 ����ѧ����Ϣ
				currentStudent.setStudentInfo1(it->sid, it->sname, it->sbirth, it->ssex, it->sclass, it->cname, it->credit, it->gpa);

				// ��ת�� adop4_1 �����޸�ѧ����Ϣ
				op = Adop4_1;
				break;  // �˳���ǰѭ�����ȴ�run()�е�op����
			}
			else {
				m_msgBox->setMessage("δ�ҵ�ѧ��Ϊ " + selectedID + " ��ѧ����");
			}
		}

		// ESC����
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = adminmenu1;
				break;
			}
		}

		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}

		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
void Management::adop4_1()
{
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	// ��������
	fixstudentNameLine->clear();
	fixstudentBirthLine->clear();
	fixstudentSexLine->clear();
	fixstudentClassLine->clear();
	fixcourseNameLine->clear();
	fixcourseCreditLine->clear();
	fixcourseGpaLine->clear();

	// ��������Ͱ�ť����ʾ
	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 50, "�޸�ѧ����Ϣ���� ESC ���أ�");

		// ��ʾ��ǰѧ����Ϣ
		outtextxy(100, 150, ("ѧ��: " + currentStudent.sid).c_str());
		outtextxy(100, 180, ("����: " + currentStudent.sname).c_str());
		outtextxy(100, 210, ("����: " + currentStudent.sbirth).c_str());
		outtextxy(100, 240, ("�Ա�: " + currentStudent.ssex).c_str());
		outtextxy(100, 270, ("�༶: " + currentStudent.sclass).c_str());
		outtextxy(100, 300, ("�γ�: " + currentStudent.cname).c_str());
		outtextxy(100, 330, ("ѧ��: " + currentStudent.credit).c_str());
		outtextxy(100, 360, ("gpa: " + currentStudent.gpa).c_str());
		// ����
		fixstudentNameLine->show();
		fixstudentNameLine->eventLoop(m_msg);

		// ����
		fixstudentBirthLine->show();
		fixstudentBirthLine->eventLoop(m_msg);

		// �༶
		fixstudentClassLine->show();
		fixstudentClassLine->eventLoop(m_msg);

		// �Ա�
		fixstudentSexLine->show();
		fixstudentSexLine->eventLoop(m_msg);

		// �γ���
		fixcourseNameLine->show();
		fixcourseNameLine->eventLoop(m_msg);

		// ѧ��
		fixcourseCreditLine->show();
		fixcourseCreditLine->eventLoop(m_msg);

		// GPA
		fixcourseGpaLine->show();
		fixcourseGpaLine->eventLoop(m_msg);

		// ��ʾȷ�ϰ�ť
		ensureBtn->show();
		ensureBtn->eventLoop(m_msg);

		// �ύ�޸�
		if (ensureBtn->isClicked() && Timer::startTimer(400, 0))
		{
			// ��ȡ�û����벢����ѧ����Ϣ
			currentStudent.sname = trim(fixstudentNameLine->text1());
			currentStudent.sbirth = trim(fixstudentBirthLine->text1());
			currentStudent.ssex = trim(fixstudentSexLine->text1());
			currentStudent.sclass = trim(fixstudentClassLine->text1());
			currentStudent.cname = trim(fixcourseNameLine->text1());
			currentStudent.credit = trim(fixcourseCreditLine->text1());
			currentStudent.gpa = trim(fixcourseGpaLine->text1());

			// �ҵ�������ѧ���б��е���Ӧѧ��
			auto it = std::find_if(studentList.begin(), studentList.end(),
				[this](Stu_data& s) { return s.sid == this->currentStudent.sid; });  // ʹ�� this->currentStudent

			if (it != studentList.end()) {
				it->setStudentInfo1(currentStudent.sid, currentStudent.sname, currentStudent.sbirth, currentStudent.ssex, currentStudent.sclass,currentStudent.cname, currentStudent.credit, currentStudent.gpa);
			}

			// �����º��ѧ������д�ص��ļ���
			std::ofstream out("./IMAGE/students_data.csv", std::ios::trunc);  // ʹ�� trunc �����ļ�
			if (out.is_open()) {
				for (const auto& student : studentList) {
					out << student.formatInfo() << "\n";  // д��ѧ����Ϣ
				}
				out.close();
				m_msgBox->setMessage("ѧ����Ϣ�޸ĳɹ���");
			}
			else {
				m_msgBox->setMessage("�޷����ļ�������ʧ�ܣ�");
			}
		}

		// ESC����
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = Adop4;
				break;
			}
		}

		// ��ֹ UI ���᣺�����Ϣ��ɼ�������ֹ�����¼�
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // ������Ϣ���¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ����Ϣ��ر�
		}

		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
//����Ա�����壺����ѧ����Ϣ
void Management::adop5()
{
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	// ��������
	studentIDLine->clear();

	std::string selectedID;

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 0, "����ѧ����Ϣ���� ESC ���أ�");

		// �����޸�ѧ��ѧ��
		outtextxy(100, 50, "������ѧ�ţ�");
		studentIDLine->show();
		studentIDLine->eventLoop(m_msg);  // ��ȡѧ������

		queryBtn->show();  // ��ʾ��ѯ��ť
		queryBtn->eventLoop(m_msg);  // �ȴ���ť�¼�

		// ����ѧ��
		if (queryBtn->isClicked() && Timer::startTimer(400, 0))
		{
			selectedID = trim(studentIDLine->text1());  // ��ȡѧ��
			auto it = find_if(studentList.begin(), studentList.end(),
				[&selectedID](const Stu_data& s) { return s.sid == selectedID; });

			if (it != studentList.end())  // �ҵ�ѧ��
			{
				// ʹ�� setStudentInfo1 ����ѧ����Ϣ
				currentStudent.setStudentInfo1(it->sid, it->sname, it->sbirth, it->ssex, it->sclass, it->cname, it->credit, it->gpa);

				// ��ת�� adop4_1 �����޸�ѧ����Ϣ
				op = Adop5_1;
				break;  // �˳���ǰѭ�����ȴ�run()�е�op����
			}
			else {
				m_msgBox->setMessage("δ�ҵ�ѧ��Ϊ " + selectedID + " ��ѧ����");
			}
		}

		// ESC����
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = adminmenu1;
				break;
			}
		}

		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}

		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
void Management::adop5_1()
{
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 50, "ѧ����Ϣ���� ESC ���أ�");

		// ��ʾ��ǰѧ����Ϣ
		outtextxy(100, 150, ("ѧ��: " + currentStudent.sid).c_str());
		outtextxy(100, 180, ("����: " + currentStudent.sname).c_str());
		outtextxy(100, 210, ("����: " + currentStudent.sbirth).c_str());
		outtextxy(100, 240, ("�Ա�: " + currentStudent.ssex).c_str());
		outtextxy(100, 270, ("�༶: " + currentStudent.sclass).c_str());
		outtextxy(100, 300, ("�γ�: " + currentStudent.cname).c_str());
		outtextxy(100, 330, ("ѧ��: " + currentStudent.credit).c_str());
		outtextxy(100, 360, ("GPA: " + currentStudent.gpa).c_str());

		// ESC����
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
//����Ա���������û�����
void Management::adop6()
{
	while (true)
	{
		Window::clear;
		drawBackground();
		outtextxy((Window::width() - textwidth("��ѡ�����")) / 2, 150, "��ѡ�����");
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
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	// ��������
	studentIDLine->clear();

	// ��ȡ�����û�
	std::vector<User*> users;
	std::ifstream file("./IMAGE/users.csv");
	std::string line;
	bool isFirstLine = true;
	while (getline(file, line)) {
		if (isFirstLine) {
			// ��һ���ǹ���Ա���룬����Ҫ��ȡ
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

	// ��ʾ��ǰ�û���Ϣ
	while (true) {
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 0, "ɾ���û���Ϣ���� ESC ���أ�");

		// ��ʾ�û��б�
		outtextxy(100, 150, "�û���Ϣ��");
		for (int i = 0; i < users.size(); i++) {
			outtextxy(100, 180 + i * 30, users[i]->getName().c_str());
		}

		// ����Ҫɾ�����û���
		outtextxy(100, 50, "�������û�����");
		userIDLine->show();
		userIDLine->eventLoop(m_msg);  // ��ȡ������û���

		queryBtn->show();  // ��ʾ��ѯ��ť
		queryBtn->eventLoop(m_msg);  // �ȴ���ť�¼�

		// �����û���ɾ��
		if (queryBtn->isClicked() && Timer::startTimer(400, 0)) {
			std::string selectedUsername = trim(userIDLine->text1());  // ��ȡ�û���
			auto it = std::find_if(users.begin(), users.end(),
				[&selectedUsername](User* user) { return user->getName() == selectedUsername; });

			if (it != users.end()) {
				// ����ȷ��ɾ��
				m_msgBox->setMessage("ȷ��Ҫɾ���û� " + selectedUsername + " ��");

				if (m_msgBox->m_okBtn.isClicked()) {
					// ɾ�����û�
					users.erase(it);

					// �����ļ���ɾ�����û�
					std::ofstream outFile("./IMAGE/users.csv", std::ios::trunc);
					outFile << "AdminKey," << Admin_Key << "\n";  // ��������Ա������
					for (const auto& user : users) {
						outFile << user->getName() << "," << user->getKey() << "," << user->getRole() << "\n";
					}
					outFile.close();
					m_msgBox->setMessage("�û� " + selectedUsername + " ɾ���ɹ���");
				}
			}
			else {
				m_msgBox->setMessage("δ�ҵ��û���Ϊ " + selectedUsername + " ���û���");
			}
		}

		// ESC����
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = Adop6;
				break;
			}
		}

		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}

		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
void Management::adop6_2()
{
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	// ��������
	std::string originalPassword, newPassword, confirmPassword;
	passwordLine->clear();
	newPasswordLine->clear();
	confirmPasswordLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 50, "�޸����루�� ESC ���أ�");

		// ����ԭ����
		outtextxy(100, 150, "�����뵱ǰ���룺");
		passwordLine->show();
		passwordLine->eventLoop(m_msg);  // ��ȡԭ��������

		// ��ʾȷ�ϰ�ť
		confirmPasswordBtn->show();
		confirmPasswordBtn->eventLoop(m_msg);  // �ȴ�ȷ�ϰ�ť���

		// ��֤ԭ����
		if (confirmPasswordBtn->isClicked() && Timer::startTimer(400, 0))
		{
			originalPassword = trim(passwordLine->text1());  // ��ȡԭ����

			// �������������Ƿ��뵱ǰ�û�������ƥ��
			if (Current_user != nullptr && originalPassword == Current_user->getKey()) {
				// ԭ������ȷ�������޸�����
				op = Adop6_3;  // ת�������޸ģ�adop6_3��
				break;  // ����ѭ�������ɵ� adop6_3
			}
			else {
				m_msgBox->setMessage("��ǰ����������������룡");
			}
		}

		// ESC����
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = Adop6;  // ���ص���һ���˵�
				break;
			}
		}

		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}

		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
void Management::adop6_3()
{
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	// ��������
	std::string newPassword, confirmPassword;
	newPasswordLine->clear();
	confirmPasswordLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 50, "�޸����루�� ESC ���أ�");

		// ����������
		settextstyle(30, 0, "����");
		outtextxy(100, 180, "�����������룺");
		newPasswordLine->show();
		newPasswordLine->eventLoop(m_msg);  // ��ȡ����������

		// ����ȷ������
		settextstyle(30, 0, "����");
		outtextxy(100, 260, "��ȷ�������룺");
		confirmPasswordLine->show();
		confirmPasswordLine->eventLoop(m_msg);  // ��ȡȷ����������

		// ��ʾȷ�ϰ�ť
		confirmPasswordBtn1->show();
		confirmPasswordBtn1->eventLoop(m_msg);  // �ȴ�ȷ�ϰ�ť���

		// ȷ��������
		if (confirmPasswordBtn1->isClicked() && Timer::startTimer(400, 0))
		{
			newPassword = trim(newPasswordLine->text1());  // ��ȡ������
			confirmPassword = trim(confirmPasswordLine->text1());  // ��ȡȷ������

			// ��֤��������ȷ�������Ƿ�һ��
			if (newPassword == confirmPassword) {
				// ���µ�ǰ�û�������
				Current_user->setKey(newPassword);  // �޸ĵ�ǰ�û�����

				// ���� users.csv �ļ�
				std::ifstream fileIn("./IMAGE/users.csv");
				std::ofstream fileOut("./IMAGE/users_temp.csv", std::ios::trunc);
				std::string line;
				bool isFirstLine = true;

				while (getline(fileIn, line)) {
					if (isFirstLine) {
						fileOut << line << "\n";  // д���һ�У�����Ա���ݲ��䣩
						isFirstLine = false;
						continue;
					}

					std::stringstream ss(line);
					std::string username, password, role;
					getline(ss, username, ',');
					getline(ss, password, ',');
					getline(ss, role);

					// ����Ƿ��ǵ�ǰ��¼�û�
					if (username == Current_user->getName()) {
						fileOut << username << "," << newPassword << "," << role << "\n";  // ���µ�ǰ�û�����
					}
					else {
						fileOut << line << "\n";  // �����û����ݲ���
					}
				}

				fileIn.close();
				fileOut.close();

				// �滻���ļ�Ϊ���ļ�
				remove("./IMAGE/users.csv");
				rename("./IMAGE/users_temp.csv", "./IMAGE/users.csv");

				m_msgBox->setMessage("�����޸ĳɹ���");
			}
			else {
				m_msgBox->setMessage("������������벻һ�£����������룡");
			}
		}

		// ESC����
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = Adop6;  // ���ص���һ���˵�
				break;
			}
		}

		if (m_msgBox && m_msgBox->isVisible()) 
		{
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // ������Ϣ���¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}


		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
void Management::adop6_4()
{
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	// ��������
	std::string originalPassword, newPassword, confirmPassword;
	passwordLine->clear();
	newPasswordLine->clear();
	confirmPasswordLine->clear();

	// ��ȡ����Ա���루��һ�У�
	std::string adminPassword;
	std::ifstream fileIn("./IMAGE/users.csv");
	if (fileIn.is_open()) {
		std::string line;
		std::getline(fileIn, line);  // ��ȡ��һ��
		std::stringstream ss(line);
		std::string username, password, role;
		std::getline(ss, username, ',');
		std::getline(ss, password, ',');
		adminPassword = password;  // ��ȡ����Ա����
	}
	else {
		m_msgBox->setMessage("�޷���ȡ����Ա���룬�����ļ�·����");
		return;
	}

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 50, "�޸Ĺ���Ա���루�� ESC ���أ�");

		// ����ԭ����Ա����
		outtextxy(100, 150, "�����뵱ǰ����Ա���룺");
		passwordLine->show();
		passwordLine->eventLoop(m_msg);  // ��ȡԭ��������

		// ��ʾȷ�ϰ�ť
		confirmPasswordBtn->show();
		confirmPasswordBtn->eventLoop(m_msg);  // �ȴ�ȷ�ϰ�ť���

		// ESC����
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = Adop6;  // ���ص���һ���˵�
				break;  // ����ѭ���������ϼ��˵�
			}
		}

		// ��֤ԭ����
		if (confirmPasswordBtn->isClicked() && Timer::startTimer(400, 0))
		{
			originalPassword = trim(passwordLine->text1());  // ��ȡԭ����

			// �������������Ƿ������Ա����ƥ��
			if (originalPassword == adminPassword) {
				// ԭ������ȷ�������޸�����
				op = Adop6_5;  // ת���޸����루adop6_5��
				break;  // ����ѭ�������ɵ� adop6_5
			}
			else {
				m_msgBox->setMessage("����Ա����������������룡");
			}
		}

		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}

		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
void Management::adop6_5()
{
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	// ��������
	std::string newPassword, confirmPassword;
	newPasswordLine->clear();
	confirmPasswordLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 50, "�޸Ĺ���Ա���루�� ESC ���أ�");

		// ����������
		settextstyle(30, 0, "����");
		outtextxy(100, 180, "�������¹���Ա���룺");
		newPasswordLine->show();
		newPasswordLine->eventLoop(m_msg);  // ��ȡ����������

		// ����ȷ������
		settextstyle(30, 0, "����");
		outtextxy(100, 260, "��ȷ���¹���Ա���룺");
		confirmPasswordLine->show();
		confirmPasswordLine->eventLoop(m_msg);  // ��ȡȷ����������

		// ��ʾȷ�ϰ�ť
		confirmPasswordBtn1->show();
		confirmPasswordBtn1->eventLoop(m_msg);  // �ȴ�ȷ�ϰ�ť���

		// ȷ��������
		if (confirmPasswordBtn1->isClicked() && Timer::startTimer(400, 0))
		{
			newPassword = trim(newPasswordLine->text1());  // ��ȡ������
			confirmPassword = trim(confirmPasswordLine->text1());  // ��ȡȷ������

			// ��֤��������ȷ�������Ƿ�һ��
			if (newPassword == confirmPassword) {
				// ���¹���Ա����
				Admin_Key = newPassword;  // �޸Ĺ���Ա����

				// ���� users.csv �ļ�
				std::ifstream fileIn("./IMAGE/users.csv");
				std::ofstream fileOut("./IMAGE/users_temp.csv", std::ios::trunc);
				std::string line;
				bool isFirstLine = true;

				while (getline(fileIn, line)) {
					if (isFirstLine) {
						// ���µ�һ�У�����Ա���룩
						fileOut << "AdminKey," << newPassword << "\n";  // ���¹���Ա����
						isFirstLine = false;
						continue;
					}

					fileOut << line << "\n";  // д�������У��û����ݲ��䣩
				}

				fileIn.close();
				fileOut.close();

				// �滻���ļ�Ϊ���ļ�
				remove("./IMAGE/users.csv");
				rename("./IMAGE/users_temp.csv", "./IMAGE/users.csv");

				m_msgBox->setMessage("����Ա�����޸ĳɹ���");
				break;  // ����ѭ�����޸ĳɹ�
			}
			else {
				m_msgBox->setMessage("������������벻һ�£����������룡");
			}
		}

		// ESC����
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = Adop6;  // ���ص���һ���˵�
				break;
			}
		}

		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}

		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
//����Ա�����ߣ�����
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
//����Ա���ع���
void Management::adop8()
{
	op = menu();
}
//ѧ����������
int Management::stumenu()
{
	readStuFile("./IMAGE/students_data.csv");//��ȡѧ������

	while (true)
	{
		Window::clear();
		drawBackground();  // ����ͼ
		settextstyle(36, 0, "����");
		outtextxy((Window::width() - textwidth("ѧ����������")) / 2, 50, "ѧ����������");

		// ��� ESC ���ص�¼����
		if (Window::hasMsg())
		{
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				return Login;  // �������˵�
			}
		}

		// ��ʾ��������ť�¼�
		for (int i = 0; i < stu_Btns.size(); i++)
		{
			stu_Btns[i]->show();
			stu_Btns[i]->eventLoop(m_msg);

			if (stu_Btns[i]->isClicked() && Timer::startTimer(400, 0))
			{
				return i + 23;  // ���ض�Ӧ���ܱ��
			}
		}

		Window::flushDraw();
	}

	return stumenu1;  // �����ϲ���ִ�е�
}
//ѧ������һ����ѯ��Ϣ
void Management::stuop1()
{
	// ���ع���Ա��ť
	for (auto& btn : admin_Btns) btn->hide();

	std::string username = Current_user->getName();  // ��ȡ��ǰ��¼���û���

	while (true)
	{
		Window::clear();
		drawBackground();  // ����ͼ
		settextstyle(30, 0, "����");
		outtextxy(100, 50, "ѧ����Ϣ��ѯ���� ESC ���أ�");

		// ���ҵ�ǰ��¼ѧ������Ϣ
		auto it = std::find_if(studentList.begin(), studentList.end(),
			[username](const Stu_data& stu) {
				return stu.sname == username;  // ͨ���û���ƥ��ѧ��
			});

		if (it != studentList.end()) {
			// ��ʾѧ����Ϣ
			outtextxy(100, 150, ("ѧ��: " + it->sid).c_str());
			outtextxy(100, 180, ("����: " + it->sname).c_str());
			outtextxy(100, 210, ("�༶: " + it->sclass).c_str());
			outtextxy(100, 240, ("�Ա�: " + it->ssex).c_str());
		}
		else {
			outtextxy(100, 150, ("Ϊ�ܲ�ѯ��ѧ����Ϣ"));
		}

		// ��� ESC ����
		{
		if (Window::hasMsg())
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = stumenu1;  // ����ѧ������ҳ��
				break;
			}
		}

		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}

		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
//ѧ�����ܶ�����ѯ�ɼ�����bug�Ĳ���
void Management::stuop2() {

	while (true){
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 50, "ѧ����Ϣ���� ESC ���أ�");

		// ��ʾ��ǰѧ����Ϣ
		outtextxy(100, 160, ("�γ�: ���ݽṹ" ));
		outtextxy(100, 200, ("ѧ��:4 "));
		outtextxy(100, 240, ("GPA:4 " ));
		outtextxy(100, 280, ("ƽ��GPA:3.5 "));
		outtextxy(100, 320, ("GPAƽ��������1"));

		// ��� ESC ����
		{
			if (Window::hasMsg())
				m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE)
			{
				op = stumenu1;  // ����ѧ������ҳ��
				break;
			}
		}


	Window::flushDraw();
	}

}
//ѧ��������������
void Management::stuop3()
{
	while (true)
	{
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = stumenu1;  // ���ص���һ���˵�
				break;
			}
		}
	}
}
//ѧ�������ģ��޸�����
void Management::stuop4()
{
	for (auto& btn : stu_Btns) btn->hide();  // ���ذ�ť

	// ��������
	std::string originalPassword, newPassword, confirmPassword;
	passwordLine->clear();
	newPasswordLine->clear();
	confirmPasswordLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 50, "�޸����루�� ESC ���أ�");

		// ����ԭ����
		outtextxy(100, 150, "�����뵱ǰ���룺");
		passwordLine->show();
		passwordLine->eventLoop(m_msg);  // ��ȡԭ��������

		// ��ʾȷ�ϰ�ť
		confirmPasswordBtn->show();
		confirmPasswordBtn->eventLoop(m_msg);  // �ȴ�ȷ�ϰ�ť���

		// ��֤ԭ����
		if (confirmPasswordBtn->isClicked() && Timer::startTimer(400, 0))
		{
			originalPassword = trim(passwordLine->text1());  // ��ȡԭ����

			// �������������Ƿ��뵱ǰ�û�������ƥ��
			if (Current_user != nullptr && originalPassword == Current_user->getKey()) {
				// ԭ������ȷ�������޸�����
				op = Adop9;  // ת�������޸ģ�adop9��
				break;  // ����ѭ�������ɵ� adop9
			}
			else {
				m_msgBox->setMessage("��ǰ����������������룡");
			}
		}

		// ESC����
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = stumenu1;  // ���ص���һ���˵�
				break;
			}
		}

		// �¼�������ֹ��������
		if (m_msgBox && m_msgBox->isVisible()) {
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // �������¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}

		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
void Management::adop9()
{
	for (auto& btn : admin_Btns) btn->hide();  // ���ع���Ա��ť

	// ��������
	std::string newPassword, confirmPassword;
	newPasswordLine->clear();
	confirmPasswordLine->clear();

	while (true)
	{
		Window::clear();
		drawBackground();
		settextstyle(30, 0, "����");
		outtextxy(100, 50, "�޸����루�� ESC ���أ�");

		// ����������
		settextstyle(30, 0, "����");
		outtextxy(100, 180, "�����������룺");
		newPasswordLine->show();
		newPasswordLine->eventLoop(m_msg);  // ��ȡ����������

		// ����ȷ������
		settextstyle(30, 0, "����");
		outtextxy(100, 260, "��ȷ�������룺");
		confirmPasswordLine->show();
		confirmPasswordLine->eventLoop(m_msg);  // ��ȡȷ����������

		// ��ʾȷ�ϰ�ť
		confirmPasswordBtn1->show();
		confirmPasswordBtn1->eventLoop(m_msg);  // �ȴ�ȷ�ϰ�ť���

		// ȷ��������
		if (confirmPasswordBtn1->isClicked() && Timer::startTimer(400, 0))
		{
			newPassword = trim(newPasswordLine->text1());  // ��ȡ������
			confirmPassword = trim(confirmPasswordLine->text1());  // ��ȡȷ������

			// ��֤��������ȷ�������Ƿ�һ��
			if (newPassword == confirmPassword) {
				// ���µ�ǰ�û�������
				Current_user->setKey(newPassword);  // �޸ĵ�ǰ�û�����

				// ���� users.csv �ļ�
				std::ifstream fileIn("./IMAGE/users.csv");
				std::ofstream fileOut("./IMAGE/users_temp.csv", std::ios::trunc);
				std::string line;
				bool isFirstLine = true;

				while (getline(fileIn, line)) {
					if (isFirstLine) {
						fileOut << line << "\n";  // д���һ�У�����Ա���ݲ��䣩
						isFirstLine = false;
						continue;
					}

					std::stringstream ss(line);
					std::string username, password, role;
					getline(ss, username, ',');
					getline(ss, password, ',');
					getline(ss, role);

					// ����Ƿ��ǵ�ǰ��¼�û�
					if (username == Current_user->getName()) {
						fileOut << username << "," << newPassword << "," << role << "\n";  // ���µ�ǰ�û�����
					}
					else {
						fileOut << line << "\n";  // �����û����ݲ���
					}
				}

				fileIn.close();
				fileOut.close();

				// �滻���ļ�Ϊ���ļ�
				remove("./IMAGE/users.csv");
				rename("./IMAGE/users_temp.csv", "./IMAGE/users.csv");

				m_msgBox->setMessage("�����޸ĳɹ���");
			}
			else {
				m_msgBox->setMessage("������������벻һ�£����������룡");
			}
		}

		// ESC����
		if (Window::hasMsg()) {
			m_msg = Window::getMsg();
			if (m_msg.message == WM_KEYDOWN && m_msg.vkcode == VK_ESCAPE) {
				op = stumenu1;  // ���ص���һ���˵�
				break;
			}
		}

		if (m_msgBox && m_msgBox->isVisible())
		{
			m_msgBox->show();
			m_msgBox->eventLoop(m_msg);  // ������Ϣ���¼�
			Window::flushDraw();  // ���½���
			continue;  // ��ֹ�����߼�ִ�У�ֱ�������ر�
		}


		// ÿ֡���½��沢ˢ��
		Window::flushDraw();
	}
}
//ѧ�������壺�˳�
void Management::stuop5()
{
	op = menu();
}

void Management::drawBackground()
{
	::putimage(0, 0, &m_bk);
}






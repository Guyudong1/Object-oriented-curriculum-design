#pragma once
#include"Window.h"
#include<vector>
#include"PushButton.h"
#include<memory>
#include"LineEdit.h"
#include"User.h"
#include"MsgBox.h"
#include "Stu_data.h"
#include <graphics.h>


class Management
{
	enum Operator
	{
		Login,
		Register,
		Registera,
		Registerb,
		stumenu1,
		adminmenu1,
		Adop1,
		Adop3,
		Adop2,
		Adop4,
		Adop5,
		Adop6,
		Adop7,
		Adop8,
		Adop9,
		Adop2_1,
		Adop4_1,
		Adop5_1,
		Adop6_1,
		Adop6_2,
		Adop6_3,
		Adop6_4,
		Adop6_5,
		Stuop1,
		Stuop2,
		Stuop3,
		Stuop4,
		Stuop5,
		Menu = 66

	};
public:
	Management();
	void run();

	int menu();
	int op = 66;

	//1,��½����
	void display();
	//2,ע�����
	int add();
	//3,����Աע��
	void Register1();
	//4,ѧ��ע��
	void Register2();
	//5��ѧ����������
	int stumenu();
	//6������Ա��������
	int adminmenu();
	//7������Ա����1
	void adop1();
	//8������Ա����2
	void adop2();
	//9������Ա����3
	void adop3();
	//10������Ա����4
	void adop4();
	//11������Ա����5
	void adop5();
	//12������Ա����6
	void adop6();
	//13������Ա����7
	void adop7();
	//14������Ա����8
	void adop8();
	//15������Ա����9
	void adop9();
	//16������Ա����10
	void adop2_1();
	//����Ա��������
	void adop4_1();
	void adop5_1();
	void adop6_1();
	void adop6_2();
	void adop6_3();
	void adop6_4();
	void adop6_5();
	//ѧ������
	void stuop1();
	void stuop2();
	void stuop3();
	void stuop4();
	void stuop5();

	void drawBackground();
	void eventLoop();


	//��д�û�����
	void readFile(const std::string& fileName);
	void readStuFile(const std::string& fileName);

	PushButton* menubtn;
	//ע��ѧ��ҳ
	PushButton* RegisterBtn;
	PushButton* RegisterBtn1;
	LineEdit* RegisterLine;
	LineEdit* RegisterLine1;
	LineEdit* RegisterLine2;
	LineEdit* RegisterLine3;
	LineEdit* RegisterLine4;
	LineEdit* RegisterLine5;
	LineEdit* RegisterLine6;
	//adminmenu�й���ʵ��
	PushButton* submitInfoBtn;
	PushButton* addGradeBtn;
	PushButton* finishAllBtn;
	LineEdit* stuLineID;
	LineEdit* stuLineName;
	LineEdit* stuLineBirth;
	LineEdit* stuLineSex;
	LineEdit* stuLineClass;
	LineEdit* gradeLineCourse;
	LineEdit* gradeLineCredit;
	LineEdit* gradeLineGPA;
	LineEdit* studentIDLine;     
	LineEdit* studentNameLine;   
	LineEdit* studentClassLine;  
	LineEdit* courseNameLine;    
	LineEdit* courseCreditLine;  
	LineEdit* courseGpaLine;     
	PushButton* submitGradeBtn;  
	PushButton* finishAllBtn1;    
	PushButton* queryBtn;
	LineEdit* studentBirthLine;
	LineEdit* studentSexLine;
	LineEdit* courseIndexLine;
	LineEdit* fixstudentNameLine;
	LineEdit* fixstudentBirthLine;
	LineEdit* fixstudentSexLine;
	LineEdit* fixstudentClassLine;
	PushButton* ensureBtn;
	LineEdit* fixcourseNameLine;
	LineEdit* fixcourseCreditLine;
	LineEdit* fixcourseGpaLine;
	PushButton* adopbtn;
	PushButton* adopbtn1;
	PushButton* adopbtn2;
	LineEdit* passwordLine;
	LineEdit* newPasswordLine;
	LineEdit* confirmPasswordLine;
	PushButton* confirmPasswordBtn;
	PushButton* confirmPasswordBtn1;
	LineEdit* userIDLine;
	//ѧ����������

	//ѧ������
	Stu_data currentStudent;
	static User* Current_user;

	static std::string Current_name;
private:
	IMAGE m_bk;
	ExMessage m_msg;

	std::vector<std::unique_ptr<PushButton>>menu_btns;
	std::vector<std::unique_ptr<PushButton>>Register_Btns;
	std::vector<std::unique_ptr<PushButton>>admin_Btns;
	std::vector<std::unique_ptr<PushButton>>stu_Btns;

	//��Ӱ�ť
	std::unique_ptr<PushButton> m_addBtn;
	std::unique_ptr<LineEdit> m_addEdit;
	std::unique_ptr<LineEdit> m_addEdit1;
	//��ȡ�ļ� �����û���Ϣ
	std::string m_header;

	std::vector<User*> Users;
	std::string Admin_Key;
	std::unique_ptr<MsgBox> m_msgBox;
	std::vector<Stu_data> studentList;
};


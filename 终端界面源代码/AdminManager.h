#pragma once

#include <string.h>
#include <vector>
#include <queue>
#include "MessageManager.h"


//-----------------------成绩类-------------------------
class Grade {
public:
	string Cname;		//课程名
	float Credit;			//课程学分
	float GPA;			//学生绩点

	Grade();
	Grade(string Cna,float Cre, float Gpa);
	~Grade();

	string GetCname() const;
	float GetCredit() const;
	float GetGPA() const;
	void GradeDisplay() const;
};

//-----------------------学生类----------------------
class Student {
public:
	string Sid;			//学号
	string Sname;		//姓名
	string Sbirth;		//生辰
	string Ssex;			//性别
	string Sclass;		//班级

	vector<Grade> grades;		//成绩类的vector数组

	Student(string Id, string Name, string Birth, string Sex, string Class);

	string GetId();
	string GetName();
	string GetBirth();
	string GetSex();
	string GetClass();
	void StuDisplay() const;
	void GradesDisplay() const;
};

//-------------------------管理员系统类------------------------
class AdminManager {
private:


public:

	vector<Student> students;		//学生类的vector数组

	std::vector<Message> messages;

	//----------------管理员主菜单---------------

	int Admin_Menu();

	//----------------功能一：录入----------------

	string Add_Student_Information();

	void Add_Student_Grade(string, const Grade&);

	void Add_Student_Screem();

	//-----------------功能二：打印-----------------

	bool In_Id(string);

	void Table_Student_Information_Display();

	void Table_Student_Grade_Display(string);

	string Student_Information_Display();

	void Student_Grade_Display(string);

	void Display_Student_Screem();

	//------------------功能三：备份------------------

	void Backup_Student_Screem();

	//-------------------功能四：读取备份------------------

	void Read_Student_Screem();

	//--------------------功能五：增加---------------------

	void Add_Student_Grades_Screem();

	//--------------------功能六：删除---------------------

	void Delete_Student_Screem();

	//--------------------功能七：修改----------------------

	void Modify_Student_Screem();
	void Modify_Student_Grades(Student& student);

	//---------------------功能八：查询---------------------

	void Search_Student_Screem();

	//---------------------开机自启动-----------------------

	void Load_Students();  // 新增方法：从文件加载学生数据



	void MailboxMenu();

	void ReplyToStudentScreen();
};
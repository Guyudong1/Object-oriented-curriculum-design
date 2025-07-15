#pragma once

#include <string.h>
#include <vector>
#include <queue>
#include "MessageManager.h"


//-----------------------�ɼ���-------------------------
class Grade {
public:
	string Cname;		//�γ���
	float Credit;			//�γ�ѧ��
	float GPA;			//ѧ������

	Grade();
	Grade(string Cna,float Cre, float Gpa);
	~Grade();

	string GetCname() const;
	float GetCredit() const;
	float GetGPA() const;
	void GradeDisplay() const;
};

//-----------------------ѧ����----------------------
class Student {
public:
	string Sid;			//ѧ��
	string Sname;		//����
	string Sbirth;		//����
	string Ssex;			//�Ա�
	string Sclass;		//�༶

	vector<Grade> grades;		//�ɼ����vector����

	Student(string Id, string Name, string Birth, string Sex, string Class);

	string GetId();
	string GetName();
	string GetBirth();
	string GetSex();
	string GetClass();
	void StuDisplay() const;
	void GradesDisplay() const;
};

//-------------------------����Աϵͳ��------------------------
class AdminManager {
private:


public:

	vector<Student> students;		//ѧ�����vector����

	std::vector<Message> messages;

	//----------------����Ա���˵�---------------

	int Admin_Menu();

	//----------------����һ��¼��----------------

	string Add_Student_Information();

	void Add_Student_Grade(string, const Grade&);

	void Add_Student_Screem();

	//-----------------���ܶ�����ӡ-----------------

	bool In_Id(string);

	void Table_Student_Information_Display();

	void Table_Student_Grade_Display(string);

	string Student_Information_Display();

	void Student_Grade_Display(string);

	void Display_Student_Screem();

	//------------------������������------------------

	void Backup_Student_Screem();

	//-------------------�����ģ���ȡ����------------------

	void Read_Student_Screem();

	//--------------------�����壺����---------------------

	void Add_Student_Grades_Screem();

	//--------------------��������ɾ��---------------------

	void Delete_Student_Screem();

	//--------------------�����ߣ��޸�----------------------

	void Modify_Student_Screem();
	void Modify_Student_Grades(Student& student);

	//---------------------���ܰˣ���ѯ---------------------

	void Search_Student_Screem();

	//---------------------����������-----------------------

	void Load_Students();  // �������������ļ�����ѧ������



	void MailboxMenu();

	void ReplyToStudentScreen();
};
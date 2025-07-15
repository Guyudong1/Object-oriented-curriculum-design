#pragma once

#include <vector>

//--------------�û���Ϣ��---------------
class UserInformation {
	protected:
		string UserName;		//�û�����
		string UserKey;			//�û�����
		string UserRole;			//�û���ݣ�Ȩ�ޣ�

	public:
		
		UserInformation(string Username, string Userkey, string role);
		string getname();
		string getkey();
		string getrole();
		void display();
		void setkey(const string& newKey);  // �޸�����
};

//---------------�û���Ϣ������------------------
 class UserInformationManager {

	 private:

		 vector<UserInformation*>Users;			//�û���Ϣ��vector����

		 int Count;		//��¼�ж������û���Ϣ

		 string Admin_Key;		//����Ա����

		 int kk;


	public:

		string Current_name;			//��¼�е��û���

		string Current_key;				//��¼�е��û�����

		UserInformationManager();

		~UserInformationManager();

		//++++++++++++++++++��¼����+++++++++++++++++

		string Login();

		//--------------��¼���������---------------

		int Login_Screem();

		//-------------��¼--------------
		void InputkeyScreem(string &,string &);

		//-------------ע��---------------
		void RegisterScreem(string &,string &);

		void DisplayUsers();

		void AddUsers(string,string,string);

		bool InName(string);

		bool KeyMatchName(string, string);

		bool IsAdmin(string);

		bool IsSingle(string);

		string Findrole(string);


		//++++++++++++++����������++++++++++++++++
		
		void Load_Users();

		//++++++++++++++����Ա����++++++++++++++++
		// 
		//---------���ܾţ��������---------

		bool In_User(string);

		void Delete_Users();

		void Backup_Users();

		void Replace_Admin_Key();

		void Display_Admin_Key();

		void Key_Manage_Screem();

		//----------�����㣺�˳���¼---------

		char  Exit_Screem();

		//+++++++++++++ѧ������+++++++++++++

		//----------�����壺�޸�����----------

		void Replace_Student_Key();

		//----------��������ע��----------

		char Log_Off();

 };
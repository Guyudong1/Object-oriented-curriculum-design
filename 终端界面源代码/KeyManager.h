#pragma once

#include <vector>

//--------------用户信息类---------------
class UserInformation {
	protected:
		string UserName;		//用户名称
		string UserKey;			//用户密码
		string UserRole;			//用户身份（权限）

	public:
		
		UserInformation(string Username, string Userkey, string role);
		string getname();
		string getkey();
		string getrole();
		void display();
		void setkey(const string& newKey);  // 修改密码
};

//---------------用户信息操作类------------------
 class UserInformationManager {

	 private:

		 vector<UserInformation*>Users;			//用户信息的vector数组

		 int Count;		//记录有多少行用户信息

		 string Admin_Key;		//管理员密码

		 int kk;


	public:

		string Current_name;			//登录中的用户名

		string Current_key;				//登录中的用户密码

		UserInformationManager();

		~UserInformationManager();

		//++++++++++++++++++登录操作+++++++++++++++++

		string Login();

		//--------------登录祖册主界面---------------

		int Login_Screem();

		//-------------登录--------------
		void InputkeyScreem(string &,string &);

		//-------------注册---------------
		void RegisterScreem(string &,string &);

		void DisplayUsers();

		void AddUsers(string,string,string);

		bool InName(string);

		bool KeyMatchName(string, string);

		bool IsAdmin(string);

		bool IsSingle(string);

		string Findrole(string);


		//++++++++++++++开机自启动++++++++++++++++
		
		void Load_Users();

		//++++++++++++++管理员操作++++++++++++++++
		// 
		//---------功能九：密码管理---------

		bool In_User(string);

		void Delete_Users();

		void Backup_Users();

		void Replace_Admin_Key();

		void Display_Admin_Key();

		void Key_Manage_Screem();

		//----------功能零：退出登录---------

		char  Exit_Screem();

		//+++++++++++++学生操作+++++++++++++

		//----------功能五：修改密码----------

		void Replace_Student_Key();

		//----------功能六：注销----------

		char Log_Off();

 };
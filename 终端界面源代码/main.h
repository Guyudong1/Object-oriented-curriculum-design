//#pragma once
//
//#include "KeyManager.h"
//#include "AdminManager.h"
//#include "StudentManager.h"
//
//UserInformationManager uim;
//AdminManager am;
//StudentManager sm;
//
////===============================菜单界面=============================
//
////--------------登录祖册主界面---------------
//int Login_Screem();
//
////----------------管理员主菜单---------------
//int Admin_Menu();
//
////---------------学生主菜单---------------
//int Student_Menu();
//
////===============================登录操作=============================
//// 
//string Login();
//
////-------------登录--------------
//void InputkeyScreem(string&, string&);
//
////-------------注册---------------
//void RegisterScreem(string&, string&);
//
//void DisplayUsers();
//
//void AddUsers(string, string, string);
//
//bool InName(string);
//
//bool KeyMatchName(string, string);
//
//bool IsAdmin(string);
//
//bool IsSingle(string);
//
//string Findrole(string);
//
////==========================开机自启动===============================
//
//void Load_Users();
//
////==========================管理员操作===============================
//
////----------------功能一：录入----------------
//string Add_Student_Information();
//
//void Add_Student_Grade(string, const Grade&);
//
//void Add_Student_Screem();
//
////-----------------功能二：打印-----------------
//bool In_Id(string);
//
//void Table_Student_Information_Display();
//
//void Table_Student_Grade_Display(string);
//
//string Student_Information_Display();
//
//void Student_Grade_Display(string);
//
//void Display_Student_Screem();
//
////------------------功能三：备份------------------
//void Backup_Student_Screem();
//
////-------------------功能四：读取备份------------------
//void Read_Student_Screem();
//
////--------------------功能五：增加---------------------
//
//
////--------------------功能六：删除---------------------
//
//
////--------------------功能七：修改----------------------
//
//
////---------------------功能八：查询---------------------
//
//
////---------功能九：密码管理---------
//bool In_User(string);
//
//void Delete_Users();
//
//void Backup_Users();
//
//void Replace_Admin_Key();
//
//void Display_Admin_Key();
//
//void Key_Manage_Screem();
//
////----------功能零：退出登录---------
//void Exit_Screem();
//
////=========================学生操作===========================
//// 
////------------功能一：查看个人信息--------------
//
//
////------------功能二：查看个人成绩--------------
//
//
////------------功能三：查询均绩点---------------
//
//
////------------功能四：查询排名--------------
//
//
////----------功能五：修改密码----------
//void Replace_Student_Key();
//
////----------功能六：注销----------
//void Log_Off();
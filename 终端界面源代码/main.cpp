    #include <iostream>
    using namespace std;

    #include "StudentManager.h"
    #include "KeyManager.h"
    #include "AdminManager.h"
    #include "MessageManager.h"

    int main() {
        char i,j;
        UserInformationManager uim;
        uim.Load_Users();

        while (true) {
            
            string Role = uim.Login();  // 每次登录都刷新身份

            if (Role == "Admin") {
                AdminManager am;
                bool adminSession = true;
                am.Load_Students();
                while (adminSession) {
                    i = 'y';
                    switch (am.Admin_Menu()) {
                    case 1:
                        //录入学生信息
                        am.Add_Student_Screem();
                        break;
                    case 2: 
                        //打印学生信息
                        am.Display_Student_Screem();
                        break;
                    case 3:
                        //备份学生信息
                        am.Backup_Student_Screem();
                        break;
                    case 4:
                        //读取学生信息
                        am.Read_Student_Screem();
                        break;
                    case 5:
                        //增加学生信息
                        am.Add_Student_Grades_Screem();
                        break;
                    case 6:
                        //删除学生信息
                        am.Delete_Student_Screem();
                        break;
                    case 7:
                        //修改学生信息
                        am.Modify_Student_Screem();
                        break;
                    case 8:
                        //查询学生信息
                        am.Search_Student_Screem();
                        break;
                    case 9:
                        //用户密码管理
                        uim.Key_Manage_Screem();
                        break;
                    case 10: 
                        // 邮箱
                        am.MailboxMenu();
                        break;
                    case 0:
                        MessageManager::SaveMessages(); // 保存消息
                        i = uim.Exit_Screem();
                        if (i == 'n')break;
                        adminSession = false;
                        break;
                    }
                    if (adminSession) {
                        system("pause");
                        system("cls");
                    }
                }
            }

            else if (Role == "Stu") {
                AdminManager am2;
                am2.Load_Students();
                StudentManager sm(am2.students, uim.Current_name);
                bool studentSession = true;

                while (studentSession) {
                    i = 'y',j = 'y';
                    switch (sm.Student_Menu()) {
                    case 1:
                        //查看个人信息
                        sm.ViewPersonalInfo();
                        break;
                    case 2:
                        //查看成绩
                        sm.ViewGrades();
                        break;
                    case 3:
                        //查询课程平均绩点
                        sm.QueryCourseAverageGPA();
                        break;
                    case 4:
                        //查询所在班级的总排名
                        sm.QueryGradeRanking();
                        break;
                    case 5:
                        //修改密码
                        uim.Replace_Student_Key();
                        break;
                    case 6:  
                        // 注销账户
                        j = uim.Log_Off(); 
                        if (j == 'n') break;
                        studentSession = false;
                        break;
                    case 7:  
                        // 邮箱
                        sm.MailboxMenu();
                        break;
                    case 0:
                        MessageManager::SaveMessages(); // 保存消息
                        i = uim.Exit_Screem();
                        if (i == 'n') break;
                        studentSession = false;
                        break;
                    }
                    if (studentSession) {
                        system("pause");
                        system("cls");
                    }
                }
            }
            // 清屏，返回 Login 循环
            system("cls");
        }
        return 0;
    }

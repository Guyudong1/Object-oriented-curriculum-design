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
            
            string Role = uim.Login();  // ÿ�ε�¼��ˢ�����

            if (Role == "Admin") {
                AdminManager am;
                bool adminSession = true;
                am.Load_Students();
                while (adminSession) {
                    i = 'y';
                    switch (am.Admin_Menu()) {
                    case 1:
                        //¼��ѧ����Ϣ
                        am.Add_Student_Screem();
                        break;
                    case 2: 
                        //��ӡѧ����Ϣ
                        am.Display_Student_Screem();
                        break;
                    case 3:
                        //����ѧ����Ϣ
                        am.Backup_Student_Screem();
                        break;
                    case 4:
                        //��ȡѧ����Ϣ
                        am.Read_Student_Screem();
                        break;
                    case 5:
                        //����ѧ����Ϣ
                        am.Add_Student_Grades_Screem();
                        break;
                    case 6:
                        //ɾ��ѧ����Ϣ
                        am.Delete_Student_Screem();
                        break;
                    case 7:
                        //�޸�ѧ����Ϣ
                        am.Modify_Student_Screem();
                        break;
                    case 8:
                        //��ѯѧ����Ϣ
                        am.Search_Student_Screem();
                        break;
                    case 9:
                        //�û��������
                        uim.Key_Manage_Screem();
                        break;
                    case 10: 
                        // ����
                        am.MailboxMenu();
                        break;
                    case 0:
                        MessageManager::SaveMessages(); // ������Ϣ
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
                        //�鿴������Ϣ
                        sm.ViewPersonalInfo();
                        break;
                    case 2:
                        //�鿴�ɼ�
                        sm.ViewGrades();
                        break;
                    case 3:
                        //��ѯ�γ�ƽ������
                        sm.QueryCourseAverageGPA();
                        break;
                    case 4:
                        //��ѯ���ڰ༶��������
                        sm.QueryGradeRanking();
                        break;
                    case 5:
                        //�޸�����
                        uim.Replace_Student_Key();
                        break;
                    case 6:  
                        // ע���˻�
                        j = uim.Log_Off(); 
                        if (j == 'n') break;
                        studentSession = false;
                        break;
                    case 7:  
                        // ����
                        sm.MailboxMenu();
                        break;
                    case 0:
                        MessageManager::SaveMessages(); // ������Ϣ
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
            // ���������� Login ѭ��
            system("cls");
        }
        return 0;
    }

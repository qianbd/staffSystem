#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;

int main() {

	//ʵ���������߶���
	WorkManager wm;

	int choice = 0;

	while (true) {
		wm.Show_Menu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice) {
		case 0:	//�˳�
			wm.ExitSystem();
			break;
		case 1:	//����ְ��
			wm.Add_Emp();
			break;
		case 2:	//��ʾְ��
			break;
		case 3:	//ɾ��ְ��
			break;
		case 4:	//�޸�ְ��
			break;
		case 5:	//����ְ��
			break;
		case 6:	//����ְ��
			break;
		case 7:	//���ְ��
			break;
		default:
			system("cls");
			break;

		}
	}
	
	system("pause");
	return 0;
}
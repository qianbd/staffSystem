#pragma once
#include "workerManager.h"

WorkManager::WorkManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArrary = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ��" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArrary = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int num = this->get_EmpNum();
	
	this->m_EmpNum = num;

	this->m_EmpArrary = new Worker * [this->m_EmpNum];
	this->init_Emp();
	
}

void WorkManager::Show_Menu() {
	cout << "**************************************************" << endl;
	cout << "************   ��ӭʹ��ְ������ϵͳ   ************" << endl;
	cout << "**************   0.�˳��������   ****************" << endl;
	cout << "**************   1.����ְ����Ϣ   ****************" << endl;
	cout << "**************   2.��ʾְ����Ϣ   ****************" << endl;
	cout << "**************   3.ɾ����ְְ��   ****************" << endl;
	cout << "**************   4.�޸�ְ����Ϣ   ****************" << endl;
	cout << "**************   5.����ְ����Ϣ   ****************" << endl;
	cout << "**************   6.���ձ������   ****************" << endl;
	cout << "**************   7.��������ĵ�   ****************" << endl;
	cout << "**************************************************" << endl;
	cout << endl;
}

void WorkManager::ExitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}


void WorkManager::Add_Emp() {
	cout << "���������ְ�������� " << endl;
	int addNum = 0;	
	cin >> addNum;
	if (addNum > 0) {
		int newSize = this->m_EmpNum + addNum;
		
		Worker ** newSpace = new Worker* [newSize];
		//��ԭ���ռ������ݣ��������¿ռ���
		if (this->m_EmpArrary != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArrary[i];
			}
		}
		//���������
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;
			cout << "�������" << i + 1 << "����ְ����ţ� " << endl;
			cin >> id;
			if (IsExist(id) == -1) {
				cout << "�������" << i + 1 << "����ְ�������� " << endl;
				cin >> name;
				cout << "��ѡ���ְ����λ�� " << endl;
				cout << "1.��ְͨ��" << endl;
				cout << "2.����" << endl;
				cout << "3.�ϰ�" << endl;
				cin >> dSelect;
				Worker* worker = NULL;
				switch (dSelect)
				{
				case 1:
					worker = new Employee(id, name, 1);
					break;
				case 2:
					worker = new Manager(id, name, 2);
					break;
				case 3:
					worker = new Boss(id, name, 3);
					break;
				default:
					break;
				}
				//������ְ��ְ�𣬱��浽������
				//newSpace[this->m_EmpNum + i] = worker;

				int index = this->m_EmpNum + i;

				cout << "index = " << index << endl;
				if (index >= newSize)
					break;
				newSpace[index] = worker;
				

				delete[] this->m_EmpArrary;	
				this->m_EmpArrary = newSpace;	
				this->m_EmpNum = newSize;	
				this->m_FileIsEmpty = false;
				cout << "�ɹ����" << addNum << "��ְ��" << endl;
				this->save();
			}
				
			else {
				cout << "�ñ������ӣ����������" << endl;
				i--;
			}
		}
	}
	else {
		cout << "��������" << endl;
	}

	system("pause");
	system("cls");
}

void WorkManager::save() {
	ofstream ofs;
	ofs.open(FILENAME,ios::out);	
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArrary[i]->m_Id << " "
			<< this->m_EmpArrary[i]->m_Name << " "
			<< this->m_EmpArrary[i]->m_DeptId << endl;
	}
	ofs.close();
}

int WorkManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		num++;
	}
	return num;
}
void WorkManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;
		if (dId == 1) {
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {
			worker = new Manager(id, name, dId);
		}
		else {
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArrary[index] = worker;
		index++;
	}
	ifs.close();
}

void WorkManager::Show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			this->m_EmpArrary[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else {
		cout << "��������Ҫɾ��ְ���ı�ţ� " << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1) {
			for (int i = index; i < this->m_EmpNum - 1; i++) {
				this->m_EmpArrary[i] = this->m_EmpArrary[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "ɾ���ɹ���" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
		system("pause");
		system("cls");
	}
}
int WorkManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArrary[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}

void WorkManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else {
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1) {
			delete this->m_EmpArrary[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "�鵽�� " << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newId;

			cout << "������������" << endl;
			cin >> newName;

			cout << "�������λ�� " << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;

			cin >> dSelect;
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;

			default:
				break;
			}
			this->m_EmpArrary[ret] = worker;
			cout << "�޸ĳɹ�" << endl;
			this->save();
		}
		else {
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkManager::Find_Emp() {
	if (this->m_FileIsEmpty)
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	else {
		cout << "��������ҵķ�ʽ" << endl;
		cout << "1������ְ����Ų���" << endl;
		cout << "2������ְ����������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "��������ҵ�ְ����ţ� " << endl;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1) {
				cout << "���ҳɹ�����ְ����Ϣ����: " << endl;
				this->m_EmpArrary[ret]->showInfo();
			}
			else {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "��������ҵ�����: " << endl;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++) {
				if (this->m_EmpArrary[i]->m_Name == name) {
					cout << "���ҳɹ���ְ�����Ϊ�� " << this->m_EmpArrary[i]->m_Id << "��ְ����Ϣ���" << endl;
					this->m_EmpArrary[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false) {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else {
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}


void WorkManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "��ѡ������ʽ�� " << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < m_EmpNum; i++) {
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++) {
				if (select == 1) {
					if (this->m_EmpArrary[minOrMax]->m_Id > this->m_EmpArrary[j]->m_Id) {
						minOrMax = j;
					}
				}
				else {
					if (this->m_EmpArrary[minOrMax]->m_Id < this->m_EmpArrary[j]->m_Id) {
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax) {
				Worker* temp = this->m_EmpArrary[i];
				this->m_EmpArrary[i] = this->m_EmpArrary[minOrMax];
				this->m_EmpArrary[minOrMax] = temp;
			}
		}
		cout << "����ɹ��������Ľ��Ϊ�� " << endl;
		this->save();
		this->Show_Emp();
	}
}
void WorkManager::Clean_File() {
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);	//ɾ���ļ������´���
		ofs.close();

		if (this->m_EmpArrary != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArrary[i];
				this->m_EmpArrary[i] = NULL;
			}
			delete[] this->m_EmpArrary;
			this->m_EmpArrary = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

WorkManager::~WorkManager() {
	if (this->m_EmpArrary != NULL) {
		for (int i = 0; i < this->m_EmpNum; i++) {
			if (this->m_EmpArrary[i] != NULL) {
				delete[] this->m_EmpArrary;
			}
		}
		this->m_EmpArrary = NULL;
	}
}
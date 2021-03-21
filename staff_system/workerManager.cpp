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
			newSpace[this->m_EmpNum + i] = worker;
		}
		delete[] this->m_EmpArrary;	//�ͷ�ԭ�пռ�
		this->m_EmpArrary = newSpace;	//�����¿ռ��ָ��
		this->m_EmpNum = newSize;	//�����µ�ְ������
		this->m_FileIsEmpty = false;
		cout << "�ɹ����" << addNum << "��ְ��" << endl;
		this->save();
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

WorkManager::~WorkManager() {
	if (this->m_EmpArrary != NULL) {
		delete[] this->m_EmpArrary;
		this->m_EmpArrary = NULL;
	}
}
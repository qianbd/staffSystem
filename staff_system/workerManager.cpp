#include "workerManager.h"

WorkManager::WorkManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArrary = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空" << endl;
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
	cout << "************   欢迎使用职工管理系统   ************" << endl;
	cout << "**************   0.退出管理程序   ****************" << endl;
	cout << "**************   1.增加职工信息   ****************" << endl;
	cout << "**************   2.显示职工信息   ****************" << endl;
	cout << "**************   3.删除离职职工   ****************" << endl;
	cout << "**************   4.修改职工信息   ****************" << endl;
	cout << "**************   5.查找职工信息   ****************" << endl;
	cout << "**************   6.按照编号排序   ****************" << endl;
	cout << "**************   7.清空所有文档   ****************" << endl;
	cout << "**************************************************" << endl;
	cout << endl;
}

void WorkManager::ExitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}


void WorkManager::Add_Emp() {
	cout << "请输入添加职工数量： " << endl;
	int addNum = 0;	
	cin >> addNum;
	if (addNum > 0) {
		int newSize = this->m_EmpNum + addNum;
		Worker ** newSpace = new Worker* [newSize];
		//将原来空间下数据，拷贝到新空间下
		if (this->m_EmpArrary != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArrary[i];
			}
		}
		//添加新数据
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i + 1 << "个新职工编号： " << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名： " << endl;
			cin >> name;
			cout << "请选择该职工岗位： " << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
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
			//将创建职工职责，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		delete[] this->m_EmpArrary;	//释放原有空间
		this->m_EmpArrary = newSpace;	//更改新空间的指向
		this->m_EmpNum = newSize;	//更新新的职工人数
		this->m_FileIsEmpty = false;
		cout << "成功添加" << addNum << "名职工" << endl;
		this->save();
	}
	else {
		cout << "输入有误" << endl;
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
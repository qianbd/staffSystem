#pragma once
#include <iostream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
using namespace std;

#define FILENAME "empFile.txt"
class WorkManager {
public:
	WorkManager();

	void Show_Menu();

	void ExitSystem();

	int m_EmpNum;

	Worker** m_EmpArrary;

	void Add_Emp();

	void save();

	bool m_FileIsEmpty;

	int get_EmpNum();
	
	void init_Emp();

	void Show_Emp();

	void Del_Emp();
	int IsExist(int id);

	void Mod_Emp();

	void Find_Emp();

	void Sort_Emp();

	void Clean_File();

	~WorkManager();
};
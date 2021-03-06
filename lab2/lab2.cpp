// lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>

using namespace std;

const int name_size = 20;

struct info
{
	char name[name_size] = { 0 };
	int pr1;
	int pr2;
	int pr3;
	int pr4;
};

void show();

int main()
{
	setlocale(LC_ALL, "Russian");
	show();

	STARTUPINFO StartupInfo;
	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof(StartupInfo);

	PROCESS_INFORMATION ProcInfo;
	ZeroMemory(&ProcInfo, sizeof(ProcInfo));

	char name[20];
	char  pr1[20], pr2[20], pr3[20], pr4[20], number[20];
	cout << "Введите номер структуры для редактирования" << endl;
	cin >> number;
	cout << "Введите имя студента" << endl;
	cin >> name;
	cout << "Введите оценку по 1 предмету" << endl;
	cin >> pr1;
	cout << "Введите оценку по 2 предмету" << endl;
	cin >> pr2;
	cout << "Введите оценку по 3 предмету" << endl;
	cin >> pr3;
	cout << "Введите оценку по 4 предмету" << endl;
	cin >> pr4;

	char daughter[] = "C:/Users/админ/Desktop/СПО/lab2_daughter/Debug/lab2_daughter.exe";
	char fname[100] = "lab2_daughter.exe"; strcat_s(fname, " ");
	strcat_s(fname, number); strcat_s(fname, " ");
	strcat_s(fname, name); strcat_s(fname, " ");
	strcat_s(fname, pr1); strcat_s(fname, " ");
	strcat_s(fname, pr2); strcat_s(fname, " ");
	strcat_s(fname, pr3); strcat_s(fname, " ");
	strcat_s(fname, pr4); strcat_s(fname, " ");
	if (!CreateProcess(daughter, fname, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcInfo)) return 0;

	WaitForSingleObject(ProcInfo.hProcess, INFINITE);
	CloseHandle(ProcInfo.hProcess);
	CloseHandle(ProcInfo.hThread);
	show();
	return 0;
}

void show()
{
	LPCTSTR filename = "qwe.txt";
	HANDLE myFile = CreateFile(
		filename,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (myFile == INVALID_HANDLE_VALUE)
		cout << "Ошибка";
	else
		cout << "Файл успешно открыт в основном процессе" << endl;
	cout << endl;

	DWORD n;

	info marks;

	SetFilePointer(myFile, 0, 0, FILE_BEGIN);
	while (ReadFile(myFile, &marks, sizeof(marks), &n, NULL) && n != 0)
	{
		cout << marks.name << " " << marks.pr1 << " " << marks.pr2 << " " << marks.pr3 << " " << marks.pr4 << endl;
	}
	CloseHandle(myFile);
	system("pause");

	cout << endl;

	return;

}

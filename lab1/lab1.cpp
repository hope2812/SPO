// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>;
#include <windows.h>;
#include "conio.h"
#include "ctime"

using namespace std;

struct info
{
	char name[20];
	int pr1;
	int pr2;
	int pr3;
	int pr4;
}marks;
DWORD bytesWritten;

void menu(HANDLE&);

void read(HANDLE& handle)
{
	SetFilePointer(handle, 0, NULL, FILE_BEGIN);
	while (ReadFile(handle, &marks, sizeof(marks), &bytesWritten, 0) && bytesWritten != 0)
	{
		if (((marks.pr1 + marks.pr2 + marks.pr3 + marks.pr4) / 4) > 7)
		{
			cout << marks.name << "\n" ;
		}
	}
	HANDLE tmp_handle = CreateFile("result.txt", GENERIC_READ | GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(tmp_handle, &marks, sizeof(marks), &bytesWritten, 0);
	cout << "нажмите любую клавишу для выхода\n";
	char ch;
	while (!(ch = _getche()))
	{
	}
	menu(handle);
}


void write(HANDLE& handle)
{
	SetFilePointer(handle, 0, NULL, FILE_END);
	cout << "введите имя студента: ";
	cin.ignore();
	cin >> marks.name;
	cout << "введите оценку по 1 предмету: ";
	cin >> marks.pr1;
	cout << "введите оценку по 2 предмету: ";
	cin >> marks.pr2;
	cout << "введите оценку по 3 предмету: ";
	cin >> marks.pr3;
	cout << "введите оценку по 4 предмету: ";
	cin >> marks.pr4;
	WriteFile(handle, &marks, sizeof(marks), &bytesWritten, NULL);
	menu(handle);
}


void menu(HANDLE& handle)
{
	system("cls");
	cout << "выберите действие :\n";
	cout << "1.ввести данные в файл\n";
	cout << "2.вывести результат\n";
	cout << "3.нажмите для выхода\n";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:write(handle); break;
	case 2:read(handle); break;
	case 3:exit(1);
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	LPCTSTR fileName = "base.txt";
	HANDLE handle = NULL;
	handle = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (GetLastError() == ERROR_FILE_NOT_FOUND)
		handle = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);

	menu(handle);

	return 0;
}
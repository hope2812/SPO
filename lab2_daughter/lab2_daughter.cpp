// lab2_daughter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS_
#include "pch.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>

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

void write(char[], char[], char[], char[], char[], char[]);

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	cout << endl;
	cout << "Дочерний процесс запущен с этого момента" << endl;
	cout << endl << "Введённые данные" << endl;
	for (int i = 1; i < argc; i++)
	{
		cout << argv[i] << " ";
	}


	cout << endl;
	write(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
	cout << "Закрытие дочернего процесса" << endl;
	cout << endl;
	system("pause");
	return 0;
}


void write(char number[], char name_s[], char pr1[], char pr2[], char pr3[], char pr4[])
{
	int num = atoi(number);
	info marks;
	strcat_s(marks.name, name_s);
	marks.pr1 = atoi(pr1);
	marks.pr2 = atoi(pr2);
	marks.pr3 = atoi(pr3);
	marks.pr4 = atoi(pr4);


	LPCTSTR fn = "C:/Users/админ/Desktop/СПО/lab2/qwe.txt";
	HANDLE myFile = CreateFile(
		fn,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (myFile == INVALID_HANDLE_VALUE)
		cout << "Ошибка";
	else
		cout << "Файл успешно изменён в дочернем процессе" << endl;
	DWORD m;


	unsigned long pos = (num - 1) * sizeof(info);


	SetFilePointer(myFile, pos, NULL, FILE_BEGIN);
	WriteFile(myFile, &marks, sizeof(info), &m, NULL);
	FlushFileBuffers(myFile);
	CloseHandle(myFile);
	return;
}
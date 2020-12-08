// laba3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <iostream>
#include <windows.h>
using namespace std;


int counter1 = 0;
int counter2 = 0;
int counter3 = 0;
char ch;
HANDLE hTh01, hTh02, hTh03;

void thread01()
{
	while (true) {
		counter1++; Sleep(10);
	}
}

void thread02()
{
	while (true) {
		counter2++; Sleep(50);
	}
}

void thread03()
{
	while (true) {
		counter3++; Sleep(100);
	}
}


int main()
{
	DWORD IDTh01;
	hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread01, NULL, 0, &IDTh01);
	if (hTh01 == NULL) return GetLastError();

	DWORD IDTh02;
	hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread02, NULL, 0, &IDTh02);
	if (hTh02 == NULL) return GetLastError();

	DWORD IDTh03;
	hTh03 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread03, NULL, 0, &IDTh03);
	if (hTh03 == NULL) return GetLastError();

	do
	{
		cout << "\n Enter :" << endl;
		cout << " 'q' Exit" << endl; // Выход
		cout << " 'n' Display n" << endl; // Вывод текущего значения 
		if (counter2 < 80 && counter3 < 80)
		{
			SuspendThread(hTh01);
		}
		else
		{
			ResumeThread(hTh01);
		};
		cin >> ch;


		switch (ch)
		{
		case 'n':
		{
			DWORD result = WaitForSingleObject(hTh01, 0);
			if (result != WAIT_FAILED)
				cout << "thread1 counter = " << counter1 << endl;
			result = WaitForSingleObject(hTh02, 0);
			if (result != WAIT_FAILED)
				cout << "thread2 counter = " << counter2 << endl;
			result = WaitForSingleObject(hTh03, 0);
			if (result != WAIT_FAILED)
				cout << "thread3 counter = " << counter3 << endl; break;
		}
		}
	} while (ch != 'q');

}
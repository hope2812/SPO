// lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include "time.h"

using namespace std;

const int N = 10;
HANDLE semafor;


DWORD WINAPI thread1_F(LPVOID mass)
{
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		*((int*)mass + i) = rand() % 500;
		Sleep(1000);
		cout << *((int*)mass + i) << "  ";
		ReleaseSemaphore(semafor, 1, NULL);
	}
	return 1;
}


DWORD WINAPI thread2_F(LPVOID mass)
{
	int counter = 0;
	for (int i = 0; i < N; i++)
	{
		WaitForSingleObject(semafor, INFINITE);
		if (*((int*)mass + i) % 2 == 0 && *((int*)mass + i) > 0) {
			counter++;
			cout << "(" << counter << ") ";
		}
	}
	return 1;
}


int main()
{
	int mass[N];
	setlocale(LC_ALL, "rus");
	semafor = CreateSemaphore(NULL, 0, N, TEXT("semafor"));
	HANDLE thread1 = CreateThread(NULL, 0, thread1_F, (void*)mass, NULL, 0);
	HANDLE thread2 = CreateThread(NULL, 0, thread2_F, (void*)mass, NULL, 0);
	HANDLE Threads[2] = { thread1, thread2 };
	WaitForMultipleObjects(2, Threads, TRUE, INFINITE);
	for (int i = 0; i < 2; i++)
	{
		CloseHandle(Threads[i]);
	}
	return 1;
}
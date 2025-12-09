// DataRace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<Windows.h>
#include"AutoCriticalSection.h"
CRITICAL_SECTION cs;
int data = 11;
void updatedata(int temp);

DWORD WINAPI DoWork(PVOID param)
{
    int x = *(int*)param; // Casting pointer to void to pointer to integer
    printf("Worker thread, %u\n", GetCurrentThreadId());
    Sleep(10000);

    printf("WOrker thread done %u\n ", GetCurrentThreadId());
    return x*x;
}

void updatedata(int temp)
{
    AutoCriticalSection locker(cs);
    data = temp;
}

int main()
{
    std::cout << "Hello World!\n";
    InitializeCriticalSection(&cs);
    updatedata(30);
    HANDLE hThread = CreateThread(nullptr, 0, DoWork, &data, 0, nullptr);
    if (!hThread)
        return 1;

    Sleep(100);

    updatedata(20);
    HANDLE hThread2 = CreateThread(nullptr, 0, DoWork, &data, 0, nullptr);
    if (!hThread2)
        return 1;

    printf("Main thread %u\n ", GetCurrentThreadId());
    HANDLE h[] = { hThread,hThread2 };
    WaitForMultipleObjects(2, h, TRUE, INFINITE);

    DWORD total = 0;
    DWORD result;
    for(int i=0;i<2;i++)
    {
        GetExitCodeThread(h[i], &result);
        printf("\n Result from thread %u : %u \n",GetThreadId(h[i]), result);
        total = total + result;
        CloseHandle(h[i]);
    }
    printf("Total is %u\n ", total);
    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

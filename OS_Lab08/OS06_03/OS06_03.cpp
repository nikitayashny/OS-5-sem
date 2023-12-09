#include <iostream>
#include <Windows.h>

using namespace std;

#define KB (1024)
#define MB (1024 * KB)
#define PG (4 * KB)

/*
    Я - DF(16) - 223(10)
    ш - F8(16) - 248(10)
    н - ED(16) - 237(10)
    Страница DF = 223
    223 * 4096 = 913408(10) = 0xDF000
    Смещение F8E = 3982(10) = 0xF8E
    913408 + 3982 = 917 390(10) / 4 * 4 =  0xDFF8C (его добавлять)

    (913408 + 3982) / 4 = 229347(10) = 0x37FE3
*/

void checkMemory();

int main()
{
    int pages = 256;
    int countItems = pages * PG / sizeof(int);

    cout << "--- Initially in the system" << endl;
    checkMemory();

    LPVOID xmemaddr = VirtualAlloc(NULL, pages * PG, MEM_COMMIT, PAGE_READWRITE);   // выделено 1024 KB виртуальной памяти
    cout << "--- Allocated " << pages * PG / 1024 << " KB virtual memory" << endl;
    checkMemory();

    int* arr = (int*)xmemaddr;
    for (int i = 0; i < countItems; i++)
        arr[i] = i;


    int* byte = arr + (223 * 4096 + 3982) / 4;
    cout << "------  Memory value in byte: " << *byte << "  ------" << endl;

    VirtualFree(xmemaddr, NULL, MEM_RELEASE) ? cout << "Virtual memory freed" << endl : cout << "Virtual memory not freed" << endl;
    checkMemory();
}

void checkMemory()
{
    MEMORYSTATUS ms;
    GlobalMemoryStatus(&ms);
    cout << "Total physical memory:      " << ms.dwTotalPhys / KB << " KB" << endl;
    cout << "Available physical memory:  " << ms.dwAvailPhys / KB << " KB" << endl;
    cout << "Total virtual memory:       " << ms.dwTotalVirtual / KB << " KB" << endl;
    cout << "Available virtual memory:   " << ms.dwAvailVirtual / KB << " KB" << endl << endl;
}
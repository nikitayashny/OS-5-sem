#include <iostream>
#include <Windows.h>

using namespace std;

#define KB (1024)

// Параметры пользовательской кучи:
// 1. доступ не синхронизирован
// 2. куча заполняется нулями
// 3. начальный размер 4 мб
// 4. конечный размер ограничен размером виртуальной памяти

void sh(HANDLE pheap);

int main() 
{
	HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 4096 * 1024, 0);
	sh(heap);

	int* x1 = (int*)HeapAlloc(heap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 300000 * sizeof(int));
	cout << "\nAddress x1: " << x1 << endl;
	sh(heap);

	HeapFree(heap, HEAP_NO_SERIALIZE, x1);
	cout << endl;
	sh(heap);
	HeapDestroy(heap);
}

void sh(HANDLE pheap)
{
	PROCESS_HEAP_ENTRY phe;
	phe.lpData = NULL;
	while (HeapWalk(pheap, &phe))
	{
		cout << "-- Address = " << showbase << hex << phe.lpData << " Size = " << dec << phe.cbData <<
				((phe.wFlags & PROCESS_HEAP_REGION) ? " R" : "") <<				// R - начало непрерывной области
				((phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " U" : "") <<	// U - нераспределенная область 
				((phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? " B" : "") << endl;	// B - распределенная область
	}
}
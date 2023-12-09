#include <iostream>
#include <Windows.h>

using namespace std;

void sh(HANDLE pheap);

int main() 
{
	HANDLE pheap = GetProcessHeap();
	sh(pheap);

	int size = 300000;
	int* m = new int[size];
	cout << "\n-- m = " << showbase << hex << m << " Size = " << dec << size << "\n\n";
	sh(pheap);
}

void sh(HANDLE pheap)
{
	PROCESS_HEAP_ENTRY phe;
	phe.lpData = NULL;
	while (HeapWalk(pheap, &phe)) {
		cout << "-- Address = " << showbase << hex << phe.lpData << ", Size = " << dec << phe.cbData <<
			((phe.wFlags & PROCESS_HEAP_REGION) ? " R" : "") <<				// R - начало непрерывной области
			((phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " U" : "") <<	// U - нераспределенная область 
			((phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? " B" : "") << endl;	// B - распределенная область
	}
}
#include <iostream>
#include <cstdlib>
#include <intrin.h>
#include <iomanip>
#include "Windows.h"
#include "bitset"

using namespace std;

void PrintProcessPriority(HANDLE processHandle);
void PrintThreadPriority(HANDLE threadHandle);
void PrintAffinityMask(HANDLE hp, HANDLE ht);

int main()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	HANDLE processHandle = GetCurrentProcess();
	HANDLE threadHandle = GetCurrentThread();

	cout << "PID: " << pid << "\n";
	cout << "TID: " << tid << "\n";

	PrintProcessPriority(processHandle);
	PrintThreadPriority(threadHandle);
	PrintAffinityMask(processHandle, threadHandle);

	system("pause");
}

void PrintProcessPriority(HANDLE processHandle)
{
	DWORD processPriority = GetPriorityClass(processHandle);

	switch (processPriority)
	{
	case IDLE_PRIORITY_CLASS:				cout << "Process priority:  IDLE_PRIORITY_CLASS\n";				break;
	case BELOW_NORMAL_PRIORITY_CLASS:		cout << "Process priority:  BELOW_NORMAL_PRIORITY_CLASS\n";		break;
	case NORMAL_PRIORITY_CLASS:				cout << "Process priority:  NORMAL_PRIORITY_CLASS\n";			break;
	case ABOVE_NORMAL_PRIORITY_CLASS:		cout << "Process priority:  ABOVE_NORMAL_PRIORITY_CLASS\n";		break;
	case HIGH_PRIORITY_CLASS:				cout << "Process priority:  HIGH_PRIORITY_CLASS\n";				break;
	case REALTIME_PRIORITY_CLASS:			cout << "Process priority:  REALTIME_PRIORITY_CLASS\n";			break;
	default:								cout << "[ERROR] Unknown process priority.\n";					break;
	}
}

void PrintThreadPriority(HANDLE threadHandle)
{
	DWORD threadPriority = GetThreadPriority(threadHandle);

	switch (threadPriority)
	{
	case THREAD_PRIORITY_LOWEST:		cout << "Thread proiority:  THREAD_PRIORITY_LOWEST\n";			break;
	case THREAD_PRIORITY_BELOW_NORMAL:	cout << "Thread proiority:  THREAD_PRIORITY_BELOW_NORMAL\n";	break;
	case THREAD_PRIORITY_NORMAL:		cout << "Thread proiority:  THREAD_PRIORITY_NORMAL\n";			break;
	case THREAD_PRIORITY_ABOVE_NORMAL:	cout << "Thread proiority:  THREAD_PRIORITY_ABOVE_NORMAL\n";	break;
	case THREAD_PRIORITY_HIGHEST:		cout << "Thread proiority:  THREAD_PRIORITY_HIGHEST\n";			break;
	case THREAD_PRIORITY_IDLE:			cout << "Thread proiority:  THREAD_PRIORITY_IDLE\n";			break;
	default:							cout << "[ERROR] Unknown thread priority.\n";					break;
	}
}

void PrintAffinityMask(HANDLE hp, HANDLE ht) 
{
	DWORD_PTR pa = NULL, sa = NULL, icpu = -1;

	if (!GetProcessAffinityMask(hp, &pa, &sa))
		throw "[FATAL] GetProcessAffinityMask threw an exception.";

	cout << "Process affinity mask: " << showbase << bitset<sizeof(pa) * 2>(pa) << "\n";
	cout << "System affinity mask:  " << showbase << bitset<sizeof(sa) * 2>(sa) << "\n";
	SetProcessAffinityMask(hp, 5);
	GetProcessAffinityMask(hp, &pa, &sa);
	/*SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	cout << "Max processors count:  " << dec << sys_info.dwNumberOfProcessors << "\n";*/
	cout << "Max processors count:  ";
	for (int i = 0; i <= 7; i++) {
		if (bitset<sizeof(pa) * 2>(pa)[i] != 0)
		cout << i << " ";
	}
	cout << endl;
	icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);
	cout << "Thread IdealProcessor: " << dec << icpu << "\n";
}
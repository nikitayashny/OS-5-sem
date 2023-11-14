#include <iostream>
#include <cstdlib>
#include <intrin.h>
#include <iomanip>
#include "Windows.h"
#include "bitset"

using namespace std;

void PrintProcessPriority(HANDLE processHandle);
void PrintThreadPriority(HANDLE threadHandle);

int main()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	HANDLE processHandle = GetCurrentProcess();
	HANDLE threadHandle = GetCurrentThread();
	DWORD icpu = SetThreadIdealProcessor(threadHandle, MAXIMUM_PROCESSORS);

	for (int i = 1; i <= 1000000; i++)
	{
		if (i % 1000 == 0)
		{
			cout << "Iteration: " << i << "\n";
			cout << "PID: " << pid << "\n";
			cout << "TID: " << tid << "\n";
			PrintProcessPriority(processHandle);
			PrintThreadPriority(threadHandle);
			cout << "Thread IdealProcessor: " << dec << icpu << "\n";
			cout << "\n";

			Sleep(200);
		}
	}

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
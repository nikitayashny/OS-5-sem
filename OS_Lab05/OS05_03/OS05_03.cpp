#include <iostream>
#include <cstdlib>
#include "Windows.h"
#include "bitset"

using namespace std;

DWORD intToProcessPriority(int i);
DWORD intToThreadPriority(int i);
void PrintProcessPriority(HANDLE processHandle);
void PrintThreadPriority(HANDLE threadHandle);
void childThread();

int main(int argc, char* argv[])
{
	try
	{
		if (argc == 5)
		{
			HANDLE processHandle = GetCurrentProcess();
			DWORD_PTR pa = NULL, sa = NULL, icpu = -1;

			int parm1 = atoi(argv[1]);
			int parm2 = atoi(argv[2]);
			int parm3 = atoi(argv[3]);
			int parm4 = atoi(argv[4]);

			if (!GetProcessAffinityMask(processHandle, &pa, &sa)) 
				throw "Error in GetProcessAffinityMask";

			cout << "\t\tBefore applying parameters:\n";
			cout << "Process affinity mask: " << showbase << bitset<sizeof(pa) * 2>(pa) << "\n";
			cout << "System affinity mask:  " << showbase << bitset<sizeof(sa) * 2>(sa) << "\n";

			if (!SetProcessAffinityMask(processHandle, parm1)) 
				throw "ERROR in SetProcessAffinityMask";
			if (!GetProcessAffinityMask(processHandle, &pa, &sa)) 
				throw "Error in GetProcessAffinityMask";

			cout << "\t\tAfter applying parameters:\n";
			cout << "Process affinity mask: " << showbase << bitset<sizeof(pa) * 2>(pa) << "\n";
			cout << "System affinity mask:  " << showbase << bitset<sizeof(sa) * 2>(sa) << "\n";

			SetPriorityClass(processHandle, intToProcessPriority(parm2));
			cout << "Main PriorityClass: " << parm2 << endl;

			DWORD childId_T1, childId_T2 = NULL;
			HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)childThread, NULL, CREATE_SUSPENDED, &childId_T1);
			HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)childThread, NULL, CREATE_SUSPENDED, &childId_T2);

			SetThreadPriority(hChild1, intToThreadPriority(parm3));
			SetThreadPriority(hChild2, intToThreadPriority(parm4));

			PrintThreadPriority(hChild1);
			PrintThreadPriority(hChild2);

			ResumeThread(hChild1);
			ResumeThread(hChild2);

			WaitForSingleObject(hChild1, INFINITE);
			WaitForSingleObject(hChild2, INFINITE);

			CloseHandle(hChild1);
			CloseHandle(hChild2);
		}
		else cout << "No parameters provided" << endl;
	}
	catch (string err) {
		cout << err << endl;
	}
	system("pause");
}

DWORD intToProcessPriority(int i)
{
	switch (i)
	{
	case 1: return IDLE_PRIORITY_CLASS;
	case 2: return BELOW_NORMAL_PRIORITY_CLASS;
	case 3: return NORMAL_PRIORITY_CLASS;
	case 4: return ABOVE_NORMAL_PRIORITY_CLASS;
	case 5: return HIGH_PRIORITY_CLASS;
	case 6: return REALTIME_PRIORITY_CLASS;
	default: throw "Unknown priority class";
	}
}

DWORD intToThreadPriority(int i)
{
	switch (i)
	{
	case 1: return THREAD_PRIORITY_LOWEST;
	case 2: return THREAD_PRIORITY_BELOW_NORMAL;
	case 3: return THREAD_PRIORITY_NORMAL;
	case 4: return THREAD_PRIORITY_ABOVE_NORMAL;
	case 5: return THREAD_PRIORITY_HIGHEST;
	case 6: return THREAD_PRIORITY_IDLE;
	default: throw "No such priority class";
	}
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

void childThread()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	HANDLE processHandle = GetCurrentProcess();
	HANDLE threadHandle = GetCurrentThread();
	DWORD icpu = SetThreadIdealProcessor(threadHandle, MAXIMUM_PROCESSORS);

	for (int i = 0; i < 1000000; i++)
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
	return;
}
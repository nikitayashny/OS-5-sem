#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <sys/resource.h>

int main() 
{
    pid_t pid = getpid();
    pid_t tid = gettid();
    int nice_value = getpriority(PRIO_PROCESS, 0);

    std::cout << "PID: " << pid << std::endl; 
    std::cout << "TID: " << tid << std::endl;
    std::cout << "Thread Priority (nice): " << nice_value << std::endl;

    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    sched_getaffinity(0, sizeof(cpu_set_t), &cpu_set);

    std::cout << "Accesseble processors: ";
    for (int i = 0; i < CPU_SETSIZE; ++i) {
        if (CPU_ISSET(i, &cpu_set))
            std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
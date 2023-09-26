#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t process_id = getpid();
    for (int j = 1; j <= 1000; j++)
    {
        printf("%d-%d \n", process_id, j);
        sleep(2);
    }
}


#include <stdio.h>
#include <unistd.h>
// top
// sudo renice -20 pid
int main() {
    for (int i = 1; ; i++) {
        printf("Iteration %d\n", i);
        sleep(1);
    }
    return 0;
}
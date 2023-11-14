#include <stdio.h>
#include <unistd.h>
// ./OS05_06 &
// bg переводит остановленный в фоновый
// fg переводит фоновый в активный
// ctrl+z останавливает текущий и помещает в фоновый
// jobs выводит список фоновых
// kill -9 pid убивает процесс
int main() {
    for (int i = 1; ; i++) {
        //printf("Iteration %d\n", i);
        sleep(1);
    }
    return 0;   
}
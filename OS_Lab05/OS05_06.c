#include <stdio.h>
#include <unistd.h>
// ./OS05_06 &
// bg ��������� ������������� � �������
// fg ��������� ������� � ��������
// ctrl+z ������������� ������� � �������� � �������
// jobs ������� ������ �������
// kill -9 pid ������� �������
int main() {
    for (int i = 1; ; i++) {
        //printf("Iteration %d\n", i);
        sleep(1);
    }
    return 0;   
}
#include<stdio.h>
#include<stdlib.h>

void main(){


    int ***x;//double형 pointer x변수

    printf("[----- [조민재] [2019038045] -----]\n");
    printf("sizeof(x) = %lu\n", sizeof(x));//주소를 저장하고 있는 바이트
    printf("sizeof(*x) = %lu\n", sizeof(*x));//주소를 저장하고 있는 바이트
    printf("sizeof(**x) = %lu\n", sizeof (**x));//두번 reference해서 실제 intege값을 저장한다.
}
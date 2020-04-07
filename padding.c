#include <stdio.h>//compiler마다 padding처리가 다르다!!
struct student {//student구조체의 총 크기는19byte이다
char lastName[13]; /* 13 bytes */
int studentId;/* 4 bytes */
short grade;/* 2 bytes */
};


int main()
{
    printf("[----- [조민재] [2019038045] -----]\n");
struct student pst;
printf("size of student = %ld\n", sizeof(struct student));//lastname에서 padding3byte+grade에서 padding 2byte 떄문에 총 24byte가된다.
printf("size of int = %ld\n", sizeof(int));//4
printf("size of short = %ld\n", sizeof(short));//2
return 0;
}
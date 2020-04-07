#include <stdio.h>
#include <stdlib.h>
void main()
{
    printf("[----- [조민재] [2019038045] -----]\n");
int list[5];
int *plist[5];
list[0] = 10;
list[1] = 11;
plist[0] = (int*)malloc(sizeof(int));
printf("list[0] \t= %d\n", list[0]);//10이 출력
printf("address of list \t= %p\n", list);//list의첫번째 주소
printf("address of list[0] \t= %p\n", &list[0]);//list의첫번째 주소
printf("address of list + 0 \t= %p\n", list+0);//list의첫번째 주소
printf("address of list + 1 \t= %p\n", list+1);//list[0]의 주소에 4byte 증가해준다
printf("address of list + 2 \t= %p\n", list+2);//list[1]의 주소에 4byte 증가해준다
printf("address of list + 3 \t= %p\n", list+3);//list[2]의 주소에 4byte 증가해준다
printf("address of list + 4 \t= %p\n", list+4);//list[3]의 주소에 4byte 증가해준다
printf("address of list[4] \t= %p\n", &list[4]);//list[4]의 주소출력
free(plist[0]);
}
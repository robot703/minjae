#include <stdio.h>
#include <stdlib.h>
void main()
{
    printf("[----- [조민재] [2019038045] -----]\n");
int list[5];//크기가 5인 list배열
int *plist[5] = {NULL,};//list정수에 대한 포인터의 배열을 초기화
plist[0] = (int *)malloc(sizeof(int));//plist배열을 malloc을 통해서 동적으로 메모리 할당
list[0] = 1;//배열0번쨰를 1로 초기화
list[1] = 100;//배열 1번째를 100으로 초기화

*plist[0] = 200;//배열 포인터 plist의 0번째를 200으로 초기화 
printf("value of list[0] = %d\n", list[0]);//1이 출력
printf("address of list[0] =%p\n",&list[0]);//첫번째 배열의 주소가 출력
printf("value of list =%p\n",&list);//첫번째 배열의 주소가 출력
printf("address of list (&list) =%p\n",&list);//첫번째 배열의 주소가 출력

printf("---------------------------------------------------------------\n\n");
printf("value of list[1]= %d\n", list[1]);//100이 출력
printf("address of list[1] = %p\n", &list[1]);//2번째 배열의 주소가 출력(첫주소보다4바이트크다)
printf("value of *(list+1) = %d\n", *(list + 1));//100이출력
printf("address of list+1 = %p\n", list+1);//2번째 배열의 주소가 출력(첫주소보다4바이트크다)

printf("---------------------------------------------------------------\n\n");

printf("value of *plist[0] = %d\n", *plist[0]);//200이 출력
printf("&plist[0]= %p\n", &plist[0]);//첫번째 주소 출력
printf("&plist= %p\n", &plist);//plist의 주소 출력
printf("plist= %p\n", plist);//plist의 주소 출력
printf("plist[0]= %p\n", plist[0]);//plist가 가지고 있는 주소출력
printf("plist[1]= %p\n", plist[1]);//null값
printf("plist[2]= %p\n", plist[2]);//null값
printf("plist[3]= %p\n", plist[3]);//null값
printf("plist[4]= %p\n", plist[4]);//null값

free(plist[0]);
}
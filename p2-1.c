#include <stdio.h>
#define MAX_SIZE 100

float sum(float [], int);
float input[MAX_SIZE], answer;
int i;
void main(void)
{
    printf("[----- [조민재] [2019038045] -----]\n");
for(i=0; i < MAX_SIZE; i++)//100번 반복하는 반복문이다
input[i] = i;//배열 전체를 복사하는 것이아니라 주소값을 가져오는 것이다.
/* for checking call by reference*/
printf("address of input = %p\n", input);//호출 시 input은 주소를 담고 있다.

answer = sum(input, MAX_SIZE);//주소를 sum함수의 list에 복사한다
printf("The sum is: %f\n", answer);//반환해준 tempsum값을 출력해준다.
}
float sum(float list[], int n)//list는 call by reference, input의 주소를 list가 받아 input 배열을 list를 통해 접근한다.
{

printf("value of list = %p\n", list);
printf("address of list = %p\n\n", &list);

int i;
float tempsum = 0;
for(i = 0; i < n; i++)
tempsum += list[i];//n은 call by value, 값을 그대로 변수n에 복사 n이 변경되도 caller의 값은 변하지 않음
return tempsum;
}
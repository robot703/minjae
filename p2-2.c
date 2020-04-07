#include <stdio.h>
void print1 (int *ptr, int rows);
int main()
{
    printf("[----- [조민재] [2019038045] -----]\n");
int one[] = {0, 1, 2, 3, 4};//배열을 초기화 해줌
printf("one= %p\n", one);//one[0]의 첫번째 주소
printf("&one= %p\n", &one);//one[0]의 첫번째 주소
printf("&one[0]%p\n", &one[0]);//one[0]의 첫번째 주소
printf("\n");
print1(&one[0], 5);//매개변수
return 0;
}

void print1 (int *ptr, int rows)//main함수에서 매개변수의 값을 받아서 카운트할 때마다 주소의 끝자리변화을 알아보는 함수
{/* print out a one-dimensional array using a potnter */
int i;
printf ("Address \t Contents\n");//카운트하는 숫자가 0~4까지 늘어나면서 주소의 끝자리가 4씩 커지는 것을 볼 수 있다..
for (i = 0; i < rows; i++)
printf("%p \t %5d\n", ptr + i, *(ptr + i));
printf("\n");
}
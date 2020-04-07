#include<stdio.h>

struct student1 {//student1 구조체
    char lastName;
    int studentId;
    char grade;
};

typedef struct {//typedef student2구조체
char lastName;
int studentId;
char grade;
 } student2;

int main() {
    printf("[----- [조민재] [2019038045] -----]\n");
struct student1 st1 = {'A', 100, 'A'};//struct키워드를 넣어줘야한다.

printf("st1.lastName = %c\n", st1.lastName);//st1구조체에서 lastname출력
printf("st1.studentId = %d\n", st1.studentId);//st1구조체에서 studentID출력
printf("st1.grade = %c\n", st1.grade);//st1구조체에서 grade출력

student2 st2 = {'B', 200, 'B'};//typedef을 써주면 앞에 stucrt키워드를 안넣어줘도된다.

printf("\nst2.lastName = %c\n", st2.lastName);//st2구조체에서 lastname출력
printf("st2.studentId = %d\n", st2.studentId);//st2구조체에서 studentID출력
printf("st2.grade %c\n", st2.grade);//st2구조체에서 grade출력

student2 st3;

st3 = st2;//구조 치환

printf("\nst3.lastName = %c\n", st3. lastName);//구조체3번에 구조체2번을 넣어줬기 때문에 같은결과가 출력된다.
printf("st3.studentId = %d\n", st3.studentId);
printf("st3.grade %c\n", st3.grade);
/* equality test "/
if(st3 ==
printf("equal\n");
else
printf("not equal\n");
*/
return 0;
}
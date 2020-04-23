/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20


typedef enum {//우선순위를 지정해준다.
	lparen = 0,  //( 왼쪽 괄호 
	rparen = 9,  // ) 오른쪽 괄호
	times = 7,  // *곱셈 
	divide = 6,  // /나눗셈 
	plus = 5,   // + 덧셈 
	minus = 4, // - 뺄셈 
	operand = 1 // 피연산자 
} precedence;


char infixExp[MAX_EXPRESSION_SIZE]; //중위표기법을 저장하는 배열  	
char postfixExp[MAX_EXPRESSION_SIZE];//후위표기법을 저장하는 배열
char postfixStack[MAX_STACK_SIZE];	//후위표기로 변환할 때 사용하는 스택
int evalStack[MAX_STACK_SIZE];		//연산하는데 쓰이는 스택

int postfixStackTop = -1;  //후위표기 스택의 탑을 -1로 초기화
int evalStackTop = -1;	   //연산하는 스택의 탑을 -1로 초기화

int evalResult = 0;	   //계산결과저장 변수

void postfixPush(char x)//후위표시스택에 하나씩 추가
{
	postfixStack[++postfixStackTop] = x;//후위표기스택 배열의 탑을 추가하고 x의 값을 저장한다.
}

char postfixPop()//후위표시스택에서 하나씩 빼줌
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];//후위표기스택 배열의 탑을 줄이고 x에 저장한다.
	}
	return x;
}


void evalPush(int x)//연산 스택에 하나씩 추가
{
	evalStack[++evalStackTop] = x;//연산 스택 배열의 탑을 추가하고 x의 값을 저장한다.
}

int evalPop()//연산 스택에서 하나씩 빼줌
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];//연산 스택 배열의 탑을 줄이고 x에 저장한다.
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

precedence getToken(char symbol)
{
	switch (symbol) {
	case '(': return lparen;//토큰마다 앞서 우선순위를 정해준 알맞은 변수를 반환
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;//토큰마다 앞서 우선순위를 정해준 알맞은 변수를 반환
	}

}

precedence getPriority(char x)//우선순위를 지정해준다
{
	return getToken(x);//토큰들을 입력받는다.
}


void charCat(char* c)
{
	if (postfixExp == '\0')//후위표기법 배열이 비어있다면
		strncpy(postfixExp, c, 1);//기존문자를 1만큼 후위표기법배열에 복사한다.
	else
		strncat(postfixExp, c, 1);//기존문자뒤에 후위표기법배열 1만큼 이어준다.
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x;/* 문자하나를 임시로 저장하기 위한 변수 */
	precedence token = getToken(*exp);//입력받은 토큰을 우선순위토큰에 저장한다.

	/*토큰이 null값이 나올때까지 글자 하나씩 받는 반복문*/
	for (token = getToken(*exp); token != '\0'; token = getToken(*exp))
	{
		if (token == operand)//토큰이 피연산자 경우
			charCat(exp);//문자하나를 charCat함수로 전달
		else if (token == lparen)//토큰이 '(' 인 경우
		{
			while (postfixStack[postfixStackTop] != rparen)//토큰이 ')' 가 나올 때까지반복
				x = postfixPop();
			charCat(&x);
		}
		else if (token == rparen)
		{
			while (postfixStack[postfixStackTop] != lparen)//토큰이 '(' 가 나올 때까지반복
				x = postfixPop();
			charCat(&x);
		}
		else
		{
			if (postfixStack[postfixStackTop] >= getPriority(*exp)) {//새로운 연산자의 우선순위가 큰거나 같은경우
				x = postfixPop();
				charCat(&x);
			}
			else if (postfixStack[postfixStackTop] < getPriority(*exp))//연산자의 우선순위가 큰경우 
				postfixPush(*exp);//postfixStack저장

		}
		while (postfixStackTop != -1)
		{
			x = postfixPop();
			charCat(&x);
		}

	}
}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

int evaluation()
{
	precedence token;
	char *exp;
	int op1, op2;
	/* postfixExp, evalStack을 이용한 계산 */
	token = getToken(*exp); /* postExp의 문자 하나씩을 읽기위한 포인터 */
	while (token != '\0') {//null값이 나올 때까지 반복
		if (token == operand)//피연산자면 우선순위 토큰에 저장
			evalPush(*exp - '0');
		else {
			op2 = evalPop();
			op1 = evalPop();
			switch (token) {
			case plus: evalPush(op1 + op2);
				break;
			case minus: evalPush(op1 - op2);
				break;
			case divide: evalPush(op1 / op2);
				break;
			case times: evalPush(op1 * op2);
				break;
			}
		}
		token = getToken(*exp);
	}
	evalResult = evalPop();//결과
}


int main()
{

	char command;
    printf("[---- - [조민재][2019038045] ---- - ]");

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 0;


}
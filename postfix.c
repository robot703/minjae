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


typedef enum {//�켱������ �������ش�.
	lparen = 0,  //( ���� ��ȣ 
	rparen = 9,  // ) ������ ��ȣ
	times = 7,  // *���� 
	divide = 6,  // /������ 
	plus = 5,   // + ���� 
	minus = 4, // - ���� 
	operand = 1 // �ǿ����� 
} precedence;


char infixExp[MAX_EXPRESSION_SIZE]; //����ǥ����� �����ϴ� �迭  	
char postfixExp[MAX_EXPRESSION_SIZE];//����ǥ����� �����ϴ� �迭
char postfixStack[MAX_STACK_SIZE];	//����ǥ��� ��ȯ�� �� ����ϴ� ����
int evalStack[MAX_STACK_SIZE];		//�����ϴµ� ���̴� ����

int postfixStackTop = -1;  //����ǥ�� ������ ž�� -1�� �ʱ�ȭ
int evalStackTop = -1;	   //�����ϴ� ������ ž�� -1�� �ʱ�ȭ

int evalResult = 0;	   //��������� ����

void postfixPush(char x)//����ǥ�ý��ÿ� �ϳ��� �߰�
{
	postfixStack[++postfixStackTop] = x;//����ǥ�⽺�� �迭�� ž�� �߰��ϰ� x�� ���� �����Ѵ�.
}

char postfixPop()//����ǥ�ý��ÿ��� �ϳ��� ����
{
	char x;
	if (postfixStackTop == -1)
		return '\0';
	else {
		x = postfixStack[postfixStackTop--];//����ǥ�⽺�� �迭�� ž�� ���̰� x�� �����Ѵ�.
	}
	return x;
}


void evalPush(int x)//���� ���ÿ� �ϳ��� �߰�
{
	evalStack[++evalStackTop] = x;//���� ���� �迭�� ž�� �߰��ϰ� x�� ���� �����Ѵ�.
}

int evalPop()//���� ���ÿ��� �ϳ��� ����
{
	if (evalStackTop == -1)
		return -1;
	else
		return evalStack[evalStackTop--];//���� ���� �迭�� ž�� ���̰� x�� �����Ѵ�.
}


/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

precedence getToken(char symbol)
{
	switch (symbol) {
	case '(': return lparen;//��ū���� �ռ� �켱������ ������ �˸��� ������ ��ȯ
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;//��ū���� �ռ� �켱������ ������ �˸��� ������ ��ȯ
	}

}

precedence getPriority(char x)//�켱������ �������ش�
{
	return getToken(x);//��ū���� �Է¹޴´�.
}


void charCat(char* c)
{
	if (postfixExp == '\0')//����ǥ��� �迭�� ����ִٸ�
		strncpy(postfixExp, c, 1);//�������ڸ� 1��ŭ ����ǥ����迭�� �����Ѵ�.
	else
		strncat(postfixExp, c, 1);//�������ڵڿ� ����ǥ����迭 1��ŭ �̾��ش�.
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x;/* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */
	precedence token = getToken(*exp);//�Է¹��� ��ū�� �켱������ū�� �����Ѵ�.

	/*��ū�� null���� ���ö����� ���� �ϳ��� �޴� �ݺ���*/
	for (token = getToken(*exp); token != '\0'; token = getToken(*exp))
	{
		if (token == operand)//��ū�� �ǿ����� ���
			charCat(exp);//�����ϳ��� charCat�Լ��� ����
		else if (token == lparen)//��ū�� '(' �� ���
		{
			while (postfixStack[postfixStackTop] != rparen)//��ū�� ')' �� ���� �������ݺ�
				x = postfixPop();
			charCat(&x);
		}
		else if (token == rparen)
		{
			while (postfixStack[postfixStackTop] != lparen)//��ū�� '(' �� ���� �������ݺ�
				x = postfixPop();
			charCat(&x);
		}
		else
		{
			if (postfixStack[postfixStackTop] >= getPriority(*exp)) {//���ο� �������� �켱������ ū�ų� �������
				x = postfixPop();
				charCat(&x);
			}
			else if (postfixStack[postfixStackTop] < getPriority(*exp))//�������� �켱������ ū��� 
				postfixPush(*exp);//postfixStack����

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
	/* postfixExp, evalStack�� �̿��� ��� */
	token = getToken(*exp); /* postExp�� ���� �ϳ����� �б����� ������ */
	while (token != '\0') {//null���� ���� ������ �ݺ�
		if (token == operand)//�ǿ����ڸ� �켱���� ��ū�� ����
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
	evalResult = evalPop();//���
}


int main()
{

	char command;
    printf("[---- - [������][2019038045] ---- - ]");

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
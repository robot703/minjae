#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct{
	element queue[MAX_QUEUE_SIZE];//queue�迭�� ��������
	int front, rear;//�迭�� ��,�ڸ� ��Ÿ���ִ� ������
}QueueType;//����ü�� Ī�ϴ� �̸�

QueueType *createQueue();//�����Ҵ����ִ� �Լ�
int freeQueue(QueueType *cQ);//���������� ���ִ� �Լ�
int isEmpty(QueueType *cQ);//�迭�� ����ִ��� Ȯ�����ִ� �Լ�
int isFull(QueueType *cQ);//�迭�� ���� ���ִ��� Ȯ�����ִ� �Լ�
void enQueue(QueueType *cQ, element item);//item�� ������� �Է¹޴� �Լ�
void deQueue(QueueType *cQ, element* item);//item�� ���� ������� �����ϴ� �Լ�
void printQ(QueueType *cQ);//������ִ� �Լ�
void debugQ(QueueType *cQ);//�迭�� ���� ���¸� �����ִ� �Լ�

int freeQueue(QueueType *cQ)
{
	if (cQ == NULL) return 1;//cQ�� null�� ��� ��������
		free(cQ);
		return 1;
}

element getElement();//�ʱ⿡ �Է��� �޴´�.item�� �Է¹޴´�.

int main(void)
{
	printf("[---- - [������][2019038045] ---- - ]");

		QueueType *cQ = createQueue();//cQ��  �����Ҵ� ���ش�.
		element data;
	
		char command;//�Է� �޴� ���ĺ��� ����

		do {
			printf("\n------------------------------------------------------- \n");
			printf("                       Circular Q                         \n");
			printf("----------------------------------------------------------\n");
			printf(" Insert=i,  Delete=d,  PrintQ = p,  Debug = b,  Quit = q  \n");
			printf("----------------------------------------------------------\n");

			printf("Command = ");
			scanf(" %c", &command);//�޴������ �Է¹޴´�.

			switch (command) {
			case 'i': case 'I'://i,I�� ���
				data = getElement();//�Է¹޴� ������ �Լ� ȣ��
				enQueue(cQ, data);//�߰����ִ� �Լ� ���
				break;

			case 'd': case 'D'://d,D�� ���
				deQueue(cQ, &data);//���� �Լ� ȣ��
				break;
			case 'p': case 'P'://p,P�� ���
				printQ(cQ);//����Ʈ �Լ� ȣ��
				break;
			case 'b': case 'B'://b,B�� ���
				debugQ(cQ);//����� �Լ� ȣ��
				break;
			case 'q': case 'Q'://q,Q�� ���
				freeQueue(cQ);//�Ҵ� �����Լ� ȣ��
				break;

			default:
				printf("        >>>>>   Concentration!!   <<<<<       \n\n");
				break;
			}

		}while (command != 'q' && command != 'Q');//

			return 1;
}
						
		QueueType *createQueue()//�����Ҵ� ���ִ� �Լ�
		{
			QueueType *cQ;//������ ���� ����
			cQ = (QueueType *)malloc(sizeof(QueueType));//malloc���� �����Ҵ��� ���ش�.
			cQ->front = 0;//�ʱ�ȭ���ش�.
			cQ->rear = 0;//�ʱ�ȭ���ش�
			return cQ;
		}

		element getElement()//����ť�ȿ� ���� ���ڸ� �Է¹޴� �Լ�
		{
			element item;
			printf("Input element = ");
			scanf(" %c", &item);
			return item;
		}
			/* complete the function */
		int isEmpty(QueueType *cQ)//���� ť�� ������� �ִ��� Ȯ�����ִ� �Լ�
		{
			if (cQ->rear == cQ->front)//rear�ϰ�front�� �������� ���� ���� ���ڰ� ���� �Ҹ��̴�.
			{
				printf("ť�� ����ֽ��ϴ�.");
				return 1;
			}
			else return 0;
			
		}

		/* complete the function */
		int isFull(QueueType *cQ)//���� ť�� ������ ���ִ� �� �˷��ִ� �Լ�
		{
			if ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front)//rear�� ���� �ּҰ� front�� ���� ��� ���� ���� ť ���ִٴ� �Ҹ��̴�.
			{
				printf("ť�� ���� ���ֽ��ϴ�.");
				return 1;
			}
		   else return 0;
		}

		/* complete the function */
		void enQueue(QueueType *cQ, element item)//���� ť�� �����͸� �Է¹޴� �Լ��̴�.
		{
			if (isFull(cQ))//���� ť�� �������ִ��� Ȯ�����ش�.
			{
				printf("ť�� ���� á���ϴ�");
			}
			else
			{
				cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;//������ �������ּҸ� ������ �ּ�+1�� �ٲ��ش�.
				cQ->queue[cQ->rear] = item;//�Է¹��� �����͸� ������ �ּ�+1�� �ٰ� �������ش�.
			}
		}
			/* complete the function */
		void deQueue(QueueType *cQ, element *item)//�Է¹��� �����͸� �������ִ� �Լ��̴�.
		{
			if (isEmpty(cQ)) //���� ť�� ����ִ��� Ȯ���ؼ� ������ ������ �������� Ȯ�����ش�.
            {
				printf("ť�� ����ֽ��ϴ�.\n");
			}
			else 
				*item = cQ->queue[cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE];/*������ front �ּҸ� front �ٷξ��� �ּҷ� �ٲ��ְ�, 
                front+1 �ּҸ� ������ item���� �־��ָ� item�� ���� �ּҾ��� ���� �����ϰ� �ȴ�.*/
			return;
		}
		
		void printQ(QueueType *cQ)
		{
			int i, first, last;

			first = (cQ->front + 1) % MAX_QUEUE_SIZE;
			last = (cQ->rear + 1) % MAX_QUEUE_SIZE;

			printf("Circular Queue : [");

			i = first;
			while (i != last) {
				printf("%3c", cQ->queue[i]);
				i = (i + 1) % MAX_QUEUE_SIZE;
			}
			printf(" ]\n");	
		}
		void debugQ(QueueType *cQ)
		{
			printf("\n---DEBUG\n");
			for (int i = 0; i < MAX_QUEUE_SIZE; i++)
			{
				if (i == cQ->front)
				{
					printf(" [%d] = front\n", i);
					continue;
				}
				printf(" [%d] = %c\n", i, cQ->queue[i]);
			}
			printf("front = %d, rear= %d\n", cQ->front, cQ->rear);
		}
			 
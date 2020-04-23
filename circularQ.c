#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct{
	element queue[MAX_QUEUE_SIZE];//queue배열을 선언해줌
	int front, rear;//배열의 앞,뒤를 나타내주는 변수들
}QueueType;//구조체를 칭하는 이름

QueueType *createQueue();//동적할당해주는 함수
int freeQueue(QueueType *cQ);//동적해제를 해주는 함수
int isEmpty(QueueType *cQ);//배열이 비어있는지 확인해주는 함수
int isFull(QueueType *cQ);//배열이 가득 차있는지 확인해주는 함수
void enQueue(QueueType *cQ, element item);//item을 순서대로 입력받는 함수
void deQueue(QueueType *cQ, element* item);//item을 들어온 순서대로 삭제하는 함수
void printQ(QueueType *cQ);//출력해주는 함수
void debugQ(QueueType *cQ);//배열을 현재 상태를 보여주는 함수

int freeQueue(QueueType *cQ)
{
	if (cQ == NULL) return 1;//cQ가 null인 경우 동적해제
		free(cQ);
		return 1;
}

element getElement();//초기에 입력을 받는다.item을 입력받는다.

int main(void)
{
	printf("[---- - [조민재][2019038045] ---- - ]");

		QueueType *cQ = createQueue();//cQ를  동적할당 해준다.
		element data;
	
		char command;//입력 받는 알파벳들 변수

		do {
			printf("\n------------------------------------------------------- \n");
			printf("                       Circular Q                         \n");
			printf("----------------------------------------------------------\n");
			printf(" Insert=i,  Delete=d,  PrintQ = p,  Debug = b,  Quit = q  \n");
			printf("----------------------------------------------------------\n");

			printf("Command = ");
			scanf(" %c", &command);//메뉴얼들을 입력받는다.

			switch (command) {
			case 'i': case 'I'://i,I일 경우
				data = getElement();//입력받는 데이터 함수 호출
				enQueue(cQ, data);//추가해주는 함수 출력
				break;

			case 'd': case 'D'://d,D일 경우
				deQueue(cQ, &data);//삭제 함수 호출
				break;
			case 'p': case 'P'://p,P일 경우
				printQ(cQ);//프린트 함수 호출
				break;
			case 'b': case 'B'://b,B일 경우
				debugQ(cQ);//디버그 함수 호출
				break;
			case 'q': case 'Q'://q,Q일 경우
				freeQueue(cQ);//할당 해제함수 호출
				break;

			default:
				printf("        >>>>>   Concentration!!   <<<<<       \n\n");
				break;
			}

		}while (command != 'q' && command != 'Q');//

			return 1;
}
						
		QueueType *createQueue()//동적할당 해주는 함수
		{
			QueueType *cQ;//포인터 변수 선언
			cQ = (QueueType *)malloc(sizeof(QueueType));//malloc으로 동적할당을 해준다.
			cQ->front = 0;//초기화해준다.
			cQ->rear = 0;//초기화해준다
			return cQ;
		}

		element getElement()//원형큐안에 넣을 문자를 입력받는 함수
		{
			element item;
			printf("Input element = ");
			scanf(" %c", &item);
			return item;
		}
			/* complete the function */
		int isEmpty(QueueType *cQ)//원형 큐에 빈공간이 있는지 확인해주는 함수
		{
			if (cQ->rear == cQ->front)//rear하고front가 같은것은 아직 들어온 문자가 없는 소리이다.
			{
				printf("큐가 비어있습니다.");
				return 1;
			}
			else return 0;
			
		}

		/* complete the function */
		int isFull(QueueType *cQ)//원형 큐에 공간이 차있는 지 알려주는 함수
		{
			if ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front)//rear의 다음 주소가 front랑 같을 경우 가득 원형 큐 차있다는 소리이다.
			{
				printf("큐가 가득 차있습니다.");
				return 1;
			}
		   else return 0;
		}

		/* complete the function */
		void enQueue(QueueType *cQ, element item)//원형 큐에 데이터를 입력받는 함수이다.
		{
			if (isFull(cQ))//먼저 큐가 가득차있는지 확인해준다.
			{
				printf("큐가 가득 찼습니다");
			}
			else
			{
				cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;//기존의 마지막주소를 마지막 주소+1로 바꿔준다.
				cQ->queue[cQ->rear] = item;//입력받은 데이터를 마지막 주소+1에 다가 저장해준다.
			}
		}
			/* complete the function */
		void deQueue(QueueType *cQ, element *item)//입력받은 데이터를 삭제해주는 함수이다.
		{
			if (isEmpty(cQ)) //먼저 큐가 비어있는지 확인해서 삭제가 가능한 상태인지 확인해준다.
            {
				printf("큐가 비어있습니다.\n");
			}
			else 
				*item = cQ->queue[cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE];/*기존의 front 주소를 front 바로앞의 주소로 바꿔주고, 
                front+1 주소를 포인터 item으로 넣어주면 item은 받은 주소안의 값을 참조하게 된다.*/
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
			 
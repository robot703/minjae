#include <stdio.h>
#include<stdlib.h>
#define MAX_VERTEX 20 /* you can change value 20 */

typedef struct Vertex {
	int num; /* vertex number */
	struct Vertex* link; /* link to a next adjacent vertext */
} Vertex;
typedef struct VertexHead {
	int num_members;
	Vertex* tail;
	Vertex* head; /* linked list of all adjacent vertices */
} VertexHead;
typedef struct Graph {
	int num_vertices;
	VertexHead* vlist; /* list of all vertices: vlist[MAX_VERTEX] */
} Graph;


int arr[MAX_VERTEX] = { 0 };
#define FALSE 0
#define TRUE 1
short int visited[MAX_VERTEX];
typedef struct stackNode//스택연산 
{
	int data;
	struct stackNode *link;
}stackNode;

stackNode* top;

void push(int item)
{
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
	temp->data = item;
	temp->link = top;
	top = temp;
}



int pop()
{
	int item;
	stackNode* temp = top;

	if (top == NULL)
	{
		printf("\n\n Stack is empty !\n");
		return 0;
	}
	else
	{
		item = temp->data;
		top = temp->link;
		free(temp);
		return item;
	}
}


typedef struct QNode//큐연산 구조체
{
	int data;
	struct QNode *link;
}QNode;

typedef struct
{
	QNode *front, *rear;
}LQueueType;
void enQueue(LQueueType *LQ, int item);
int deQueue(LQueueType *LQ);



Graph* createGraph(int n); /* empty graph creation */
void destroyGraph(VertexHead ** graph); /* deallocating all allocated memory */
void insertVertex(VertexHead*h, int num); /* vertex insertion */
void deleteVertex(VertexHead *h, int num); /* vertex deletion */
void insertEdge(Graph *graph, int scr, int dest); /* new edge creation between two vertices */
int deleteEdge(VertexHead *h, int src, int dest); /* edge removal */
void depthFS(VertexHead* g, int v); /* depth firt search using stack */
void breadthFS(VertexHead* g, int v);/* breadth head search using queue */
void printGraph(Graph*graph); /* printing graph with vertices and edges */
Vertex*createNode(int v);
int main()
{
	char command;
	int num;
	VertexHead* vertexhead = (VertexHead*)malloc(sizeof(MAX_VERTEX));
	Graph* vlist = (Graph*)malloc(sizeof(MAX_VERTEX));
	VertexHead *head = (VertexHead*)malloc(sizeof(MAX_VERTEX));
	Vertex*h = NULL;
	int scr;
	int dest;
	int scr1;
	int dest1;
	int n = 0;
	int x, y;
	do {
		printf("2019038045 조민재\n");
		printf("----------------------------------------------------------------\n");
		printf("                            Graph                               \n");
		printf("----------------------------------------------------------------\n");
		printf(" createGraph      = z          destroyGraph    = a\n");
		printf(" deleteVertex     = i          breadthFS       = e\n");
		printf(" insertVertex     = b          deleteEdge      = l\n");
		printf(" insertEdge       = k          printGraph      = p\n");
		printf(" depthFS          = h          Quit            = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			createGraph(MAX_VERTEX);
			break;
		case 'a': case 'A':
			destroyGraph(&vertexhead);
			break;
		case 'i': case 'I':
			printf("Your num = ");
			scanf("%d", &num);
			deleteVertex(vertexhead, num);
			break;
		case 'b': case 'B':
			printf("Your num = ");
			scanf("%d", &num);
			insertVertex(vertexhead, num);
			break;
		case 'l': case 'L':
			printf("Your num1 = ");
			scanf("%d", &scr1);
			printf("Your num2 = ");
			scanf("%d", &dest1);
			deleteEdge(vertexhead, scr1, dest1);
			break;
		case 'k': case 'K':
			printf("Your num1 = ");
			scanf("%d", &scr);
			printf("Your num2 = ");
			scanf("%d", &dest);
			insertEdge(vlist, scr, dest);
			break;
		case 'h': case 'H':
			printf("Your num = ");
			scanf("%d", &x);
			depthFS(vertexhead,x);
			break;
		case 'e': case 'E':
			printf("Your num = ");
			scanf("%d", &y);
			breadthFS(vertexhead,y);
			break;
		case 'p': case 'P':
			printGraph(vlist);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

Graph* createGraph(int n) {

	Graph * graph = (Graph *)malloc(sizeof(MAX_VERTEX));//MAXVERTEX만큼 동적할당
	Graph* num_vertices = NULL;
	graph->num_vertices = n;//정점의 개수를 초기화
	graph->vlist = (VertexHead *)malloc(n * sizeof(MAX_VERTEX));

	// malloc 생성 후엔 꼭 초기화
	for (int i = 0; i < n; i++)
	{
		graph->vlist[i].head = graph->vlist[i].tail = NULL;//배열과 정점의 개수를 초기화
		
	}

	return graph;
}
Vertex*createNode(int v)//인접노드 리스트 생성함수
{
	Vertex * newNode = (Vertex *)malloc(sizeof(Vertex));//mallloc을 이용하여 초기화
	newNode->num = v; // 정점(MAX_VERTEX)
	newNode->link = NULL;//malloc할 시에 항상 값들을 초기화
	return newNode;//반환
}


void destroyGraph(VertexHead ** graph) { /* deallocating all allocated memory */
	if (*graph)//그래프가 있는 경우
	{
		if ((*graph)->head)//그래프 구조체의 vlist가 있는 경우
		{
			for (int v = 0; v < MAX_VERTEX; v++)//MAX_VERTEX만큼 반복
			{
				Vertex * adjListPtr = (*graph)->head[v].link;//vlist에 저장되었있는head들을 하나씩 불러옴
				while (adjListPtr)//adjListPtr이 아닐 때까지
				{
					Vertex * tmp = adjListPtr;//tmp에 adjListPtr를 넣어줌,
					adjListPtr = adjListPtr->link;//다음링크로 이동
					free(tmp);//해제
				}

				free((*graph)->head);//해제
			}
			free(*graph);//해제
		}
		else
		{
			printf("없애줄 그래프가 없습니다.\n");
		}
	}
}
void insertVertex(VertexHead*h, int num) { /* vertex insertion */

	num++;
	int i;
	
	if (arr[num ] == 0) {
		arr[num ] = num;
	}
	else if (arr[num ] == num) {
		printf("이미존재합니다.\n");
	}
}

void deleteVertex(VertexHead *h, int num) { /* vertex deletion */

}

void insertEdge(Graph *graph, int src, int dest) { /* new edge creation between two vertices */

	Vertex * newNode = createNode(dest);//인접노드 src를 추가해준다.
	// 인접노드가 존재 할 경우, tail에 삽입, tail은 새로운 노드를 가리키도록 한다.
	if (graph->vlist[src].tail != NULL)
	{
		graph->vlist[src].tail->link = newNode;//마지막 링크인 tail의 링크에 새로운 노드를 넣어준다.
		graph->vlist[src].tail = newNode;
	}
	else // 첫번째 인접 노드일 경우
	{
		graph->vlist[src].head = graph->vlist[src].tail = newNode;//head노드애 넣어준다.
	}
	graph->vlist[src].num_members++;


	
	newNode = createNode(src);//인접노드 dest를 추가해준다.
	// 인접노드가 존재 할 경우, tail에 삽입, tail은 새로운 노드를 가리키도록 한다.
	if (graph->vlist[dest].tail != NULL)
	{
		graph->vlist[dest].tail->link = newNode;//마지막 링크인 tail의 링크에 새로운 노드를 넣어준다.
		graph->vlist[dest].tail = newNode;
	}
	else// 첫번째 인접 노드일 경우
	{
		graph->vlist[dest].head = graph->vlist[dest].tail = newNode;//head노드애 넣어준다.
	}
}

int deleteEdge(VertexHead *h, int src, int dest) { /* edge removal */
	Vertex* tmp = h[src].head;//head의 주소를 tmp에 넣어줌
	Vertex* pre;

	if (h[src].head == NULL)//만약에 배열이 NULL인경우
		return 0;

	if (tmp->num == src|| tmp->num == dest) {//사용자가 입력한 숫자와 같은경우
		h->head = tmp->link;
		free(tmp);
		return 0;
	}
	while (tmp->link != NULL)//마지막이 NULLL이 나올 때까지
	{
		if (tmp->num == src|| tmp->num == dest)
		{
			Vertex* del = tmp->link;
			if (del->link != NULL)
				tmp->link = del->link;
			else
				tmp->link = NULL;
			free(del);
			return 0;
		}
		tmp = tmp->link;
	}
}

void depthFS(VertexHead* g,int v) {
 

}/* depth firt search using stack */
void breadthFS(VertexHead* g, int v) {

}/* breadth head search using queue */

void printGraph(Graph*graph) {
	
	/*그래프의 인접노드 리스트 배열을 for문을 통해 탐색하여 각각 인접리스트 포인터가 
	NULL일 경우까지 탐색하여 출력한다.*/
	for (int i = 0; i < MAX_VERTEX; i++) {
		Vertex * adjListPtr = graph->vlist[i].head;
		printf("vertex [%d] ", i);
		while (adjListPtr)//인접노드 포인터가 NULL일 경우까지 탐색
		{
			printf(" -> 인접노드 : %d ", adjListPtr->num);
			adjListPtr = adjListPtr->link;
		}
		printf("\n");
	}
}

int isEmpty(LQueueType *LQ)
{
	if (LQ->front == NULL)
	{
		printf("\n Linked Queue is empty! \n");
		return 1;
	}
	else
		return 0;
}



void enQueue(LQueueType *LQ, int item)
{
	QNode* newNode = (QNode*)malloc(sizeof(QNode));
	newNode->data = item;
	newNode->link = NULL;

	if (LQ->front == NULL)
	{
		LQ->front = newNode;
		LQ->rear = newNode;
	}
	else
	{
		LQ->rear->link = newNode;
		LQ->rear = newNode;
	}
}


int deQueue(LQueueType *LQ)
{
	QNode* old = LQ->front;
	int item;
	if (isEmpty(LQ))
		return 0;
	else
	{
		item = old->data;
		LQ->front = LQ->front->link;

		if (LQ->front == NULL)
			LQ->rear = NULL;
		free(old);
		return item;
	}
}


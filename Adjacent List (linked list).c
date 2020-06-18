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
typedef struct stackNode//���ÿ��� 
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


typedef struct QNode//ť���� ����ü
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
		printf("2019038045 ������\n");
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

	Graph * graph = (Graph *)malloc(sizeof(MAX_VERTEX));//MAXVERTEX��ŭ �����Ҵ�
	Graph* num_vertices = NULL;
	graph->num_vertices = n;//������ ������ �ʱ�ȭ
	graph->vlist = (VertexHead *)malloc(n * sizeof(MAX_VERTEX));

	// malloc ���� �Ŀ� �� �ʱ�ȭ
	for (int i = 0; i < n; i++)
	{
		graph->vlist[i].head = graph->vlist[i].tail = NULL;//�迭�� ������ ������ �ʱ�ȭ
		
	}

	return graph;
}
Vertex*createNode(int v)//������� ����Ʈ �����Լ�
{
	Vertex * newNode = (Vertex *)malloc(sizeof(Vertex));//mallloc�� �̿��Ͽ� �ʱ�ȭ
	newNode->num = v; // ����(MAX_VERTEX)
	newNode->link = NULL;//malloc�� �ÿ� �׻� ������ �ʱ�ȭ
	return newNode;//��ȯ
}


void destroyGraph(VertexHead ** graph) { /* deallocating all allocated memory */
	if (*graph)//�׷����� �ִ� ���
	{
		if ((*graph)->head)//�׷��� ����ü�� vlist�� �ִ� ���
		{
			for (int v = 0; v < MAX_VERTEX; v++)//MAX_VERTEX��ŭ �ݺ�
			{
				Vertex * adjListPtr = (*graph)->head[v].link;//vlist�� ����Ǿ��ִ�head���� �ϳ��� �ҷ���
				while (adjListPtr)//adjListPtr�� �ƴ� ������
				{
					Vertex * tmp = adjListPtr;//tmp�� adjListPtr�� �־���,
					adjListPtr = adjListPtr->link;//������ũ�� �̵�
					free(tmp);//����
				}

				free((*graph)->head);//����
			}
			free(*graph);//����
		}
		else
		{
			printf("������ �׷����� �����ϴ�.\n");
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
		printf("�̹������մϴ�.\n");
	}
}

void deleteVertex(VertexHead *h, int num) { /* vertex deletion */

}

void insertEdge(Graph *graph, int src, int dest) { /* new edge creation between two vertices */

	Vertex * newNode = createNode(dest);//������� src�� �߰����ش�.
	// ������尡 ���� �� ���, tail�� ����, tail�� ���ο� ��带 ����Ű���� �Ѵ�.
	if (graph->vlist[src].tail != NULL)
	{
		graph->vlist[src].tail->link = newNode;//������ ��ũ�� tail�� ��ũ�� ���ο� ��带 �־��ش�.
		graph->vlist[src].tail = newNode;
	}
	else // ù��° ���� ����� ���
	{
		graph->vlist[src].head = graph->vlist[src].tail = newNode;//head���� �־��ش�.
	}
	graph->vlist[src].num_members++;


	
	newNode = createNode(src);//������� dest�� �߰����ش�.
	// ������尡 ���� �� ���, tail�� ����, tail�� ���ο� ��带 ����Ű���� �Ѵ�.
	if (graph->vlist[dest].tail != NULL)
	{
		graph->vlist[dest].tail->link = newNode;//������ ��ũ�� tail�� ��ũ�� ���ο� ��带 �־��ش�.
		graph->vlist[dest].tail = newNode;
	}
	else// ù��° ���� ����� ���
	{
		graph->vlist[dest].head = graph->vlist[dest].tail = newNode;//head���� �־��ش�.
	}
}

int deleteEdge(VertexHead *h, int src, int dest) { /* edge removal */
	Vertex* tmp = h[src].head;//head�� �ּҸ� tmp�� �־���
	Vertex* pre;

	if (h[src].head == NULL)//���࿡ �迭�� NULL�ΰ��
		return 0;

	if (tmp->num == src|| tmp->num == dest) {//����ڰ� �Է��� ���ڿ� �������
		h->head = tmp->link;
		free(tmp);
		return 0;
	}
	while (tmp->link != NULL)//�������� NULLL�� ���� ������
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
	
	/*�׷����� ������� ����Ʈ �迭�� for���� ���� Ž���Ͽ� ���� ��������Ʈ �����Ͱ� 
	NULL�� ������ Ž���Ͽ� ����Ѵ�.*/
	for (int i = 0; i < MAX_VERTEX; i++) {
		Vertex * adjListPtr = graph->vlist[i].head;
		printf("vertex [%d] ", i);
		while (adjListPtr)//������� �����Ͱ� NULL�� ������ Ž��
		{
			printf(" -> ������� : %d ", adjListPtr->num);
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


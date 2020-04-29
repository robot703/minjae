/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 //필요한 헤더파일 추가 
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


//함수 리스트
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	printf(" 2019038045 조민재 \n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	//headnode가 null이 아니며니 freenode를 호출하여 할당된 메모리 모두 해제
	if (h != NULL)
		freeList(h);

	//headnode에 대한 메모리를 할당하여 리턴
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	//h와 연결된 listnode 메모리 해제
	//headnode도 해제되어야함
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



int insertFirst(headNode* h, int key) {
	//list처음에 key에 대한 노드 하나를 추가
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


//리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(headNode* h, int key) {
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));//새로운노드를 할당
	struct Node* pre = h->first;//노드 하나를 만들고 초기값을 h->first로해줌
	struct Node* cur = h->first;//노드 하나를 만들고 초기값을 h->first로해줌
	new_node->key = key;//만들어준 노드에 키값을 받는다
	new_node->link = NULL;//만들어준 노드의 다음 리스트를 NULL로 만들어준다

	if (h->first == NULL) {//맨처음이 NULL값인 경우
		h->first = new_node;//만들어준 노드를 첫번쨰에 넣어준다
		return 0;
	}
	while (cur != NULL)//cur이 NULL이되면 빠져나오는 반복문을 만들어준다.
	{
		if (cur->key >= key)//만약 기존의 키값이 입력한 키값보다 크거나 같은경우
		{
			if (cur == h->first) //기존의 노드가 맨 처음일 경우
			{	
				new_node->link = cur;//만들어준 노드의 링크가 기존노드를 향하게한다.
				h->first = new_node;// 맨처음에는 만들어준 노드를 너어준다.
			}

			else//아니면
			{
				new_node->link = pre->link;//만들어준 노드의 링크가 이전의 노드가 가리켰던 노드를 향하도록 정한다.
				pre->link = new_node;//기존의 노드를 만들어준 노드를 향하도록 해준다
			}
			return 0;
		}
		else
		{
			pre = cur;//전의 노드가 기존의 노드를 따라가도록 만들어준다
			cur = cur->link;//기존의 노드가 계속해서 앞의로 가줄 수 있도록 해준다.
		}
	}
	pre->link = new_node;//아무것도 찾지 못한경우 만들어준노드를 맨뒤로 보낸다.
	return 0;
}



//list에 key에 대한 노드 하나를 추가
int insertLast(headNode *h, int key) {
	struct Node* n_node = (struct Node*)malloc(sizeof(struct Node));//새로운 노드를 할당해준다.
	struct Node *last = h->first;//노드 하나를 만들고 초기값을 h->first로해줌

	n_node->key = key;//만들어준 노드에 키값을 받을 수 있도록 한다.
	n_node->link = NULL;//만들어준 노드의 링크는 NULL로 향하게 한다.

	if (h->first== NULL) {//맨처음에 아무것도 없을경우
		h->first = n_node;//바로 만들어준 노드를 넣어준다.
		return 0;
	}
	while (last->link != NULL) {//마지막노드의 링크가 NULL이 되떄까지 반복된다.
		last = last->link;//마지막 링크가 계속 마자막을 향해 갈 수 있도록 해준다.
	}

	
	last->link = n_node;// 마지막 링크에 마지막 값을 넣어준다.
	return 0;
}


//list의 첫번째 노드 삭제
int deleteFirst(headNode* h) {
	listNode* firstnode = h->first;//노드 하나를 만들고 초기값을 h->first로해줌
	h->first = firstnode->link;//처음을 가리키던 링크를 만들어준 노드의 링크로 바꿔준다.
	
	return 0;
}


//list에서 key 에 대한 노드 삭제
int deleteNode(headNode* h, int key) {
	listNode* tmp = h->first;//노드 하나를 만들고 초기값을 h->first로해줌
	listNode* pre;

	if (h->first == NULL)
		return 0;

	while (tmp->link != NULL)//현재 위치에서 다음노드의 값이 삭제할 수 있는지 확인하다.
	{
		if (tmp->link->key == key)//삭제하는 값인경우
		{
			listNode* del = tmp->link;//del노드를 선언해주고 해당 주소를 가지고 있는다.
			if (del->link != NULL)
				tmp->link = del->link;//현재위치를 del노드의 다음 주소값을 가진다.
			else
				tmp->link = NULL;
			free(del);//해제해준다.삭제해준다
			return 0;
		}
		tmp = tmp->link;
	}
}


//list의 마지막 노드 삭제
int deleteLast(headNode* h) {
	
	listNode* delNode;
	if (h->first == NULL) //빈 리스트인 경우 삭제할 노드가 없으므로 종료
		return 0; 
	if (h->first->link == NULL) { //리스트에 노드가 한 개인 경우
		free(h->first); //그 노드의 메모리 해제
		h->first = NULL;
		return 0;
	}
	
	else {
		listNode* pre;//리스트에 노드가 2개 이상인 경우
		pre = h->first;
		delNode = h->first->link;
		while (delNode->link != NULL) {
			pre = delNode;
			delNode = delNode->link;
		}
		free(delNode);
		pre->link = NULL;
	}
}


//리스트의 링크를 역순으로 재배치
int invertList(headNode *h) {
	listNode * cur=h->first, *pre=NULL , *qu= NULL;
//노드 하나를 만들고 초기값을 h->first로해줌
	while (cur != NULL)

	{//swap과 비슷한 것같다.
	qu = pre;
	pre = cur;
	cur = cur->link;
	pre->link = qu;
	
	}
	
	h->first = pre;
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
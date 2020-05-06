
/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	do {
        printf("2019038045 조민재");
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode);
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


int initialize(headNode** h) {
	
	if (*h != NULL)
		freeList(*h);
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	
	
	return 1;
}

int freeList(headNode* h) {
	//h와 연결된 listnode 메모리 해제
	//headnode도 해제되어야함
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
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
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	struct Node* n_node = (struct Node*)malloc(sizeof(struct Node));
	struct Node *last = h->first;

	n_node->key = key;
	n_node->rlink = NULL;

	if (h->first == NULL) {
		h->first = n_node;
		return 0;
	}
	while (last->rlink != NULL) {
		last = last->rlink;
	}


	last->rlink = n_node;

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* delNode;
	if (h->first == NULL)
		return 0;    //빈 리스트인 경우 삭제할 노드가 없으므로 종료
	if (h->first->rlink == NULL) {    //리스트에 노드가 한 개인 경우
		free(h->first);    //그 노드의 메모리 해제
		h->first = NULL;
		return 0;
	}

	else {
		listNode* pre;               //리스트에 노드가 2개 이상인 경우
		pre = h->first;
		delNode = h->first->rlink;
		while (delNode->rlink != NULL) {
			pre = delNode;
			delNode = delNode->rlink;
		}
		free(delNode);
		pre->rlink = NULL;
	}

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	
	
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;
	node->rlink = h->first;
	node->llink = NULL;
	h->first = node;
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode* firstnode = h->first;
	h->first = firstnode->rlink;
	free(firstnode);
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode * cur = h->first, *pre = NULL, *qu = NULL;
	//다음노드, 현재노드, 이전노드
	while (cur != NULL)
		//다음노드가 NULL값이 될때까지 반복
	{
		qu = pre;
		pre = cur;
		cur = cur->rlink;//다음노드로 이동
		pre->rlink = qu;//다음노드에 연결
		pre->llink = cur;//이전노드에 연결
	}

	h->first = pre;
	return 0;
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	struct Node* pre = h->first;
	struct Node* cur = h->first;
	new_node->key = key;
	new_node->rlink = NULL;

	if (h->first == NULL) {
		h->first = new_node;
		return 0;
	}
	while (cur != NULL)
	{
		if (cur->key >= key)
		{
			if (cur == h->first)
			{
				new_node->rlink = cur;
				h->first = new_node;
			}

			else
			{
				new_node->rlink = pre->rlink;
				pre->llink = new_node;
			}
			return 0;
		}
		else
		{
			pre = cur;
			cur = cur->rlink;
		}
	}
	pre->rlink = new_node;
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	
	listNode* tmp = h->first;
	listNode* pre;

	if (h->first == NULL)
		return 0;

	if (tmp->key == key) {
		h->first = tmp->rlink;
		tmp->llink = h->first;
		free(tmp);
		return 0;
	}
	while (tmp->rlink != NULL)
	{
		if (tmp->rlink->key == key)
		{
			listNode* del = tmp->rlink;
			if (del->rlink != NULL)
			{
				tmp->rlink = del->rlink;
				del->rlink->llink = tmp->rlink;
			}
			else
				tmp->rlink = NULL;
			free(del);
			return 0;
		}
		tmp = tmp->rlink;
	}
}
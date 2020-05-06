
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
 /* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
		 singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
		- initialize�� �� �ٸ��� ���� �Ұ�
		 - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
        printf("2019038045 ������");
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
	//h�� ����� listnode �޸� ����
	//headnode�� �����Ǿ����
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
 * list�� key�� ���� ����ϳ��� �߰�
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
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* delNode;
	if (h->first == NULL)
		return 0;    //�� ����Ʈ�� ��� ������ ��尡 �����Ƿ� ����
	if (h->first->rlink == NULL) {    //����Ʈ�� ��尡 �� ���� ���
		free(h->first);    //�� ����� �޸� ����
		h->first = NULL;
		return 0;
	}

	else {
		listNode* pre;               //����Ʈ�� ��尡 2�� �̻��� ���
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
 * list ó���� key�� ���� ����ϳ��� �߰�
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
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	listNode* firstnode = h->first;
	h->first = firstnode->rlink;
	free(firstnode);
	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	listNode * cur = h->first, *pre = NULL, *qu = NULL;
	//�������, ������, �������
	while (cur != NULL)
		//������尡 NULL���� �ɶ����� �ݺ�
	{
		qu = pre;
		pre = cur;
		cur = cur->rlink;//�������� �̵�
		pre->rlink = qu;//������忡 ����
		pre->llink = cur;//������忡 ����
	}

	h->first = pre;
	return 0;
	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
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
 * list���� key�� ���� ��� ����
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
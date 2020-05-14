/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;

	do {
        printf("2019038045 ������\n");
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h) {
	//h�� ����� listnode �޸� ����
	//headnode�� �����Ǿ����
	if (h->rlink == h) {
		free(h);
		return 0;
	}
	listNode* p = h->rlink;

	listNode* prev = NULL;
	while (p != h && p!=NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {
	struct Node* n_node = (struct Node*)malloc(sizeof(struct Node));
	struct Node *last = h->rlink;

	n_node->key = key;
	n_node->rlink = NULL;

	if (h->rlink == NULL) {
		h->rlink = n_node;
		return 0;
	}
	while (last->rlink != h) {
		last = last->rlink;
	}


	last->rlink = n_node;
	n_node->llink = last;
	n_node->rlink = h;
	h->llink = n_node;

	return 0;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {
	listNode* delNode;
	if (h->rlink == h) {
		printf("������ �� �ִ� ��尡 �����ϴ�.\n");
		return 0;
	}//����常 �ִ� ��� ������ ��尡 �����Ƿ� ����
	if (h->rlink->rlink == h) {   //����Ʈ�� ��尡 �� ���� ��� ,������� ������尡 ����带 ����Ű�� ���
		free(h->rlink);    //������� ���� ����� �޸� ����
		h->rlink = h;//������� �����ʸ�ũ�� ����ڽ��� ����Ű�� ����
		return 0;
	}

	else {
		listNode* pre;               //����Ʈ�� ��尡 2�� �̻��� ���
		pre = h->rlink;				//pre��带 ������� �������� �־��ش�.
		delNode = h->rlink->rlink;	//pre����� ������带 delnode�� �������ش�.
		while (delNode->rlink != h) {//delnode�� ������尡 ����尡 �� ������ �ݺ����ش�.
			pre = delNode;
			delNode = delNode->rlink;//delnode�� �������� ��� �̵������ش�.
		}
		free(delNode);
		pre->rlink = h;//pre�� ������带  ����带 ����Ű�� ���ش�,
		h->llink = pre;
	}

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;
	node->rlink = h->rlink;
	h->rlink = node;
	node->llink = h;

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	listNode* firstnode = h->rlink;
	h->rlink = firstnode->rlink;
	firstnode->rlink->llink = h;
	free(firstnode);
	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {
	listNode * cur = h->rlink, *pre = h, *qu;
	//  �������,        ������,    �������
	if (h->rlink == h || h == NULL) {
		printf("�ٲ� �ʿ䰡 �����ϴ�.");
		
		return 0;
	}//�����̰ų� ��尡 �ϳ��� ���

	while (cur != h && cur!=NULL)
		//������尡 NULL���� �ɶ����� �ݺ�
	{
		qu = pre;
		pre = cur;
		cur = cur->rlink;//�������� �̵�
		pre->rlink = qu;//������忡 ����
		pre->llink = cur;//������忡 ����
	}
	h = h->rlink;
	cur->rlink = pre;

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	struct Node* pre = h->rlink;
	struct Node* cur = h->rlink;
	new_node->key = key;
	new_node->rlink = NULL;
	new_node->llink = NULL;

	if (h->rlink == h) {
		h->rlink = new_node;
		new_node->rlink = h;
		return 1;
	}
	while (cur != h)
	{
		if (cur->key >= key)
		{
			if (cur == h->rlink)
			{
				new_node->rlink = cur;
				cur->llink = new_node;
				h->rlink = new_node;
				new_node->llink = h;

			}

			else
			{
				new_node->rlink = cur;
				new_node->llink = cur->llink;
				cur->llink->rlink = new_node;
				
			}
			return 0;
		}
		else
		{
			
			cur = cur->rlink;
		}
	}
	insertLast(h, key);
	return 0;
	
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
	listNode* tmp = h->rlink;
	listNode* pre;

	if (h->rlink == NULL || h->rlink==h)
		return 0;

	if (tmp->key == key) {
		h->rlink = tmp->rlink;
		tmp->llink = h->rlink;
		free(tmp);
		return 0;
	}
	while (tmp->rlink != h)
	{
		if (tmp->rlink->key == key)
		{
			listNode* del = tmp->rlink;
			if (del->rlink != h)
			{
				tmp->rlink = del->rlink;
				del->rlink->llink = tmp->rlink;
			}
			else
				tmp->rlink = h;
			free(del);
			return 0;
		}
		tmp = tmp->rlink;
	}
	return 0;
}

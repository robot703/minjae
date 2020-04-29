/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 //�ʿ��� ������� �߰� 
typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


//�Լ� ����Ʈ
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

	printf(" 2019038045 ������ \n");
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

	//headnode�� null�� �ƴϸ�� freenode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ����
	if (h != NULL)
		freeList(h);

	//headnode�� ���� �޸𸮸� �Ҵ��Ͽ� ����
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	//h�� ����� listnode �޸� ����
	//headnode�� �����Ǿ����
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
	//listó���� key�� ���� ��� �ϳ��� �߰�
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


//����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
int insertNode(headNode* h, int key) {
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));//���ο��带 �Ҵ�
	struct Node* pre = h->first;//��� �ϳ��� ����� �ʱⰪ�� h->first������
	struct Node* cur = h->first;//��� �ϳ��� ����� �ʱⰪ�� h->first������
	new_node->key = key;//������� ��忡 Ű���� �޴´�
	new_node->link = NULL;//������� ����� ���� ����Ʈ�� NULL�� ������ش�

	if (h->first == NULL) {//��ó���� NULL���� ���
		h->first = new_node;//������� ��带 ù������ �־��ش�
		return 0;
	}
	while (cur != NULL)//cur�� NULL�̵Ǹ� ���������� �ݺ����� ������ش�.
	{
		if (cur->key >= key)//���� ������ Ű���� �Է��� Ű������ ũ�ų� �������
		{
			if (cur == h->first) //������ ��尡 �� ó���� ���
			{	
				new_node->link = cur;//������� ����� ��ũ�� ������带 ���ϰ��Ѵ�.
				h->first = new_node;// ��ó������ ������� ��带 �ʾ��ش�.
			}

			else//�ƴϸ�
			{
				new_node->link = pre->link;//������� ����� ��ũ�� ������ ��尡 �����״� ��带 ���ϵ��� ���Ѵ�.
				pre->link = new_node;//������ ��带 ������� ��带 ���ϵ��� ���ش�
			}
			return 0;
		}
		else
		{
			pre = cur;//���� ��尡 ������ ��带 ���󰡵��� ������ش�
			cur = cur->link;//������ ��尡 ����ؼ� ���Ƿ� ���� �� �ֵ��� ���ش�.
		}
	}
	pre->link = new_node;//�ƹ��͵� ã�� ���Ѱ�� ������س�带 �ǵڷ� ������.
	return 0;
}



//list�� key�� ���� ��� �ϳ��� �߰�
int insertLast(headNode *h, int key) {
	struct Node* n_node = (struct Node*)malloc(sizeof(struct Node));//���ο� ��带 �Ҵ����ش�.
	struct Node *last = h->first;//��� �ϳ��� ����� �ʱⰪ�� h->first������

	n_node->key = key;//������� ��忡 Ű���� ���� �� �ֵ��� �Ѵ�.
	n_node->link = NULL;//������� ����� ��ũ�� NULL�� ���ϰ� �Ѵ�.

	if (h->first== NULL) {//��ó���� �ƹ��͵� �������
		h->first = n_node;//�ٷ� ������� ��带 �־��ش�.
		return 0;
	}
	while (last->link != NULL) {//����������� ��ũ�� NULL�� �ǋ����� �ݺ��ȴ�.
		last = last->link;//������ ��ũ�� ��� ���ڸ��� ���� �� �� �ֵ��� ���ش�.
	}

	
	last->link = n_node;// ������ ��ũ�� ������ ���� �־��ش�.
	return 0;
}


//list�� ù��° ��� ����
int deleteFirst(headNode* h) {
	listNode* firstnode = h->first;//��� �ϳ��� ����� �ʱⰪ�� h->first������
	h->first = firstnode->link;//ó���� ����Ű�� ��ũ�� ������� ����� ��ũ�� �ٲ��ش�.
	
	return 0;
}


//list���� key �� ���� ��� ����
int deleteNode(headNode* h, int key) {
	listNode* tmp = h->first;//��� �ϳ��� ����� �ʱⰪ�� h->first������
	listNode* pre;

	if (h->first == NULL)
		return 0;

	while (tmp->link != NULL)//���� ��ġ���� ��������� ���� ������ �� �ִ��� Ȯ���ϴ�.
	{
		if (tmp->link->key == key)//�����ϴ� ���ΰ��
		{
			listNode* del = tmp->link;//del��带 �������ְ� �ش� �ּҸ� ������ �ִ´�.
			if (del->link != NULL)
				tmp->link = del->link;//������ġ�� del����� ���� �ּҰ��� ������.
			else
				tmp->link = NULL;
			free(del);//�������ش�.�������ش�
			return 0;
		}
		tmp = tmp->link;
	}
}


//list�� ������ ��� ����
int deleteLast(headNode* h) {
	
	listNode* delNode;
	if (h->first == NULL) //�� ����Ʈ�� ��� ������ ��尡 �����Ƿ� ����
		return 0; 
	if (h->first->link == NULL) { //����Ʈ�� ��尡 �� ���� ���
		free(h->first); //�� ����� �޸� ����
		h->first = NULL;
		return 0;
	}
	
	else {
		listNode* pre;//����Ʈ�� ��尡 2�� �̻��� ���
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


//����Ʈ�� ��ũ�� �������� ���ġ
int invertList(headNode *h) {
	listNode * cur=h->first, *pre=NULL , *qu= NULL;
//��� �ϳ��� ����� �ʱⰪ�� h->first������
	while (cur != NULL)

	{//swap�� ����� �Ͱ���.
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
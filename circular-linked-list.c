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
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
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
        printf("2019038045 조민재\n");
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

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {
	//h와 연결된 listnode 메모리 해제
	//headnode도 해제되어야함
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
 * list에 key에 대한 노드하나를 추가
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
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	listNode* delNode;
	if (h->rlink == h) {
		printf("삭제할 수 있는 노드가 없습니다.\n");
		return 0;
	}//헤드노드만 있는 경우 삭제할 노드가 없으므로 종료
	if (h->rlink->rlink == h) {   //리스트에 노드가 한 개인 경우 ,헤드노드의 다음노드가 헤드노드를 가리키는 경우
		free(h->rlink);    //헤드노드의 다음 노드의 메모리 해제
		h->rlink = h;//헤드노드의 오른쪽링크를 헤드자신을 가리키게 해줌
		return 0;
	}

	else {
		listNode* pre;               //리스트에 노드가 2개 이상인 경우
		pre = h->rlink;				//pre노드를 헤드노드의 다음으로 넣어준다.
		delNode = h->rlink->rlink;	//pre노드의 다음노드를 delnode로 선언해준다.
		while (delNode->rlink != h) {//delnode의 다음노드가 헤드노드가 될 때까지 반복해준다.
			pre = delNode;
			delNode = delNode->rlink;//delnode를 다음노드로 계속 이동시켜준다.
		}
		free(delNode);
		pre->rlink = h;//pre의 다음노드를  헤드노드를 가리키게 해준다,
		h->llink = pre;
	}

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
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
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	listNode* firstnode = h->rlink;
	h->rlink = firstnode->rlink;
	firstnode->rlink->llink = h;
	free(firstnode);
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	listNode * cur = h->rlink, *pre = h, *qu;
	//  다음노드,        현재노드,    이전노드
	if (h->rlink == h || h == NULL) {
		printf("바꿀 필요가 없습니다.");
		
		return 0;
	}//공백이거나 노드가 하나일 경우

	while (cur != h && cur!=NULL)
		//다음노드가 NULL값이 될때까지 반복
	{
		qu = pre;
		pre = cur;
		cur = cur->rlink;//다음노드로 이동
		pre->rlink = qu;//다음노드에 연결
		pre->llink = cur;//이전노드에 연결
	}
	h = h->rlink;
	cur->rlink = pre;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
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
 * list에서 key에 대한 노드 삭제
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

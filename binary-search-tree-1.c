/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);     /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);     /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;   /* temp */

	do {
		printf("\n\n");
        printf("2019038045 조민재\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;   /* head */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr == NULL)
		return;

	if (ptr != NULL) {
		inorderTraversal(ptr->left);
		printf("[%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr == NULL)
		return;

	if (ptr != NULL) {
		printf("[%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}

}

void postorderTraversal(Node* ptr)
{
	if (ptr == NULL)
		return;

	if (ptr != NULL) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf("[%d] ", ptr->key);
	}

}


int insert(Node* head, int key)
{
	Node *NewNode = (Node *)malloc(sizeof(Node));
	NewNode->left = NULL;
	NewNode->right = NULL;
	NewNode->key = key;
	Node *Cur = head->left;
	
		if (head->left == NULL)//없을경우
		{
			head->left = NewNode;//왼쪽에 새로운 노드
			return 1;
		}

		while (1)
		{

			if (Cur->key < key)
			{
				if (Cur->right == NULL)
				{
					Cur->right = NewNode;//오른쪽에 새로운노드
					return 1;
				}
				else
					Cur = Cur->right;//이동

			}
			else if (Cur->key > key)
			{
				if (Cur->left == NULL)
				{
					Cur->left = NewNode;//왼쪽에 새로운노드
					return 1;
				}
				else
					Cur = Cur->left;//이동
			}
			else {//키가 같은경우
				printf("동일한 키가 존재합니다.");
				return 1;
			}
		}
		return 0;
	
}



int deleteLeafNode(Node* head, int key)
{

	Node* hero = NULL;
	Node* i = head->left;

	while (i != NULL && i->key != key)
	{
		hero = i;
		if (key < hero->key) {
			i = hero->left;
			
		}
		else {
			i = hero->right;
			
		}
	}
	

		if (!i)
		{
			printf("cannot find the node\n");
			return 1;
		}

		if (head->left == NULL) {
			printf("not have node");
			return 1;
		}

		if (i->left == NULL && i->right == NULL)
		{
			if (hero)
			{
				if (hero->left == i)
					hero->left = NULL;
				else
					hero->right = NULL;
			}
			else
				head->left = NULL;
		}

		else
		{
			printf("cannot delete");
			return 1;
		}
		return 1;

	
}

Node* searchRecursive(Node* ptr, int key)
{

	if (!ptr)
		return NULL;

	// 찾는값을 찾았을 때
	if (key == ptr->key)
		return ptr; 

	  // 찾는값보다 키값이 작은 경우
	else if (key > ptr->key)
		searchRecursive(ptr->right, key); 

	  // 찾는값보다 키값이 큰 경우
	else
		searchRecursive(ptr->left, key);

}

Node* searchIterative(Node* head, int key)
{
	
	Node* m= head->left;
	while (m != NULL) 
	{
		// 찾는값을 발견했을 경우
		if (key == m->key)
			return m; 

		  // 찾는값보다 키값이 더 큰 경우
		else if (key < m->key)
			m = m->left; 

		  // 찾는값보다 루트키값이 더 작은 경우
		else
			m = m->right; 
	}

	return NULL;
}


int freeBST(Node* head)
{
	if (head == NULL)
		return 1;

	freeBST(head->left);
	freeBST(head->right);
	free(head);
}




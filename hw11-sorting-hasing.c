
/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE                  13      /* prime number */
#define MAX_HASH_TABLE_SIZE     MAX_ARRAY_SIZE

 /* �ʿ信 ���� �Լ� �߰� ���� */
int initialize(int **a);//�޸𸮸� �����Ҵ� ���ش�.
int freeArray(int *a);//�����������ִ� �Լ��̴�.
void printArray(int *a);//������ִ��Լ��̴�.

int selectionSort(int *a);//���� �������ִ� �Լ��̴�.
int insertionSort(int *a);//���� �������ִ� �Լ��̴�.
int bubbleSort(int *a);//���� �������ִ� �Լ��̴�.
int shellSort(int *a);//�� �������ִ� �Լ��̴�.
/* recursive function���� ���� */
int quickSort(int *a, int n);//�� �������ִ� �Լ��̴�.


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a���� �� hash table�� �����. */
int hashing(int *a, int **ht);//�迭�� �ؽ����̺� �������ִ� �Լ��̴�.

/* hash table���� key�� ã�� hash table�� index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do {
        printf("2019038045 ������\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array�� NULL�� ��� �޸� �Ҵ� */
	if (*a == NULL) {//������ a�� NULL�� ���
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);//�����Ҵ� ���ش�.
		*a = temp;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	}
	else
		temp = *a;

	/* �������� �迭�� ������ ���� */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)//MAX_ARRAY_SIZE��ŭ �ݺ��ϴ� �ݺ���
		temp[i] = rand() % MAX_ARRAY_SIZE;//0~13���� �������� �迭0������ �迭12������ �־��ش�.

	return 0;
}

int freeArray(int *a)//�迭�� �������� ���ش�.
{
	if (a != NULL)//a�� NULL�� �ƴҰ�� 
		free(a);//free�Լ��� a�� ���ڷκ�����.
	return 0;
}

void printArray(int *a)//���⼭ ������ a�� �迭�� �ּ��̰� ���ڷ� �޾ƿ´�.
{
	if (a == NULL) {//a�� NULL�ΰ��
		printf("nothing to print.\n");//����Ʈ�� ���� ����������ش�.
		return;
	}
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)//i�� 13�� �ݺ��Ѵ�.
		printf("a[%02d] ", i);//ó���� 0�ΰ��� ä���, 00������12������ ������ش�.ex)a[00]~a[12]
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)//i�� 13�� �ݺ��Ѵ�.
		printf("%5d ", a[i]);//�տ� �ټ�ĭ�� ���� ����Ѵ�. �׸��� a[i]��°�� �ִ� ������ initialize�Լ����� �־��� �������� ������ش�.
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;//i�� minindex�� �����Ѵ�.
		min = a[i];//�迭 a�� �ʱⰪ�� �ּڰ����� �������ش�.
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++)//j�� �ʱⰪ ������ ����Ű�Ƿ� i+1�� �������ش�.i�� �񱳴���� i�� ���� �����̹Ƿ�  i+1����Ѵ�.
		{										//�ι�° for���� �迭i��°�� ���ϸ鼭 �ּڰ��� ã�� ������ �ݺ��Ѵ�.		
			if (min > a[j])//���࿡ �ּڰ��� ���������� Ŭ ���
			{
				min = a[j];//�������� �ּڰ����� �־��ش�.
				minindex = j;//j�� minindex�� �������ش�.
			}
		}
		a[minindex] = a[i];//�迭 a�� i��°�� �迭 a�� minindex�� ���� �־��ش�.�׷��� ���� i��°�� ���� minindex�� ���� ���� ��Ȳ�̴�.
		a[i] = min;//���� ������ min������ ����Ǿ� �ִ� �ּڰ��� a�� i��°�� �־��ش�.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 1; i < MAX_ARRAY_SIZE; i++)//ù��° for���� ���ϴ� ������,��key�� ���ϱ����� �����Ѵ�.key�� ���� �ϳ��� �������ش�.
	{
		t = a[i];//t���ٰ� �迭a�� i��°�� �־��ش�.�ʱ� i���� 1�̴�.key���� �־��ش�.
		j = i;//i���� j�� �־��ش�.
		while (a[j - 1] > t && j > 0)//a�� j-1��°�� t���� ũ�� j�� 0����Ŭ������ �ݺ��Ѵ�.key�̶� ���Ͽ� ������ ������ �Ǵ��Ѵ�.
		{
			a[j] = a[j - 1];//a�� j��° �տ����� ���� j��°�� �־��ش�.
			j--;//j�� ���� �ļ��������ڷ� �ϳ��ٿ��ش�.
		}
		a[j] = t;//t�� a�� j ��°�� �־��ش�.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)//�ι�°for���� ������ �Ǹ� ū���ڴ� ���������� �������Եȴ�. ���� ���� ������ 13�� �ݺ����ش�.
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)//ū���ڸ� �ǵڷ� ������ �ݺ����̴�. �迭�� index�� �ϳ��� �÷��ָ鼭 �ϳ��� �����ش�.
		{
			if (a[j - 1] > a[j])//�迭a�� j-1��°�� j��°�� �����ִ��ڵ��̴�.��, �ΰ��� ���ڸ� �����ָ鼭 ū���ڸ� �ڷκ�����. 
			{
				t = a[j - 1];//�ΰ��� ������ �ڸ��� �ٲ��ִ� �����ڵ��̴�.
				a[j - 1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)//�迭�� ���� �ϳ��� ���� ������ �ݾ� ���´�.
	{
		for (i = 0; i < h; i++)//h��ŭ ¦�� �̷� ���� ���������� ���� �ٲ��ش�.
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h)//h��ŭ �������ִ� ���̶� �����ش�.
			{
				v = a[j];//�迭a��j��° ���� v�� �־��ش�.
				k = j;//j�� k�� �־��ش�.
				while (k > h - 1 && a[k - h] > v)//a[k-h]�� ���� v�ǰ��� �����ش�.
				{
					a[k] = a[k - h];//while���� ������ �����ϴ°�� ū���� �ڷ� �Ű��ְ�
					k -= h;//k=k-h(k���� h�� ���ش�. ¦�� �̷� ������ �������ִ� ��ŭ ���ش�)
				}
				a[k] = v;//v�� �������� ��(������ �ΰ��� ���߿��� ������)�� a�� k��°�� �־��ش�.
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;//v�� ������ ����ִ� �����̴�.
	int i, j;

	if (n > 1)
	{
		v = a[n - 1];//������index�� ��
		i = -1;//�迭 0��° ������ index
		j = n - 1;//������ index

		while (1)
		{
			while (a[++i] < v);//v�� ���ϸ鼭 a[++i]�ǰ��� v���� Ŀ�� ������ i�� ���� �������ش�.
			while (a[--j] > v);//v�� ���ϸ鼭 a[--j]�� ���� v���� ���� ������ j�ǰ��� �����Ѵ�.

			if (i >= j) break;//i��j�� ���ų� ū��쿡 while���� ���´�.
			t = a[i];//a[i]��a[j]���� �������ش�.
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];//a[i]�� v�ǰ��� �������ش�.
		a[i] = a[n - 1];
		a[n - 1] = t;
		/*����Լ��� �̿��ؼ� ������ �ݺ��Ѵ�*/
		quickSort(a, i);//v�� �������� v�ǰ����� ���� ������ �ٽ� ���������ش�.
		quickSort(a + i + 1, n - i - 1);//v�� �������� v�� ������ ū ������ �ٽ� ���������ش�.
	}


	return 0;
}

int hashCode(int key) {/*hashcode�� �迭�� key���� �迭�� ũ��� ������ ������ �������� ���Ѵ�.*/
	return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;//NULL�� �ʱ�ȭ ���ش�.

	/* hash table�� NULL�� ��� �޸� �Ҵ� */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* �Ҵ�� �޸��� �ּҸ� ���� --> main���� �迭�� control �Ҽ� �ֵ��� ��*/
	}
	else {
		hashtable = *ht;/* hash table�� NULL�� �ƴѰ��, table ��Ȱ��, reset to -1 */
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)//hashtable�ȿ� �ִ� ������ ��� -1�� �ʱ�ȭ���ش�.-1�� ����ִٰ� �����ϸ� ���ϴ�.
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
			printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];//i�� �÷��ָ鼭 key�� ���� �ִ´�.������ ������ ���� �ȴ�.
		hashcode = hashCode(key);//key���� hashcode�Լ��� �����־� �迭�� ũ��� �������ְ�, hashcode�� �־��ش�.
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)/*hashtable�� hashcode��°�� ���� -1�ϰ�� ���ǹ��� ���Եȴ�.
									������ -1�� �ʱ�ȭ�� ���ְ�, �ٸ� ���� ������� ��쿡�� �������� �ʴ´�.*/
		{
			hashtable[hashcode] = key;//key�� ������ִ� ���� hashtable[hashcode]�� �־��ش�.
		}								//�浹�� �Ͼ�� �ʴ´ٸ�, �ؽ��ڵ尡 �ε��� �� ���ε��� ������ index�� key���� �Ȱ����� �ۿ�����.
		else {//-1�̾ƴѰ��, �̹̰��� ���ִ°��, �浹�ΰ��

			index = hashcode;//hashcode�� index�� �־��ش�.

			while (hashtable[index] != -1)//�迭���� -1�� ������� ������ �ݺ��Ѵ�.
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;//-1�� ã�ƾ��ϱ� ������ index�� �ϳ����ø��� HASH TABLE SIZE�� ���� ������ ���� index�� �־��ش�.
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;//while���� ���Դٴ°��� index�� ���� -1�̶�� �Ҹ��̰�, ������ �ƹ��͵� ���°��̶�� �����Ͽ� key���� �־�д�.
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);//hashcode�� index�� �־��ش�.

	if (ht[index] == key)//hashtable�� index���� key�� �������
		return index;//index�� ��ȯ�Ѵ�. 

	while (ht[++index] != key)//key�� ã�� ������ index�� �÷����� �ϳ��� ã���ش�.
	{						//�浹�� �Ͼ�� ���������� �̵��ϰԵȴ�.
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;//index�� ��ȯ�Ѵ�. 
}



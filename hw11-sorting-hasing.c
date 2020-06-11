
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

 /* 필요에 따라 함수 추가 가능 */
int initialize(int **a);//메모리를 동적할당 해준다.
int freeArray(int *a);//동적해제해주는 함수이다.
void printArray(int *a);//출력해주는함수이다.

int selectionSort(int *a);//선택 정렬해주는 함수이다.
int insertionSort(int *a);//삽입 정렬해주는 함수이다.
int bubbleSort(int *a);//버블 정렬해주는 함수이다.
int shellSort(int *a);//쉘 정렬해주는 함수이다.
/* recursive function으로 구현 */
int quickSort(int *a, int n);//퀵 정렬해주는 함수이다.


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);//배열을 해쉬테이블에 저장해주는 함수이다.

/* hash table에서 key를 찾아 hash table의 index return */
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
        printf("2019038045 조민재\n");
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

	/* array가 NULL인 경우 메모리 할당 */
	if (*a == NULL) {//포인터 a가 NULL일 경우
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);//동적할당 해준다.
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)//MAX_ARRAY_SIZE만큼 반복하는 반복문
		temp[i] = rand() % MAX_ARRAY_SIZE;//0~13까지 랜덤으로 배열0번부터 배열12번까지 넣어준다.

	return 0;
}

int freeArray(int *a)//배열을 동적해제 해준다.
{
	if (a != NULL)//a가 NULL이 아닐경우 
		free(a);//free함수에 a를 인자로보낸다.
	return 0;
}

void printArray(int *a)//여기서 포인터 a는 배열의 주소이고 인자로 받아온다.
{
	if (a == NULL) {//a가 NULL인경우
		printf("nothing to print.\n");//프린트할 것이 없다출력해준다.
		return;
	}
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)//i가 13번 반복한다.
		printf("a[%02d] ", i);//처음에 0두개를 채우고, 00번부터12번까지 출력해준다.ex)a[00]~a[12]
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)//i가 13번 반복한다.
		printf("%5d ", a[i]);//앞에 다섯칸을 띄우고 출력한다. 그리고 a[i]번째에 있는 기존에 initialize함수에서 넣어준 랜덤값을 출력해준다.
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
		minindex = i;//i를 minindex에 저장한다.
		min = a[i];//배열 a의 초기값을 최솟값으로 지정해준다.
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++)//j는 초기값 다음을 가리키므로 i+1로 선언해준다.i의 비교대상은 i의 다음 숫자이므로  i+1라고한다.
		{										//두번째 for문은 배열i번째와 비교하면서 최솟값을 찾을 때까지 반복한다.		
			if (min > a[j])//만약에 최솟값이 다음값보다 클 경우
			{
				min = a[j];//다음값을 최솟값으로 넣어준다.
				minindex = j;//j를 minindex에 저장해준다.
			}
		}
		a[minindex] = a[i];//배열 a의 i번째에 배열 a의 minindex의 값을 넣어준다.그러면 현재 i번째의 값과 minindex의 값이 같은 상황이다.
		a[i] = min;//따라서 기존에 min변수에 저장되어 있는 최솟값을 a의 i번째에 넣어준다.
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

	for (i = 1; i < MAX_ARRAY_SIZE; i++)//첫번째 for문은 비교하는 기준점,즉key를 정하기위해 존재한다.key의 값을 하나씩 증가해준다.
	{
		t = a[i];//t에다가 배열a의 i번째를 넣어준다.초기 i값은 1이다.key값을 넣어준다.
		j = i;//i값을 j에 넣어준다.
		while (a[j - 1] > t && j > 0)//a의 j-1번째가 t보다 크고 j가 0보다클때까지 반복한다.key이랑 비교하여 스왑의 조건을 판단한다.
		{
			a[j] = a[j - 1];//a의 j번째 앞에오는 값을 j번째에 넣어준다.
			j--;//j의 값을 후순위연산자로 하나줄여준다.
		}
		a[j] = t;//t를 a의 j 번째에 넣어준다.
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

	for (i = 0; i < MAX_ARRAY_SIZE; i++)//두번째for문을 돌리게 되면 큰숫자는 마지막으로 보내지게된다. 따라서 같은 정렬을 13번 반복해준다.
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)//큰숫자를 맨뒤로 보내는 반복문이다. 배열의 index를 하나씩 늘려주면서 하나씩 비교해준다.
		{
			if (a[j - 1] > a[j])//배열a의 j-1번째와 j번째를 비교해주는코드이다.즉, 두개의 숫자를 비교해주면서 큰숫자를 뒤로보낸다. 
			{
				t = a[j - 1];//두개의 숫자의 자리를 바꿔주는 스왑코드이다.
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

	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)//배열을 각각 하나씩 묶일 때까지 반씩 묶는다.
	{
		for (i = 0; i < h; i++)//h만큼 짝을 이룬 값을 삽입정렬을 통해 바꿔준다.
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h)//h만큼 떨어져있는 값이랑 묶어준다.
			{
				v = a[j];//배열a의j번째 값을 v에 넣어준다.
				k = j;//j를 k에 넣어준다.
				while (k > h - 1 && a[k - h] > v)//a[k-h]의 값과 v의값을 비교해준다.
				{
					a[k] = a[k - h];//while문의 조건이 성립하는경우 큰값을 뒤로 옮겨주고
					k -= h;//k=k-h(k에서 h를 빼준다. 짝을 이룬 값끼리 떨어져있는 만큼 빼준다)
				}
				a[k] = v;//v에 저장해준 값(묶어준 두개의 값중에서 작은값)을 a의 k번째에 넣어준다.
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;//v는 기준을 잡아주는 변수이다.
	int i, j;

	if (n > 1)
	{
		v = a[n - 1];//마지막index의 값
		i = -1;//배열 0번째 이전의 index
		j = n - 1;//마지막 index

		while (1)
		{
			while (a[++i] < v);//v와 비교하면서 a[++i]의값이 v보다 커질 때까지 i의 값을 증가해준다.
			while (a[--j] > v);//v와 비교하면서 a[--j]의 값이 v보다 작을 때까지 j의값을 감소한다.

			if (i >= j) break;//i가j와 같거나 큰경우에 while문을 나온다.
			t = a[i];//a[i]와a[j]값을 스왑해준다.
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];//a[i]와 v의값을 스왑해준다.
		a[i] = a[n - 1];
		a[n - 1] = t;
		/*재귀함수를 이용해서 정렬을 반복한다*/
		quickSort(a, i);//v를 기준으로 v의값보다 작은 값들을 다시 퀵정렬해준다.
		quickSort(a + i + 1, n - i - 1);//v를 기준으로 v의 값보다 큰 값들을 다시 퀵정렬해준다.
	}


	return 0;
}

int hashCode(int key) {/*hashcode는 배열의 key값을 배열의 크기로 나누어 나오는 나머지를 말한다.*/
	return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;//NULL로 초기화 해준다.

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else {
		hashtable = *ht;/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)//hashtable안에 있는 값들을 모두 -1로 초기화해준다.-1을 비어있다고 생각하면 편하다.
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
		key = a[i];//i를 늘려주면서 key에 값을 넣는다.랜덤한 값들이 들어가게 된다.
		hashcode = hashCode(key);//key값을 hashcode함수에 보내주어 배열의 크기로 나누어주고, hashcode에 넣어준다.
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)/*hashtable의 hashcode번째의 값이 -1일경우 조건문에 들어가게된다.
									기존에 -1로 초기화를 해주고, 다른 값이 들어있을 경우에는 성립하지 않는다.*/
		{
			hashtable[hashcode] = key;//key에 저장되있는 값을 hashtable[hashcode]에 넣어준다.
		}								//충돌이 일어나지 않는다면, 해쉬코드가 인덱스 값 으로들어가기 때문에 index와 key값이 똑같을수 밖에없다.
		else {//-1이아닌경우, 이미값이 들어가있는경우, 충돌인경우

			index = hashcode;//hashcode를 index에 넣어준다.

			while (hashtable[index] != -1)//배열값에 -1이 들어있을 때가지 반복한다.
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;//-1을 찾아야하기 때문에 index를 하나씩늘리고 HASH TABLE SIZE로 나눈 나머지 값을 index에 넣어준다.
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;//while문을 나왔다는것은 index의 값이 -1이라는 소리이고, 때문에 아무것도 없는것이라는 가정하에 key값을 넣어둔다.
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);//hashcode를 index에 넣어준다.

	if (ht[index] == key)//hashtable의 index값이 key와 같은경우
		return index;//index를 반환한다. 

	while (ht[++index] != key)//key를 찾을 때까지 index를 늘려가며 하나씩 찾아준다.
	{						//충돌이 일어나면 다음값으로 이동하게된다.
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;//index를 반환한다. 
}



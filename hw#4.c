#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int** create_matrix(int row, int col);//malloc을 통해서동적할당을 해준다.
int fill_data(int **matrix, int row, int col);//배열의 값을 랜덤하게 받아주는 함수이다.
void print_matrix(int** matrix, int row, int col);//일벽받은 행렬을 출력시켜준다.
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col);//A행렬과 B행렬을 더해준다.
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col);//A행렬과 B행렬을 빼준다.
int transpose_matrix(int **matrix_a, int **matrix_t, int row, int col);//행렬을 전치행렬로 변환해준다.
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col);//A행렬과 T행렬을 곱해준다.			
int free_matrix(int** matrix, int row, int col);//동적할당을 해제시켜준다.

int main(void)
{
	printf("[----- [조민재] [2019038045] -----]");

	int x, y;//각각 행과 열의 변수
	int **arrA;//A대응
	int **arrB;//B대응
	int **arrT;//T대응
	int **arrSUM;//sum 대응
	int **arrSUB;//sub 대응
	int **arrMUL;//mul 대응

	printf("\n\n행과 열을 입력해주세요. ex)2 3 :");

	scanf_s("%d %d", &x, &y);//행과 열을 입력받는 라이브러리함수

	if (x <= 0 || y <= 0) {  //입력받은 값이 하나라도 0보다 작을 경우, 행렬의 수를 다시 입력받기 위함
		printf("행과 열을 1 이상으로 입력해야 됩니다.\n 행과 열 입력해주세요 ex2 3 : ");
		scanf("%d %d", &x, &y);
	}

	arrA = create_matrix(x, y);//A행렬 할당선언
	arrB = create_matrix(x, y);//B행렬 할당선언
	arrT = create_matrix(x, y);//T행렬 할당선언
	arrSUM = create_matrix(x, y);//SUM행렬 할당선언
	arrSUB = create_matrix(x, y);//SUB행렬 할당선언
	arrMUL = create_matrix(x, y);//MUL행렬 할당선언

	srand((unsigned)time(NULL));//main 에다 난수설정

	fill_data(arrA, x, y);//행렬 A 채워넣기
	fill_data(arrB, x, y);//행렬 B 채워넣기

	if (x == y) {  //만약 행과 열이 같을경우
		arrT = create_matrix(x, y);  //행과 열을 그대로 넣어줌
	}

	else {
		arrT = create_matrix(y, x);  //행과 열을 바꿔서 넣어줌
	}

	printf("\n\n\n1. 행렬 A B 값 출력\n\n");//행렬 A B 출력
	printf("행렬 A\n\n");
	print_matrix(arrA, x, y);//행렬 A출력
	puts(" ");
	printf("행렬 B\n\n");
	print_matrix(arrB, x, y);//행렬 B출력

	printf("\n2. 행렬 SUM (A+B) 출력\n\n");//행렬 A+B
	addition_matrix(arrA, arrB, arrSUM, x, y);//행렬A,B를 더해주는 함수의 매개변수
	print_matrix(arrSUM, x, y);

	printf("\n3. 행렬 SUB (A-B) 출력\n\n");//행렬 A-B
	subtraction_matrix(arrA, arrB, arrSUB, x, y);
	print_matrix(arrSUB, x, y);

	printf("\n4. 행렬 A의 전치행렬 T 출력\n\n");//A의 전치행렬
	transpose_matrix(arrA, arrT, x, y);
	print_matrix(arrT, y, x);//행과 열을 바꿔입력한다.


	printf("\n4. 행렬 A와 전치행렬 T의 곱 (A x T) 출력\n\n");
	if (x != y)//행과 열이 서로 다를경우
	{
		printf("행과 열을 똑같이 입력해주세요. ex)3 3 \n");
		return 1;
	}
	else {//같을경우 전치행렬곱 함수로 이동한 다음 출력
    
		multiply_matrix(arrA, arrT, arrMUL, x, y);
		print_matrix(arrMUL, x, y);
	}

	free_matrix(arrA, x, y);//동적할당
	free_matrix(arrB, x, y);
	free_matrix(arrSUM, x, y);
	free_matrix(arrSUB, x, y);
	free_matrix(arrMUL, x, y);//해제구간

	if (x == y) {  // 동적할당을 해제
		free_matrix(arrT, x, y);
	}
	if (x != y) {
		free_matrix(arrT, x, y);
	}
	free_matrix(arrMUL, x, y);
	return 0;
}

int **create_matrix(int row, int col)//사용자가 원하는 만큼 행과열을 동적으로 항당해준다.
{
	if (row <= 0 || col <= 0) { /* check pre conditions */  //전처리검사
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	else
	{
		int **x;
		x = (int**)malloc(row * sizeof(int*));
		for (int i = 0; i < row; i++) {
			x[i] = (int*)malloc(col * sizeof(int*));//배열x를 동적할당해준다.
			for (int j = 0; j < col; ++j) {
				x[i][j] = 0;
			}
		}
		if (x == NULL) {/* check post conditions */  //후처리검사
			printf(" 잘못된 값입니다. ");
		}
		return x;
	}
}

int fill_data(int **matrix, int row, int col)//랜덤숫자 생성
{
	//srand((unsigned)time(NULL));
	for (int a = 0; a < row; a++)
	{
		for (int b = 0; b < col; b++)
		{
			matrix[a][b] = rand() % 20;//0부터19중에서 랜덤으로 숫자 적용
		}
	}
	return **matrix;
}

void print_matrix(int** matrix, int row, int col)//matrix출력
{
	for (int a = 0; a < row; a++)
	{
		for (int b = 0; b < col; b++)
		{
			printf("%3d", matrix[a][b]);
		}
		printf("\n");

	}
}

int addition_matrix(int** matrix_a, int **matrix_b, int* *matrix_sum, int row, int col)		//matrixSUM 출력
{
	if (row <= 0 || col <= 0) {/* check pre conditions */  //전처리검사
		printf("Check the sizes of row and col!\n");
		return NULL;
	}

	for (int a = 0; a < row; a++)
	{
		for (int b = 0; b < col; b++)
		{
			matrix_sum[a][b] = matrix_a[a][b] + matrix_b[a][b];
		}
	}
	if (matrix_sum == NULL) {/* check post conditions */  //후처리검사
		printf(" 잘못된 값입니다. ");
	}
	return **matrix_sum;
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col)	//행렬의 빼기
{
	if (row <= 0 || col <= 0) {/* check pre conditions */  //전처리검사
		printf("Check the sizes of row and col!\n");
		return NULL;
	}

	for (int a = 0; a < row; a++)
	{
		for (int b = 0; b < col; b++)
		{
			matrix_sub[a][b] = matrix_a[a][b] - matrix_b[a][b];
		}
	}
	if (matrix_sub == NULL) {/* check post conditions */  //후처리검사
		printf(" 잘못된 값입니다. ");
	}
	return **matrix_sub;
}

int transpose_matrix(int **matrix_a, int **matrix_t, int row, int col) //행렬의 전치
{
	if (row <= 0 || col <= 0) {/* check pre conditions */  //전처리검사
		printf("Check the sizes of row and col!\n");
        return NULL;
	}

	if (matrix_a == 0) {
		return 1;
	}
    
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			matrix_t[j][i] = matrix_a[i][j];	
		
	}
    
	if (matrix_t == NULL) {/* check post conditions */  //후처리검사
		printf(" 잘못된 값입니다. ");
	}
	return **matrix_t;
}

int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col) //행렬의 곱셈
{
	if (row <= 0 || col <= 0) { /* check pre conditions */  //전처리검사
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	for (int i = 0; i < row; ++i) {  //matrix_axt 배열초기화
		for (int j = 0; j < col; ++j)
			matrix_axt[i][j] = 0;
	}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < row; j++)
			for (int k = 0; k < col; k++) {
				matrix_axt[i][j] += matrix_a[i][k] * matrix_t[k][j];
			}


	/* check post conditions */  //후처리검사
	if (matrix_axt == NULL)
	{
		printf(" 잘못된 값입니다. ");

	}
	return **matrix_axt;
}

int free_matrix(int** matrix, int row, int col)												//배열 해제
{
	for (int i = 0; i < row; ++i)  //for문을 통해 해제시켜줌
		free(matrix[i]);
	free(matrix);

	
	return 0;
}

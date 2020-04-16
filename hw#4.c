#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int** create_matrix(int row, int col);//malloc�� ���ؼ������Ҵ��� ���ش�.
int fill_data(int **matrix, int row, int col);//�迭�� ���� �����ϰ� �޾��ִ� �Լ��̴�.
void print_matrix(int** matrix, int row, int col);//�Ϻ����� ����� ��½����ش�.
int addition_matrix(int **matrix_a, int **matrix_b, int **matrix_sum, int row, int col);//A��İ� B����� �����ش�.
int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col);//A��İ� B����� ���ش�.
int transpose_matrix(int **matrix_a, int **matrix_t, int row, int col);//����� ��ġ��ķ� ��ȯ���ش�.
int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col);//A��İ� T����� �����ش�.			
int free_matrix(int** matrix, int row, int col);//�����Ҵ��� ���������ش�.

int main(void)
{
	printf("[----- [������] [2019038045] -----]");

	int x, y;//���� ��� ���� ����
	int **arrA;//A����
	int **arrB;//B����
	int **arrT;//T����
	int **arrSUM;//sum ����
	int **arrSUB;//sub ����
	int **arrMUL;//mul ����

	printf("\n\n��� ���� �Է����ּ���. ex)2 3 :");

	scanf_s("%d %d", &x, &y);//��� ���� �Է¹޴� ���̺귯���Լ�

	if (x <= 0 || y <= 0) {  //�Է¹��� ���� �ϳ��� 0���� ���� ���, ����� ���� �ٽ� �Է¹ޱ� ����
		printf("��� ���� 1 �̻����� �Է��ؾ� �˴ϴ�.\n ��� �� �Է����ּ��� ex2 3 : ");
		scanf("%d %d", &x, &y);
	}

	arrA = create_matrix(x, y);//A��� �Ҵ缱��
	arrB = create_matrix(x, y);//B��� �Ҵ缱��
	arrT = create_matrix(x, y);//T��� �Ҵ缱��
	arrSUM = create_matrix(x, y);//SUM��� �Ҵ缱��
	arrSUB = create_matrix(x, y);//SUB��� �Ҵ缱��
	arrMUL = create_matrix(x, y);//MUL��� �Ҵ缱��

	srand((unsigned)time(NULL));//main ���� ��������

	fill_data(arrA, x, y);//��� A ä���ֱ�
	fill_data(arrB, x, y);//��� B ä���ֱ�

	if (x == y) {  //���� ��� ���� �������
		arrT = create_matrix(x, y);  //��� ���� �״�� �־���
	}

	else {
		arrT = create_matrix(y, x);  //��� ���� �ٲ㼭 �־���
	}

	printf("\n\n\n1. ��� A B �� ���\n\n");//��� A B ���
	printf("��� A\n\n");
	print_matrix(arrA, x, y);//��� A���
	puts(" ");
	printf("��� B\n\n");
	print_matrix(arrB, x, y);//��� B���

	printf("\n2. ��� SUM (A+B) ���\n\n");//��� A+B
	addition_matrix(arrA, arrB, arrSUM, x, y);//���A,B�� �����ִ� �Լ��� �Ű�����
	print_matrix(arrSUM, x, y);

	printf("\n3. ��� SUB (A-B) ���\n\n");//��� A-B
	subtraction_matrix(arrA, arrB, arrSUB, x, y);
	print_matrix(arrSUB, x, y);

	printf("\n4. ��� A�� ��ġ��� T ���\n\n");//A�� ��ġ���
	transpose_matrix(arrA, arrT, x, y);
	print_matrix(arrT, y, x);//��� ���� �ٲ��Է��Ѵ�.


	printf("\n4. ��� A�� ��ġ��� T�� �� (A x T) ���\n\n");
	if (x != y)//��� ���� ���� �ٸ����
	{
		printf("��� ���� �Ȱ��� �Է����ּ���. ex)3 3 \n");
		return 1;
	}
	else {//������� ��ġ��İ� �Լ��� �̵��� ���� ���
    
		multiply_matrix(arrA, arrT, arrMUL, x, y);
		print_matrix(arrMUL, x, y);
	}

	free_matrix(arrA, x, y);//�����Ҵ�
	free_matrix(arrB, x, y);
	free_matrix(arrSUM, x, y);
	free_matrix(arrSUB, x, y);
	free_matrix(arrMUL, x, y);//��������

	if (x == y) {  // �����Ҵ��� ����
		free_matrix(arrT, x, y);
	}
	if (x != y) {
		free_matrix(arrT, x, y);
	}
	free_matrix(arrMUL, x, y);
	return 0;
}

int **create_matrix(int row, int col)//����ڰ� ���ϴ� ��ŭ ������� �������� �״����ش�.
{
	if (row <= 0 || col <= 0) { /* check pre conditions */  //��ó���˻�
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	else
	{
		int **x;
		x = (int**)malloc(row * sizeof(int*));
		for (int i = 0; i < row; i++) {
			x[i] = (int*)malloc(col * sizeof(int*));//�迭x�� �����Ҵ����ش�.
			for (int j = 0; j < col; ++j) {
				x[i][j] = 0;
			}
		}
		if (x == NULL) {/* check post conditions */  //��ó���˻�
			printf(" �߸��� ���Դϴ�. ");
		}
		return x;
	}
}

int fill_data(int **matrix, int row, int col)//�������� ����
{
	//srand((unsigned)time(NULL));
	for (int a = 0; a < row; a++)
	{
		for (int b = 0; b < col; b++)
		{
			matrix[a][b] = rand() % 20;//0����19�߿��� �������� ���� ����
		}
	}
	return **matrix;
}

void print_matrix(int** matrix, int row, int col)//matrix���
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

int addition_matrix(int** matrix_a, int **matrix_b, int* *matrix_sum, int row, int col)		//matrixSUM ���
{
	if (row <= 0 || col <= 0) {/* check pre conditions */  //��ó���˻�
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
	if (matrix_sum == NULL) {/* check post conditions */  //��ó���˻�
		printf(" �߸��� ���Դϴ�. ");
	}
	return **matrix_sum;
}

int subtraction_matrix(int **matrix_a, int **matrix_b, int **matrix_sub, int row, int col)	//����� ����
{
	if (row <= 0 || col <= 0) {/* check pre conditions */  //��ó���˻�
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
	if (matrix_sub == NULL) {/* check post conditions */  //��ó���˻�
		printf(" �߸��� ���Դϴ�. ");
	}
	return **matrix_sub;
}

int transpose_matrix(int **matrix_a, int **matrix_t, int row, int col) //����� ��ġ
{
	if (row <= 0 || col <= 0) {/* check pre conditions */  //��ó���˻�
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
    
	if (matrix_t == NULL) {/* check post conditions */  //��ó���˻�
		printf(" �߸��� ���Դϴ�. ");
	}
	return **matrix_t;
}

int multiply_matrix(int **matrix_a, int **matrix_t, int **matrix_axt, int row, int col) //����� ����
{
	if (row <= 0 || col <= 0) { /* check pre conditions */  //��ó���˻�
		printf("Check the sizes of row and col!\n");
		return NULL;
	}
	for (int i = 0; i < row; ++i) {  //matrix_axt �迭�ʱ�ȭ
		for (int j = 0; j < col; ++j)
			matrix_axt[i][j] = 0;
	}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < row; j++)
			for (int k = 0; k < col; k++) {
				matrix_axt[i][j] += matrix_a[i][k] * matrix_t[k][j];
			}


	/* check post conditions */  //��ó���˻�
	if (matrix_axt == NULL)
	{
		printf(" �߸��� ���Դϴ�. ");

	}
	return **matrix_axt;
}

int free_matrix(int** matrix, int row, int col)												//�迭 ����
{
	for (int i = 0; i < row; ++i)  //for���� ���� ����������
		free(matrix[i]);
	free(matrix);

	
	return 0;
}

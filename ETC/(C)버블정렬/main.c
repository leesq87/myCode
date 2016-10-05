/*
Ex)��������
���������� �����Ͻÿ�.
�ߺ����� �ʴ� ���� 10���� �����Ͽ� ũ�Ⱑ 10�� �迭�� ��´�.
�������� / �������� ���Ĺ�� 2���߿� �ϳ��� �����Ѵ�.
���õ� ���Ĺ������ ���������Ѵ�.
��, ���ĵǴ� ������ ��� ����ؾ� �Ѵ�.
*/

#include <stdio.h>
#include<stdlib.h>
#include<time.h>


void CreateNum(int *arr, int num);
void AscBubbleSort(int *arr, int k);
void DesBubbleSort(int *arr, int k);
void Printnum(int *arr, int k);

int main() {
	int arr[10];
	int sel;

	CreateNum(arr, 10);
	printf("������ ���� : ");
	Printnum(arr, 10);
	printf("1.�������� 2.��������\n�Է�:");
	scanf("%d", &sel);
	if (sel == 1) {
		AscBubbleSort(arr, 10);
		printf("�������� ���İ�� : ");
		Printnum(arr, 10);
	}
	else {
		DesBubbleSort(arr, 10);
		printf("�������� ���İ�� : ");
		Printnum(arr, 10);
	}
}

void CreateNum(int *arr, int num) {
	srand((unsigned)time(NULL));
	int cnt1 = 1;
	int cnt2 = 0;
	for (int i = 0; i < num; i++) {
		arr[i] = rand()%99+1;
		for (int j = 0; j < i; j++) {
			if (arr[j] == arr[i]) {
				i--;
				break;
			}
		}
	}
}

void Printnum(int *arr, int k) {
	for (int i = 0; i < k; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void AscBubbleSort(int *arr, int k) {
	int temp;
	int cnt1 = 0, cnt2;

	for (int i = k - 1; i > 0; i--) {
		cnt1++;
		printf("*******  %dȸ��  *******\n", cnt1);
		cnt2 = 1;
		for (int j = 1; j <= i; j++) {
			if (arr[j - 1] > arr[j]) {
				temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
			printf("%dȽ�� : ", cnt2);
			Printnum(arr, 10);
			cnt2++;
		}
	}
}

void DesBubbleSort(int *arr, int k) {
	int temp;
	int cnt1 =0 , cnt2;

	for (int i = k - 1; i > 0; i--) {
		cnt1++;
		printf("*******  %dȸ��  *******\n", cnt1);
		cnt2 = 1;
		for (int j = 1; j <= i; j++) {
			if (arr[j - 1] < arr[j]) {
				temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
			printf("%dȽ�� : ", cnt2);
			Printnum(arr, 10);
			cnt2++;
		}
		cnt1++;
	}
}



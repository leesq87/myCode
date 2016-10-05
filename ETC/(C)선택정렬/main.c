/*
Exam)��������
�ߺ����� �ʴ� ���� 10��(1~99)�� �����Ͽ� ũ�Ⱑ 10�� �迭�� ��´�.
�������� / �������� ���Ĺ�� 2���߿� �ϳ��� �����Ѵ�.
���õ� ���Ĺ������ ���������Ѵ�.
���������̶� �迭�� ��ĵ���� ����ū��(������)�� �����ϴ� �˰����̴�
��, ���ĵǴ� ������ ��� ����ؾ� �Ѵ�.
*/

#include <stdio.h>
#include<stdlib.h>
#include<time.h>

void CreateNum(int *arr, int num);
void AscSelectSort(int *arr, int k);
void DesSelectSort(int *arr, int k);
void PrintNum(int *arr, int k);

int main() {
	int arr[10];
	int sel;

	CreateNum(arr, 10);
	printf("������ ���� : ");
	PrintNum(arr, 10);
	printf("1.�������� 2.��������\n�Է�:");
	scanf("%d", &sel);
	if (sel == 1) {
		AscSelectSort(arr, 10);
		printf("�������� ���İ�� : ");
		PrintNum(arr, 10);
	}
	else {
		DesSelectSort(arr, 10);
		printf("�������� ���İ�� : ");
		PrintNum(arr, 10);
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

void PrintNum(int *arr, int k) {
	for (int i = 0; i < k; i++)
	printf("%d ", arr[i]);
	printf("\n");
}

void AscSelectSort(int *arr, int k) {
	int temp;
	int max;
	int cnt = 1;
	for (int i = k - 1; i > 0; i--) {
		max = arr[0];
		temp = 0;
		for (int j = 0; j <= i; j++) {
			if (max < arr[j]) {
				max = arr[j];
				temp = j;
			}
		}
		arr[temp] = arr[i];
		arr[i] = max;
		printf("%d ȸ����� : ", cnt);
		PrintNum(arr,10);
		cnt++;
	}
}
void DesSelectSort(int *arr, int k) {
	int temp;
	int min;
	int cnt = 1;
	for (int i = k - 1; i > 0; i--) {
		min = arr[0];
		temp = 0;
		for (int j = 0; j <= i; j++) {
			if (min > arr[j]) {
				min = arr[j];
				temp = j;
			}
		}
		arr[temp] = arr[i];
		arr[i] = min;
		printf("%d ȸ����� : ", cnt);
		PrintNum(arr, 10);
		cnt++;
	}
}



/*
Exam)선택정렬
중복되지 않는 난수 10개(1~99)를 생성하여 크기가 10인 배열에 담는다.
오름차순 / 내림차순 정렬방법 2개중에 하나를 선택한다.
선택된 정렬방법으로 선택정렬한다.
선택정렬이란 배열을 스캔한후 가장큰수(작은수)를 스왑하는 알고리즘이다
단, 정렬되는 과정을 모두 출력해야 한다.
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
	printf("생성된 난수 : ");
	PrintNum(arr, 10);
	printf("1.오름차순 2.내림차순\n입력:");
	scanf("%d", &sel);
	if (sel == 1) {
		AscSelectSort(arr, 10);
		printf("오름차순 정렬결과 : ");
		PrintNum(arr, 10);
	}
	else {
		DesSelectSort(arr, 10);
		printf("내림차순 정렬결과 : ");
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
		printf("%d 회전결과 : ", cnt);
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
		printf("%d 회전결과 : ", cnt);
		PrintNum(arr, 10);
		cnt++;
	}
}



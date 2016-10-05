/*
Ex)버블정렬
버블정렬을 구현하시오.
중복되지 않는 난수 10개를 생성하여 크기가 10인 배열에 담는다.
오름차순 / 내림차순 정렬방법 2개중에 하나를 선택한다.
선택된 정렬방법으로 버블정렬한다.
단, 정렬되는 과정을 모두 출력해야 한다.
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
	printf("생성된 난수 : ");
	Printnum(arr, 10);
	printf("1.오름차순 2.내림차순\n입력:");
	scanf("%d", &sel);
	if (sel == 1) {
		AscBubbleSort(arr, 10);
		printf("오름차순 정렬결과 : ");
		Printnum(arr, 10);
	}
	else {
		DesBubbleSort(arr, 10);
		printf("내림차순 정렬결과 : ");
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
		printf("*******  %d회전  *******\n", cnt1);
		cnt2 = 1;
		for (int j = 1; j <= i; j++) {
			if (arr[j - 1] > arr[j]) {
				temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
			printf("%d횟수 : ", cnt2);
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
		printf("*******  %d회전  *******\n", cnt1);
		cnt2 = 1;
		for (int j = 1; j <= i; j++) {
			if (arr[j - 1] < arr[j]) {
				temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
			printf("%d횟수 : ", cnt2);
			Printnum(arr, 10);
			cnt2++;
		}
		cnt1++;
	}
}



#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int RandonNumCreate();
void Compare(int a, int b);
int ReadNum();
void OutputChar(int a);

int main() {
	int me, com;
	int cnt=1;
	printf("가위바위보게임\n");

	while (1) {
		printf("******  %d 라운드  ******\n", cnt);
		me = ReadNum();
		if (me == 4)
			break;
		if (me != 1 && me != 2 && me != 3) {
			printf("잘못입력하셨습니다. 다시입력해주세요\n\n");
			continue;
		}
		com = RandonNumCreate();
		printf("사용자 : ");
		OutputChar(me);
		printf("컴퓨터 : ");
		OutputChar(com);
		Compare(me, com);
		cnt++;
	}
	printf("게임종료\n");
}

int ReadNum() {
	int a;
	printf("1.가위  2.바위  3.보  4.종료\n");
	printf("입력: ");
	scanf("%d", &a);
	return a;
}

int RandonNumCreate() {
	int a;
	srand((int)time(NULL));
	a = rand() % 3 + 1;
	return a;
}
void Compare(int a, int b) {
	if (a == b)
		printf("결과 : 무승부\n\n");
	else if ((a == 1 && b == 2) || (a == 2 && b == 3) || (a == 3 && b == 1))
		printf("결과 : 패배\n\n");
	else
		printf("결과 : 승리\n\n");
}

void OutputChar(int a) {
	if (a == 1)
		printf("가위\t");
	else if (a == 2)
		printf("바위\t");
	else
		printf("보\t");
}


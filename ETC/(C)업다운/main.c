/*
업다운게임

1.컴퓨터는 1~100사이의 숫자 하나를 생성한다.
2.총 시도횟수는 7번을 부여한다.
3.사용자는 7번의 시도안에 숫자를 맞춰야 한다.
4.사용자가 숫자를 입력했을때 컴퓨터는 높은지/낮은지 알려준다.
5.7번안에 맞추면 성공, 맞추지 못하면 실패
6.성공/실패 후 계속 할지를 물어보고 Y면 게임 재시작, N이면 프로그램을 종료한다.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int RandonNumCreate();
void SelNum();
void Compare(int user, int com);
int Continue();

int main() {
	int round = 1;
	while (1) {
		printf("%d라운드!!\n", round);
		SelNum();
		if (Continue() == 2)
			break;
		round++;

	}
}

int Continue() {
	char st;
	while (1) {
		printf("계속하시겠습니까?(Y/N)  입력: ");
		scanf(" %c", &st);
		if (st != 'Y'&&  st != 'y' && st != 'N' && st != 'n') {
			printf("잘못입력하셨습니다. 다시 입력해주세요.\n");
			continue;
		}
		else
			break;
	}
	if (st == 'Y' || st == 'y')
		return 1;
	else
		return 2;
}

void SelNum() {
	int user, com, count = 1;
	com = RandonNumCreate();

	for (int i = 1; i <= 7; i++) {
		printf("%d 번째 기회, 숫자입력: ", i);
		scanf("%d", &user);
//		getchar();
		if (user == com) {
			printf("성공!!\n");
			break;
		}
		else
			Compare(user, com);
		if (i == 7)
			printf("실패. 숫자: %d\n",com);
	}
}

void Compare(int user, int com) {
	if (user > com)
		printf("다운!\n");
	else if (user < com)
		printf("업!\n");
}

int RandonNumCreate() {
	int a;
	srand((int)time(NULL));
	a = rand() % 100 + 1;
	return a;
}


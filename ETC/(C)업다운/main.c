/*
���ٿ����

1.��ǻ�ʹ� 1~100������ ���� �ϳ��� �����Ѵ�.
2.�� �õ�Ƚ���� 7���� �ο��Ѵ�.
3.����ڴ� 7���� �õ��ȿ� ���ڸ� ����� �Ѵ�.
4.����ڰ� ���ڸ� �Է������� ��ǻ�ʹ� ������/������ �˷��ش�.
5.7���ȿ� ���߸� ����, ������ ���ϸ� ����
6.����/���� �� ��� ������ ����� Y�� ���� �����, N�̸� ���α׷��� �����Ѵ�.
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
		printf("%d����!!\n", round);
		SelNum();
		if (Continue() == 2)
			break;
		round++;

	}
}

int Continue() {
	char st;
	while (1) {
		printf("����Ͻðڽ��ϱ�?(Y/N)  �Է�: ");
		scanf(" %c", &st);
		if (st != 'Y'&&  st != 'y' && st != 'N' && st != 'n') {
			printf("�߸��Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.\n");
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
		printf("%d ��° ��ȸ, �����Է�: ", i);
		scanf("%d", &user);
//		getchar();
		if (user == com) {
			printf("����!!\n");
			break;
		}
		else
			Compare(user, com);
		if (i == 7)
			printf("����. ����: %d\n",com);
	}
}

void Compare(int user, int com) {
	if (user > com)
		printf("�ٿ�!\n");
	else if (user < com)
		printf("��!\n");
}

int RandonNumCreate() {
	int a;
	srand((int)time(NULL));
	a = rand() % 100 + 1;
	return a;
}


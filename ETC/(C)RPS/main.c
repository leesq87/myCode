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
	printf("��������������\n");

	while (1) {
		printf("******  %d ����  ******\n", cnt);
		me = ReadNum();
		if (me == 4)
			break;
		if (me != 1 && me != 2 && me != 3) {
			printf("�߸��Է��ϼ̽��ϴ�. �ٽ��Է����ּ���\n\n");
			continue;
		}
		com = RandonNumCreate();
		printf("����� : ");
		OutputChar(me);
		printf("��ǻ�� : ");
		OutputChar(com);
		Compare(me, com);
		cnt++;
	}
	printf("��������\n");
}

int ReadNum() {
	int a;
	printf("1.����  2.����  3.��  4.����\n");
	printf("�Է�: ");
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
		printf("��� : ���º�\n\n");
	else if ((a == 1 && b == 2) || (a == 2 && b == 3) || (a == 3 && b == 1))
		printf("��� : �й�\n\n");
	else
		printf("��� : �¸�\n\n");
}

void OutputChar(int a) {
	if (a == 1)
		printf("����\t");
	else if (a == 2)
		printf("����\t");
	else
		printf("��\t");
}


/*
Ex)����ã��
	1.���ڿ͹��ڸ� �������� �Է¹޴´�. > 123abc654ijuyh
	2.���߿� ���ڸ� ã�Ƴ���.
	3.ã�Ƴ� ������ ���� ���ؼ� ����Ѵ�.
*/

#include<stdio.h>
int main() {
	char str[100];
	int cnt = 0;
	int sum = 0;

	printf("�����͸� �Է��� �ּ��� : ");
	scanf("%s", str);
	printf("�Է¹������� : %s\n", str);

	while (str[cnt] != '\0')
		cnt++;
	for (int i = 0; i < cnt; i++) {
		if ((int)str[i] >= 48 && (int)str[i] <= 57) {
			printf("%c -> ����\n", str[i]);
			sum = sum + (int)str[i] - 48;
		}
		else
			printf("%c -> ����\n", str[i]);
	}
	printf("������ �� : %d\n", sum);
}	


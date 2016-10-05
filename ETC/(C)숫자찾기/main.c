/*
Ex)숫자찾기
	1.숫자와문자를 무작위로 입력받는다. > 123abc654ijuyh
	2.이중에 숫자만 찾아낸다.
	3.찾아낸 숫자의 합을 구해서 출력한다.
*/

#include<stdio.h>
int main() {
	char str[100];
	int cnt = 0;
	int sum = 0;

	printf("데이터를 입력해 주세요 : ");
	scanf("%s", str);
	printf("입력받은문자 : %s\n", str);

	while (str[cnt] != '\0')
		cnt++;
	for (int i = 0; i < cnt; i++) {
		if ((int)str[i] >= 48 && (int)str[i] <= 57) {
			printf("%c -> 숫자\n", str[i]);
			sum = sum + (int)str[i] - 48;
		}
		else
			printf("%c -> 문자\n", str[i]);
	}
	printf("숫자의 합 : %d\n", sum);
}	


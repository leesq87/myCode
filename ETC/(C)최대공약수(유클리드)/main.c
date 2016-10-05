#include <stdio.h>

int main() {
	int num1, num2;
	int gcd;

	printf("두개의 정수를 입력 : ");
	scanf("%d %d", &num1, &num2);

	while (1)
		if (num1 >= num2) {
			if (num1 % num2 != 0) {
				num1 = num1%num2;
				printf("%d, %d\n", num1, num2);
			}
			else {
				gcd = num2;
				break;
			}
		}
		else {
			if (num2 % num1 != 0) {
				num2 = num2%num1;
				printf("%d, %d\n", num1, num2);
			}
			else {
				gcd = num1;
				break;
			}
		}
	printf("최대공약수 : %d\n", gcd);
}

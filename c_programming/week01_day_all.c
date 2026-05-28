#include <stdio.h>
#include <stdint.h>

#if 1 // Q. 자릿수 구하기 프로그램
int digit_count(int num)
{
	int count = 1;
	while (num > 9)
	{
		count++;
		num /= 10;
	}
	return count;
}
int digit_change(int num)
{
	int result = 0;
	while (num)
	{
		result = (result * 10) + (num % 10);
		num /= 10;
	}
	return result;
}
int main(void)
{
	int num = 0;
	do
	{
		printf("Enter number(1~10000000): "); scanf("%d", &num);
	} while (num < 1 || num > 10000000);
	printf("%d\n", digit_count(num));
	printf("original num : %d, changed num : %d\n", num, digit_change(num));
	return 0;
}
#endif

#if 0 // Q. 조건문 - 합격/불합격 판정 프로그램
void print_msg(int score)
{
	if (score >= 70) printf("\nTest PASS!\nThank you.\n");
	else if (score >= 60) printf("\nRe-Test!\nThank you.\n");
	else printf("\nTest NOT PASS!\nThank you.\n");
}
int main(void)
{
	int num = 0;
	do
	{
		printf("Enter score(0~100): "); scanf("%d", &num);
	} while (num < 0 || num > 100);
	print_msg(num);

	return 0;
}
#endif

#if 0 // Q. 조건문 - 배수 판단 프로그램
int func(int num)
{
	if (num % 2 == 0) return num = 2;
	if (num % 3 == 0) return num = 3;
	if (num % 5 == 0) return num = 5;
	
	return 0;
}
int main(void)
{
	int num = 15;
	printf("num = %d, result = %d", num, func(num));
	return 0;
}
#endif

#if 0 // 조건문 - 배열(학점)
int main(void)
{
	int score = 75;
	//char *grade = ['F', 'D', 'C', 'B', 'A'];
	char* grade = "FFFFFFDCBAA";
	printf("score : %d, grade : %c\n", score, grade[score/10]);
	return 0;
}
#endif

#if 0 // 승격화
int main(void)
{
	char a = 127, b = 1;
	printf("a + b = %d, sizeof(a+b) = %d\n", a+b, sizeof(a+b));
	return 0;
}
#endif

#if 0 // 복합 대입 연산자
int main(void)
{
	int a = 20, b = 5;
	 a %= b -= 1;
	//b = b - 1; a = a % b;
	printf("a = %d, b = %d\n", a, b);
	return 0;
}
#endif

#if 0 // 조건문
unsigned int num_check(unsigned int n)
{
	return (!(n % 3)) || (!(n % 5));
	//if (n % 3 == 0 || n % 5 == 0) return 1;
	//else return 0;
}
int main(void)
{
	int num = 0;
	do
	{
		printf("Enter number to check: "); scanf("%d", &num);
	} while (num < 0);
	printf("num_check: %u\n", num_check(num));

	return 0;
}
#endif

#if 0	// Q. 비트 여러개 세팅 및 2진법으로 출력
unsigned int setBits(unsigned int num, int start, int count)
{
	// V1. 최적화 버전
	return num | ((1 << count) - 1 << start);
	// V2. mask 사용한 버전
	//unsigned int mask = (1 << count) - 1;
	//return num | (mask << start);
	// V3. for문 사용한 버전
	//for(int i = start; i < start + count; i++) num |= 1 << i;
	//return num;
}
unsigned int clearBits(unsigned int num, int start, int count)
{
	// V1. 최적화 버전
	return num & ~(((1 << count) - 1) << start);
	// V2. mask 사용한 버전
	//unsigned int mask = (1 << count) - 1;
	//return num & ~(mask << start);
	// V3. for문 사용한 버전
	//for (int i = start; i < start + count; i++) num &= ~(1 << i);
	//return num;
}
unsigned int toggleBits(unsigned int num, int start, int count)
{
	// V1. 최적화 버전
	return num ^ (((1 << count) - 1) << start);
	// V2. mask 사용한 버전
	//unsigned int mask = (1 << count) - 1;
	//return num ^= (mask << start);
	// V3. for문 사용한 버전
	//for (int i = start; i < start + count; i++) num ^= (1 << i);
	//return num;
}
unsigned int isBitSet(unsigned int num, int bitPosition)
{
	return (num >> bitPosition) & 1;
}
void printBits(unsigned int num)
{
	unsigned int bit_check = 0;
	for (int i = sizeof(num) * 8 - 1; i >= 0; i--)
	{
		bit_check = (num >> i) & 1;
		printf("%u", bit_check);
		if (!(i % 4)) printf(" ");
	}
	printf("\n");
}

int main(void)
{
	unsigned int num = 0b10101010;
	printf("%X\n", setBits(num, 2, 3));			// 0b10111110 BE
	printf("%X\n", clearBits(num, 4, 2));		// 0b10001010 8A
	printf("%X\n", toggleBits(num, 1, 5));	// 0b10010100 94
	/*
	int num_input = 0, bitPosition = 0;
	do
	{
		printf("Enter a number : "); scanf("%u", &num_input);
		printf("Enter bit position to check (0-31): "); scanf("%u", &bitPosition);
	} while (num_input < 0 || bitPosition < 0);

	unsigned int res = isBitSet(num_input, bitPosition);
	printf("Bit %d of number %u is %u.\n", bitPosition, num_input, res);
	printBits(num_input);
	*/

	char x = -128;
	char y = x - 1;
	printf("x = %d, x - 1 = %d, y = %d\n", x, x - 1, y);
	printf("x : "); printBits((int)x); printf("\n");
	printf("x - 1 : "); printBits((int)x - 1); printf("\n");
	printf("y : "); printBits((int)y); printf("\n");
	return 0;
}
#endif

#if 0	// Q. 비트 1개 세팅
unsigned int setBit(unsigned int num, int position)
{
	return num | (1 << position);
}
unsigned int clearBit(unsigned int num, int position)
{
	return num & ~(1 << position);
}
unsigned int toggleBit(unsigned int num, int position)
{
	return num ^ (1 << position);
}

int main(void)
{
	unsigned int num = 0b1010;
	printf("%X\n", setBit(num, 2));			// 0b1110 E
	printf("%X\n", clearBit(num, 1));		// 0b1000 8
	printf("%X\n", toggleBit(num, 3));	// 0b0010 2

	return 0;
}
#endif

#if 0	// 도입
int main(void)
{
	/* stdint.h 헤더 사용(int32_t)
	int32_t A = 0;
	if (A = 10) printf("A : %d\n", A);
	// A == 0 ? printf("S\n") : printf("F\n");
	*/

	/* 배열과 포인터
	int a[3][4];
	int *b = a; // int (*b)[4] = a; // int *b = &(a[0][0]);
	printf("&a+1 b+1 = %p %p\n", &(a[1]), b + (1 * sizeof(int)));
	*/

	/* const 사용해도 메모리는 읽고 쓰는게 가능
	const int num = 10;
	int *p = &num;
	*p = 100;
	printf("num = %d\n", num);
	*/

	return 0;
}
#endif
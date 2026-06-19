/*
The MIT License (MIT)

Copyright (c) 2015 guileschool

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/*
	제목: 은행 정기 예금 가입 프로그램
	설명: 1년 정기 예금 이자율을 보여주고 사용자 가입을 유도하는 프로그램
*/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <process.h>

#define DEMOAMOUNT 1000000 // 백만원
#define TAXRATE    0.154   // 15.4% 세율
#define D_MAX      1000000000000 // 만억원(유효숫자 13개 미만으로 설정)

// 전국은행고시율 확인 https://portal.kfb.or.kr/compare/receiving_neosearch.php
const float PreTaxRate = 1.20f;			// 세전금리
const float AfterTaxRate = 1.02f;		// 세후금리
const float HighestPreferRate =  1.90f;		// 최고우대금리
const float MidCancelRate = 0.33f;				// 중도해지금리
const char InterestCalcMethod[] = "단리";	// 이자계산방식(단리)
double MyInterestAfterTaxRate = 0.0f;			// 세후이자
double EstimatedAmount = 0.0f;				// 만기시예상금액
double amount = DEMOAMOUNT;	// 고객 정기 예금 가입액(menu3에서 menu2 함수 사용을 위해 초기화 값 변경)

// 전역 변수
const char subMenu[][50] = {
	"은행 현재 고시 이자율 확인",
	"나의 예상 수익율 확인",
	"정기 예금 가입하기",
	"종료하기",
	"# 아무키나 입력하면 메인 메뉴로 돌아갑니다"
};

// 함수 선언부
void prompt(int xx, int yy);
int displayMenu(void);
void menu1(void);
void menu2(void);
void menu3(void);

int main()
{
	int select;

	while(1)
	{
		select = displayMenu();		// 메뉴 화면 출력
		if(select=='4') {break;}	// 'exit'
		switch(select){
			case '1' : menu1(); break;
			case '2' : menu2(); break;
			case '3' : menu3(); break;
		}
	}

	// 마무리(exit)
	printf("계속하려면 아무 키나 누르십시오 . . .\n");
	getch();

	printf("\n------------------------------------------------------------------------\n");
	printf("written by : 김은혜\n");
	printf("------------------------------------------------------------------------\n");

	return 0;
}

// prompt
void prompt(int xx, int yy)
{
	COORD locate = {xx-1, yy-1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), locate);
}

// displayMenu
int displayMenu(void)
{
	int select = 0;

	system("cls");
	for(int i=0; i < 4; i++){
		prompt(30, 4+i*2);
		printf("%2d. %s", i+1, subMenu[i]);
	}
	while(select < '1' || select > '4'){
		prompt(25, 17); printf("* 원하시는 메뉴를 선택하세요 : _\b");
		select = getchar();
		fflush(stdin);
	}

	return(select);
}

// menu1 : 은행 현재 고시 이자율 확인
void menu1(void)
{
	system("cls");
	prompt(1, 7);   printf("%s", subMenu[0]);
	prompt(1, 11);  printf("세전금리 세후금리 최고우대금리 중도해지금리 이자계산방식");
	prompt(1, 13);  printf("---------------------------------------------------------");
	prompt(3, 15);  printf("%.2f", PreTaxRate);					// 세전금리
	prompt(12, 15); printf("%.2f", AfterTaxRate);				// 세후금리
	prompt(23, 15); printf("%.2f", HighestPreferRate);	// 최고우대금리
	prompt(36, 15); printf("%.2f", MidCancelRate);			// 중도해지금리
	prompt(48, 15); printf("%s", InterestCalcMethod);		// 이자계산방식
	prompt(1, 17);  printf("---------------------------------------------------------");
	prompt(1, 19);  printf("%s", subMenu[4]);
	getch();
}

// menu2 : 나의 예상 수익율 확인
void menu2(void)
{
	MyInterestAfterTaxRate = amount * (AfterTaxRate / 100);	// 세후이자 계산
	EstimatedAmount = amount + MyInterestAfterTaxRate;			// 만기시예상금액 계산

	// display
	system("cls");
	prompt(1, 7);   printf("%s(%.0lf 원 입금 기준)", subMenu[1], amount);
	prompt(1, 11);  printf("세전금리 세후금리 최고우대금리 중도해지금리 이자계산방식 세후이자 만기시예상금액");
	prompt(1, 13);  printf("--------------------------------------------------------------------------------");
	prompt(3, 15);  printf("%.2f", PreTaxRate);		// 세전금리
	prompt(12, 15); printf("%.2f", AfterTaxRate);	// 세후금리
	prompt(23, 15); printf("%.2f", HighestPreferRate);	// 최고우대금리
	prompt(36, 15); printf("%.2f", MidCancelRate);			// 중도해지금리
	prompt(48, 15); printf("%s", InterestCalcMethod);		// 이자계산방식
	prompt(59, 15); printf("%.0lf", MyInterestAfterTaxRate);	// 세후이자
	prompt(71, 15); printf("%.0lf", EstimatedAmount);		// 만기시예상금액
	prompt(1, 17);  printf("--------------------------------------------------------------------------------");
	prompt(1, 19);  printf("%s", subMenu[4]);
	getch();
}

// menu3 : 정기 예금 가입하기
void menu3(void)
{
	char menu3_input = '\0';
	system("cls");

	do
	{
		system("cls");

		// 사용자로부터 예금액수(amount) 입력 받기
		prompt(1, 7); printf("원하시는 예금 액수를 입력하세요: _\b");
		scanf("%lf", &amount);
		fflush(stdin); getchar();	// 버퍼 완전히 비우기

		// 예외처리 : 설정한 유효범위의 자리 넘어가거나 1원 미만일 경우 다시 입력 받기
		if((amount > D_MAX) || (amount < 1))
		{
			prompt(1, 9); printf("만억원을 초과하였거나 1보다 작은 값이 입력되었습니다. 다시 입력해주세요.");
			prompt(1, 11); printf("# 아무키나 입력하여 이전으로 돌아갑니다.");
			getch();
			continue;
		}

		// 사용자로부터 예금액수 확인 받기
		system("cls");
		prompt(1, 5); printf("계약금액 %.0lf 원", amount);
		prompt(1, 7); printf("입력하신 내용이 맞습니까(y/n)? _\b");
		menu3_input = getch();
		fflush(stdin);
		system("cls");
	} while((menu3_input != 'y') && (menu3_input != 'Y'));

	// 입력 받은 예금액수로 계산된 화면 출력(기존 menu2 함수 사용)
	menu2();

	// 고객 정기 예금 가입액 DEMOAMOUNT로 초기화 -> menu3에서 menu2 함수 사용하기 위함
	amount = DEMOAMOUNT;
	menu3_input = '\0';	// 사용자 입력 값 초기화
}

// 실행 결과 주석
/* main 메뉴 display
                              1. 은행 현재 고시 이자율 확인

                              2. 나의 예상 수익율 확인

                              3. 정기 예금 가입하기

                              4. 종료하기






                        * 원하시는 메뉴를 선택하세요 : _
*/
/* menu1 display
은행 현재 고시 이자율 확인



세전금리 세후금리 최고우대금리 중도해지금리 이자계산방식

---------------------------------------------------------

  1.20     1.02       1.90         0.33        단리

---------------------------------------------------------

# 아무키나 입력하면 메인 메뉴로 돌아갑니다
*/
/* menu2 display
나의 예상 수익율 확인(1000000 원 입금 기준)



세전금리 세후금리 최고우대금리 중도해지금리 이자계산방식 세후이자 만기시예상금액

--------------------------------------------------------------------------------

  1.20     1.02       1.90         0.33        단리       10200       1010200

--------------------------------------------------------------------------------

# 아무키나 입력하면 메인 메뉴로 돌아갑니다
*/
/* menu3 display 1
원하시는 예금 액수를 입력하세요: _
*/
/* menu3 display 1_1 (입력값 : -1) // 예외처리
원하시는 예금 액수를 입력하세요: -1

만억원을 초과하였거나 1보다 작은 값이 입력되었습니다. 다시 입력해주세요.

# 아무키나 입력하여 이전으로 돌아갑니다.
*/
/* menu3 display 2 (입력값 : 15000)
계약금액 15000 원

입력하신 내용이 맞습니까(y/n)? _
*/
/* menu3 display 3 (입력값 : y)
나의 예상 수익율 확인(15000 원 입금 기준)



세전금리 세후금리 최고우대금리 중도해지금리 이자계산방식 세후이자 만기시예상금액

--------------------------------------------------------------------------------

  1.20     1.02       1.90         0.33        단리       153         15153

--------------------------------------------------------------------------------

# 아무키나 입력하면 메인 메뉴로 돌아갑니다
*/
/* main exit display
                              1. 은행 현재 고시 이자율 확인

                              2. 나의 예상 수익율 확인

                              3. 정기 예금 가입하기

                              4. 종료하기






                        * 원하시는 메뉴를 선택하세요 : 4
계속하려면 아무 키나 누르십시오 . . .

------------------------------------------------------------------------
written by : 김은혜
------------------------------------------------------------------------
*/
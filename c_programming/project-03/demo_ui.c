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
	제목: 텍스트 기반 UI 생성 템플릿
	설명: 
	*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <process.h>

int displayMenu(void);
void menu1(void);
void menu2(void);
void menu3(void);
void prompt(int, int);

int main(void)
{
	int select;

	while(1)
	{
		select = displayMenu(); // 메뉴 화면 출력
		if(select=='4') {break;}  // 'exit'
		switch(select){
			case '1' : menu1(); break;
			case '2' : menu2(); break;
			case '3' : menu3(); break;
		}
	}
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
	int i;
	char subMenu[][20] = { "서브메뉴1", "서브메뉴2", "서브메뉴3", "종료하기" };

	system("cls");
	for(i=0; i < 4; i++){
		prompt(30, 4+i*2);
		printf("%2d. %s", i+1, subMenu[i]);
	}
	while(select < '1' || select > '4'){
		prompt(25, 17);printf("* 원하시는 메뉴를 선택하세요 : _\b");
		select = getchar();
		fflush(stdin);
	}
	return(select);
}

// menu1
void menu1(void)
{
	system("cls");
	prompt(30, 7); printf("서브 메뉴1");
	prompt(20, 20); printf("# 아무키나 입력하면 메인 메뉴로 돌아갑니다");
	getch();
}

// menu2
void menu2(void)
{
	system("cls");
	prompt(30, 7); printf("서브 메뉴2");
	prompt(20, 20); printf("# 아무키나 입력하면 메인 메뉴로 돌아갑니다");
	getch();
}

// menu3
void menu3(void)
{
	system("cls");
	prompt(30, 7); printf("서브 메뉴3");
	prompt(20, 20); printf("# 아무키나 입력하면 메인 메뉴로 돌아갑니다");
	getch();
}

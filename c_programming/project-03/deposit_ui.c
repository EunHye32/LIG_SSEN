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

// 전국은행고시율 확인 https://portal.kfb.or.kr/compare/receiving_neosearch.php
const float PreTaxRate = 1.20f; //세전금리
const float AfterTaxRate = 1.02f; //세후금리
const float HighestPreferRate =  1.90f; //최고우대금리
const float MidCancelRate = 0.33f; //중도해지금리
const char InterestCalcMethod[] = "단리"; //이자계산방식(단리)
float MyInterestAfterTaxRate = 0.0f; //세후이자
float EstimatedAmount = 0.0f; //만기시예상금액
float amount = 0.0f; // 고객 정기 예금 가입액

int main() {


    printf("\n------------------------------------------------------------------------\n");
    printf("written by : 홍길동\n");
    printf("------------------------------------------------------------------------\n");
    return 0;
}


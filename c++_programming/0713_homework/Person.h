#pragma once
#include <string>
#include <iostream>
using namespace std;

class Person {
private:
	int num;
	string name;
	string tel;
public:
	Person() :num(0), name(""), tel("") {}
	Person(int num, string name, string tel) :num(num), name(name), tel(tel) {}
	string toString() const;
	void setTel(string tel);
	int getNum();
};

class PersonArr {		//dao. 배열에 추가, 검색, 수정, 삭제
private:
	Person* arr[10];  //Person 주소 갖음. 소멸자에서 Person*를 해제
	int cnt;	//요소 개수`
public:
	PersonArr() :cnt(0), arr({ NULL, }) {}
	~PersonArr();
	bool addPerson(Person* p);
	Person* getPerson(int idx);
	int getPersonIdx(int num);
	int getCnt();
	void delPerson(int idx);
};

class PersonService {
private:
	PersonArr arr;	//포함관계. has a 관계
public:
	void add();
	void get();
	void edit();
	void del();
	void printAll();
};
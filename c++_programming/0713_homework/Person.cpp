#include "Person.h"
/// Person 멤버 함수 구현 //////
string Person::toString() const {
	//to_string(숫자) : 숫자를 문자열로 변환
	return "";
}

//멤버 tel setter
void Person::setTel(string tel) {

}
//멤버변수 num 리턴
int Person::getNum() {

}

/// PersonArr 멤버 함수 구현 //////

//배열에 Person 주소를 끝에 추가
bool PersonArr::addPerson(Person* p) {

	return false;
}

//인덱스로 Person주소를 반환
Person* PersonArr::getPerson(int idx) {

}

//번호로 검색을 해서 방번호 반환
int PersonArr::getPersonIdx(int num) {

	return -1;
}

//요소 개수 반환
int PersonArr::getCnt() {

}

//삭제할 방번호를 파람으로 받아서 해당 방의 Person객체 메모리 해제, 방을 한칸씩 앞으로 이동
void PersonArr::delPerson(int idx) {

}

//현재 객체가 소멸되기 전에 배열에 저장된 모든 Person 객체 메모리 해제
PersonArr::~PersonArr() {
	cout << "=== del all item ===" << endl;

}

/// PersonService 멤버 함수 구현 //////
void PersonService::add() {
	int num, idx = 0;
	string name, tel;
	cout << "=== add ===" << endl;


}

void PersonService::get() {
	int num, idx;
	cout << "=== search ===" << endl;
	cout << "search num:";

}

void PersonService::edit() {
	int num, idx;
	string tel;
	cout << "=== edit ===" << endl;
	cout << "edit num:";

}
void PersonService::del() {
	int num, idx;
	cout << "=== del ===" << endl;
	cout << "del num:";
	cin >> num;

}
void PersonService::printAll() {
	cout << "=== printAll ===" << endl;
	for (int i = 0;i < arr.getCnt();i++) {
		cout << arr.getPerson(i)->toString() << endl;
	}
}
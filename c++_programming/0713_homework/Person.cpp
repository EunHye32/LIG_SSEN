#include "Person.h"
/// Person 멤버 함수 구현 //////

string Person::toString() const {
	//to_string(숫자) : 숫자를 문자열로 변환
	return "Num: " + to_string(num) + ", name: " + name + ", phone: " + tel;
}

//멤버 tel setter
void Person::setTel(string tel) {
	this->tel = tel;
}

//멤버변수 num 리턴
int Person::getNum() {
	return num;
}

/// PersonArr 멤버 함수 구현 //////

//배열에 Person 주소를 끝에 추가
bool PersonArr::addPerson(Person* p) {
	if (cnt < 10) {
		arr[cnt++] = p;
		return true;
	}
	return false;
}

//인덱스로 Person주소를 반환
Person* PersonArr::getPerson(int idx) {
	if (idx >= 0 && idx < cnt) return arr[idx];
	return nullptr;
}

//번호로 검색을 해서 방번호 반환
int PersonArr::getPersonIdx(int num) {
	for (int i = 0; i < cnt; i++) {
		if (arr[i]->getNum() == num) return i;
	}
	return -1;
}

//요소 개수 반환
int PersonArr::getCnt() {
	return cnt;
}

//삭제할 방번호를 파람으로 받아서 해당 방의 Person객체 메모리 해제, 방을 한칸씩 앞으로 이동
void PersonArr::delPerson(int idx) {
	if (idx < 0 || idx >= cnt) return;
	delete arr[idx];
	for (int i = idx; i < cnt - 1; i++) {
		arr[i] = arr[i + 1];
	}
	arr[cnt - 1] = nullptr;
	cnt--;
}

//현재 객체가 소멸되기 전에 배열에 저장된 모든 Person 객체 메모리 해제
PersonArr::~PersonArr() {
	cout << "=== del all item ===" << endl;
	for (int i = 0; i < cnt; i++) {
		cout << "del item: " << arr[i]->toString() << endl;
		delete arr[i];
	}
}

/// PersonService 멤버 함수 구현 //////
void PersonService::add() {
	int num, idx = 0;
	string name, tel;
	cout << "=== add ===" << endl;
	cout << "Num: "; cin >> num;
	cout << "Name: "; cin >> name;
	cout << "Phone: "; cin >> tel;

	// 헤더의 Person(int, string, string) 생성자 호출
	arr.addPerson(new Person(num, name, tel));
}

void PersonService::get() {
	int num, idx;
	cout << "=== search ===" << endl;
	cout << "search num: "; cin >> num;
	idx = arr.getPersonIdx(num);
	if (idx != -1) cout << arr.getPerson(idx)->toString() << endl;
	else cout << "Can't find number." << endl;

}

void PersonService::edit() {
	int num, idx;
	string tel;
	cout << "=== edit ===" << endl;
	cout << "edit num:"; cin >> num;
	idx = arr.getPersonIdx(num);
	if (idx != -1) {
		cout << "New phone number: "; cin >> tel;
		arr.getPerson(idx)->setTel(tel);
	}
	else {
		cout << "Can't find number." << endl;
	}
}

void PersonService::del() {
	int num, idx;
	cout << "=== del ===" << endl;
	cout << "del num:"; cin >> num;
	idx = arr.getPersonIdx(num);
	if (idx != -1) {
		arr.delPerson(idx);
		cout << "Delete complete." << endl;
	}
	else {
		cout << "Can't find number." << endl;
	}
}

void PersonService::printAll() {
	cout << "=== printAll ===" << endl;
	for (int i = 0;i < arr.getCnt();i++) {
		cout << arr.getPerson(i)->toString() << endl;
	}
}
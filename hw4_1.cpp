#include <iostream>
#include <cstring>
using namespace std;

class Monster {
private:
	int ImUnHappy;
	char* name; //몬스터의 이름에 대한 멤버 변수
	int hp; //몬스터의 hp에 대한 멤버 변수
	bool init; //초기화 여부(name 동적 할당 여부) 확인
public:
	Monster() : Monster("NONE", 0) {} //매개변수 없이 객체 생성시 이름을 "None", hp = 0으로 초기화, (char*)를 사용한 이유는 이걸 쓰지 않으면 "None"을 const char* 타입으로 인식해 컴파일 에러
	Monster(const char* name, int hp) { 
		this->name = new char[strlen(name) + 1]; //name의 경우, 같은 길이의 동적 배열 할당 받기
		strcpy_s(this->name, strlen(name) + 1, name); //매개변수 값으로 복사
		this->hp = hp; 
		init = true;
	} //입력받은 매개변수대로 몬스터의 이름과 hp를 초기화
	Monster(const Monster& temp) { *this = temp; } // 복사생성자, 연산자 중복을 이용함
	Monster& operator= (const Monster& temp); //복사대입연산자, 밑에서 구현
	bool operator ==(const Monster& temp); //멤버 변수 값이 같은지 확인하기 위한 연산자 중복, 밑에서 구현
	~Monster() {
		cout << name << ' ' << hp << " 객체 소멸" << endl; 
		if (init == true) delete[] name;
	} //어느 객체가 소멸했는지 알려주는 소멸자
};

bool Monster::operator==(const Monster& temp) { // ==연산자 중복
	if (init == true) //현재 객체의 멤버 변수가 초기화 됐다면
		if (!strcmp(name, temp.name) && hp == temp.hp) // 자기 자신의 멤버 변수 값과 입력받은 객체의 매개 변수 값을 비교
			return true; //두 멤버 변수 값이 모두 같다면 두 몬스터는 같은 것으로 인식
		else
			return false; //두 멤버 변수 값 둘 중 하나라도 다르다면 두 몬스터는 다른 것으로 인식
	else //초기화 되지 않았다면
		return false; //temp는 이미 초기화된 특정 객체의 참조이므로, 초기화 되지 않은 자기 자신과 같을 수 없다.
}

Monster& Monster::operator=(const Monster& temp) { //복사대입연산자, = 연산자 중복
	if (!(*this == temp)) { // 오버로딩된 ==연산자를 실행시켜 두 멤버 변수 값이 모두 같은지 아닌지 확인
		if (init == true) //초기화 됐다면
			delete [] name; //어떤 식으로 초기화했든 동적 할당을 무조건 받게 돼있으므로 반환
		name = new char[strlen(temp.name) + 1]; //새롭게 동적 할당
		strcpy_s(name, strlen(temp.name) + 1, temp.name); //값 복사
		hp = temp.hp; //둘 중 하나라도 다를 경우 복사 대입
		init = 1; //초기화(name이 동적 할당) 됐으므로 1로 변경
	}
	else 
		cout << "자기 자신을 복사할 순 없습니다." << endl; //둘 다 값이 같다면 복사하지 않음
	return *this; //복사된(혹은 복사되지 않은) 자기 자신에 대한 참조를 리턴
}

int main()
{
	Monster mon1((char*)"bear", 50); 
	Monster mon2((char*)"dragon", 1030);
	Monster mon3 = mon1; //선언과 동시에 = 연산자 사용시, 복사 생성자가 실행되고 복사 생성자 속 오버로딩된 = 연산자가 실행됨
	if (mon2 == mon3) //두 객체의 멤버 변수 둘 다 같은지 아닌지 확인
		cout << "it is same" << endl; //둘 다 다르기 때문에 이 라인은 실행되지 않는다.
	if (mon1 == mon2) 
		cout << "it is same" << endl; //둘 다 다르기 때문에 이 라인은 실행되지 않는다.
	if (mon1 == mon3) 
		cout << "it is same" << endl; //둘 다 같기 때문에 이 라인 실행
	cout << endl << endl;

	cout << "[이 부분 부터는 테스트 부분입니다.]" << endl << endl; //코드를 테스트하기 위한 부분
	char name1[20] = "1", name2[20] = "2";
	while(1) { //두 문자열이 다를 때까지 반복하는 반복문
		cout << "두 개의 서로 다른 이름을 쓰시오>>"; cin >> name1 >> name2;
		if (strcmp(name1, name2))
			break; //두 문자열이 다를 경우 탈출
		else
			cout << "서로 달라야 합니다!" << endl; //같을 경우 다시 반복
	}
	int hp1, hp2;
	while (1) { //두 체력이 다를 때까지 반복하는 반복문
		cout << "두 개의 서로 다른 hp을 쓰시오>>"; cin >> hp1 >> hp2;
		if (hp1 != hp2)
			break; //두 문자열이 다를 경우 탈출
		else
			cout << "서로 달라야 합니다!" << endl; //같을 경우 다시 반복
	}
	
	Monster test1; //매개변수 없는 생성자가 호출됨
	Monster test2(name1, hp1);
	Monster test3(test2); //복사 생성자 호출로, test2와 멤버 변수 값이 일치하는 객체
	Monster test4(name1, hp2); //test2, 3과 이름만 같은 객체
	Monster test5(name2, 50); //test2, 3과 hp만 같은 객체
	if (test2 == test3)
		cout << "(TEST)it is same" << endl; //두 객체의 멤버 변수가 모두 일치하므로 해당 메세지 출력
	test3 = test2; //두 객체의 멤버 변수가 모두 일치하므로 복사되지 않고, 복사할 수 없다는 메세지가 출력될 것이다.
	if (test3 == test4)
		cout << "(TEST)it is same" << endl; //두 객체의 멤버 변수 중 이름 하나만 일치하므로 실행 안 됨
	test3 = test4; //위 주석에 적힌 이유로 복사 성공. 소멸자 메세지를 통해 확인 가능
	if (test2 == test5)
		cout << "(TEST)it is same" << endl; //두 객체의 멤버 변수 중 hp 하나만 일치하므로 실행 안 S됨
	test2 = test4; //위 주석에 적힌 이유로 복사 성공. 소멸자 메세지를 통해 확인 가능
	
	return 0; //test5, test4 소멸자의 메세지가 각각 test2, test3 소멸자의 메세지와 일치할 것이며, 다섯 번째 소멸자 메세지는 None과 0이 표시될 것이다.
}

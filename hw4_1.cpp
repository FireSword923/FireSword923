#include <iostream>
#include <cstring>
using namespace std;

class Monster {
private:
	char* name; //������ �̸��� ���� ��� ����
	int hp; //������ hp�� ���� ��� ����
	bool init; //�ʱ�ȭ ����(name ���� �Ҵ� ����) Ȯ��
public:
	Monster() : Monster("NONE", 0) {} //�Ű����� ���� ��ü ������ �̸��� "None", hp = 0���� �ʱ�ȭ, (char*)�� ����� ������ �̰� ���� ������ "None"�� const char* Ÿ������ �ν��� ������ ����
	Monster(const char* name, int hp) { 
		this->name = new char[strlen(name) + 1]; //name�� ���, ���� ������ ���� �迭 �Ҵ� �ޱ�
		strcpy_s(this->name, strlen(name) + 1, name); //�Ű����� ������ ����
		this->hp = hp; 
		init = true;
	} //�Է¹��� �Ű�������� ������ �̸��� hp�� �ʱ�ȭ
	Monster(const Monster& temp) { *this = temp; } // ���������, ������ �ߺ��� �̿���
	Monster& operator= (const Monster& temp); //������Կ�����, �ؿ��� ����
	bool operator ==(const Monster& temp); //��� ���� ���� ������ Ȯ���ϱ� ���� ������ �ߺ�, �ؿ��� ����
	~Monster() {
		cout << name << ' ' << hp << " ��ü �Ҹ�" << endl; 
		if (init == true) delete[] name; //�� ������ �Ҵ�޾��� ��� ���� ��ȯ
	} //��� ��ü�� �Ҹ��ߴ��� �˷��ִ� �Ҹ���
};

bool Monster::operator==(const Monster& temp) { // ==������ �ߺ�
	if (init == true) //���� ��ü�� ��� ������ �ʱ�ȭ �ƴٸ�
		if (!strcmp(name, temp.name) && hp == temp.hp) // �ڱ� �ڽ��� ��� ���� ���� �Է¹��� ��ü�� �Ű� ���� ���� ��
			return true; //�� ��� ���� ���� ��� ���ٸ� �� ���ʹ� ���� ������ �ν�
		else
			return false; //�� ��� ���� �� �� �� �ϳ��� �ٸ��ٸ� �� ���ʹ� �ٸ� ������ �ν�
	else //�ʱ�ȭ ���� �ʾҴٸ�
		return false; //temp�� �̹� �ʱ�ȭ�� Ư�� ��ü�� �����̹Ƿ�, �ʱ�ȭ ���� ���� �ڱ� �ڽŰ� ���� �� ����.
}

Monster& Monster::operator=(const Monster& temp) { //������Կ�����, = ������ �ߺ�
	if (!(*this == temp)) { // �����ε��� ==�����ڸ� ������� �� ��� ���� ���� ��� ������ �ƴ��� Ȯ��
		if (init == true) //�ʱ�ȭ �ƴٸ�
			delete [] name; //� ������ �ʱ�ȭ�ߵ� ���� �Ҵ��� ������ �ް� �������Ƿ� ��ȯ
		name = new char[strlen(temp.name) + 1]; //���Ӱ� ���� �Ҵ�
		strcpy_s(name, strlen(temp.name) + 1, temp.name); //�� ����
		hp = temp.hp; //�� �� �ϳ��� �ٸ� ��� ���� ����
		init = 1; //�ʱ�ȭ(name�� ���� �Ҵ�) �����Ƿ� 1�� ����
	}
	else 
		cout << "�ڱ� �ڽ��� ������ �� �����ϴ�." << endl; //�� �� ���� ���ٸ� �������� ����
	return *this; //�����(Ȥ�� ������� ����) �ڱ� �ڽſ� ���� ������ ����
}

int main()
{
	Monster mon1((char*)"bear", 50); 
	Monster mon2((char*)"dragon", 1030);
	Monster mon3 = mon1; //����� ���ÿ� = ������ ����, ���� �����ڰ� ����ǰ� ���� ������ �� �����ε��� = �����ڰ� �����
	if (mon2 == mon3) //�� ��ü�� ��� ���� �� �� ������ �ƴ��� Ȯ��
		cout << "it is same" << endl; //�� �� �ٸ��� ������ �� ������ ������� �ʴ´�.
	if (mon1 == mon2) 
		cout << "it is same" << endl; //�� �� �ٸ��� ������ �� ������ ������� �ʴ´�.
	if (mon1 == mon3) 
		cout << "it is same" << endl; //�� �� ���� ������ �� ���� ����
	cout << endl << endl;

	cout << "[�� �κ� ���ʹ� �׽�Ʈ �κ��Դϴ�.]" << endl << endl; //�ڵ带 �׽�Ʈ�ϱ� ���� �κ�
	char name1[20] = "1", name2[20] = "2";
	while(1) { //�� ���ڿ��� �ٸ� ������ �ݺ��ϴ� �ݺ���
		cout << "�� ���� ���� �ٸ� �̸��� ���ÿ�>>"; cin >> name1 >> name2;
		if (strcmp(name1, name2))
			break; //�� ���ڿ��� �ٸ� ��� Ż��
		else
			cout << "���� �޶�� �մϴ�!" << endl; //���� ��� �ٽ� �ݺ�
	}
	int hp1, hp2;
	while (1) { //�� ü���� �ٸ� ������ �ݺ��ϴ� �ݺ���
		cout << "�� ���� ���� �ٸ� hp�� ���ÿ�>>"; cin >> hp1 >> hp2;
		if (hp1 != hp2)
			break; //�� ���ڿ��� �ٸ� ��� Ż��
		else
			cout << "���� �޶�� �մϴ�!" << endl; //���� ��� �ٽ� �ݺ�
	}
	
	Monster test1; //�Ű����� ���� �����ڰ� ȣ���
	Monster test2(name1, hp1);
	Monster test3(test2); //���� ������ ȣ���, test2�� ��� ���� ���� ��ġ�ϴ� ��ü
	Monster test4(name1, hp2); //test2, 3�� �̸��� ���� ��ü
	Monster test5(name2, hp1); //test2, 3�� hp�� ���� ��ü
	if (test2 == test3)
		cout << "(TEST)it is same" << endl; //�� ��ü�� ��� ������ ��� ��ġ�ϹǷ� �ش� �޼��� ���
	test3 = test2; //�� ��ü�� ��� ������ ��� ��ġ�ϹǷ� ������� �ʰ�, ������ �� ���ٴ� �޼����� ��µ� ���̴�.
	if (test3 == test4)
		cout << "(TEST)it is same" << endl; //�� ��ü�� ��� ���� �� �̸� �ϳ��� ��ġ�ϹǷ� ���� �� ��
	test3 = test4; //�� �ּ��� ���� ������ ���� ����. �Ҹ��� �޼����� ���� Ȯ�� ����
	if (test2 == test5)
		cout << "(TEST)it is same" << endl; //�� ��ü�� ��� ���� �� hp �ϳ��� ��ġ�ϹǷ� ���� �� S��
	test2 = test5; //�� �ּ��� ���� ������ ���� ����. �Ҹ��� �޼����� ���� Ȯ�� ����
	
	return 0; //test5, test4 �Ҹ����� �޼����� ���� test2, test3 �Ҹ����� �޼����� ��ġ�� ���̸�, �ټ� ��° �Ҹ��� �޼����� None�� 0�� ǥ�õ� ���̴�.
}
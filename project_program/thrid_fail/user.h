#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
using namespace std;

// 상수
const int MAX_MENU = 10;
extern int make_coffee_count; // 전역 변수 선언
extern int staff_count;       // 전역 변수 선언

class Event {
public:
    // 신문 파일과 키워드 저장
    map<string, string> newspaperKeywords = {
        {"newspaper1.txt", "nobel"},
        {"newspaper2.txt", "newjeans"},
        {"newspaper3.txt", "ott"},
        {"newspaper4.txt", "chuncheon"},
        {"newspaper5.txt", "electric"},
        {"newspaper6.txt", "apple"},
        {"newspaper7.txt", "ai"},
        {"newspaper8.txt", "martial law"},
        {"newspaper9.txt", "bitcoin"},
        {"newspaper10.txt", "subway"}
    };

    void ShowNewspaper(int index);
	void MiniGame(int index);
};

class Employee{
private:
// 나중에 수정 예정
	string rand_name[10];
	string employee_name;
public:
	
	Employee(){
		rand_name[0] = "김수현";
		rand_name[1] = "이정환";
		rand_name[2] = "박지현";
		rand_name[3] = "황서연";
		rand_name[4] = "김칠우";
		rand_name[5] = "엄준성";
		rand_name[6] = "김재현";
		rand_name[7] = "박건우";
		rand_name[8] = "함시우";
		rand_name[9] = "지현아";
	}
	
	int employee_price = 0;

	friend void Hire(Employee& hire);
};

class Anim{
public:
	void clearScreen();
	void anim_text(string message);
};

// 카페 메뉴와 관련된 클래스입니다. 
class Menu{
	// 커피 메뉴에 관련된 내용입니다. 
	vector<string> menu_name;
	vector<int> menu_price;
	vector<int> menu_sell;
	// 수요 공급 곡선을 어떤걸 사용할 지 저장해 놓습니다.
	vector<int> supply_demand_num;
	
	bool check_menu_make = false;
	
	// 디저트에 관련된 내용을 저장합니다.
	string dessert_name;
	int dessert_price;
	int dessert_sell; 
	int dessert_total_sell;
	
	// 메뉴 확인시에 디저트가 만들어지지 않았다면 보여주지 않습니다.
	bool check_dessert_make = false;
	// 정산시에 사용되는 디저트와 커피 판매액을 모두 저장해 놓습니다.
	int total_sell;

public:
	Menu(){
		total_sell = 0;
	}
	Employee employ;
	
	void MakeMenu();
	void MakeDessert();
	void ShowMenu();
	void ModifyMenu(); 
	void SellMenu();
	int ReturnCount();
	bool ReturnMenuCheck();
	//수요 공급 곡선을 선택하는 함수입니다.
	void SupplyDemand(int i);
	void Total(int total_staff);
};

// 행동 요소와 관련된 클래스 입니다. 
class Run{
	int day = 1;
public:
	// 메뉴, 애니메이션(보류), 직원 클래스를 참조합니다. 
	Menu menu;
	Anim anim;
	Employee employee[3];
	Event event;

	bool check_employee = true;
	int total_staff = 0;

	void run();
};

void Hire(Employee& hire);

#endif // USER_H

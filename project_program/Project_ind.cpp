#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include <chrono>
#include <thread>
using namespace std;

const int MAX_MENU = 10;

class Employee{
public:
	// 나중에 수정 예정
	string rand_name[10];
	Employee(){
		rand_name[0] = "김수현";
		rand_name[1] = "이정환";
		rand_name[2] = "박지현";
		rand_name[3] = "황서연";
		rand_name[4] = "김칠우";
		rand_name[5] = "홍길동";
		rand_name[6] = "김재현";
		rand_name[7] = "박건우";
		rand_name[8] = "함시우";
		rand_name[9] = "지현아";
	}
	vector<string> employee_name;
	vector<int> employee_price;
	bool check_employee = true;
};

class Anim{
public:
	void clearScreen();
	void anim_text(string message);
};

void Anim::clearScreen() {
    system("cls");  // Windows용 화면 지우기
}

void Anim::anim_text(string state){
	string message = "...";

    for (char c : message) {
        state += c;
        clearScreen();  // 화면을 지움
        cout << state << endl;
        this_thread::sleep_for(chrono::seconds(1));  // 0.5초 지연
    }
    
    clearScreen();
}

// 카페 메뉴와 관련된 클래스입니다. 
class Menu{
	// 커피 메뉴에 관련된 내용입니다. 
	vector<string> menu_name;
	vector<int> menu_price;
	vector<int> menu_sell; 
	
	bool check_menu_make = false;
	
	string dessert_name;
	int dessert_price;
	int dessert_sell; 
	
	bool check_dessert_make = false;
	int total_income;

public:
	int make_coffee_count;
	Menu(){
		total_income = 0;
		make_coffee_count = 1;
	}
	Employee employ;
	
	void make_menu();
	void make_dessert();
	void show_menu();
	void modify_menu(); 
	void sell_menu();
	int Return_count();
	void employee();
};

//직원 고용에 따른 커피의 개수를 반환하여 줍니다.
int Menu::Return_count(){
	return menu_name.size();
}

void Menu::make_menu(){
	string name;
	int price;
	
	// 해당 변수를 통해 메뉴가 정상적으로 입력되었는지 확인합니다. 
	bool menu_check = true;
	
	// 제작할 메뉴를 입력받습니다. 
	while(menu_check){
		menu_check = false;
		
		cout << "메뉴명을 입력해주세요 : " << endl;
		cin >> name;

		cout << "메뉴 가격을 입력해주세요 : " << endl;
		cin >> price;	
	
		for(int i = 0; i < menu_name.size(); i++){
			// 이미 존재하는 메뉴라면 menu_check를 true로 두어 다시 실행합니다. 
			if(menu_name[i] == name){
				cout << "이미 존재하는 메뉴입니다." << endl; 
				menu_check = true;
			}
		}		
	
		if(!menu_check){
			menu_name.push_back(name);
			menu_price.push_back(price);
			
			menu_sell.push_back(-1);
			check_menu_make= true;
		}
	}
}

void Menu::make_dessert(){
	string name;
	int price;
	
	// 제작할 메뉴를 입력받습니다. 
	cout << "디저트를 입력해주세요 : " << endl;
	cin >> name;

	cout << "디저트 가격은 5000원입니다. " << endl;
	
	dessert_name = name;
	dessert_price = 5000; 
	
	// 디저트 확인 시에 디저트의 여부를 판별  
	check_dessert_make = true;
}

void Menu::show_menu(){
	if(check_menu_make){
		cout << "==============(coffee)================" << endl;
		
		for(int i = 0; i < menu_name.size(); i++){
			cout << (i+1) << "번 메뉴" << endl;	
			cout << menu_name[i] << endl;
			cout << menu_price[i] << endl;
			//만약 아직 판매가 되지 않았다면 판매량이 -1이니 출력하지 않습니다. 
			if(menu_sell[i] != -1){
				cout << "판매량" << endl; 
				cout << menu_sell[i] << endl;
			}
			cout << endl;
		}
	}
	else{
		cout << "아직 만들어진 메뉴가 없습니다." << endl; 
	}
	
	if(check_dessert_make){
		cout << "==============(dessert)================" << endl;
		cout << "오늘의 디저트" << endl;
		cout << dessert_name << endl;
		cout << dessert_price << endl;
		cout << endl; 
	}
	else{
		cout << "아직 만들어진 디저트가 없습니다." << endl; 
	}

}

void Menu::modify_menu(){
	string name;
	int price;
	int modify = -1; 
	bool menu_check = true;
	
	while(menu_check){
		// 제작할 메뉴를 입력받습니다.
		cout << "수정할 메뉴명를 입력해주세요 : " << endl;
		cin >> name;
		
		for(int i = 0; i < menu_name.size(); i++){
			// 이미 존재하는 메뉴라면 menu_check를 true로 수정이 가능하도록 합니다. 
			if(menu_name[i] == name){
				modify = i; 
				menu_check = false;
			}
		}
		
		//수정이 가능합니다. 
		if(!menu_check){
			cout << "수정할 가격을 입력해주세요 : " << endl;
			cin >> price;
			menu_name[modify] = name;
			menu_price[modify] = price;
		}
		else{
			cout << "메뉴 이름을 다시 한번 확인해주세요." << endl;
		}	
	}
	
}

// 판매 가격에 맞추어 판매 개수를 결정합니다.
// 임의의 수요 공급 곡선을 여러가지 설정할 예정이며
// 임의의 수요 공급 곡선에 따라서 지정됩니다.
// 가격이 너무 싸다면 공급자의 공급이 줄어 판매가 줄어듭니다.
// 가격이 너무 비싸다면 수요가 줄어 판매가 줄어듭니다.
// 둘의 지점이 일치하는 곳이 가장 총 판매량이 가장 많은 지점입니다.
// 핵심 기능으로써 여러가지 공급 곡선을 추가할 예정입니다.
void Menu::sell_menu(){
	int price;
	for(int i = 0; i < menu_price.size(); i++){
		// 균형지점을 결정하여 줍니다.
		price = menu_price[i] / 100; 
		int demand = 100 - price;
    	int supply = 10 + 2 * price;
    	
    	int insert = min(demand, supply);
    	
    	menu_sell[i] = insert;

		// 판매된 최종개수를 입력합니다. (정산에서 이용됩니다.)
		total_income = menu_price[i] * menu_sell[i];
	}

	
}

//직원 고용 토대 제작중
void Menu::employee(){
	srand((unsigned)time(NULL));

	string yn;
	cout << "직원 고용" << endl;

	for(int i = 0; i < 3; i++){
		// 가격과 고용비용, 이름을 랜덤으로 뽑습니다.
		int employee_money = rand()%10000 + 1000;
		int menu_count_plus = rand()%3 + 1;
		int k = rand()%9;

		// 저장된 직원의 이름을 랜덤으로 보여줍니다.
		cout << "직원이름 : "  << employ.rand_name[k] << endl;

		// 랜덤으로 고용비용을 소개하여 줍니다.
		cout << "고용비용 : " << employee_money << "원" << endl;

		// 메뉴 추가의 개수도 제공하여 줍니다. (추후 확률 조정 예정)
		cout << "메뉴 추가 개수 : " << menu_count_plus << "개" << endl;

		// 한번만 고용이 가능합니다.
		cout << "해당 직원을 고용하시겠습니까?(Y/N) : ";
		cin >> yn;

		if(yn == "Y" || yn == "y" || yn == "Yes" || yn == "yes"){
			cout << "해당직원을 고용하였습니다." << endl;
			// 고용 시에 만들 수 있는 메뉴 개수 추가
			// 최대 메뉴 개수를 제한하여 추가합니다.
			if(make_coffee_count + menu_count_plus < MAX_MENU){
				make_coffee_count += menu_count_plus;
			}
			else{
				// 메뉴의 최대개수로 제한합니다.
				cout << "최대 메뉴 개수에 도달하였습니다.(10개)" << endl;
				make_coffee_count = MAX_MENU;
			}
			
			// Employee class에 고용한 이름과 고용 비용 vector에 입력
			employ.employee_name.push_back(employ.rand_name[k]);
			employ.employee_price.push_back(employee_money);

			// 현재 가용 메뉴 개수를 출력하여 보여줍니다.
			cout << "현재 가용 가능한 메뉴의 개수는 " << make_coffee_count << "개 입니다." << endl;

			// 직원 고용시에 해당 날짜에는 더이상 고용하지 못하도록 합니다.
			employ.check_employee = false;
			break;
		}
		else if(yn == "N" || yn == "n" || yn == "No" || yn == "no"){
			cout << "다음 직원을 소개합니다." << endl;
			cout << endl;
		}
		else{
			cout << "다시 한번 입력해주세요." << endl;
		}
	} 

	
}

// 행동 요소와 관련된 클래스 입니다. 
class Run{
	int day = 1;
public:
	// 메뉴 클래스를 참조합니다. 
	Menu menu;
	Anim anim;
	Employee employee;
	void run();
};


// 전체적인 행동 요소를 나타내는 함수 입니다. 
void Run::run(){
	int menu_select;
	
	int time = 0;
	
	while(day < 7){
		menu_select = 0;
		if(time == 0){
			cout << "낮" << endl; 
		}
		else{
			cout << "밤" << endl; 
		}
		
		cout << day << "일차" << endl; 
		
		if(time == 0){
			// 낮에 할 행동을 보여주고 입력을 통해 확인합니다. 
			while(menu_select < 5){
				cout << "===================행동(낮)=====================" << endl; 
				cout << "1. 카페 메뉴 만들기" << endl; 
				cout << "2. 디저트 만들기" << endl;
				cout << "3. 카페 메뉴 확인" << endl;
				cout << "4. 미니 게임" << endl;
				cout << "5. 판매 시작" << endl;
				cout << ">> ";
				cin >> menu_select;
				
				switch(menu_select){
					case 1:
						// 직원 고용에 따라 만들 수 있는 커피 개수를 제한합니다.
						if(menu.make_coffee_count > menu.Return_count()){
							// 참조한 Menu클래스의 함수 make_menu함수를 불러옵니다. 
							menu.make_menu();
						}
						else{
							cout << "만들 수 있는 커피의 개수를 넘었습니다." << endl;
						}
						break;
					case 2:
						// 참조한 Menu클래스의 함수 make_dessert함수를 불러옵니다. 
						menu.make_dessert(); 
						break;
					case 3:
						// 참조한 Menu클래스의 show_menu 함수를 불러옵니다. 
						menu.show_menu();
						break;
					case 4:
						
						break;
					case 5:
						// 시간을 밤으로 만듭니다. 
						//anim.anim_text("판매중");
						menu.sell_menu();
						time = 1; 
						break;
					default:
						cout << "잘못된 입력입니다." << endl;
						break;
				}
			}
		} 
		else{
			//밤에 진행할 활동을 선택합니다.
			//밤이 왔다면 다시 고용할 수 있도록 함수를 조정합니다. 
			employee.check_employee = true;

			while(menu_select < 6){
				cout << "===================행동(밤)=====================" << endl; 
				cout << "1. 메뉴 가격 수정" << endl; 
				cout << "2. 직원 고용" << endl;
				cout << "3. 카페 메뉴 확인" << endl;
				cout << "4. 정산" << endl;
				cout << "5. 미니 게임" << endl; 
				cout << "6. 잠자기" << endl;
				cout << ">> ";
				cin >> menu_select;

				switch(menu_select){
					case 1:
						menu.modify_menu(); 
						break;
					case 2:
					// 직원 고용이 한번 이루어 졌다면 그날은 접근하지 못하도록 합니다.
				 		if(employee.check_employee){
							menu.employee();
						}
						
						break;
					case 3:
						menu.show_menu();
						break;
					case 4:
						
						break;
					case 5:
						
						break;
					case 6:
						// 시간을 낮으로 만듭니다. 
						//anim.anim_text("자는중");
						time = 0;
						day++;
						break;
					default:
						cout << "잘못된 입력입니다." << endl;			
						break;
				}	
			}		
		}
		cout << endl;
	}
}

int main(){
	Run a;
	
	a.run();
	
	return 0;
}
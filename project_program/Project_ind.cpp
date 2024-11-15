#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <chrono>
#include <thread>
using namespace std;

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
	 
	int totalIncome;
public:
	Menu(){
		totalIncome = 0;
	}
	
	void make_menu();
	void make_dessert();
	void show_menu();
	void modify_menu(); 
	void sell_menu();
};

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

void Menu::sell_menu(){
	int price;
	for(int i = 0; i < menu_price.size(); i++){
		price = menu_price[i] / 100; 
		int demand = 100 - price;
    	int supply = 10 + 2 * price;
    	
    	int insert = min(demand, supply);
    	
    	menu_sell[i] = insert;
	}
}

// 행동 요소와 관련된 클래스 입니다. 
class Run{
	int day = 1;
public:
	// 메뉴 클래스를 참조합니다. 
	Menu menu;
	Anim anim;
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
						// 참조한 Menu클래스의 함수 make_menu함수를 불러옵니다. 
						menu.make_menu(); 
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
			while(menu_select < 6){
				cout << "===================행동(밤)=====================" << endl; 
				cout << "1. 메뉴 가격 수정" << endl; 
				cout << "2. 디저트 만들기" << endl;
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
						menu.make_dessert(); 
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
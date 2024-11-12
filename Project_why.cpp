#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// 카페 메뉴와 관련된 클래스입니다. 
class Menu{
	// 커피 메뉴에 관련된 내용입니다. 
	vector<string> menu_name;
	vector<int> menu_price;
	vector<int> menu_sell; 
	
	vector<string> dessert_name;
	vector<int> dessert_price;
	
	 
	int totalIncome;
public:
	Menu(){
		totalIncome = 0;
	}
	
	void in_menu();
};

void Menu::in_menu(){
	string name;
	int price;
	
	// 해당 변수를 통해 메뉴가 정상적으로 입력되었는지 확인합니다. 
	bool menu_check = true;
	
	// 제작할 메뉴를 입력받습니다. 
	while(menu_check){
		cout << "메뉴명을 입력해주세요 : " << endl;
		cin >> name;

		cout << "메뉴 가격을 입력해주세요 : " << endl;
		cin >> price;
		
		for(int i = 0; i < menu_name.size(); i++){
			// 이미 존재하는 메뉴라면 menu_check를 true로 두어 다시 실행합니다. 
			if(menu_name[i] == name){
				cout << "이미 존재하는 메뉴입니다." << endl; 
			}
			else{
				// 정상적으로 입력이 된다면 menu_check를 false로 두어 while문을 빠져나옵니다. 
				menu_check = false;
				menu_name.push_back(name);
				menu_price.push_back(price);
				
				menu_sell.push_back(0);
				cout << menu_check << endl;
			}
		}
	}
		
}

// 행동 요소와 관련된 클래스 입니다. 
class Run{
	int day = 1;
public:
	// 메뉴 클래스를 참조합니다. 
	Menu menu;
	void run();
};

// 전체적인 행동 요소를 나타내는 함수 입니다. 
void Run::run(){
	int menu_select;
	
	int time = 0;
	
	while(day < 10){
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
				cin >> menu_select;
				
				switch(menu_select){
					case 1:
						// 참조한 Menu클래스의 함수 in_menu를 불러옵니다. 
						menu.in_menu(); 
						break;
					case 2:
						
						break;
					case 3:
						
						break;
					case 4:
						
						break;
					case 5:
						// 시간을 밤으로 만듭니다. 
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
				cin >> menu_select;
				
				switch(menu_select){
					case 1:
						
						break;
					case 2:
						
						break;
					case 3:
						
						break;
					case 4:
						
						break;
					case 5:
						
						break;
					case 6:
						// 시간을 낮으로 만듭니다. 
						time = 0;
						day++;
						break;
					default:
						cout << "잘못된 입력입니다." << endl;			
						break;
				}	
			}		
		}
	}
}

int main(){
	Run a;
	
	a.run();
	
	return 0;
}
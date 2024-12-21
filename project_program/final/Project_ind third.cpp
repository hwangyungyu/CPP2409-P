#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <map>
#include <fstream>
#include <cstdlib>

#include <chrono>
#include <thread>
using namespace std;

// 만들 수 있는 커피는 10개로 한정되어 있습니다.
const int MAX_MENU = 10;

// 제작할 수 있는 커피의 개수입니다.
static int make_coffee_count = 1;

// 가용가능한 직원의 수를 저장합니다.
int staff_count = 0;

// 각종 이벤트와 관련된 클래스 입니다.
class Event {
public:
    // 신문 파일과 키워드 저장합니다.
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
        {"newspaper10.txt", "subway"},
    };

	// 신문을 보여주는데 사용되어집니다. index의 경우에는 하루에 랜덤으로 선택되어집니다.
    void ShowNewspaper(int index);

	// 미니게임을 실행합니다.
	void MiniGame(int index);

	// 그날의 keyword를 반환합니다.
	string ReturnKeyword(int index);
};

// 미니게임을 실행합니다.
void Event::MiniGame(int index) {
    // map에서 index에 해당하는 키 찾기
	string keyword;

	if(index != 100){
		auto it = newspaperKeywords.begin();
		advance(it, index);

		keyword = it->second;  // 해당 키워드
		
	}
	else{
		keyword = "veblen";
	}
    string guessed(keyword.size(), '_');
    

	// 사용할 수 있는 횟수이며 10번으로 제한합니다.
    int attempts_left = 10;

	// 추측한 단어를 저장합니다.
    string guessed_letters = "";

	// 맞추거나 횟수를 모두 소진할 때까지 반복하여 실행합니다.
    while (attempts_left > 0 && guessed != keyword) {
        // 현재 상태 출력
        cout << "\n단어: ";
        for (char c : guessed) {
            cout << c << ' ';
        }
        cout << "\n남은 시도 횟수: " << attempts_left << "\n";
        cout << "추측한 글자: " << guessed_letters << "\n";
        cout << "알파벳 한 글자를 입력하세요: ";

		// 추측할 단어를 입력받습니다.
        char guess;
        cin >> guess;
        guess = tolower(guess);

		// 잘못된 입력이거나 이미 추측한 단어일 경우에 다시 진행합니다.
        if (!isalpha(guess) || guessed_letters.find(guess) != std::string::npos) {
            cout << "잘못된 입력입니다. 한 글자 알파벳만 입력하거나, 이미 추측한 글자를 제외해주세요.\n";
            continue;
        }

		// 추측한 단어는 담아줍니다.
        guessed_letters += guess;

		// 추측한 알파벳이 포함되어져 있는 곳을 찾습니다.
        bool found = false;
        for (size_t i = 0; i < keyword.size(); ++i) {
            if (keyword[i] == guess) {
                guessed[i] = guess;
                found = true;
            }
        }
		
		// 포함 여부를 보여줍니다.
        if (found) {
            cout << "좋아요! '" << guess << "'는 단어에 포함되어 있습니다.\n";
        } else {
            cout << "안타깝습니다. '" << guess << "'는 단어에 없습니다.\n";
        }
		
		// 횟수를 소진합니다.
		attempts_left--;
    }

	// 성공 여부를 보여줍니다.
    if (guessed == keyword) {
        cout << "\n축하합니다! 단어를 맞추셨습니다: " << keyword << "\n";
    } else {
        cout << "\n게임 오버! 다시 도전해주세요!!: " << "\n";
    }
}

// 신문을 보여주는 함수입니다.
void Event::ShowNewspaper(int index) {
    // map에서 index에 해당하는 키 찾기
    auto it = newspaperKeywords.begin();
    advance(it, index);

    string news = it->first;  // 선택된 파일 이름
    string keyword = it->second;  // 해당 키워드

	// 선택되어지는 신문을 확인합니다.
    //cout << "선택된 신문 파일: " << news << endl;
    //cout << "핵심 키워드: " << keyword << endl;

    // 파일 읽기
    ifstream is{news};
    if (!is) {
        cerr << "파일 오픈에 실패하였습니다: " << news << endl;
        return;
    }

    cout << "==================| 신문 내용 |====================" << endl;
    char c;
    while (is.get(c)) {
        cout << c;
    }
    cout << endl;
}

// 그 날의 키워드를 반환하여 줍니다.
string Event::ReturnKeyword(int index){
	// map에서 index에 해당하는 키 찾기
    auto it = newspaperKeywords.begin();
    advance(it, index);

    string keyword = it->second;  // 해당 키워드

	return keyword;
}

// 직원 고용과 관련된 클래스입니다.
class Employee{
private:
	// 랜덤으로 보내줄 이름을 저장하여 놓습니다.
	string rand_name[10];
	string employee_name;
public:
	// 직원의 이름을 설정 해놓습니다.
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
	
	// 직원의 고용비용입니다.
	int employee_price = 0;

	// 고용에 사용되어지는 함수입니다.
	friend void Hire(Employee& hire);
};

// 애니메이션은 아직 보류중입니다.
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
	// 수요 공급 곡선을 어떤걸 사용할 지 저장해 놓습니다.
	vector<int> supply_demand_num;
	
	// 메뉴가 만들어졌는지를 체크합니다.
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

	// 베블런 효과에서 사용되는 변수압니다.
	string veblen;
public:
	Menu(){
		total_sell = 0;
		dessert_total_sell = 0;
		veblen = "veblen";
	}
	Employee employ;
	
	// 메뉴를 만드는데 관여합니다.
	void MakeMenu();

	// 디저트를 만드는데 관여하고 key값을 받아 만일 그날 key단어가 포함되어있는지 체크합니다.
	void MakeDessert(string key);

	// 메뉴를 보여줍니다. 여기서 check_dessert_make, check_menu_make를 이용하여 
	// 메뉴가 만들어졌는지 체크합니다.
	void ShowMenu();

	// 메뉴를 수정합니다.
	void ModifyMenu(); 

	// 날짜를 보낼때 사용되며 총 판매량을 저장합니다.
	void SellMenu();

	// 총 만들어져 있는 메뉴의 개수를 반환합니다.
	int ReturnCount();

	// 메뉴가 만들어졌는지 여부를 반환합니다.
	bool ReturnMenuCheck();

	//수요 공급 곡선을 선택하는 함수입니다.
	void SupplyDemand(int i, bool& check);

	// 정산에 사용됩니다.
	void Total(int total_staff);

	// 디저트에 사용되며 그날의 key단어가 포함되어져 있는지 여부를 파악합니다.
	bool containsWord(const string& targetWord, const string& Word);

	// 날짜가 지나가면 디저트의 가격을 다시 5000원으로 조정합니다.
	void ResetDessertPrice();

};

//직원 고용에 따른 커피의 개수를 반환하여 줍니다.
int Menu::ReturnCount(){
	return menu_name.size();
}

// 메뉴가 하나라도 만들어졌는지의 여부를 반환합니다.
bool Menu::ReturnMenuCheck(){
	return check_menu_make;
}

// 메뉴를 만듭니다.
void Menu::MakeMenu(){
	// 이름과 가격을 입력받을 변수입니다.
	string name;
	int price;
	
	// 해당 변수를 통해 메뉴가 정상적으로 입력되었는지 확인합니다. 
	bool menu_check = true;
	
	// 제작할 메뉴를 입력받습니다. 
	while(menu_check){
		menu_check = false;

		cout << "=======================| 주의 사항 |==========================" << endl;
		cout << "메뉴의의 이름은 영어로 작성하여 주시길 바랍니다." << endl;
		cout << "왜 한글이 안되는 것일까요...." << endl;
		cout << "=============================================================" << endl;
		cout << endl;

		cout << "메뉴명을 입력해주세요 : " << endl;
		cin.ignore(); // 이전 입력이 있다면 버퍼를 비웁니다.
		// 메뉴의 이름을 입력받습니다.
    	getline(cin, name);

		//메뉴의 가격을 입력받습니다.
		cout << "메뉴 가격을 입력해주세요 : " << endl;
		cin >> price;	

		// 지금까지 만들어진 메뉴의 크기만큼 for문을 돕니다.
		for(int i = 0; i < menu_name.size(); i++){
			// 이미 존재하는 메뉴라면 menu_check를 true로 두어 다시 실행합니다. 
			if(menu_name[i] == name){
				cout << "이미 존재하는 메뉴입니다." << endl; 
				menu_check = true;
			}
		}		

		// 메뉴의 중복여부를 판단합니다.
		if(!menu_check){
			// 랜덤으로 수요공급곡선 번호를 지정하여 줍니다.
			int num = rand()%3 + 1;
			// 정해진 수요 공급 곡선의 번호를 저장합니다.
			supply_demand_num.push_back(num);

			// 메뉴의 이름과 가격을 집어넣어 줍니다.
			menu_name.push_back(name);
			menu_price.push_back(price);
			
			// 판매 시작 전에는 판매량이 없다는 것을 알리기위해 -1로 지정합니다.
			menu_sell.push_back(-1);
			
			// 메뉴가 만들어졌음을 나타냅니다.
			check_menu_make= true;
		}
	}
}

// 디저트를 만듭니다.
void Menu::MakeDessert(string key){
	int price;
	string name;

	cout << "=======================| 주의 사항 |==========================" << endl;
	cout << "디저트의 이름은 영어로 작성하여 주시길 바랍니다." << endl;
	cout << "왜 한글이 안되는 것일까요...." << endl;
	cout << "=============================================================" << endl;
	cout << endl;
	
	// 제작할 메뉴를 입력받습니다. 
	cout << "디저트를 입력해주세요 : " << endl;
	cin.ignore(); // 이전 입력이 있다면 버퍼를 비웁니다.
    getline(cin, name);
	dessert_name = name;

	cout << "기본 디저트 가격은 5000원입니다. " << endl;
	
	// 그날의 키워드가 포함되어져 있는 지 체크합니다.
	if(containsWord(key, dessert_name)){
		cout << "디저트가 더 비싼 가격에 팔립니다!!" << endl;
		dessert_price = 7000;
	}
	else{
		dessert_price = 5000; 
	}
	
	// 디저트 확인 시에 디저트의 여부를 판별  
	check_dessert_make = true;
}

// 디저트의 가격을 5000원으로 초기화할때 사용되어집니다.
void Menu::ResetDessertPrice(){
	dessert_price = 5000; 
}

// 메뉴를 보여줍니다.
void Menu::ShowMenu(){
	// 메뉴가 만들어졌는지 체크하여 그 여부에 따라 메뉴를 보여줍니다.
	if(check_menu_make){
		cout << "==============(coffee)================" << endl;
		
		// 메뉴의 크기만큼 for문을 작동시킵니다.
		for(int i = 0; i < menu_name.size(); i++){
			cout << (i+1) << "번 메뉴" << endl;	
			cout << menu_name[i] << endl;
			cout << menu_price[i] << endl;

			//만약 아직 판매가 진행되어진 메뉴는 판매량을 보여줍니다.
			// 판매가 진행되지 않은 메뉴는 판매량이 -1임으로 이를 통해 판단합니다.
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

	// 디저트 제작여부에 따라서 메뉴를 보여줍니다.
	if(check_dessert_make){
		cout << "==============(dessert)================" << endl;
		cout << "오늘의 디저트" << endl;
		cout << dessert_name << endl;
		cout << dessert_price << endl;

		// 디저트도 판매 여부를 판단하여 판매가 되었다면 판매량을 보여줍니다.
		if(dessert_sell != 0){
			cout << "판매량" << endl; 
			cout << dessert_sell << endl;
		}
		cout << endl; 
	}
	else{
		cout << "아직 만들어진 디저트가 없습니다." << endl; 
	}

}

// 메뉴를 수정합니다.
void Menu::ModifyMenu(){
	string name;
	string yn;
	int price;
	int modify = -1; 
	bool menu_check = true;
	
	// 수정이 완료될 때까지 while문을 진행합니다.
	while(menu_check){
		// 수정할 메뉴를 입력받습니다.
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
			// 수정할 가격을 입력받아 수정해줍니다.
			menu_name[modify] = name;
			menu_price[modify] = price;
		}
		else{
			cout << "메뉴 이름을 다시 한번 확인해주세요." << endl;
		}	

		// 수정의 진행여부를 입력받습니다.
		cout << " 수정을 다시 진행하시겠습니까? (y/n): ";
		cin >> yn;
		// 수정을 원치 않을 시에 빠져 나갑니다.
		if(yn == "n" || yn == "N"){
			break;
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
void Menu::SellMenu(){
	bool check_veblen = true;

	// 디저트의 판매량은 커피의 절반만큼 팔립니다.
	// 다만 커피의 판매량은 가격에 따라 바뀔 수 있음으로 0으로 초기화하고 다시 받아줍니다.
	dessert_sell = 0;

	// 메뉴를 전부 돌면서 정해진 
	for(int i = 0; i < menu_price.size(); i++){
		SupplyDemand(i, check_veblen);
	}
	
	// 커피의 모든 판매량의 절반만큼 판매되어 저장합니다.
	if(check_dessert_make){
		dessert_total_sell += 5000 * dessert_sell;
	}
}

// 특정 단어가 문자열에 포함되어 있는지 확인하는 함수
bool Menu::containsWord(const string& targetWord,const string& Word) {
    istringstream stream(Word);
    string word;

    while (stream >> word) {
        if (word == targetWord) {
            return true;
        }
    }
	// 만일 단어가 포함되어져 있지 않다면 false를 반환합니다.
    return false;
}

// 균형지점을 지정해주는 함수 입니다.
void Menu::SupplyDemand(int i, bool& check){
	int price, demand, supply;

	// 3개의 균형지점 중에 랜덤으로 결정하여 줍니다.
	if(supply_demand_num[i] == 1){
		price = menu_price[i] / 100; 
		demand = 100 - price;
		supply = 3 * price;
	}
	else if(supply_demand_num[i] == 2){
		price = menu_price[i] / 100; 
		demand = 150 - price;
		supply = 1.5 * price;
	}
	else{
		price = menu_price[i] / 100; 
		demand = 80 - price;
		supply = price;
	}
	
	// 수요와 공급 중에서 작은 값을 판매량으로 결정합니다.
	int insert = min(demand, supply);
	
	// 몇개가 판매되는지 판매량을 넣습니다.
	// veblen이 포함 시에 판매량이 늘어납니다.
	// check를 통해 veblen은 한번만 적용 가능하도록 합니다.
	if(containsWord(veblen, menu_name[i]) && check){
		menu_sell[i] = insert + 30;
		check = false;
	}
	else{
		menu_sell[i] = insert;
	}
		
	// 디저트의 판매량은 커피의 절반만큼 팔립니다.
	if(check_dessert_make){
		dessert_sell += menu_sell[i] / 2;
	}

	// 판매된 총 가격을 입력합니다. (정산에서 이용됩니다.)
	total_sell += menu_price[i] * menu_sell[i];
}

//정산하여 총 가격을 보여줍니다.
void Menu::Total(int total_staff){
	cout << "===================| 정산 |======================" << endl;
	// 커피의 총 판매량을 모두 계산하여 보여줍니다.
	cout << "===| 커피 |===" << endl;
	cout << total_sell << endl;
	cout << "\n";

	// 디저트의 총 판매량을 모두 계산하여 보여줍니다.
	cout << "===| 디저트 |===" << endl;
	cout << dessert_total_sell << endl;
	cout << "\n";

	// 직원 월급의 총 판매량을 모두 계산하여 보여줍니다.
	cout << "===| 직원 월급 |===" << endl;
	cout << total_staff << endl;
	cout << "\n";

	// 커피 + 디저트 - 직원월급, 즉 총 이윤을 보여줍니다.
	cout << "===| 정산 |===" << endl;
	cout << total_sell + dessert_total_sell - total_staff << endl;
}

//직원 고용 토대 제작 완료
void Hire(Employee& hire){
	srand((unsigned)time(NULL));

	string yn;
	cout << "=======================| 주의 사항 |==========================" << endl;
	cout << "직원 고용을 진행시 고용 여부와 상관없이 그날 고용은 끝이납니다" << endl;
	cout << "주의하여 고용을 진행하여 주시길 바랍니다." << endl;
	cout << "=============================================================" << endl;

	cout << "직원 고용" << endl;

	//직원을 돌아가면서 총 3번을 보여줍니다.
	for(int i = 0; i < 3; i++){
		// 가격과 고용비용, 이름을 랜덤으로 뽑습니다.
		int employee_money = rand()%10000 + 1000;
		int menu_count_plus = rand()%3 + 1;
		int k = rand()%9;

		// 저장된 직원의 이름을 랜덤으로 보여줍니다.
		cout << "직원이름 : "  << hire.rand_name[k] << endl;

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
			hire.employee_name = hire.rand_name[k];
			hire.employee_price = employee_money;
			staff_count++;

			// 현재 가용 메뉴 개수를 출력하여 보여줍니다.
			cout << "현재 가용 가능한 메뉴의 개수는 " << make_coffee_count << "개 입니다." << endl;
			cout << "현재 고용한 직원 수는 " << "(" << staff_count << "/3)" << "명 입니다." << endl;
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
	// 메뉴, 애니메이션(보류), 직원 클래스를 참조합니다. 
	Menu menu;
	Anim anim;
	Employee employee[3];
	Event event;

	bool check_employee = true;
	int total_staff = 0;

	void run();
	void ending();
};

void Run::ending(){
	cout << "부족한 게임을 플레이해주셔서 감사합니다." << endl;
	cout << endl;
	cout << "해당 게임은 수요공급곡선, 베블런 효과, 외부 효과를 재미있게 알려주기 위해" <<endl;
	cout << "제작되었습니다." << endl;
	cout << "가격이 일정 이상 올라가게 되면 판매량이 줄어들거나, 가격을 많이 내리면 판매량이 줄어들었을 겁니다." << endl;
	cout << "이는 가격이 줄어들면 공급자가 공급을 하지 않게 되고," << endl;
	cout << "반대로 가격을 올리면 소비자가 구매하지 않는 효과를 보여줍니다. 비싸면 사기 싫잖아요..." << endl;
	cout << "그렇지만 비싸도 오히려 잘팔리는 경우도 있습니다. 이를 베블런 효과라고 합니다." << endl;
	cout << "신문에 나오는 단어를 사용하면 디저트를 더 비싸게 팔 수도 있었습니다." << endl;
	cout << "예능에서 맛있어 보이는 음식이 나오면 먹고싶어져 비싸도 사먹곤 합니다." << endl;
	cout << "이를 외부 효과라고 합니다." << endl;
	cout << "요즘 3줄이상 안 읽는 경우가 많은데 말이 길었네요.." << endl;
	cout << "부족한 저의 게임을 플레이 해주셔서 감사합니다." << endl;
}

// 전체적인 행동 요소를 나타내는 함수 입니다. 
void Run::run(){
	srand(static_cast<unsigned int>(time(nullptr)));
    int r = rand() % 10; // 인덱스는 0~9 범위
	// keyword를 받아옴

	string key_word = event.ReturnKeyword(r);
	// 디저트의 가격을 초기화 시킵니다.
	menu.ResetDessertPrice();

	int menu_select;
	
	int time = 0;

	int number;
	
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
				cout << "2. 디저트 만들기/수정하기" << endl;
				cout << "3. 카페 메뉴 확인" << endl;
				cout << "4. 신문 확인" << endl;
				cout << "5. 미니 게임" << endl;
				cout << "6. 판매 시작" << endl;
				cout << ">> ";
				cin >> menu_select;
				
				switch(menu_select){
					case 1:
						// 직원 고용에 따라 만들 수 있는 커피 개수를 제한합니다.
						if(make_coffee_count > menu.ReturnCount()){
							// 참조한 Menu클래스의 함수 make_menu함수를 불러옵니다. 
							menu.MakeMenu();
						}
						else{
							cout << "만들 수 있는 커피의 개수를 넘었습니다." << endl;
						}
						break;
					case 2:
						// 참조한 Menu클래스의 함수 make_dessert함수를 불러옵니다. 
						menu.MakeDessert(key_word); 
						break;
					case 3:
						// 참조한 Menu클래스의 show_menu 함수를 불러옵니다. 
						menu.ShowMenu();
						break;
					case 4:
						// 신문을 보여줍니다.
						event.ShowNewspaper(r);
						break;
					case 5:
						number = 0;
						//미니게임을 실행합니다.
						try{
							cout << "=====================| 미니게임 |=====================" << endl;
							cout << "1. 특수 미니게임" << endl;
							cout << "2. 신문 미니게임" << endl;
							cout << ">>";
							cin.exceptions(ios::failbit | ios::badbit);
							cin >> number;

							if(number == 1){
								event.MiniGame(100);
							}
							else if(number == 2){
								event.MiniGame(r);
							}
							else{
								throw number;
							}
						}
						catch(const ios_base::failure& e){
							cout << "다시 입력해주세요." << endl;
							// 입력 스트림을 초기화
        					cin.clear(); // 상태 플래그를 초기화
        					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼 비우기
						}
						
						break;
					case 6:
						// 시간을 밤으로 만듭니다. 
						//anim.anim_text("판매중");
						if(menu.ReturnMenuCheck()){
							menu.SellMenu();
							time = 1;
						}
						else{
							cout << "아직 메뉴가 하나도 없습니다." << endl;
						}
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
			check_employee = true;

			// 밤이 오면 직원들의 일급을 하루마다 더해줍니다.
			for(int i = 0; i < staff_count; i++){
				total_staff += employee[i].employee_price;
			}

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
						menu.ModifyMenu(); 
						break;
					case 2:
						// 직원 고용이 한번 이루어 졌다면 그날은 접근하지 못하도록 합니다.
						// 직원 수가 3명이 넘어가면 더이상 고용이 불가능합니다.
				 		if(check_employee && staff_count < 3){
							Hire(employee[staff_count]);
						}
						else{
							cout << "오늘의 직원 고용은 마무리 되었습니다. 내일 다시오세요" << endl;
						}
						// 직원 고용을 진행하면 고용 여부와 상관없이 그날 고용은 끝이 납니다.
						check_employee = false;

						break;
					case 3:
						menu.ShowMenu();
						break;
					case 4:
						menu.Total(total_staff);
						break;
					case 5:
						number = 0;
						//미니게임을 실행합니다.
						try{
							cout << "=====================| 미니게임 |=====================" << endl;
							cout << "1. 특수 미니게임" << endl;
							cout << "2. 신문 미니게임" << endl;
							cout << ">>";
							cin.exceptions(ios::failbit | ios::badbit);
							cin >> number;

							if(number == 1){
								event.MiniGame(100);
							}
							else if(number == 2){
								event.MiniGame(r);
							}
							else{
								throw number;
							}
						}
						catch(const ios_base::failure& e){
							cout << "다시 입력해주세요." << endl;
							// 입력 스트림을 초기화
        					cin.clear(); // 상태 플래그를 초기화
        					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 입력 버퍼 비우기
						}
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

	ending();
}

int main(){
	Run a;
	
	a.run();
	
	return 0;
}
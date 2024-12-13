#include "user.h"

// 전역 변수 초기화
int make_coffee_count = 1;
int staff_count = 0;

// Event 클래스 구현
Event::Event() {
    newspaperKeywords = {
        {"newspaper1.txt", "nobel"}, {"newspaper2.txt", "newjeans"}, {"newspaper3.txt", "ott"},
        {"newspaper4.txt", "chuncheon"}, {"newspaper5.txt", "electric"}, {"newspaper6.txt", "apple"},
        {"newspaper7.txt", "ai"}, {"newspaper8.txt", "martial law"}, {"newspaper9.txt", "bitcoin"},
        {"newspaper10.txt", "subway"}
    };
}

void Event::ShowNewspaper(int index) {
    auto it = newspaperKeywords.begin();
    advance(it, index);
    string news = it->first;
    string keyword = it->second;

    cout << "선택된 신문 파일: " << news << endl;
    cout << "핵심 키워드: " << keyword << endl;

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

void Event::MiniGame(int index) {
    auto it = newspaperKeywords.begin();
    advance(it, index);
    string keyword = it->second;
    string guessed(keyword.size(), '_');
    int attempts_left = 10;
    string guessed_letters = "";

    while (attempts_left > 0 && guessed != keyword) {
        cout << "\n단어: ";
        for (char c : guessed) cout << c << ' ';
        cout << "\n남은 시도 횟수: " << attempts_left << "\n";
        cout << "추측한 글자: " << guessed_letters << "\n알파벳 한 글자를 입력하세요: ";

        char guess;
        cin >> guess;
        guess = tolower(guess);

        if (!isalpha(guess) || guessed_letters.find(guess) != string::npos) {
            cout << "잘못된 입력입니다. 다시 입력해주세요.\n";
            continue;
        }

        guessed_letters += guess;
        bool found = false;

        for (size_t i = 0; i < keyword.size(); ++i) {
            if (keyword[i] == guess) {
                guessed[i] = guess;
                found = true;
            }
        }

        if (found) {
            cout << "좋아요! '" << guess << "'는 단어에 포함되어 있습니다.\n";
        } else {
            cout << "안타깝습니다. '" << guess << "'는 단어에 없습니다.\n";
        }

        attempts_left--;
    }

    if (guessed == keyword) {
        cout << "\n축하합니다! 단어를 맞추셨습니다: " << keyword << "\n";
    } else {
        cout << "\n게임 오버! 단어는 다음과 같았습니다: " << keyword << "\n";
    }
}

// Employee 클래스 구현
Employee::Employee() {
    rand_name[0] = "김수현"; rand_name[1] = "이정환"; rand_name[2] = "박지현";
    rand_name[3] = "황서연"; rand_name[4] = "김칠우"; rand_name[5] = "엄준성";
    rand_name[6] = "김재현"; rand_name[7] = "박건우"; rand_name[8] = "함시우"; rand_name[9] = "지현아";
}

void Hire(Employee& hire) {
    srand((unsigned)time(NULL));
    string yn;
    cout << "직원 고용을 진행합니다.\n";
    for (int i = 0; i < 3; i++) {
        int employee_money = rand() % 10000 + 1000;
        int menu_count_plus = rand() % 3 + 1;
        int k = rand() % 9;

        cout << "직원이름: " << hire.rand_name[k] << "\n고용비용: " << employee_money 
             << "원\n메뉴 추가 개수: " << menu_count_plus << "\n고용하시겠습니까?(Y/N): ";
        cin >> yn;

        if (yn == "Y" || yn == "y") {
            cout << "직원을 고용했습니다.\n";
            if (make_coffee_count + menu_count_plus < MAX_MENU) {
                make_coffee_count += menu_count_plus;
            } else {
                cout << "최대 메뉴 개수에 도달하였습니다.\n";
                make_coffee_count = MAX_MENU;
            }
            hire.employee_name = hire.rand_name[k];
            hire.employee_price = employee_money;
            staff_count++;
            cout << "현재 메뉴 개수: " << make_coffee_count << "\n고용 직원 수: " << staff_count << "/3명\n";
            break;
        } else {
            cout << "다음 직원을 소개합니다.\n";
        }
    }
}

// Anim, Menu, Run 클래스 구현 (추가로 필요 시 작성)

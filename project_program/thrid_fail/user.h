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

// 클래스 및 함수 선언
class Event {
public:
    map<string, string> newspaperKeywords;
    Event();
    void ShowNewspaper(int index);
    void MiniGame(int index);
};

class Employee {
private:
    string rand_name[10];
    string employee_name;

public:
    int employee_price = 0;
    Employee();
    friend void Hire(Employee& hire);
};

class Anim {
public:
    void clearScreen();
    void anim_text(string message);
};

class Menu {
private:
    vector<string> menu_name;
    vector<int> menu_price;
    vector<int> menu_sell;
    vector<int> supply_demand_num;
    bool check_menu_make = false;
    string dessert_name;
    int dessert_price;
    int dessert_sell;
    int dessert_total_sell;
    bool check_dessert_make = false;
    int total_sell;

public:
    Menu();
    void MakeMenu();
    void MakeDessert();
    void ShowMenu();
    void ModifyMenu();
    void SellMenu();
    int ReturnCount();
    bool ReturnMenuCheck();
    void SupplyDemand(int i);
    void Total(int total_staff);
};

class Run {
private:
    int day = 1;

public:
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

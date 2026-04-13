#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Tinfo {
    string productCode;   // ключ
    string saleDate;      // дата продажи: dd.mm.yyyy
    double price;         // цена
    bool isReturned;      // отметка о возврате
    string returnDate;    // дата возврата
};

struct Tnode {
    Tinfo info;
    Tnode* next;
    Tnode* prev;
};

extern Tnode* HeadList;
extern Tnode* TailList;

// Базовые операции
Tnode* createNode(Tinfo value);
void insertFirst(Tinfo value);
void insertLast(Tinfo value);
Tnode* searchByCode(const string& code);
void deleteByCode(const string& code);
void print_left_right();
void print_right_left();
void clearList();
void create_manual_list();
void create_ready_list();

// Дополнительные функции
Tinfo inputInfo();
void printInfo(const Tinfo& x);

// Операции варианта 12
void sortByReturnStatus();                 // сначала не возвращенные, потом возвращенные
void moveReturnedToFront();                // вернуть часть с возвращенными в начало
void deleteSoldBeforeDate(const string& date); // удалить товар, проданный до указанной даты

// Вспомогательные функции
int dateToInt(const string& date);
void removeNode(Tnode* node);
void insertBeforeNode(Tnode* pos, Tnode* newNode);
void insertAfterNode(Tnode* pos, Tnode* newNode);
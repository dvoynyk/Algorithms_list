#include <iostream>
#include <clocale>
#include "Tnode.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    string code;
    string date;
    Tinfo value;

    do {
        cout << "\n============= МЕНЮ =============\n";
        cout << "1. Использовать готовый список\n";
        cout << "2. Создать список вручную\n";
        cout << "3. Добавить товар в начало\n";
        cout << "4. Добавить товар в конец\n";
        cout << "5. Удалить товар по коду\n";
        cout << "6. Найти товар по коду\n";
        cout << "7. Вывести список слева направо\n";
        cout << "8. Вывести список справа налево\n";
        cout << "9. Очистить список\n";
        cout << "10. Упорядочить: сначала не возвращенные, затем возвращенные\n";
        cout << "11. Перенести возвращенные товары в начало списка\n";
        cout << "12. Удалить товары, проданные до указанной даты\n";
        cout << "0. Выход\n";
        cout << "================================\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {

        case 1:
            create_ready_list();
            print_left_right();
            break;
        case 2:
            create_manual_list();
            cout << "\nСписок создан:\n";
            print_left_right();
            break;

        case 3:
            cout << "\nВвод нового товара:\n";
            value = inputInfo();
            insertFirst(value);
            cout << "Товар добавлен в начало.\n";
            print_left_right();
            break;

        case 4:
            cout << "\nВвод нового товара:\n";
            value = inputInfo();
            insertLast(value);
            cout << "Товар добавлен в конец.\n";
            print_left_right();
            break;

        case 5:
            cout << "Введите код товара для удаления: ";
            cin >> code;
            deleteByCode(code);
            print_left_right();
            break;

        case 6: {
            cout << "Введите код товара для поиска: ";
            cin >> code;

            Tnode* found = searchByCode(code);
            if (found != nullptr) {
                cout << "Товар найден:\n";
                printInfo(found->info);
                cout << endl;
            }
            else {
                cout << "Товар не найден.\n";
            }
            break;
        }

        case 7:
            cout << "\nСписок слева направо:\n";
            print_left_right();
            break;

        case 8:
            cout << "\nСписок справа налево:\n";
            print_right_left();
            break;

        case 9:
            clearList();
            cout << "Список очищен.\n";
            break;

        case 10:
            sortByReturnStatus();
            cout << "Список упорядочен.\n";
            print_left_right();
            break;

        case 11:
            moveReturnedToFront();
            cout << "Возвращенные товары перенесены в начало.\n";
            print_left_right();
            break;

        case 12:
            cout << "Введите дату (dd.mm.yyyy): ";
            cin >> date;
            deleteSoldBeforeDate(date);
            print_left_right();
            break;

        case 0:
            cout << "Выход из программы.\n";
            break;

        default:
            cout << "Ошибка: неверный пункт меню.\n";
        }

    } while (choice != 0);

    clearList();
    return 0;
}
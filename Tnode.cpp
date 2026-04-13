#include "Tnode.h"

Tnode* HeadList = nullptr;
Tnode* TailList = nullptr;

Tnode* createNode(Tinfo value) {
    Tnode* node = new Tnode;
    node->info = value;
    node->next = nullptr;
    node->prev = nullptr;
    return node;
}

Tinfo inputInfo() {
    Tinfo x;

    cout << "Введите код товара: ";
    cin >> x.productCode;

    cout << "Введите дату продажи (dd.mm.yyyy): ";
    cin >> x.saleDate;

    cout << "Введите цену: ";
    cin >> x.price;

    cout << "Товар возвращен? (1 - да, 0 - нет): ";
    cin >> x.isReturned;

    if (x.isReturned) {
        cout << "Введите дату возврата (dd.mm.yyyy): ";
        cin >> x.returnDate;
    }
    else {
        x.returnDate = "-";
    }

    return x;
}

void printInfo(const Tinfo& x) {
    cout << "Код товара: " << x.productCode
        << ", Дата продажи: " << x.saleDate
        << ", Цена: " << x.price
        << ", Возврат: " << (x.isReturned ? "Да" : "Нет")
        << ", Дата возврата: " << x.returnDate;
}

void create_ready_list()
{
    clearList();

    insertLast({ "A1", "10.03.2024", 1500, false, "-" });
    insertLast({ "B2", "05.02.2024", 3200, true,  "12.02.2024" });
    insertLast({ "C3", "18.01.2024", 2100, false, "-" });
    insertLast({ "D4", "25.12.2023", 4999, true,  "03.01.2024" });
    insertLast({ "E5", "14.04.2024", 2750, false, "-" });

    cout << "Готовый список создан.\n";
}
void create_manual_list() {
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    clearList();

    for (int i = 0; i < n; i++) {
        cout << "\nЭлемент #" << i + 1 << ":\n";
        Tinfo x = inputInfo();
        insertLast(x);
    }
}

void insertFirst(Tinfo value) {
    Tnode* node = createNode(value);

    if (HeadList == nullptr) {
        HeadList = TailList = node;
    }
    else {
        node->next = HeadList;
        HeadList->prev = node;
        HeadList = node;
    }
}

void insertLast(Tinfo value) {
    Tnode* node = createNode(value);

    if (TailList == nullptr) {
        HeadList = TailList = node;
    }
    else {
        node->prev = TailList;
        TailList->next = node;
        TailList = node;
    }
}

Tnode* searchByCode(const string& code) {
    Tnode* current = HeadList;

    while (current != nullptr) {
        if (current->info.productCode == code)
            return current;
        current = current->next;
    }

    return nullptr;
}

void removeNode(Tnode* node) {
    if (node == nullptr) return;

    if (HeadList == TailList) {
        delete node;
        HeadList = TailList = nullptr;
        return;
    }

    if (node == HeadList) {
        HeadList = HeadList->next;
        HeadList->prev = nullptr;
        delete node;
        return;
    }

    if (node == TailList) {
        TailList = TailList->prev;
        TailList->next = nullptr;
        delete node;
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

void deleteByCode(const string& code) {
    Tnode* node = searchByCode(code);

    if (node == nullptr) {
        cout << "Товар с таким кодом не найден.\n";
        return;
    }

    removeNode(node);
    cout << "Первый найденный товар с кодом " << code << " удален.\n";
}

void print_left_right() {
    if (HeadList == nullptr) {
        cout << "Список пуст.\n";
        return;
    }

    Tnode* current = HeadList;
    while (current != nullptr) {
        printInfo(current->info);
        cout << endl;
        current = current->next;
    }
}

void print_right_left() {
    if (TailList == nullptr) {
        cout << "Список пуст.\n";
        return;
    }

    Tnode* current = TailList;
    while (current != nullptr) {
        printInfo(current->info);
        cout << endl;
        current = current->prev;
    }
}

void clearList() {
    Tnode* current = HeadList;

    while (current != nullptr) {
        Tnode* temp = current;
        current = current->next;
        delete temp;
    }

    HeadList = nullptr;
    TailList = nullptr;
}

int dateToInt(const string& date) {
    // формат dd.mm.yyyy
    if (date.size() != 10) return 0;

    string dd = date.substr(0, 2);
    string mm = date.substr(3, 2);
    string yyyy = date.substr(6, 4);

    return stoi(yyyy + mm + dd);
}

void insertBeforeNode(Tnode* pos, Tnode* newNode) {
    if (pos == nullptr || newNode == nullptr) return;

    if (pos == HeadList) {
        newNode->next = HeadList;
        newNode->prev = nullptr;
        HeadList->prev = newNode;
        HeadList = newNode;
        return;
    }

    newNode->next = pos;
    newNode->prev = pos->prev;
    pos->prev->next = newNode;
    pos->prev = newNode;
}

void insertAfterNode(Tnode* pos, Tnode* newNode) {
    if (pos == nullptr || newNode == nullptr) return;

    if (pos == TailList) {
        newNode->prev = TailList;
        newNode->next = nullptr;
        TailList->next = newNode;
        TailList = newNode;
        return;
    }

    newNode->next = pos->next;
    newNode->prev = pos;
    pos->next->prev = newNode;
    pos->next = newNode;
}

// Вариант 12:
// сначала проданные, но не возвращенные, затем возвращенные
void sortByReturnStatus() {
    if (HeadList == nullptr || HeadList->next == nullptr) return;

    Tnode* current = HeadList->next;

    while (current != nullptr) {
        Tnode* nextCurrent = current->next;

        if (!current->info.isReturned) {
            Tnode* p = current->prev;
            while (p != nullptr && p->info.isReturned) {
                p = p->prev;
            }

            // Если нашли место, после которого нужно вставить
            // Если p == nullptr, значит вставляем в начало
            if (current->prev != p) {
                Tinfo tempInfo = current->info;
                removeNode(current);

                Tnode* newNode = createNode(tempInfo);

                if (p == nullptr)
                    insertFirst(tempInfo);
                else
                    insertAfterNode(p, newNode);
            }
        }

        current = nextCurrent;
    }
}

// Перенести возвращенные товары в начало списка
void moveReturnedToFront() {
    if (HeadList == nullptr || HeadList->next == nullptr) return;

    Tnode* current = HeadList;

    while (current != nullptr) {
        Tnode* nextCurrent = current->next;

        if (current->info.isReturned && current != HeadList) {
            // отсоединяем узел
            if (current == TailList) {
                TailList = current->prev;
                TailList->next = nullptr;
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            // вставляем в начало
            current->prev = nullptr;
            current->next = HeadList;
            HeadList->prev = current;
            HeadList = current;
        }

        current = nextCurrent;
    }
}

// Удалить товары, проданные до указанной даты
void deleteSoldBeforeDate(const string& date) {
    int limitDate = dateToInt(date);

    Tnode* current = HeadList;
    while (current != nullptr) {
        Tnode* nextCurrent = current->next;

        if (dateToInt(current->info.saleDate) < limitDate) {
            removeNode(current);
        }

        current = nextCurrent;
    }

    cout << "Удаление товаров, проданных до " << date << ", завершено.\n";
}
#include <initializer_list>
#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int _val) {
        val = _val;
        next = nullptr;
    }

};
struct list {
    Node* first;
    Node* last;
    list()
    {
        first = nullptr;
        last = nullptr;
    }
    list(initializer_list<int> init) {
        first = nullptr;
        last = nullptr;
        for (const int& x : init) {
            push_back(x);
        }
    }
    ~list()
    {
        clear();
    }
    void clear() {
        while (!is_empty()) {
            Node* p = first;
            first = first->next;
            delete p;
        }
        last = nullptr;
    }
    void create_ready_list(list& lst) {
        lst.clear();

        lst.push_back(1);
        lst.push_back(2);
        lst.push_back(3);
        lst.push_back(4);
        lst.push_back(5);
    }
    void create_manual_list(list& lst) {
        int n;
        int x;

        lst.clear();

        cout << "Enter number of elements: ";
        cin >> n;

        cout << "Enter elements:\n";
        for (int i = 0; i < n; i++) {
            cin >> x;
            lst.push_back(x);
        }
    }
    bool is_empty()
    {
        return first == nullptr;
    }
    void push_front(int _val) {
        Node* p = new Node(_val);
        p->next = first;
        first = p;

        if (last == nullptr) {
            last = p;
        }
    }
    void push_back(int _val)
    {
        Node* p = new Node(_val);
        if (is_empty())
        {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }
    void print()
    {
        if (is_empty()) return;
        Node* p = first;
        while (p)
        {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }
    Node* find(int _val) {
        Node* p = first;
        while (p && p->val != _val)
            p = p->next;
        return p;
    }
    void remove_first() {
        if (is_empty()) return;

        Node* p = first;
        first = first->next;
        delete p;

        if (first == nullptr) {
            last = nullptr;
        }
    }
    void remove_last()
    {
        if (is_empty()) return;

        if (first == last) {
            delete first;
            first = nullptr;
            last = nullptr;
            return;
        }

        Node* p = first;
        while (p->next != last) {
            p = p->next;
        }

        delete last;
        last = p;
        last->next = nullptr;
    }
    void remove(int _val) {
        if (is_empty()) return;
        if (first->val == _val) {
            remove_first();
            return;
        }
        else if (last->val == _val) {
            remove_last();
            return;
        }
        Node* slow = first;
        Node* fast = first->next;
        while (fast && fast->val != _val) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) {
            cout << "This element does not exist" << endl;
            return;
        }
        slow->next = fast->next;
        delete fast;
    }
};


int last_digit(int x)
{
    return x % 10;
}

void new_list_L2(list& L1, list& L2)
{
    L2.clear();

    while (!L1.is_empty())
    {
        Node* moved = L1.first;
        L1.first = L1.first->next;

        if (L1.first == nullptr)
        {
            L1.last = nullptr;
        }

        moved->next = nullptr;

        if (L2.is_empty())
        {
            L2.first = moved;
            L2.last = moved;
        }
        else if (last_digit(moved->val) < last_digit(L2.first->val))
        {
            moved->next = L2.first;
            L2.first = moved;
        }
        else
        {
            Node* p = L2.first;
            while (p->next != nullptr &&
                last_digit(p->next->val) <= last_digit(moved->val))
            {
                p = p->next;
            }

            moved->next = p->next;
            p->next = moved;

            if (moved->next == nullptr)
            {
                L2.last = moved;
            }
        }
    }
}

bool L2_up(const list& L2)
{
    if (L2.first == nullptr) return true;

    Node* p = L2.first;
    while (p->next != nullptr)
    {
        if (p->val > p->next->val)
        {
            return false;
        }
        p = p->next;
    }
    return true;
}

void remove_at(list& L1, int pos)
{
    if (L1.is_empty() || pos < 0) return;

    if (pos == 0) {
        L1.remove_first();
        return;
    }

    Node* prev = L1.first;
    for (int i = 0; i < pos - 1 && prev != nullptr; i++) {
        prev = prev->next;
    }

    if (prev == nullptr || prev->next == nullptr) {
        cout << "Invalid position" << endl;
        return;
    }

    Node* to_delete = prev->next;
    prev->next = to_delete->next;

    if (to_delete == L1.last) {
        L1.last = prev;
    }

    delete to_delete;
}

void print_menu()
{
    cout << "\nМЕНЮ:\n";
    cout << "1. Создать список L1 вручную\n";
    cout << "2. Использовать готовый список L1\n";
    cout << "3. Вывести список L1\n";
    cout << "4. Вставить новый узел перед первым в L1\n";
    cout << "5. Удалить узел по ключу из L1\n";
    cout << "6. Удалить узел по позиции из L1\n";
    cout << "7. Сформировать список L2 из L1\n";
    cout << "8. Вывести список L2\n";
    cout << "9. Проверить, упорядочен ли L2 по возрастанию\n";
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
}

int main()
{
    setlocale(LC_ALL, "russian");
    list L1;
    list L2;
    int choice;

    do
    {
        print_menu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            L1.create_manual_list(L1);
            cout << "Список L1 создан вручную.\n";
            break;

        case 2:
            L1.create_ready_list(L1);
            cout << "Готовый список L1 создан.\n";
            break;

        case 3:
            cout << "Список L1: ";
            L1.print();
            break;

        case 4:
        {
            int x;
            cout << "Введите значение нового элемента: ";
            cin >> x;
            L1.push_front(x);
            cout << "Элемент вставлен в начало списка L1.\n";
            break;
        }

        case 5:
        {
            int key;
            cout << "Введите ключ для удаления: ";
            cin >> key;
            L1.remove(key);
            break;
        }

        case 6:
        {
            int pos;
            cout << "Введите позицию для удаления (начиная с 0): ";
            cin >> pos;
            remove_at(L1, pos);
            break;
        }

        case 7:
            new_list_L2(L1, L2);
            cout << "Список L2 сформирован из L1.\n";
            break;

        case 8:
            cout << "Список L2: ";
            L2.print();
            break;

        case 9:
            if (L2_up(L2))
                cout << "Список L2 упорядочен по возрастанию.\n";
            else
                cout << "Список L2 НЕ упорядочен по возрастанию.\n";
            break;

        case 0:
            cout << "Работа программы завершена.\n";
            break;

        default:
            cout << "Неверный пункт меню.\n";
        }

    } while (choice != 0);

    return 0;
}
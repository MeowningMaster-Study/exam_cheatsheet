#include <iostream>
using namespace std;

struct double_linked_list {
    // тип хранимых значений
    typedef int value_type;

    struct node {
        value_type value;
        node *next;
        node *prev;

        node(value_type value) {
            this->value = value;
            next = nullptr;
            prev = nullptr;
        }

        // удалить текущий елемент с сохранением порядка
        // не забудь изменить размер, если он нужен
        void pull_out() {
            if (prev != nullptr) {
                prev->next = next;
            }

            if (next != nullptr) {
                next->prev = prev;
            }

            delete this;
        }
    };

    // если нужно поддерживать размер, расскоментируй все ёго упоминания
    // size_t size;
    node *begin;
    node *end;

    double_linked_list() {
        // size = 0;
        begin = nullptr;
        end = nullptr;
    }
    
    void push_back(value_type value) {
        node *node_new = new node(value);
        if (empty()) {
            begin = node_new;
        } else {
            end->next = node_new;
            node_new->prev = end;
        }
        end = node_new;
        // size++;
    }

    value_type pop_back() {
        if (empty()) {
            throw "Can't pop";
        }

        value_type value = end->value;
        node *old_end = end;

        if (end != begin) {
            end = end->prev;
            end->next = nullptr;
        } else {
            begin = nullptr;
            end = nullptr;
        }
        
        // size--;
        delete old_end;

        return value;
    }

    bool empty() {
        return begin == nullptr;
    }

    ~double_linked_list() {
        node *i = begin;
        while (i != nullptr) {
            node *s = i;
            i = i->next;
            delete s;
        }
    }
};

int main() {
    double_linked_list dll;
    
    size_t n;
    cin >> n;

    for (size_t i = 0; i < n; i++) {
        int r;
        cin >> r;
        dll.push_back(r);
    }

    // обход
    for(auto *i = dll.begin; i != nullptr; i = i->next) {
        cout << i->value << ' ';
    }
    cout << endl;

    // обратный обход
    for(auto *i = dll.end; i != nullptr; i = i->prev) {
        cout << i->value << ' ';
    }
    cout << endl;

    // удалить 2 елемент
    dll.begin->next->pull_out();
    //dll.size--;

    // достаем все елементы
    while (!dll.empty()) {
        cout << dll.pop_back() << ' ';
    }
    cout << endl;

    return 0;
}
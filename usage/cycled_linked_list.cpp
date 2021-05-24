#include <iostream>
using namespace std;

struct cycled_linked_list {
    // тип хранимых значений
    typedef int value_type;

    struct node {
        value_type value;
        node *next, *prev;

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
    node *entry;
    // entry всегда указывает на последний добавленный елемент

    cycled_linked_list() {
        // size = 0;
        entry = nullptr;
    }
    
    void push_back(value_type value) {
        node *new_node = new node(value);
        if (!empty()) {
            new_node->next = entry->next;
            new_node->prev = entry;
            entry->next->prev = new_node;
            entry->next = new_node;
        } else {
            new_node->next = new_node;
            new_node->prev = new_node;
        }

        entry = new_node;
        // size++;
    }

    value_type pop_back() {
        if (empty()) {
            throw "Can't pop";
        }

        value_type value = entry->value;
        node *old_entry = entry;

        if (entry->prev == entry) {
            entry = nullptr;
        } else {
            entry = entry->prev;
            entry->next = old_entry->next;
            old_entry->next->prev = entry;
        }
        
        delete old_entry;
        // size--;

        return value;
    }

    bool empty() {
        return entry == nullptr;
    }

    ~cycled_linked_list() {
        if (empty()) {
            return;
        }

        node *i = entry;
        do {
            node *s = i;
            i = i->next;
            delete s;
        } while (i != entry);
    }
};

int main() {
    cycled_linked_list cll;
    
    size_t n;
    cin >> n;

    for (size_t i = 0; i < n; i++) {
        int r;
        cin >> r;
        cll.push_back(r);
    }

    // обход
    if (!cll.empty()) {
        auto i = cll.entry;

        do {
            i = i->next;
            cout << i->value << ' ';
        } while (i != cll.entry);
    }
    cout << endl;

    // удалить 2 елемент
    cll.entry->next->next->pull_out();
    //cll.size--;

    // достаем все елементы
    while (!cll.empty()) {
        cout << cll.pop_back() << ' ';
    }
    cout << endl;

    return 0;
}
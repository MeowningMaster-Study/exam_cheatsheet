#include <iostream>
using namespace std;

struct cycled_linked_list {
    // тип даних, що зберігаються
    typedef int value_type;

    struct node {
        value_type value;
        node *next, *prev;

        node(value_type value) {
            this->value = value;
            next = nullptr;
            prev = nullptr;
        }

        // видалити поточний елемент із збереженням порядку
        // не забудьте змінити розмір, якщо він потрібен
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

    // якщо потрібно підтримувати розмір, розкоментуйте всі його згадування
    // size_t size;
    node *entry;
    // entry завжди вказує на останній доданий елемент

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

    // обхід
    if (!cll.empty()) {
        auto i = cll.entry;

        do {
            i = i->next;
            cout << i->value << ' ';
        } while (i != cll.entry);
    }
    cout << endl;

    // видалити 2 елемент
    cll.entry->next->next->pull_out();
    //cll.size--;

    // дістаємо всі елементи
    while (!cll.empty()) {
        cout << cll.pop_back() << ' ';
    }
    cout << endl;

    return 0;
}
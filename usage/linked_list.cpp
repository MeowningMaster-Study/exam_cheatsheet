#include <iostream>
using namespace std;

struct linked_list {
    // тип даних, що зберігаються
    typedef int value_type;

    struct node {
        value_type value;
        node *next;

        node(value_type value) {
            this->value = value;
            next = nullptr;
        }
    };

    // якщо потрібно підтримувати розмір, розкоментуйте всі його згадування
    // size_t size;
    node *begin, *end;

    linked_list() {
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
        }
        end = node_new;
        // size++;
    }

    bool empty() {
        return begin == nullptr;
    }

    ~linked_list() {
        node *i = begin;
        while (i != nullptr) {
            node *s = i;
            i = i->next;
            delete s;
        }
    }
};

int main() {
    linked_list ll;
    
    size_t n;
    cin >> n;

    for (size_t i = 0; i < n; i++) {
        int r;
        cin >> r;
        ll.push_back(r);
    }

    for (auto *i = ll.begin; i != nullptr; i = i->next) {
        cout << i->value << ' ';
    }
    cout << endl;

    return 0;
}
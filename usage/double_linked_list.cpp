#include <iostream>
using namespace std;

struct double_linked_list {
    typedef int value_type;

    struct node {
        value_type value;
        node *next;
        node *prev;

        node(value_type value): next(nullptr), prev(nullptr) {
            this->value = value;
        }
    };

    size_t size;
    node *begin;
    node *end;

    double_linked_list(): size(0), begin(nullptr), end(nullptr) {}
    
    void push_back(value_type value) {
        node *node_new = new node(value);
        if (size == 0) {
            begin = node_new;
        } else {
            end->next = node_new;
            node_new->prev = end;
        }
        end = node_new;
        size++;
    }

    value_type pop_back() {
        if (size == 0) {
            throw "Can't pop";
        }

        value_type value = end->value;
        node *old_end = end;

        if (size > 1) {
            end = end->prev;
            end->next = nullptr;
        } else {
            begin = nullptr;
            end = nullptr;
        }
        
        size--;
        delete old_end;

        return value;
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

    while (dll.size != 0) {
        cout << dll.pop_back() << ' ';
    }
    cout << endl;

    return 0;
}
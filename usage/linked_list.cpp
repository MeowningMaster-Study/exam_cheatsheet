#include <iostream>
#include <cmath>
using namespace std;

struct linked_list {
    typedef int value_type;

    struct node {
        value_type value;
        node *next;

        node(value_type value): next(nullptr) {
            this->value = value;
        }
    };

    size_t size;
    node *begin;
    node *end;

    linked_list(): size(0), begin(nullptr), end(nullptr) {}
    
    void push_back(value_type value) {
        node *node_new = new node(value);
        if (size == 0) {
            begin = node_new;
        } else {
            end->next = node_new;
        }
        end = node_new;
        size++;
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

    for (linked_list::node *i = ll.begin; i != nullptr; i = i->next) {
        cout << i->value << ' ';
    }
    cout << endl;

    return 0;
}
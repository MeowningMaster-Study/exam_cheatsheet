#include <iostream>
using namespace std;

struct stack {
    typedef int value_type;
    struct node {
        value_type value;
        node *prev;

        node(value_type value) {
            this->value = value;
            prev = nullptr;
        }
    };

    node *top;

    stack() {
        top = nullptr;
    }

    void push(value_type value) {
        node *new_node = new node(value);
        new_node->prev = top;
        top = new_node;
    }

    value_type pop() {
        if (empty()) {
            throw "Can't pop";
        }

        value_type value = top->value;
        node *old_top = top;
        top = top->prev;
        delete old_top;

        return value;
    }

    bool empty() {
        return top == nullptr;
    }
};

int main() {
    stack s;

    size_t n;
    cin >> n;

    for (size_t i = 0; i < n; i++) {
        int r;
        cin >> r;
        s.push(r);
    }

    while (!s.empty()) {
        cout << s.pop() << ' ';
    }
    
    return 0;
}
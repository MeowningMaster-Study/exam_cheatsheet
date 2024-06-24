#include <iostream>
using namespace std;

struct queue {
    typedef int value_type;
    struct node {
        value_type value;
        node *next;

        node(value_type value) {
            this->value = value;
            next = nullptr;
        }
    };

    //! last може залишитись непорожнім, навіть якщо черга порожня
    node *first, *last;

    queue() {
        first = nullptr;
        last = nullptr;
    }

    void push(value_type value) {
        node *new_node = new node(value);

        if (empty()) {
            first = new_node;
            
        } else {
            last->next = new_node;
        }
        last = new_node;
    }

    value_type pop() {
        if (empty()) {
            throw "Can't pop";
        }

        value_type value = first->value;
        node *old_first = first;
        first = first->next;
        delete old_first;

        return value;
    }

    bool empty() {
        return first == nullptr;
    }
};

int main() {
    queue q;

    size_t n;
    cin >> n;

    for (size_t i = 0; i < n; i++) {
        int r;
        cin >> r;
        q.push(r);
    }

    while (!q.empty()) {
        cout << q.pop() << ' ';
    }
    
    return 0;
}
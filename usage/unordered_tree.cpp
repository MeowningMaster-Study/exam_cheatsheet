#include <iostream>
using namespace std;

struct tree_node {
    // кількість дочірніх елементів
    const static int children_count = 2;
    // тип даних, що зберігаються
    typedef int value_type;
    value_type value;
    tree_node *children[children_count];

    tree_node(value_type value) {
        this->value = value;

        for (size_t i = 0; i < children_count; i++) {
            children[i] = nullptr;
        }
    }

    // обхід у глибину
    void dfs() {
        // тут можна робити щось з вершиною
        // cout << this->value << endl;

        for (size_t i = 0; i < children_count; i++) {
            if (children[i] != nullptr) {
                children[i]->dfs();
            }
        }
    }

    // для обходу у ширину
    struct stack {
        typedef tree_node* value_type;
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

    // обхід у ширину
    void bfs() {
        stack s;
        s.push(this);

        while (!s.empty()) {
            tree_node *x = s.pop();

            // тут можна робити щось з вершиною
            // cout << x->value << endl;

            for (size_t i = 0; i < children_count; i++) {
                if (x->children[i] != nullptr) {
                    s.push(x->children[i]);
                }
            }
        }
    }
};

int main() {
    tree_node *a = new tree_node(5);
    tree_node *b = new tree_node(2);
    tree_node *c = new tree_node(3);
    tree_node *d = new tree_node(9);

    a->children[0] = b;
    a->children[1] = c;
    b->children[0] = d;

    a->dfs();
    a->bfs();

    return 0;
}
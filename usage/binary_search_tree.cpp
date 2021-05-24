#include <iostream>
using namespace std;

struct tree_node {
    //тип хранимого значения
    typedef int value_type;
    value_type value;
    tree_node *children[2];

    tree_node(value_type value) {
        this->value = value;
        children[0] = nullptr;
        children[1] = nullptr;
    }

    bool cmp(value_type a, value_type b) {
        // поменяйте на a > b если нужен обратный порядок
        return a < b;
    }
    
    bool insert(value_type value) {
        // возвращаем false, если елемент уже был вставлен
        if (value == this->value) {
            return false;
        }

        if (cmp(value, this->value)) {
            if (children[0] == nullptr) {
                children[0] = new tree_node(value);
                return true;
            } else {
                return children[0]->insert(value);
            }
        } else {
            if (children[1] == nullptr) {
                children[1] = new tree_node(value);
                return true;
            } else {
                return children[1]->insert(value);
            }
        }
    }

    struct search_result {
        bool success;
        tree_node *node;
    };

    search_result find(value_type value) {
        if (this == nullptr) {
            return {false, nullptr};
        }

        if (value == this->value) {
            return {true, this};
        }

        if (cmp(value, this->value)) {
            return children[0]->find(value);
        } else {
            return children[1]->find(value);
        }
    }
    

    // обход в глубину
    void dfs() {
        // тут пишем что нужно
        // cout << this->value << endl;

        if (children[0] != nullptr) {
            children[0]->dfs();
        }

        if (children[1] != nullptr) {
            children[1]->dfs();
        }
    }

    // для обхода в ширину
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

    // обход в ширину
    void bfs() {
        stack s;
        s.push(this);

        while (!s.empty()) {
            tree_node *x = s.pop();

            // тут пишем что нужно
            //cout << x->value << endl;

            if (x->children[0] != nullptr) {
                s.push(x->children[0]);
            }

            if (x->children[1] != nullptr) {
                s.push(x->children[1]);
            }
        }
    }
};

int main() {
    // пример 1
    tree_node *a = new tree_node(5);
    tree_node *b = new tree_node(2);
    tree_node *c = new tree_node(3);
    tree_node *d = new tree_node(9);

    a->children[0] = b;
    a->children[1] = c;
    b->children[0] = d;

    a->dfs();
    a->bfs();

    // пример 2
    tree_node *root = nullptr;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        char a;
        int b;
        cin >> a >> b;

        switch (a) {
        case 'i': { // insert
            if (root == nullptr) {
                root = new tree_node(b);
            } else {
                if (!root->insert(b)) {
                    cout << "Already inserted" << endl;
                }
            }
            break;
        } 
        case 'f': {
            auto result = root->find(b);
            cout << (result.success ? "Yes" : "No") << endl;
            break;
        }
        default:
            cout << "Unsprecified command" << endl;
        }
    }

    return 0;
}
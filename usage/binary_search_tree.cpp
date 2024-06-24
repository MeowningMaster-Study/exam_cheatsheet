#include <iostream>
using namespace std;

struct tree_node {
    // тип даних, що зберігається
    typedef int value_type;
    value_type value;
    tree_node *children[2];

    tree_node(value_type value) {
        this->value = value;
        children[0] = nullptr;
        children[1] = nullptr;
    }

    bool cmp(value_type a, value_type b) {
        // зміни на a > b, якщо треба зворотній порядок
        return a < b;
    }
    
    bool insert(value_type value) {
        // повертаємо false, якщо елемент вже був доданий
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
    

    // обхід у глибину
    void dfs() {
        // тут можна робити щось з вершиною
        // cout << this->value << endl;

        if (children[0] != nullptr) {
            children[0]->dfs();
        }

        if (children[1] != nullptr) {
            children[1]->dfs();
        }
    }

    // для обходу в ширину
    struct queue {
        typedef tree_node* value_type;
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

    // обхід у ширину
    void bfs() {
        queue s;
        s.push(this);

        while (!s.empty()) {
            tree_node *x = s.pop();

            // тут можна робити щось з вершиною
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
    // приклад 1
    tree_node *a = new tree_node(5);
    tree_node *b = new tree_node(2);
    tree_node *c = new tree_node(3);
    tree_node *d = new tree_node(9);

    a->children[0] = b;
    a->children[1] = c;
    b->children[0] = d;

    a->dfs();
    a->bfs();

    // приклад 2
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
        case 'f': { // search
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
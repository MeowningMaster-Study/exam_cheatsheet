#include <iostream>
using namespace std;

struct sparse_linked_list {
    // тип значений
    typedef int value_type;

    struct node {
        size_t index;
        value_type value;
        node *next;

        node(size_t index, value_type value) {
            this->index = index;
            this->value = value;
            next = nullptr;
        }
    };

    // якщо потрібно підтримувати розмір, розкоментуйте всі його згадування
    // size_t size;
    node *begin, *end;

    sparse_linked_list() {
        // size = 0;
        begin = nullptr;
        end = nullptr;
    }
    
    //! push_back не дивиться на порядок індексів
    //! краще використовувати insert
    void push_back(size_t index, value_type value) {
        node *node_new = new node(index, value);
        if (empty()) {
            begin = node_new;
        } else {
            end->next = node_new;
        }
        end = node_new;
        // size++;
    }

    // поверає false, якщо індекс зайнятий
    bool insert(size_t index, value_type value) {
        if (empty()) {
            node *node_new = new node(index, value);
            begin = node_new;
            end = node_new;
            return true;
        }

        if (index == end->index) {
            return false;
        }

        if (index > end->index) {
            push_back(index, value);
            return true;
        }

        for (auto *i = begin; i != nullptr; i = i->next) {
            if (index == i->index) {
                return false;
            }

            if (index < i->index) {
                node *node_new = new node(i->index, i->value);
                node_new->next = i->next;
                i->index = index;
                i->value = value;
                i->next = node_new;

                if (end == i) {
                    end = node_new;
                }
                return true;
            }
        }

        throw "How did u get here?";
    }

    bool empty() {
        return begin == nullptr;
    }

    ~sparse_linked_list() {
        node *i = begin;
        while (i != nullptr) {
            node *s = i;
            i = i->next;
            delete s;
        }
    }
};

int main() {
    sparse_linked_list sll;
    
    size_t n;
    cin >> n;

    for (size_t i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (!sll.insert(a, b)) {
            cout << "This index is used" << endl;
            n++;
        }
    }

    for (auto *i = sll.begin; i != nullptr; i = i->next) {
        cout << i->index << '~' << i->value << ' ';
    }
    cout << endl;

    return 0;
}
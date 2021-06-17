#include <iostream>
using namespace std;

struct indexed_linked_lists {
    // тип значений
    typedef int value_type;

    struct linked_list {
        struct node {
            value_type value;
            node *next;

            node(value_type value) {
                this->value = value;
                next = nullptr;
            }
        };

        // раскоментируй все упоминания size если нужен размер
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

    size_t size;
    linked_list* lists;

    indexed_linked_lists(size_t size) {
        lists = new linked_list[size];
    }

    linked_list& operator[] (size_t index) {
        return lists[index];
    }

    ~indexed_linked_lists() {
        delete[] lists;
    }
};

int main() {
    // будем хранить числа с разными остатками от 10
    // в разных связных списках
    indexed_linked_lists storage(10);

    // заполняем
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int r;
        cin >> r;
        storage[r % 10].push_back(r);
    }

    // ищем
    int m;
    cin >> m;
    for (int i = 0; i < n; i++) {
        int r;
        cin >> r;

        indexed_linked_lists::linked_list& row = storage[r % 10];
        if (!row.empty()) {
            indexed_linked_lists::linked_list::node* it = row.begin;

            for (it = row.begin; it != nullptr; it = it->next) {
                if (it->value == r) {
                    cout << "YES" << endl;
                    break;
                }
            }

            if (it == nullptr) {
                cout << "NO" << endl;
            }
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
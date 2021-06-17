#include <iostream>
using namespace std;

// нужен для реализации bfs
struct queue {
    typedef size_t value_type;
    struct node {
        value_type value;
        node *next;

        node(value_type value) {
            this->value = value;
            next = nullptr;
        }
    };

    //! last может остаться не пустым, даже если очередь пуста
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

// для хранения списка связей
struct linked_list {
    // если нужен взвешенный, то можно заменить на pair<size_t, int>
    typedef size_t value_type;

    struct node {
        value_type value;
        node *next;

        node(value_type value) {
            this->value = value;
            next = nullptr;
        }
    };

    node *begin;
    node *end;

    linked_list() {
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


struct graph {
    size_t size;
    linked_list *adjacency_list;

    graph(size_t size) {
        this->size = size;
        adjacency_list = new linked_list[size];
    }

    // нужно для dfs и bfs
    bool *create_visited() {
        bool *visited = new bool[size];
        for (size_t i = 0; i < size; i++) {
            visited[i] = false;
        }
        return visited;
    }

    void dfs_process(size_t x, bool *visited) {
        visited[x] = true;

        // тут можно делать, что нужно с вершиной
        // cout << x << endl;

        for (auto i = adjacency_list[x].begin; i != nullptr; i = i->next) {
            if (!visited[i->value]) {
                dfs_process(i->value, visited);
            }
        }
    }

    // поиск в глубину
    void dfs(size_t begin) {
        dfs_process(begin, create_visited());
    }

    void bfs_process(size_t begin, bool *visited) {
        queue to_visit;
        visited[begin] = true;
        to_visit.push(begin);

        while (!to_visit.empty()) {
            size_t x = to_visit.pop();

            // тут можно делать, что нужно с вершиной
            // cout << x << endl;

            for (auto i = adjacency_list[x].begin; i != nullptr; i = i->next) {
                if (!visited[i->value]) {
                    visited[i->value] = true;
                    to_visit.push(i->value);
                }
            }
        }
    }

    // поиск в ширину
    void bfs(size_t begin) {
        bfs_process(begin, create_visited());
    }

    // добавить ребро
    void add_edge(size_t begin, size_t end) {
        adjacency_list[begin].push_back(end);
    }


    // для решение задач на компоненты связности
    void search_components() {
        bool *visited = create_visited();

        for (size_t i = 0; i < size; i++) {
            if (!visited[i]) {
                visited[i] = true;
                bfs_process(i, visited);

                // если нужно через dfs, то замени всё в if на:
                // dfs_process(i, visited);
            }
        }
    }

    ~graph() {
        delete [] adjacency_list;
    }
};

int main() {
    size_t n;
    cin >> n;

    // создаём граф с n вершинами
    graph g(n);

    size_t v;
    cin >> v;

    for (size_t i = 0; i < v; i++) {
        size_t a, b;
        cin >> a >> b;
        a--;
        b--;

        g.add_edge(a, b);
        // если ребро направленное второй вызов не нужен
        g.add_edge(b, a);
    }

    g.dfs(0);
    g.bfs(0);
    g.search_components();

    return 0;
}
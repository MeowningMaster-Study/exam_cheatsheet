#include <iostream>
using namespace std;

// нужен для реализации bfs
struct stack {
    typedef size_t value_type;
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

struct graph {
    // тип хранимых значений на рёбрах
    // если нужен взвешенный граф, то bool меняем на нужный тип, например на int
    typedef bool value_type;
    const static value_type default_value = false;

    size_t size;
    value_type **adjacency_matrix;

    graph(size_t size) {
        this->size = size;
        adjacency_matrix = new value_type*[size];

        for (size_t i = 0; i < size; i++) {
            value_type *row = new value_type[size];
            for (size_t j = 0; j < size; j++) {
                row[j] = default_value;
            }
            adjacency_matrix[i] = row;
        }
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

        value_type *row = adjacency_matrix[x];
        for (size_t i = 0; i < size; i++) {
            if (row[i] != default_value && !visited[i]) {
                dfs_process(i, visited);
            }
        }
    }

    // поиск в глубину
    void dfs(size_t begin) {
        dfs_process(begin, create_visited());
    }

    void bfs_process(size_t begin, bool *visited) {
        stack to_visit;
        visited[begin] = true;
        to_visit.push(begin);

        while (!to_visit.empty()) {
            size_t x = to_visit.pop();

            // тут можно делать, что нужно с вершиной
            // cout << x << endl;

            value_type *row = adjacency_matrix[x];
            for (size_t i = 0; i < size; i++) {
                if (row[i] != default_value && !visited[i]) {
                    visited[i] = true;
                    to_visit.push(i);
                }
            }
        }
    }

    // поиск в ширину
    void bfs(size_t begin) {
        bfs_process(begin, create_visited());
    }

    // добавить/изменить ребро
    void modify_edge(size_t begin, size_t end, value_type value) {
        adjacency_matrix[begin][end] = value;
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
        for (size_t i = 0; i < size; i++) {
            delete [] adjacency_matrix[i];
        }
        delete [] adjacency_matrix;
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

        g.modify_edge(a, b, true);
        // если ребро направленное второй вызов не нужен
        g.modify_edge(b, a, true);
    }

    g.dfs(0);
    g.bfs(0);
    g.search_components();

    return 0;
}
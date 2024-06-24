#include <iostream>
using namespace std;

// потрібен для реалізації bfs
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

struct graph {
    // тип значень, що зберігаються в ребрах
    // якщо потрібен зважений граф, то bool змінюємо на потрібний тип, наприклад на int
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

    // треба для dfs та bfs
    bool *create_visited() {
        bool *visited = new bool[size];
        for (size_t i = 0; i < size; i++) {
            visited[i] = false;
        }
        return visited;
    }

    void dfs_process(size_t x, bool *visited) {
        visited[x] = true;

        // тут можна робити щось з вершиною
        // cout << x << endl;

        value_type *row = adjacency_matrix[x];
        for (size_t i = 0; i < size; i++) {
            if (row[i] != default_value && !visited[i]) {
                dfs_process(i, visited);
            }
        }
    }

    // пошук у глибину
    void dfs(size_t begin) {
        dfs_process(begin, create_visited());
    }

    void bfs_process(size_t begin, bool *visited) {
        queue to_visit;
        visited[begin] = true;
        to_visit.push(begin);

        while (!to_visit.empty()) {
            size_t x = to_visit.pop();

            // тут можна робити щось з вершиною
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

    // пошук у ширину
    void bfs(size_t begin) {
        bfs_process(begin, create_visited());
    }

    // додати/змінити ребро
    void modify_edge(size_t begin, size_t end, value_type value) {
        adjacency_matrix[begin][end] = value;
    }


    // для вирішення задач на компоненти зв'язності
    void search_components() {
        bool *visited = create_visited();

        for (size_t i = 0; i < size; i++) {
            if (!visited[i]) {
                visited[i] = true;
                bfs_process(i, visited);

                // якщо потрібно через dfs, то заміни все в if на:
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

    // створюємо граф з n вершинами
    graph g(n);

    size_t v;
    cin >> v;

    for (size_t i = 0; i < v; i++) {
        size_t a, b;
        cin >> a >> b;
        a--;
        b--;

        g.modify_edge(a, b, true);
        // якщо ребро направлене другий виклик не потрібен
        g.modify_edge(b, a, true);
    }

    g.dfs(0);
    g.bfs(0);
    g.search_components();

    return 0;
}
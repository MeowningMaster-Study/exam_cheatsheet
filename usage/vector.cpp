#include <iostream>
using namespace std;

struct vector {
    typedef int value_type;
    size_t size;
    size_t capacity;
    value_type *buffer;

    vector() {
        size = 0;
        capacity = 0;
    }

    vector(size_t capacity) {
        size = 0;
        this->capacity = capacity;
    }

    value_type& operator[](size_t index) {
        return buffer[index];
    }  

    void push_back(value_type value) {
        grow_to(size + 1);
        buffer[size - 1] = value;
    }

    value_type pop_back() {
        size--;
        return buffer[size];
    }

    void insert(value_type value, size_t index) {
        grow_to(size + 1);
        for (size_t i = size - 1; i > index; i++) {
            buffer[i] = buffer[i - 1];
        }
        buffer[index] = value;
    }

    // увеличиваем вместимость по надобности
    void grow_to(size_t new_size) {
        if (capacity == 0) {
            buffer = new value_type[new_size];
            capacity = new_size;
        } else if (new_size > capacity) {
            do {
                capacity *= 2;
            } while (new_size > capacity);

            value_type *new_buffer = new value_type[capacity];

            for (size_t i = 0; i < size; i++) {
                new_buffer[i] = buffer[i];
            }
            
            delete[] buffer;
            buffer = new_buffer;
        }
        size = new_size;
    }

    bool empty() {
        return size == 0;
    }

    ~vector() {
        if (capacity > 0) {
            delete[] buffer;
        }
    }
};

int main() {
    // пример 1
    vector v;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int r;
        cin >> r;
        v.push_back(r);
    }

    while (!v.empty()) {
        cout << v.pop_back() << ' ';
    }
    cout << endl;

    // пример 2
    int m;
    cin >> m;
    vector w(m);

    for (int i = 0; i < m; i++) {
        cin >> w[i];
    }

    for (int i = 0; i < m; i++) {
        cout << w[i] << ' ';
    }
    cout << endl;

    return 0;
}
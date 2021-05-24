# Темплейты для экзамена
В каждом файле есть примеры использования.
## Базовое
- [Стек](usage/stack.cpp)
- [Очередь](usage/queue.cpp)
- [Вектор](usage/vector.cpp)
## Связные списки
- [Односвязный](usage/linked_list.cpp)
- [Двусвязный](usage/double_linked_list.cpp)
- [Циклический](usage/cycled_linked_list.cpp)
## Графы
На основе:
- [матрицы смежности](usage/adjacency_matrix_graph.cpp)
- [списка(структуры) смежности](usage/adjacency_list_graph.cpp)

Ейлер:
- [проверка на ейлеровость (критерий)](https://neerc.ifmo.ru/wiki/index.php?title=%D0%AD%D0%B9%D0%BB%D0%B5%D1%80%D0%BE%D0%B2%D0%BE%D1%81%D1%82%D1%8C_%D0%B3%D1%80%D0%B0%D1%84%D0%BE%D0%B2)
- поиск пути/цикла:
    - [emaxx](https://e-maxx.ru/algo/euler_path)
    - [ifmo](https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%BF%D0%BE%D1%81%D1%82%D1%80%D0%BE%D0%B5%D0%BD%D0%B8%D1%8F_%D0%AD%D0%B9%D0%BB%D0%B5%D1%80%D0%BE%D0%B2%D0%B0_%D1%86%D0%B8%D0%BA%D0%BB%D0%B0)
## Деревья
На указателях:
- [Обычное](usage/unordered_tree.cpp)
- [Бинарного поиска](usage/binary_search_tree.cpp)

На буффере: сделай сам на основе [вектора](usage/vector.cpp)
## Парсинг мат. выражений
- [Теория](https://www.tutorialspoint.com/data_structures_algorithms/expression_parsing.htm)
- [Инфиксная в постфиксную](https://www.tutorialspoint.com/data_structures_algorithms/expression_parsing_using_statck.htm), можно легко переделать в префиксную (польскую)

## Нереализовано
- АВЛ-дерево
- остовное дерево
- сжатое хранение
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


struct queue { // описание очереди
    int item; // значение элемента
    queue* next; // указатель на следующий эл-т
};


void push(queue*& head, queue*& tail, int val) { // добавление элемента в очередь (в конец)
    queue* r = new queue; // новый элемент
    r->next = NULL;
    r->item = val;
    if (!head && !tail) { // если очередь была пустой, то голова совпадает с хвостом
        head = tail = r;
        return;
    }
    tail->next = r; 
    tail = r; // переопределение головы
}


int pop(queue*& head, queue*& tail) { // удаление элемента из очереди (из начала)
    int el = head->item; // значение эл-та
    queue* r = head;
    head = head->next;
    if (!head) tail = NULL; // если очередь пуста, меняем указатель хвоста
    delete r;
    return el; // взвращаем значение
}


int N = 64; // число клеток на шахматной доске
vector<vector<int>> g (N); // список смежности графа
vector<int> used (N); // вектор посещенных вершин
vector<int> p (N); // вектор предков
int n, m; // кол-во вершин и ребер в графе


void bfs(int start) { // обход в ширину
    queue* head = NULL; // инициализация очереди
    queue* tail = NULL;
    used[start] = 1; // отмечаем стартовую вершину посещенной
    push(head, tail, start); // и добавляем ее в очередь
    p[start] = -1; // у старотовой вершины нет предка
    while (head && tail) { // пока очередь не пуста
        int v = pop(head, tail); // извлекаем вершину из очереди
        for (int u : g[v]) { // проходимся по смежным с ней вершинам
            if (used[u]) continue;
            // если вершина еще не была посещена
            used[u] = 1; // помечаем посещенной
            push(head, tail, u); // добавляем в очередь
            p[u] = v; // указываем предка 
        }
    }
} 


void graph() { // построение графа, в котором ребро u - v означает, что шахматный конь может за один ход попасть из клетки u в v
    for (int i = 0; i < N; ++i) {
        if (i % 8 != 0 && i / 8 > 1) g[i].push_back(i - 1 - 2 * 8);
        if (i % 8 != 7 && i / 8 > 1) g[i].push_back(i + 1 - 2 * 8);
        if (i % 8 > 1 && i / 8 != 0) g[i].push_back(i - 2 - 8);
        if (i % 8 < 6 && i / 8 != 0) g[i].push_back(i + 2 - 8);
        if (i % 8 > 1 && i / 8 != 7) g[i].push_back(i - 2 + 8);
        if (i % 8 < 6 && i / 8 != 7) g[i].push_back(i + 2 + 8);
        if (i % 8 != 0 && i / 8 < 6) g[i].push_back(i - 1 + 2 * 8);
        if (i % 8 != 7 && i / 8 < 6) g[i].push_back(i + 1 + 2 * 8);
    }
}


int A1_to_int(string s) { // функция, переводящая шахматное обозначение клетки в число
    return (8 - (s[1] - '0')) * 8 + (s[0] - 'A');
}


string int_to_A1(int x) { // функция, переводящая число в шахматное обозначение клетки
    return string(1, 'A' + x % 8) + to_string(8 - x / 8);
}


void print_path(int end) { // восстановление и вывод пути из стартовой клетки в конечную
    cout << "The shortest knight path between the cells: ";
    vector<int> path; 
    for (int v = end; v != -1; v = p[v]) { // проходимся по вектору предков, начиная из конечной клетки,
        path.push_back(v);                 // пока не дойдем до начальной (с предком равным -1)
    }
    reverse(path.begin(), path.end()); // путь записан в обратном порядке
    for (int v : path) cout << int_to_A1(v) << ' ';
}


int main() {
    graph(); // простроение графа
    cout << "Enter the starting cell in the form `A1`: ";
    string start, end; // начальная и конечная клетки
    cin >> start;
    bfs(A1_to_int(start)); // вызов обхода в ширину
    cout << "Enter the final cell in the form `A1`: ";
    cin >> end;
    print_path(A1_to_int(end)); // вывод пути
}
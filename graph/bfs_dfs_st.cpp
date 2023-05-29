#include <iostream>
#include <vector>

using namespace std;


vector<vector<int>> g; // список смежности графа
vector<int> used; // вектор посещенных вершин
int n, m; // кол-во вершин и ребер в графе


// dfs

struct stack { // описание стека
    int item; // значение элемента
    stack* next; // ссылка на следующий
};


void push_s(stack*& head, int elem) { // добавление элемента в стек (в начало)
    stack* r = new stack; // создание нового элемента
    r->item = elem; // значение из входных данных
    r->next = head; // указатель на текущую голову
    head = r; // r становится головой
}


int pop_s(stack*& head) { // удаление элемента из стека (из начала)
    int el = head->item; // значение текущей головы
    stack* r = head; // указатель на голову
    head = head->next; // перенос указателя головы на следующий элемент 
    delete r; // удаляем первый элемент
    return el; // возвращаем значение 
}


void dfs(int start) { // обход в глубину
    stack* head = NULL; // инициализация стека
    used[start] = 1; // помечаем стартовую вершину посещенной
    push_s(head, start); // добавляем ее в стек
    cout << start << ' ';
    while (head) { // пока стек непустой
        bool fl = false; // флаг, показывающий, есть ли у вершины хотя бы одна смежная непосещенная вершина
        int v = head->item; // значение головы
        int u;
        for (int x : g[v]) { // проходимся по смежным вершинам
            if (!used[x]) { // нашли не посещенную ранее вершину
                fl = true;
                u = x;
                break;
            }
        }
        if (fl) { // если флаг правдив, добавляем найденную вершину в стек
            used[u] = 1;
            push_s(head, u);
            cout << u << ' ';
        }
        else pop_s(head); // иначе извлекаем вершину стека
    }
    for (int i = 0; i < n; ++i) { // после окончания работы алгоритма, вызываем его для всех не посещенных вершин 
        if (!used[i]) dfs(i);
    }
} 

// bfs

struct queue { // описание очереди
    int item; // значение элемента
    queue* next; // указатель на следующий эл-т
};


void push_q(queue*& head, queue*& tail, int val) { // добавление элемента в очередь (в конец)
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


int pop_q(queue*& head, queue*& tail) { // удаление элемента из очереди (из начала)
    int el = head->item; // значение эл-та
    queue* r = head;
    head = head->next;
    if (!head) tail = NULL; // если очередь пуста, меняем указатель хвоста
    delete r;
    return el; // взвращаем значение
}


void bfs(int start) { // обход в ширину
    queue* head = NULL; // инициализация очереди
    queue* tail = NULL;
    used[start] = 1; // отмечаем стартовую вершину посещенной
    push_q(head, tail, start); // и добавляем ее в очередь
    cout << start << ' ';
    while (head && tail) { // пока очередь не пуста
        int v = pop_q(head, tail); // извлекаем вершину из очереди
        for (int u : g[v]) { // проходимся по смежным с ней вершинам
            if (used[u]) continue;
            // если вершина еще не была посещена
            used[u] = 1; // помечаем посещенной
            push_q(head, tail, u); // добавляем в очередь
            cout << u << ' ';
        }
    }
    for (int i = 0; i < n; ++i) { // после окончания работы алгоритма, вызываем его для всех не посещенных вершин
        if (!used[i]) bfs(i);
    }
} 


int main() {
    cout << "Enter the number of vertices (n) and edges in the graph (m): ";
    cin >> n >> m;
    g.resize(n); // изменяем размерность вектора g на n
    used.resize(n); // изменяем размерность вектора used на n
    int v, u;
    cout << "Enter " << m << " enges:\n";
    for (int i = 0; i < m; ++i) { // заполнение списка смежности
        cin >> v >> u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    cout << "Enter the starting vertex: ";
    int start = 0;
    cin >> start;
    cout << "Breadth-first search result: ";
    bfs(start); // вызов обхода в ширину

    used.assign(n, 0); // очищение вектора used
    cout << "\nDepth-first search result: ";
    dfs(start); // вызов обхода в глубину
}
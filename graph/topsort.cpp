// Реализовать топологическую сортировку

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, m; // кол-во вершин и ребер в графе
vector<vector<int>> g; // список смежности графа
vector<int> used; // массив посещенных вершин
vector<int> p; // массив предков
vector<int> order; // топсорт
bool cycle = false; // наличие цикла в графе


void dfs_cycle(int v, int pr = -1) { // поиск в глубину, находит цикл в графе
    used[v] = 1;
    p[v] = pr; // предок v
    for (int u : g[v]) {
        if (u == p[v]) continue; // если текущая вершина наш предок - пропускаем итерацию
        if (!used[u]) // если мы еще не были в вершине, то продолжаем обход
            dfs_cycle(u, v);
        else cycle = true; // иначе мы нашли цикл
    }
    used[v] = 0;
}


void dfs(int v) { // обход в глубину
    used[v] = 1;
    for (int u : g[v]) {
        if (!used[u])
            dfs(u);
    }
    order.push_back(v); // вершины записаны в обратном порядке
}


void graph() {
	cout << "n (number of vertices) = ";
	cin >> n;
	cout << "m (number of edges) = ";
	cin >> m;
	g.resize(n); // выделение памяти в векторе
    used.resize(n);
    p.resize(n);
	int v, u;
    cout << "Enter " << m << " edges:\n";
	for (int i = 0; i < m; ++i) { // добавление ребер в список смежности
		cin >> v >> u; // нумерация вершин графа начинается с 0
		if (v >= n || u >= n || v < 0 || u < 0) continue;
		g[v].push_back(u);
	}
	for (int i = 0; i < n; ++i) {
		sort(g[i].begin(), g[i].end()); // сортируем списки смежных вершин для каждой вершины
		g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end()); // удаляем дубликаты
	}
}


int main() {
	graph(); // инициализация графа
    for (int i = 0; i < n; ++i) { // проверка на наличие цикла в графе
        if (!used[i])
            dfs_cycle(i);
    }

    if (cycle) 
        cout << "There is a cycle in the graph, topological sorting is impossible :(";
    else {
        for (int i = 0; i < n; ++i) { // если в графе нет циклов, запускаем топсорт
        if (!used[i])
            dfs(i);
        }
        cout << "Topological sort: ";
        for (int i = n - 1; i >= 0; --i) // выводим топологическую сортировку 
            cout << order[i] << ' ';
    }
}
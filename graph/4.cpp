// Дан неориентированный граф. Определить содержит ли он циклы. Если да, то вывести их.

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int n, m;
vector<vector<int>> g;
vector<int> used; // вектор посещенных вершин
vector<int> p; // вектор предков
vector<vector<int>> cycles; // все циклы
set<vector<int>> sort_cycles; // отсортированные циклы


void add_cycles(int start, int end_) { // добавляем новый цикл
    vector<int> temp;
    // восстанавливаем цикл с помощью массива предков
    for (int cur = end_; cur != start; cur = p[cur]) {
        temp.push_back(cur);
    }
    temp.push_back(start);
    reverse(temp.begin(), temp.end()); // переворачиваем
    cycles.push_back(temp); 
    sort(temp.begin(), temp.end()); // сортируем вершины цикла
    sort_cycles.insert(temp); // добавляем в сет 
}


void dfs(int v, int pr = -1) { // обход в глубину
	used[v] = 1;
	p[v] = pr; // предок
	for (int u : g[v]) {
		if (p[v] == u) continue; // если текущая вершина - предок, пропускаем итерацию
		if (!used[u]) dfs(u, v);  // если не были в вершине, продолжаем обход
		else add_cycles(u, v); // иначе мы нашли цикл
	}
	used[v] = 0;
}


void graph() {
	cout << "n = ";
	cin >> n;
	cout << "m = ";
	cin >> m;
	g.resize(n); // выделение памяти в векторах
    used.resize(n);
    p.resize(n);
	int v, u;
	for (int i = 0; i < m; ++i) { // добавление ребер в список смежности
		cin >> v >> u;
        if (v > n || u > n) continue;
		v--; u--;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	for (int i = 0; i < n; ++i) {
		sort(g[i].begin(), g[i].end()); // сортируем списки смежных вершин для каждой вершины
		g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end()); // удаляем дубликаты
	}
}


void print_cycles(vector<int> c) { // выводим все циклы
    for (auto v : c) cout << v + 1 << ' ';
	cout << '\n';
}


int main() {
	graph();
	for (int i = 0; i < n; ++i) { // запускаем обход в глубину для всех непосещенных вершин
		if (!used[i]) {
			dfs(i);
		}
	}
    if (sort_cycles.empty()) cout << "There are no cycles :(";
    else {
        cout << "All cycles in the graph:\n";
        for (auto c : cycles) {  // выводим циклы и отсеиваем совпадающие
        vector<int> cycle = c;
        sort(c.begin(), c.end());
        if (sort_cycles.count(c)) {
            sort_cycles.erase(c);
            print_cycles(cycle);
        }
	}
    }
}
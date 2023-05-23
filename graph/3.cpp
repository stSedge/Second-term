// Дан неориентированный граф. Вывести количество вершин, смежных с данной.

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, m; // кол-во вершин и ребер в графе
vector<vector<int>> g; // списк смежности графа


void graph() {
	cout << "n = ";
	cin >> n;
	cout << "m = ";
	cin >> m;
	g.resize(n); // выделение памяти в векторе
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

void print() {
	cout << "Graph adjacency list\n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ": ";
		for (auto u : g[i]) cout << u + 1 << ' ';
		cout << '\n';
	}
}


void vertex() { // степень вершины, петля учитывается дважды
	cout << "\nVertex degrees:\n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ":  " << g[i].size() + (find(g[i].begin(), g[i].end(), i) != g[i].end()) << '\n';
	}
}


int main() {
	graph();
	print();
	vertex();
}
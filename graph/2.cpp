// Дан ориентированный граф. Вставить в граф ребро, соединяющее вершины A и B

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
	}
	for (int i = 0; i < n; ++i) {
		sort(g[i].begin(), g[i].end()); // сортируем списки смежных вершин для каждой вершины
		g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end()); // удаляем дубликаты
	}
}

void input(int a, int b) { // ф-я вставки нового ребра в орграф
	for (auto v : g[a]) {
		if (v == b) { // проверка на наличие ребра в графе
			cout << "Such an edge already exists\n";
			return;
		}
	}
	g[a].push_back(b); // вставка
	sort(g[a].begin(), g[a].end()); 
}

void print() { // вывод списка смежности
	cout << "Graph adjacency list\n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ": ";
		for (auto u : g[i]) cout << u + 1 << ' ';
		cout << '\n';
	}
}


int main() {
	graph();
	print();
	int a, b; // вершины нового ребра
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	if (a > n || b > n) {
		cout << "Incorrect input";
		return;
	}
	a--; b--;
	input(a, b);
	print();
}
// Дан ориентированный граф. Найти все сильно связные компоненты графа.

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

int n, m;
vector<vector<int>> g;
vector<vector<int>> gT; // транспонированный орграф
vector<int> used; // вектор посещенных вершин
vector<int> p; // вектор предков
vector<int> order; // вершины в порядке выхода из обычного графа
vector<int> path; // сильная компонента свзяности, обход по транспонированному графу


void beauty(vector<vector<int>>& gr) {
    for (int i = 0; i < n; ++i) {
		sort(gr[i].begin(), gr[i].end()); // сортируем списки смежных вершин для каждой вершины
		gr[i].erase(unique(gr[i].begin(), gr[i].end()), gr[i].end()); // удаляем дубликаты
	}
}


void graph() {
	cout << "n = ";
	cin >> n;
	cout << "m = ";
	cin >> m;
	g.resize(n); // выделение памяти в векторах
    gT.resize(n);
    used.resize(n);
    p.resize(n);
	int v, u;
	for (int i = 0; i < m; ++i) { // добавление ребер в списки смежности оргафа и транспонированного оргафа
		cin >> v >> u;
        if (v >= n || u >= n) continue;
		//v--; u--;
		g[v].push_back(u);
        gT[u].push_back(v);
	}
	beauty(g);
    beauty(gT);
}


void dfs(int v) { // обход в глубину
    used[v] = 1;
    for (auto u : g[v]) {
        if (!used[u]) dfs(u);
    }
    order.push_back(v); // вышли из вершины и добавили ее в вектор 
}


void bfs(int s) { // обход в ширину по транспонированному графу
    used[s] = 1;
    path.push_back(s); // добавили в вектор
    queue<int> q; // очередь
    q.push(s); // положили в очередь стартовую вершину
    while (!q.empty()) { // пока очередь не пуста
        int v = q.front(); // извлекаем голову
        q.pop();
        for (auto u : gT[v]) { // для всех смежных с головой
            if (used[u]) continue;
            used[u] = 1;
            q.push(u); // кладем в очередь
            path.push_back(u); // записываем в путь
        }
    }
}

/*void dfs2(int v) {
    used[v] = 1;
    path.push_back(v);
    for (auto u : gT[v]) {
        if (!used[u]) dfs2(u);
    }
}*/

int main() {
	graph();
	for (int i = 0; i < n; ++i) { // запускаем обход в глубину для всех непосещенных вершин
		if (!used[i]) {
			dfs(i);
		}
	}
    used.clear(); // очищаем used
    used.resize(n);
    reverse(order.begin(), order.end()); // переворачиваем order
    cout << "Strongly connected component:\n";
    for (int v : order) { 
        if (!used[v]) {
            bfs(v); // запускаем обход по трансп. графу
            for (auto u : path) cout << u << ' '; // выводим компоненту сильной связности
            cout << "\n";
            path.clear();
        }
    }
}
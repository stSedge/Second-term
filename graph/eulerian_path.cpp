// Дан неориентированный граф. Вывести Эйлеров путь или Эйлеров цикл, если он существует.

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

int n, m; // кол-во вершин и ребер в графе
vector<vector<int>> g; // список смежности графа


void beauty(vector<vector<int>>& gr) {
    for (int i = 0; i < n; ++i) {
		sort(gr[i].begin(), gr[i].end()); // сортируем списки смежных вершин для каждой вершины
		gr[i].erase(unique(gr[i].begin(), gr[i].end()), gr[i].end()); // удаляем дубликаты
	}
}


void graph() {
	cout << "n (number of vertices) = ";
	cin >> n;
	cout << "m (number of edges) = ";
	cin >> m;
	g.resize(n); // выделение памяти в векторах
	int v, u;
	cout << "Enter " << m << " edges:\n";
	for (int i = 0; i < m; ++i) { // добавление ребер в списки смежности
		cin >> v >> u;
        if (v >= n || u >= n || v < 0 || u < 0) continue;
		g[v].push_back(u);
        g[u].push_back(v); // граф неориентированный 
	}
	beauty(g);
}


int main() {
	graph(); // инициализация графа
	int v1 = -1, v2 = -1; // вершины с нечетными степенями
	for (int i = 0; i < n; ++i) {
		if (g[i].size() % 2) { // если у вершины нечетная степень
			if (v1 == -1) v1 = i; // первая такая вершина
			else if (v2 == -1) v2 = i; // вторая
			else { // если их больше двух, то эйлерова пути нет
				cout << "There is no Eulerian path in the graph";
				return 0;
			}
		}
	}
	stack<int> s; // стек обхода
	if (v1 != -1) { // если есть вершина с нечетной степенью
		if (v2 == -1) { // если вершина с нечетной степенью только одна
			cout << "There is no Eulerian path in the graph"; // то эйлерова пути тоже нет
			return 0;
		}
		// добавляем фиктивное ребро
		g[v1].push_back(v2);
		g[v2].push_back(v1);
		beauty(g);
		s.push(v1); // кладем вершину в стек
	}
	else s.push(0);

	vector<int> res; // результирующий вектор
	while (!s.empty()) { // пока стек не пуст
		int v = s.top(); // смотрим на голову
		if (!g[v].empty()) { // если есть смежные вершины
			int u = *g[v].begin(); // берем первую
			s.push(u); // кладем ее в стек
			g[v].erase(g[v].begin()); // удаляем ребро u-v
			g[u].erase(find(g[u].begin(), g[u].end(), v));
 		}
		else {
			res.push_back(v); // иначе записываем вершину в результат 
			s.pop(); // и удаляем из стека
		}
	}

	if (v1 != -1) { // удаляем фиктивное ребро, если оно было
		for (int i = 0; i < res.size() - 1; ++i) {
			if (res[i] == v1 && res[i + 1] == v2 || res[i] == v1 && res[i + 1] == v2) {
				vector<int> temp;
				for (int j = i + 1; j < res.size(); ++j) temp.push_back(res[j]);
				for (int j = 1; j <= i; ++j) temp.push_back(res[j]);
				res = temp; // перезаписываем результат без фиктивного ребра
				break;
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		if (!g[i].empty()) { // если в графе остались ребра, то он несвязный, эйлерова пути нет
			cout << "There is no Eulerian path in the graph";
			return 0;
		}
	}

	if (v1 != -1) cout << "Eulerian path: "; // есть путь
	else cout << "Eulerian cycle: "; // есть цикл
	for (auto v : res) cout << v << ' '; // результат
}
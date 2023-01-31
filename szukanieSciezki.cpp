#include <iostream>
#include <stack>
using namespace std;

struct weightedEdge {
	int s;
	int t;
	double w;        //waga krawêdzi
	weightedEdge(int s, int t, double w);
};

class WeightedGraph {
private:
	double** adjWeightMatrix;
	int n;                //liczba wêz³ów
	bool directed;
public:
	WeightedGraph(int n, int m, weightedEdge edges[], bool directed);    //tworzy graf w oparciu o pdan¹ listê krawêdzi z wagami
	void dijkstra(int s);
	void warshallFloyd();
	void shortestPath(int s, int t, int* parent);

	int find(bool* visited, double* d);
	//friend ostream& operator<<(ostream& out, WeightedGraph& g);
	~WeightedGraph();
};

weightedEdge::weightedEdge(int s, int t, double w) {
	this->s = s;
	this->t = t;
	this->w = w;
}

WeightedGraph::WeightedGraph(int n, int m, weightedEdge edges[], bool directed) {    //tworzy graf w oparciu o pdan¹ listê krawêdzi z wagami
	this->directed = directed;
	this->n = n;
	adjWeightMatrix = new double* [n];

	for (int i = 0; i < n; i++)
		adjWeightMatrix[i] = new double[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			adjWeightMatrix[i][j] = -1;
	}

	for (int i = 0; i < n; i++) {
		adjWeightMatrix[edges[i].s][edges[i].t] = edges[i].w;
		if (this->directed == false)
			adjWeightMatrix[edges[i].t][edges[i].s] = edges[i].w;
	}
}

int WeightedGraph::find(bool* visited, double* d) { //zwraca wêze³ w którym minimalna nieodwiedzona wartoœæ
	double min = INT_MAX;
	int index = -1; //stwierdza, który indeks mamy zwróciæ

	for (int i = 0; i < n; i++) {
		if (d[i] < min && visited[i] == false) {
			min = d[i];
			index = i;
		}
	}
	return index;
}

void WeightedGraph::dijkstra(int s) {
	double* distance = new double[n];// {INT_MAX};
	int* parent = new int[n];
	bool* visited = new bool[n];
	int u;

	for (int i = 0; i < n; i++) {
		distance[i] = INT_MAX;
		visited[i] = false;
		parent[i] = -1;
	}
	distance[s] = 0;

	for (int i = 0; i < n; i++) {
		u = find(visited, distance);
		visited[u] = true;

		for (int j = 0; j < n; j++) { //przeszukujemy wszystkich s¹siadów
			if (adjWeightMatrix[u][j] >= 0) {
				if (distance[j] > distance[u] + adjWeightMatrix[u][j]) {
					distance[j] = distance[u] + adjWeightMatrix[u][j];
					parent[j] = u;
				}
			}
		}
	}
	shortestPath(0, 5, parent);

	delete distance;
	delete parent;
	delete visited;
}

void WeightedGraph::shortestPath(int s, int t, int* parent) {
	std::stack<int>S;

	while (t != s) {
		S.push(t);
		t = parent[t];
	}
	S.push(t);

	while (!S.empty()) {
		cout << S.top() << " ";
		S.pop();
	}
}

void WeightedGraph::warshallFloyd() {
	double** d = new double* [n];

	for (int i = 0; i < n; i++) {
		d[i] = new double[n];
		for (int j = 0; j < n; j++) {
			if (i == j)
				d[i][j] = 0;
			else if (adjWeightMatrix[i][j] == -1) //jeœli bezpoœrednia droga to nieskoñczonoœæ
				d[i][j] = INT_MAX;
			else
				d[i][j] = adjWeightMatrix[i][j];
		}
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (d[i][j] > d[i][k] + d[k][j])
					d[i][j] = d[i][k] + d[k][j];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j != i) {
				if (d[i][j] < INT_MAX)
					std::cout << "najkrotsza sciezka z " << i << " do " << j << ": " << d[i][j] << std::endl;
				else
					std::cout << "sciezka z " << i << " do " << j << " nie istnieje " << std::endl;
			}
		}
		delete[] d[i];
	}
	delete[]d;
}

WeightedGraph::~WeightedGraph() {
	for (int i = 0; i < n; i++)
		delete[] adjWeightMatrix[i];
}

int main() {
	int n = 6, m = 15;
	weightedEdge directedWeightedGraph[] = { {0,1,1},{0,3,2},{1,2,2},{2,5,3},
		{3,1,4},{3,4,3},{4,1,1},{4,3,3},{5,4,1} };

	WeightedGraph g(n, m, directedWeightedGraph, true);
	g.dijkstra(0);
	cout << endl << endl;
	g.warshallFloyd();
}

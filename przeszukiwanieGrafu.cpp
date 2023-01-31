#include <iostream>
#include <queue>
using namespace std;

 //Szablon rozwi�zania:
struct edge {
	int s;
	int t;
	edge(int s, int t);
};

class Graph {
private:
	int** adjMatrix;
	int n;                              //liczba w�z��w
	bool directed;              //true - graf skierowany, false - graf nieskierowany
	void dfs(int s, bool* visited);    //wykonuje przeszukiwanie i wy�wietla w�z�y w porz�dku odwiedzenia
public:
	Graph(int n, int m, edge edges[], bool directed);    //tworzy graf w oparciu o pdan� list� kraw�dzi
	void showMatrix();
	void bfs(int s);                //wykonuje przeszukiwanie i wy�wietla w�z�y w porz�dku odwiedzenia
	void dfs(int s);                //metoda pomocnicza dla dfs - tworzy tabel� visited i wywo�uj� metod� prywatn� dfs
	int connected();
	//friend ostream& operator<<(ostream& out, Graph& g);  //wy�wietla graf
	//void silnieSpojna(int s);
	~Graph();
};

edge::edge(int s, int t) {
	this->s = s;
	this->t = t;
}

Graph::Graph(int n, int m, edge edges[], bool directed) {
	this->directed = directed;
	this->n = n;
	this->adjMatrix = new int* [n];

	for (int i = 0; i < n; i++)
		this->adjMatrix[i] = new int[n] {0};

	for (int i = 0; i < n; i++) {
		adjMatrix[edges[i].s][edges[i].t] = 1;
		if (this->directed == false)
			adjMatrix[edges[i].t][edges[i].s] = 1; //jak nieskierowany to obojetne skad wychodzi
	}
}

Graph::~Graph() {
	for (int i = 0; i < n; i++)
		delete[] adjMatrix[i];

	delete[] adjMatrix;
}

void Graph::showMatrix() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << adjMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

void Graph::bfs(int s) {
	int u;
	bool* visited = new bool[n] {false};
	int* parents = new int[n] {-1};
	//int* distance = new int[n] {0};
	//bool cykl = false; 
	//int it;

	std::queue<int>Q;

	visited[s] = true;
	Q.push(s);
	cout << s << " ";

	while (!Q.empty()) {
		u = Q.front();
		Q.pop();

		for (int i = 0; i < n; i++) { //sprawdzamy wszystkich s�siad�w
			if (adjMatrix[u][i] == 1 && visited[i] == false) { //je�li nieodwiedzony
				Q.push(i);
				visited[i] = true;
				parents[i] = u;
				cout << i << " ";
				//distance[i]=distance[u]+1; //najkr�tsze �cie�ki
			}
			//else cykl = true; //gdy spotkamy wcze�niejszy - istnieje cykl
		}
	}
	//for (int i = 0; i < n; i++)
		//cout << i<<":"<<distance[i]<<" ";

	/*cout << endl;
	it = 5;//w tym przypadku na sztywno, normalnie trzeba zmieni� do nowej funkcji
	while (it != s) {
		cout << it <<" ";
		it = parents[it];
	}
	cout << s;*/

	//cout << endl << cykl;

	delete[] visited;
	delete[] parents;

	//modyfikacja sprawdzaj�ca czy sp�jny (funkcja musi by� typu bool)
	/*for (int i = 0; i < n; i++) {
		if (visited[i] == false) {
			return false;
		}
	}

	return true;*/
}

void Graph::dfs(int s, bool* visited) { //wykonuje przeszukiwanie i wy�wietla w�z�y w porz�dku odwiedzenia
	visited[s] = true; //zmieniamy s na odwiedzony

	std::cout << s << " "; //wypisujemy posortowane topologicznie

	for (int i = 0; i < n; i++) {
		if (adjMatrix[s][i] == 1 && visited[i] == false)
			dfs(i, visited);
	}
}

void Graph::dfs(int s) {     //metoda pomocnicza dla dfs - tworzy tabel� visited i wywo�uj� metod� prywatn� dfs
	bool* visited = new bool[n] {false};
	dfs(s, visited);
}

/*void Graph::silnieSpojna(int s) {
	int** transposition = new int* [n];
	dfs(s);

	for (int i = 0; i < n; i++)
		transposition[i] = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			adjMatrix[j][i] = transposition[i][j];

	cout << endl;
	for (int i = 0; i < n; i++) {
		dfs(i);
		cout << endl;
	}
}*/

int Graph::connected() { //liczba sp�jnych sk�adowych
	bool* visited = new bool[n] {false};
	int parts = 0;

	for (int i = 0; i < n; i++) {
		if (visited[i] == false) {
			dfs(i, visited);
			parts++;
			cout << endl;
		}
	}
	return parts;
}

int main()
{
	int n = 6, m = 9;
	edge directedGraph[] = { {0,1},{0,3},{1,2},{2,5},{3,1},{3,4}, {4,1},{4,3},{5,4} };  //przyk�adowy graf
	Graph g(n, m, directedGraph, true);
	g.showMatrix();
	cout << endl;
	g.bfs(0);
	cout << endl;
	g.dfs(0);
	cout << endl;
	//g.silnieSpojna(0);
	//cout<<endl<<g.connected();


}

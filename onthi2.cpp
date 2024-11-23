#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <queue>

#define cls system("cls")
#define pause system("pause")
#define MAX 100

using namespace std;

struct Node
{
	string info;
	Node* link;
};

Node* first[MAX];
string vertices[MAX];
int dinh;

void Init_list() {
	for (int i = 0; i < dinh; i++)
		first[i] = NULL;
}

void Insert_first(Node*& node, string value)
{
	Node* p = new Node;
	p->info = value;
	p->link = node;
	node = p;
}

void input_list() {
	cout << "Nhap so dinh cua do thi: ";
	cin >> dinh;
	cin.ignore();
	for (int i = 0; i < dinh; i++)
	{
		cout << "Nhap ten dinh thu " << i + 1 << ": ";
		getline(cin, vertices[i]);
	}
	for (int i = 0; i < dinh; i++)
	{
		int m;
		cout << "Nhap so dinh ke cua " << vertices[i] << ": ";
		cin >> m;
		cin.ignore();
		for (int j = 0; j < m; j++)
		{
			string neighbor;
			cout << "Nhap dinh ke thu " << j + 1 << " cua " << vertices[i] << ": ";
			getline(cin, neighbor);
			Insert_first(first[i], neighbor);
		}
	}
}

void output_list(){
	if (dinh > 0)
	{
		for (int i = 0; i < dinh; i++)
		{
			cout << vertices[i] << ": ";
			Node* p = first[i];
			while (p != NULL)
			{
				cout << p->info << " ";
				p = p->link;
			}
			cout << endl;
		}
	}
	else
		cout << "Do thi rong!" << endl;
}

void DFS(int v, bool visited[]) {
	visited[v] = true;
	cout << vertices[v] << " ";
	Node* p = first[v];
	while (p != NULL) {
		int neighborIndex = -1;
		for (int i = 0; i < dinh; i++) {
			if (vertices[i] == p->info) {
				neighborIndex = i;
				break;
			}
		}
		if (!visited[neighborIndex]) {
			DFS(neighborIndex, visited);
		}
		p = p->link;
	}
}

void BFS(int v) {
	bool visited[MAX] = { false };
	queue<int> q;
	visited[v] = true;
	q.push(v);

	while (!q.empty()) {
		int current = q.front();
		q.pop();
		cout << vertices[current] << " ";

		Node* p = first[current];
		while (p != NULL) {
			int neighborIndex = -1;
			for (int i = 0; i < dinh; i++) {
				if (vertices[i] == p->info) {
					neighborIndex = i;
					break;
				}
			}
			if (!visited[neighborIndex]) {
				visited[neighborIndex] = true;
				q.push(neighborIndex);
			}
			p = p->link;
		}
	}
}
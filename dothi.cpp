#include <iostream>
#include <queue>
#include <stack>
#include <cstring> // Để dùng memset
using namespace std;

#define MAX 100
#define MAX_NEIGHBORS 100
#define cls system("cls")
#define pause system("pause")

enum Type_of_graph
{
    Undirected = 1,
    Directed
};

enum StorageType
{
    Undefined = 0,
    AdjacencyMatrix,
    AdjacencyList
};

// *** Biến toàn cục ***
int adjMatrix[MAX][MAX] = { 0 };      // Ma trận kề
int adjList[MAX][MAX_NEIGHBORS] = { 0 }; // Danh sách kề
int neighborsCount[MAX] = { 0 };      // Số lượng đỉnh kề
int n = 0;                          // Số đỉnh
Type_of_graph graphType;
StorageType storageType = Undefined;

// Hàm in menu
void PrintMenu(const string options[], int size)
{
    for (int i = 1; i < size; i++)
        cout << '(' << i << ") " << options[i] << endl;
    cout << "(0) " << options[0] << endl;
}

// Hàm lấy lựa chọn của người dùng
int GetUserChoice(int size)
{
    int choice;
    do
    {
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;
        if (choice < 0 || choice >= size)
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
    } while (choice < 0 || choice >= size);
    return choice;
}

// Hàm lấy số nguyên dương
int GetPositiveInt(const string& prompt)
{
    int num;
    do
    {
        cout << prompt;
        cin >> num;
        if (num < 1)
            cout << "Vui long nhap so nguyen duong!\n";
    } while (num < 1);
    return num;
}

// Nhập đồ thị dưới dạng ma trận kề
void InputAdjacencyMatrix()
{
    storageType = AdjacencyMatrix;
    n = GetPositiveInt("Nhap so dinh cua do thi: ");
    cout << "Nhap ma tran ke cua do thi (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> adjMatrix[i][j];
            // Không cần đối xứng đồ thị có hướng
        }
    }
}

// Nhập đồ thị dưới dạng danh sách kề
void InputAdjacencyList()
{
    storageType = AdjacencyList;
    n = GetPositiveInt("Nhap so dinh cua do thi: ");
    memset(neighborsCount, 0, sizeof(neighborsCount)); // Reset danh sách kề
    cout << "Nhap danh sach ke:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "So dinh ke cua dinh " << i << ": ";
        cin >> neighborsCount[i];
        cout << "Nhap cac dinh ke cua dinh " << i << ": ";
        for (int j = 0; j < neighborsCount[i]; j++)
        {
            cin >> adjList[i][j];
            if (graphType == Undirected)
            {
                int neighbor = adjList[i][j];
                adjList[neighbor][neighborsCount[neighbor]] = i;
                neighborsCount[neighbor]++;
            }
        }
    }
}

// Xuất đồ thị dưới dạng ma trận kề
void PrintAdjacencyMatrix()
{
    if (storageType != AdjacencyMatrix)
    {
        cout << "Chua nhap du lieu bang ma tran ke!\n";
        return;
    }
    cout << "Ma tran ke cua do thi:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Xuất đồ thị dưới dạng danh sách kề
void PrintAdjacencyList()
{
    if (storageType != AdjacencyList)
    {
        cout << "Chua nhap du lieu bang danh sach ke!\n";
        return;
    }
    cout << "Danh sach ke cua do thi:\n";
    for (int i = 0; i < n; i++)
    {
        cout << i << ": ";
        for (int j = 0; j < neighborsCount[i]; j++)
        {
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }
}

// Hàm duyệt BFS
void BFS(int start)
{
    if (storageType == Undefined)
    {
        cout << "Chua nhap du lieu do thi de duyet!\n";
        return;
    }

    bool visited[MAX] = { false };
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "Ket qua duyet BFS: ";
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        cout << u << " ";
        if (storageType == AdjacencyMatrix)
        {
            for (int v = 0; v < n; v++)
            {
                if (adjMatrix[u][v] == 1 && !visited[v])
                {
                    q.push(v);
                    visited[v] = true;
                }
            }
        }
        else if (storageType == AdjacencyList)
        {
            for (int i = 0; i < neighborsCount[u]; i++)
            {
                int v = adjList[u][i];
                if (!visited[v])
                {
                    q.push(v);
                    visited[v] = true;
                }
            }
        }
    }
    cout << endl;
}

// Hàm duyệt DFS
void DFS(int start)
{
    if (storageType == Undefined)
    {
        cout << "Chua nhap du lieu do thi de duyet!\n";
        return;
    }

    bool visited[MAX] = { false };
    stack<int> s;
    s.push(start);
    visited[start] = true;

    cout << "Ket qua duyet DFS: ";
    while (!s.empty())
    {
        int u = s.top();
        s.pop();
        cout << u << " ";
        if (storageType == AdjacencyMatrix)
        {
            for (int v = 0; v < n; v++)
            {
                if (adjMatrix[u][v] == 1 && !visited[v])
                {
                    s.push(v);
                    visited[v] = true;
                }
            }
        }
        else if (storageType == AdjacencyList)
        {
            for (int i = 0; i < neighborsCount[u]; i++)
            {
                int v = adjList[u][i];
                if (!visited[v])
                {
                    s.push(v);
                    visited[v] = true;
                }
            }
        }
    }
    cout << endl;
}

// Hàm chính
int main()
{
    string menu[] = { "Thoat", "Chon do thi vo huong", "Chon do thi co huong",
                     "Nhap bang ma tran ke", "Nhap bang danh sach ke",
                     "Xuat bang ma tran ke", "Xuat bang danh sach ke",
                     "Duyet BFS", "Duyet DFS" };
    int menuSize = sizeof(menu) / sizeof(menu[0]);

    while (true)
    {
        cls;
        PrintMenu(menu, menuSize);
        int choice = GetUserChoice(menuSize);

        switch (choice)
        {
        case 0:
            cout << "Ket thuc chuong trinh.\n";
            return 0;

        case 1:
            graphType = Undirected;
            cout << "Da chon do thi vo huong.\n";
            pause;
            break;

        case 2:
            graphType = Directed;
            cout << "Da chon do thi co huong.\n";
            cout << "Chon loai luu tru (1: Ma tran ke, 2: Danh sach ke): ";
            int storageChoice = GetUserChoice(3);
            if (storageChoice == 1)
                InputAdjacencyMatrix();
            else if (storageChoice == 2)
                InputAdjacencyList();
            pause;
            break;

        case 3:
            InputAdjacencyMatrix();
            pause;
            break;

        case 4:
            InputAdjacencyList();
            pause;
            break;

        case 5:
            PrintAdjacencyMatrix();
            pause;
            break;

        case 6:
            PrintAdjacencyList();
            pause;
            break;

        case 7:
            int start;
            start = GetPositiveInt("Nhap dinh bat dau duyet BFS: ");
            BFS(start);
            pause;
            break;

        case 8:
            start = GetPositiveInt("Nhap dinh bat dau duyet DFS: ");
            DFS(start);
            pause;
            break;

        default:
            cout << "Lua chon khong hop le!\n";
            pause;
            break;
        }
    }

    return 0;
}

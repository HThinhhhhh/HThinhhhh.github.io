#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
#include <queue> // Thư viện queue cho BFS

#define cls system("cls")
#define pause system("pause")
#define MAX 100

using namespace std;

// Khai báo danh sách kề
struct Node {
    string info;  // Lưu tên đỉnh dưới dạng chuỗi
    Node* link;
};

Node* first[MAX]; // Danh sách kề
string vertices[MAX]; // Tên các đỉnh
int A[MAX][MAX];      // Ma trận kề
int n;                // Số đỉnh của đồ thị

// Hàm khởi tạo danh sách kề
void init_list() {
    for (int i = 0; i < n; i++)
        first[i] = NULL;
}

// Hàm thêm phần tử vào đầu danh sách kề
void Insert_first(Node*& node, string value) {
    Node* p = new Node;
    p->info = value;
    p->link = node;
    node = p;
}

// Hàm nhập danh sách kề
void input_list() {
    cout << "Nhap so dinh cua do thi: ";
    cin >> n;
    cin.ignore(); // Bỏ ký tự xuống dòng sau khi nhập số

    // Nhập tên các đỉnh
    for (int i = 0; i < n; i++) {
        cout << "Nhap ten dinh thu " << i + 1 << ": ";
        getline(cin, vertices[i]); // Đọc chuỗi tên đỉnh
    }

    // Nhập danh sách kề
    for (int i = 0; i < n; i++) {
        int m;
        cout << "Nhap so dinh ke cua " << vertices[i] << ": ";
        cin >> m;
        cin.ignore(); // Bỏ ký tự xuống dòng sau khi nhập số
        for (int j = 0; j < m; j++) {
            string neighbor;
            cout << "Nhap dinh ke thu " << j + 1 << " cua " << vertices[i] << ": ";
            getline(cin, neighbor);
            Insert_first(first[i], neighbor);
        }
    }
}

// Hàm xuất danh sách kề
void output_list() {
    if (n > 0) {
        for (int i = 0; i < n; i++) {
            cout << vertices[i] << ": ";
            Node* p = first[i];
            while (p != NULL) {
                cout << p->info << " ";
                p = p->link;
            }
            cout << endl;
        }
    }
    else {
        cout << "Do thi rong!" << endl;
    }
}

// Hàm nhập ma trận kề
void input_matrix() {
    cout << "Nhap so dinh cua do thi: ";
    cin >> n;
    cin.ignore(); // Bỏ ký tự xuống dòng sau khi nhập số

    // Nhập tên các đỉnh
    for (int i = 0; i < n; i++) {
        cout << "Nhap ten dinh thu " << i + 1 << ": ";
        getline(cin, vertices[i]);
    }

    // Nhập ma trận kề
    cout << "Nhap ma tran ke (0/1):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i + 1 << "][" << j + 1 << "]: ";
            cin >> A[i][j];
        }
    }
}

// Hàm xuất ma trận kề
void output_matrix() {
    if (n > 0) {
        cout << "Ma tran ke cua do thi:\n";
        cout << "    ";
        for (int i = 0; i < n; i++) {
            cout << setw(5) << vertices[i]; // In tên các đỉnh trên cùng
        }
        cout << endl;

        for (int i = 0; i < n; i++) {
            cout << setw(5) << vertices[i]; // In tên đỉnh đầu cột
            for (int j = 0; j < n; j++) {
                cout << setw(5) << A[i][j]; // In ma trận
            }
            cout << endl;
        }
    }
    else {
        cout << "Do thi rong!" << endl;
    }
}

// Hàm DFS đệ quy
void DFS(int v, bool visited[]) {
    visited[v] = true;
    cout << vertices[v] << " ";
    Node* p = first[v];
    while (p != NULL) {
        int neighborIndex = -1;
        for (int i = 0; i < n; i++) {
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

// Hàm BFS
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
            for (int i = 0; i < n; i++) {
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

// Hàm main
int main() {
    const string menu[] = {
        "Thoat chuong trinh",
        "Nhap do thi bang danh sach ke",
        "Xuat do thi bang danh sach ke",
        "Nhap do thi bang ma tran ke",
        "Xuat do thi bang ma tran ke",
        "Duyet theo chieu sau (DFS)",
        "Duyet theo ben rong (BFS)"
    };
    const int menuCount = sizeof(menu) / sizeof(menu[0]);

    int choice;
    do {
        cls;
        for (int i = 0; i < menuCount; i++) {
            cout << "(" << i << ") " << menu[i] << endl;
        }
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        cls;
        switch (choice) {
        case 1: // Nhập đồ thị bằng danh sách kề
            init_list();
            input_list();
            break;
        case 2: // Xuất đồ thị bằng danh sách kề
            output_list();
            pause;
            break;
        case 3: // Nhập đồ thị bằng ma trận kề
            input_matrix();
            break;
        case 4: // Xuất đồ thị bằng ma trận kề
            output_matrix();
            pause;
            break;
        case 5: { // Duyệt theo chiều sâu (DFS)
            int startDFS;
            cout << "Nhap dinh bat dau duyet DFS (0 to " << n - 1 << "): ";
            cin >> startDFS;
            bool visitedDFS[MAX] = { false };
            cout << "Duyet theo chieu sau (DFS) bat dau tu " << vertices[startDFS] << ": ";
            DFS(startDFS, visitedDFS);
            cout << endl;
            pause;
            break;
        }
        case 6: { // Duyệt theo bề rộng (BFS)
            int startBFS;
            cout << "Nhap dinh bat dau duyet BFS (0 to " << n - 1 << "): ";
            cin >> startBFS;
            cout << "Duyet theo ben rong (BFS) bat dau tu " << vertices[startBFS] << ": ";
            BFS(startBFS);
            cout << endl;
            pause;
            break;
        }
        case 0: // Thoát chương trình
            cout << "Ket thuc chuong trinh!" << endl;
            break;
        default:
            cout << "Lua chon khong hop le! Vui long nhap lai." << endl;
            pause;
            break;
        }
    } while (choice != 0);

    return 0;
}

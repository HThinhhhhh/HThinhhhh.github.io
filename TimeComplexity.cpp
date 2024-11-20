#include<iostream>
#include<string>
#include<iomanip>
#include<ctime>
#include<algorithm>

using namespace std;

void Print_Function(const string name[], const int n)
{
	for (int i = 1; i < n; i++)
		cout << "(" << i << ")" << name[i] << endl;
	cout << endl;
	cout << "(0)" << name[0] << endl;
}

int Get_UserChoice(const int n)
{
	int input;
	bool isUserChoiceValid;
	do
	{
		cout << "Nhap vao lua chon cua ban: ";
		cin >> input;
		isUserChoiceValid = (0 <= input && input < n);
		if (!isUserChoiceValid)
			cout << "Lua chon khong hop le! Hay nhap lai!!!" << endl;
	} while (!isUserChoiceValid);
	return input;
}

int Get_PositiveINT(const string prompt)
{
	int input;
	do
	{
		cout << prompt;
		cin >> input;
		if (input < 1)
			cout << "Vui long nhap so nguyen duong!!!" << endl;
	} while (input < 1);
	return input;
}

int* Init_Array(const int n)
{
	int* ptr = new int[n];
	for (int i = 0; i < n; i++)
		ptr[i] = rand() % 50 + 1;
	return ptr;
}

void Output(const int* arr, const int n, const string prompt)
{
	cout << prompt << endl;
	for (int i = 0; i < n; i++)
		cout << arr[i] << "\t";
	cout << endl;
}

void ShellSort(int*& arr, int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i++)
		{
			int temp = arr[i], j;
			for (j = i; j >= gap && arr[j - gap] < temp; j -= gap)
			{
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
}


void Insertion_sort(int* arr, const int n, int& d)
{
	for (int i = 1; i < n; i++)
	{
		int j = i - 1, x = arr[i];
		while (j >= 0 && x < arr[j])
		{
			d++;
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = x;
	}
}

void Function1()
{
	int dem = 0;
	int n = Get_PositiveINT("Nhap vao so phan tu cua mang: ");
	int* ptr = Init_Array(n);
	ShellSort(ptr, n);
	Output(ptr, n, "Truoc khi sort:");
	Insertion_sort(ptr, n, dem);
	Output(ptr, n, "Sau khi sort:");
	cout << "So lan thuc hien phep gan: " << dem << endl;
	delete[] ptr;
	system("pause");
}
void Quick_sort(int* arr, int left, int right, int& d)
{
	int x = arr[(left + right) / 2];
	int i = left, j = right;
	while (i < j)
	{
		while (arr[i] < x)
		{
			i++;
			d++;
		}
		while (arr[j] > x)
		{
			j--;
			d++;
		}
		if (i <= j)
		{
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}

	if (left < j) Quick_sort(arr, left, j, d);
	if (i < right) Quick_sort(arr, i, right, d);
}

void Function_2()
{
	int dem = 0;
	int n = Get_PositiveINT("Nhap vao so phan tu cua mang: ");
	int* ptr = Init_Array(n);

	ShellSort(ptr, n);
	Output(ptr, n, "Truoc khi sort:");

	Quick_sort(ptr, 0, n - 1, dem);
	Output(ptr, n, "Sau khi sort:");
	cout << "So lan thuc hien phep gan: " << dem << endl;

	delete[] ptr;
	system("pause");
}

void heapify(int* arr, int n, int i, int& d)
{
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int largest = i;


	if (l < n && arr[largest] < arr[l])
		largest = l;
	if (r < n && arr[largest] < arr[r])
		largest = r;
	if (largest != i)
	{
		d++;
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest, d);
	}
}
void Function_3()
{
	int dem = 1;
	int n = Get_PositiveINT("Nhap vao so phan tu cua mang: ");
	int* ptr = Init_Array(n);

	ShellSort(ptr, n);
	Output(ptr, n, "Truoc khi sort:");

	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(ptr, n, i, dem);

	for (int i = n - 1; i > 0; i--)
	{
		swap(ptr[i], ptr[0]);
		heapify(ptr, i, 0, dem);
	}

	Output(ptr, n, "Sau khi sort:");
	cout << "So lan thuc hien phep gan: " << dem << endl;

	delete[] ptr;
	system("pause");
}

int fibo(int n, int& d)
{
	d++;
	if (n == 1)
		return 0;
	if (n == 2)
		return 1;
	return fibo(n - 1, d) + fibo(n - 2, d);
}
void Function_4()
{
	int dem = 0;
	int n = Get_PositiveINT("Nhap vao so Fibonacci ban muon tinh: ");
	int kq = fibo(n, dem);
	cout << "ket qua Fibonacci[" << n << "]: " << kq << endl;
	cout << "So lan thuc hien goi ham Fibo la: " << dem << endl;
	system("pause");
}

int main()
{
	srand(time(0));
	const string FunctionName[] =
	{
		"Ket thuc chuong trinh",
		"Time complexity of Insertion Sort",
		"Time complexity of Quick Sort",
		"Time complexity of Heap Sort",
		"Time complexity of Fibonacci",
	};
	const int countFunction = sizeof(FunctionName) / sizeof(string);
	int userchoice;

	do
	{
		system("cls");
		Print_Function(FunctionName, countFunction);
		userchoice = Get_UserChoice(countFunction);
		system("cls");
		cout << FunctionName[userchoice] << endl;
		switch (userchoice)
		{
		case 1:
			Function1();
			break;
		case 2:
			Function_2();
			break;
		case 3:
			Function_3();
			break;
		case 4:
			Function_4();
			break;
		}
	} while (userchoice != 0);
	return 0;
}
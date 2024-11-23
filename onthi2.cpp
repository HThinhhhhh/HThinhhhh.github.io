#include<iostream>
#include<iomanip>
#include<string>
#include<algorithm>
#include<ctime>
#include<vector>

#define cls system("cls")
#define pause system("pause")

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
			cout << "Lua chon khong hop le!Hay nhap lai!!!" << endl;
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
			cout << "Lua chon khong hop le!Hay nhap lai!!!" << endl;
	} while (input < 1);
	return input;
}

int Get_max_element(int* arr, int n)
{
	int max = arr[0];
	for (int i = 0; i < n; i++)
		if (max < arr[i]) max = arr[i];
	return max;
}

bool ChangeMode(string prompt)
{
	char input;
	bool isUserChoiceValid;
	cout << "\t (1) Automatic\n\t (2) Manual\n";
	do
	{
		cout << prompt;
		cin >> input;
		isUserChoiceValid = input == '1' || input == '2';
		if (!isUserChoiceValid)
			cout << "Lua chon khong hop le!!! Hay nhap lai!!!\n";
	} while (!isUserChoiceValid);
	return input == '1';
}

void Generate_array(int* arr, int n, bool automatic)
{
	if (automatic)
	{
		for (int i = 0; i < n; i++)
			arr[i] = rand() % 50 + 1;
		return;
	}
	cout << "Khoi tao gia tri cho mang:\n";
	for (int i = 0; i < n; i++) {
		cout << "Nhap gia tri cho phan tu a[" << i << "]: ";
		cin >> arr[i];
	}
}

void Print_Array(int* arr, int n, string prompt)
{
	cout << prompt << endl;
	for (int i = 0; i < n; i++)
		cout << arr[i] << "\t";
	cout << endl;
	pause;
}

void Insertion_sort(int* arr, const int n)
{
	for (int i = 1; i < n; i++)
	{
		int j = i - 1, x = arr[i];
		while (j >= 0 && x > arr[j])
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = x;
	}
}

void ShellSort(int* arr, int n, int& d)
{
	Insertion_sort(arr, n);
	Print_Array(arr, n, "Mang truoc khi sort:");
	cout << endl;
	int step = Get_PositiveINT("Nhap vao step ban dau ban muon: ");
	for (int gap = n / step; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i++) {
			int temp = arr[i], j;
			d++;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
				arr[j] = arr[j - gap];
				d++;
			}
			arr[j] = temp;
			d++;
		}
	}
	Print_Array(arr, n, "Mang sau khi sort:");
	cout << "So lan thuc hien phep gan: " << d << endl;
	pause;
}

void CountingSort(int* arr, int n, int& d)
{
	Insertion_sort(arr, n);
	Print_Array(arr, n, "Mang sau khi sort nguoc lai:");
	cout << endl;
	int max = Get_max_element(arr, n);
	int* count = new int[max + 1] {0};
	int* output = new int[n];
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		count[arr[i]]++;
		d++;
	}
	for (int i = 1; i <= max; i++)
	{
		count[i] += count[i - 1];
		d++;
	}
	for (int i = n - 1; i >= 0; i--)
	{
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
		d++;
	}
	for (int i = 0; i < n; i++)
	{
		arr[i] = output[i];
		d++;
	}
	Print_Array(output, n, "Mang sau khi duoc sort:");
	cout << "Hoan thanh sap xep!!!\n";
	cout << "So lan thuc hien phep gan: " << d << endl;
	pause;
	delete[] count;
	delete[] output;
}

void CountSort(int* arr, int n, int exp, int& d)
{
	int max = Get_max_element(arr, n);
	int count[10] = { 0 };
	int* output = new int[n];
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		int digit = (arr[i] / exp) % 10;
		count[digit]++;
		d++;
	}
	for (int i = 1; i < 10; i++) {
		count[i] += count[i - 1];
		d++;
	}
	for (int i = n - 1; i >= 0; i--)
	{
		int digit = (arr[i] / exp) % 10;
		output[count[digit] - 1] = arr[i];
		count[digit]--;
		d++;
	}
	for (int i = 0; i < n; i++) {
		arr[i] = output[i];
		d++;
	}

	delete[] output;
}

void RadixSort(int* arr, int n, int& d)
{
	Insertion_sort(arr, n);
	Print_Array(arr, n, "Mang sau khi sort nguoc lai:");
	cout << endl;
	int m = Get_max_element(arr, n);
	for (int exp = 1; m / exp > 0; exp *= 10)
	{
		CountSort(arr, n, exp, d);
		d++;
	}
	Print_Array(arr, n, "Mang sau khi sort:");
	cout << "Hoan thanh sap xep!!!\n";
	cout << "So lan thuc hien phep gan: " << d << endl;
	pause;
}

void insertionSort(vector<float>& bucket) {
	for (int i = 1; i < bucket.size(); ++i) {
		float key = bucket[i];
		int j = i - 1;
		while (j >= 0 && bucket[j] > key) {
			bucket[j + 1] = bucket[j];
			j--;
		}
		bucket[j + 1] = key;
	}
}
void PrintArray(float arr[], int n, string prompt)
{
	cout << prompt << endl;
	for (int i = 0; i < n; i++)
		cout << arr[i] << '\t';
	cout << endl;
	pause;
}
void BucketSort(float arr[], int n)
{

	vector<vector<float>> b(n);
	for (int i = 0; i < n; i++)
	{
		int bi = n * arr[i];
		b[bi].push_back(arr[i]);
	}
	for (int i = 0; i < n; i++)
		insertionSort(b[i]);
	int index = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < b[i].size(); j++) {
			arr[index++] = b[i][j];
		}
	}
	PrintArray(arr, n, "Mang sau khi sort:");
	pause;
}

int main()
{
	srand(time(0));
	const string SortName[] = {
		"Ket thuc chuong trinh",
		"Shell Sort",
		"Counting Sort",
		"Radix Sort",
		"Bucket Sort"
	};
	const int countSort = sizeof(SortName) / sizeof(string);
	int userchoice, n;
	bool automatic;
	float a[] = { 0.42,0.32,0.23,0.52,0.25,0.47,0.51 };
	const int n1 = sizeof(a) / sizeof(float);
	do
	{
		int dem = 0;
		cls;
		Print_Function(SortName, countSort);
		userchoice = Get_UserChoice(countSort);
		int* ptr = NULL;
		if (userchoice == 0)
			return 0;
		cls;
		cout << SortName[userchoice] << endl;
		if (userchoice != 4)
		{
			automatic = ChangeMode("Nhap vao che do ban muon: ");
			n = Get_PositiveINT("Nhap so luong: ");
			ptr = new int[n];
			cls;
			cout << "|*------------------------------------------------------------*|\n";
			cout << SortName[userchoice] << "\n\t" << "Che do: " << (automatic ? "Automatic\n" : "Manual\n") << "\tSo luong: " << n << endl;
			Generate_array(ptr, n, automatic);
			Print_Array(ptr, n, "Gia tri mang sau khi khoi tao:");
		}

		switch (userchoice)
		{
		case 1:
			ShellSort(ptr, n, dem);
			break;
		case 2:
			CountingSort(ptr, n, dem);
			break;
		case 3:
			RadixSort(ptr, n, dem);
			break;
		case 4:
			PrintArray(a, n1, "Mang truoc khi sort:");
			BucketSort(a, n1);
			break;
		};
		if (ptr != NULL)
			delete[] ptr;
	} while (userchoice != 0);
	return 0;
}

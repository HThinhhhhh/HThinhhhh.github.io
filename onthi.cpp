
#include <iostream>
#include <iomanip>
#include<string>
#include<algorithm>
#include <ctime>
#include<vector>

#define cls system("cls")
#define pause system("pause")

using namespace std;

void Print_Function(const string name[], const int n)
{
	for (int i = 1; i < n; i++)
		cout << '(' << i << ')' << name[i] << endl;
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
		if(!isUserChoiceValid)
			cout<< "Lua chon khong hop le!!! Hay nhap lai!!!\n";
	} while (!isUserChoiceValid);
	return input == '1';
}

void Generate_Array(int* arr, int n, bool automatic)
{
	if (automatic)
	{
		for (int i = 0; i < n; i++)
			arr[i] = rand() % 50 + 1;
		return;
	}
	cout << "Khoi tao gia tri cho mang:\n";
	for (int i = 0; i < n; i++)
	{
		cout << "Nhap gia tri cho phan tu arr[" << i << "]: ";
		cin >> arr[i];
	}
}

void Print_Array(int* arr, int n, string prompt)
{
	cout << prompt << endl;
	for (int i = 0; i < n; i++)
		cout << arr[i] << '\t';
	cout << endl;
	pause;
}

void PrintArray(float* arr, int n, string prompt)
{
	cout << prompt << endl;
	for (int i = 0; i < n; i++)
		cout << arr[i] << '\t';
	cout << endl;
	pause;
}

int Get_max_element(int* arr, int n)
{
	int max = arr[0];
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

void ShellSort(int* arr, int n)
{
	int step = Get_PositiveINT("Nhap so step ban dau ban muon: ");
	for (int gap = n / step; gap > 0; gap /= step)
	{
		for (int i = gap; i < n; i++)
		{
			int temp = arr[i], j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];
			arr[j] = temp;
		}
		Print_Array(arr, n, "Mang sau khi duoc sort voi gap = " + to_string(gap));
		if (gap == 1)
		{
			cout << "Da Sort xong!!!\n";
			pause;
		}
	}
}

void CountingSort(int* arr, int n)
{
	int max = Get_max_element(arr, n);
	int* count = new int[max + 1] {0};
	int* output = new int[n];
	cout << endl;
	for (int i = 0; i < n; i++)
		count[arr[i]]++;
	for (int i = 1; i <= max; i++)
		count[i] += count[i - 1];
	for (int i = n - 1; i >= 0; i--)
	{
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}
	for (int i = 0; i < n; i++) 
		arr[i] = output[i];
	Print_Array(output, n, "Mang sau khi duoc sort:");
	cout << "Hoan thanh sap xep!!!\n";
	pause;

	delete[] count;
	delete[] output;
}

void CountSort(int* arr, int n,int exp)
{
	int max = Get_max_element(arr, n);
	int count[10] = { 0 };
	int* output = new int[n];
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		int digit = (arr[i] / exp) % 10;
		count[digit]++;
	}
	for (int i = 1; i <10; i++)
		count[i] += count[i - 1];
	for (int i = n - 1; i >= 0; i--)
	{
		int digit = (arr[i] / exp) % 10;
		output[count[digit] - 1] = arr[i];
		count[digit]--;
	}
	for (int i = 0; i < n; i++)
		arr[i] = output[i];

	delete[] output;
}

void RadixSort(int* arr, int n)
{
	int m = Get_max_element(arr, n);
	for (int exp = 1; m / exp > 0; exp *= 10)
		CountSort(arr, n,exp);
	Print_Array(arr, n, "Mang sau khi sort:");
	cout << "Hoan thanh sap xep!!!\n";
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
void BucketSort(float* arr, int n) 
{
	vector <float>* b=new vector<float>[n];
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
	delete[] b;
	pause;
}

int main()
{
	srand(time(0));
	const string Sortingname[] =
	{
		"Ket thuc chuong trinh",
		"Shell Sort",
		"Counting Sort",
		"Radix Sort",
		"Bucket Sort"
	};
	const int countSort = sizeof(Sortingname) / sizeof(string);
	int userchoice, n;
	bool automatic;
	do
	{
		cls;
		Print_Function(Sortingname, countSort);
		userchoice = Get_UserChoice(countSort);
		if (userchoice == 0)
			return 0;
		cls;
		cout << Sortingname[userchoice] << endl;
		automatic = ChangeMode("Nhap vao che do ban muon: ");
		n = Get_PositiveINT("Nhap so luong: ");
		cls;
		cout << "|*------------------------------------------------------------*|\n";
		cout << Sortingname[userchoice] << "\n\t" << "Che do: " << (automatic ? "Automatic\n" : "Manual\n") << "\tSo luong: " << n << endl;
		int* ptr = new int[n];
		
		Generate_Array(ptr, n, automatic);
		Print_Array(ptr, n, "Gia tri mang sau khi khoi tao:");
		switch (userchoice)
		{
		case 1:
			ShellSort(ptr, n);
			break;
		case 2:
			CountingSort(ptr, n);
			break;
		case 3:
			RadixSort(ptr, n);
			break;
		case 4:
			BucketSort(ptr, n);
			break;
		}
		delete[] ptr;
	} while (userchoice != 0);
	return 0;
}
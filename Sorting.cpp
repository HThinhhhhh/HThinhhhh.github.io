#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include<ctime>

#define cls system("cls")
#define pause system ("pause")
using namespace std;

void Print_Function(const string name[], const int n)
{
	for (int i = 1; i < n; i++)
		cout << '(' << i << ')' << name[i] << endl;
	cout << endl;
	cout << "(0)" << name[0] << endl;
}

int Get_User_Choice(const int n)
{
	int input;
	bool isUserChoiceValid;
	do
	{
		cout << "Nhap vao lua chon cua ban: ";
		cin >> input;
		isUserChoiceValid = (0 < input && input < n);
		if(!isUserChoiceValid)
			cout <<"Lua chon khong hop le!Hay nhap lai!!!" << endl;
	} while (!isUserChoiceValid);
	return input;
}

int Get_PositiveINT(const string prompt)
{
	int input;
	do {
		cout << prompt;
		cin >> input;
		if (input < 1)
			cout << "Vui long nhap so nguyen duong!!!" << endl;
	} while (input < 1);
	return input;
}

bool Change_mode(string prompt)
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
		return input=='1';
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
	for (int i = 0; i < n; i++)
	{
		cout << "Nhap gia tri cho phan tu arr[" << i << "]: ";
		cin >> arr[i];
	}
}

void Print_array(int* arr, int n, string prompt)
{
	cout << prompt << endl;
	for (int i = 0; i < n; i++)
		cout << arr[i] << "\t";
	cout << endl;
	pause;
}

void Init_array(int* arr, int n, int x = 0)
{
	for (int i = 0; i < n; i++)
		arr[i] = x;
}

int Get_max_elements(int* arr, int n)
{
	int max = arr[0];
	for (int i = 0; i < n; i++)
		if (max < arr[i]) max = arr[i];
	return max;
}

void ShellSort(int* arr, int n)
{
	int step = Get_PositiveINT("Nhap vao step ban dau ban muon: ");
	for (int gap = n / step; gap > 0; gap /= step)
	{
		for (int i = gap; i < n; i++)
		{
			int temp = arr[i];
			int j;
			for ( j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];
			arr[j] = temp;
		}
		Print_array(arr, n, "Mang sau khi duoc sort voi Gap = " + to_string(gap));
		if (gap == 1)
		{
			cout << "Da sort xong!!!\n";
			pause;
		}
	}
}

void CountingSort(int* arr, int n)
{
	int max=Get_max_elements(arr, n);
	int* count = new int[max];
	Init_array(count, max);
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		count[arr[i]]++;
		Print_array(count, max, "\tMang count luc i = " + to_string(i));
	}
	for (int i = 1; i <= max; i++)
		count[i] += count[i - 1];
	Print_array(count, max, "Mang count sau khi thuc hien prefix sum");
	int* ans = new int[n];
	Init_array(ans, n);
	for (int i = n - 1; i >= 0; i--) {
		cout << endl;
		Print_array(arr, n, "Mang arr ban dau:");
		cout << "Voi i = " << i << endl;
		int idx = --count[arr[i]];
		cout << "\tarr[" << i << "] = " << arr[i]
			<< "\n\t--count[arr[" << i << "]] = " << idx << endl;
		ans[idx] = arr[i];
		Print_array(count, max, "\tMang count:");
		Print_array(ans, n, "\tMang ans:");
	}
	cout << "Hoan thanh sap xep!!!\n";
	pause;

	delete[] count;
	delete[] ans;
}

int main()
{
	srand(time(0));
	const string SortingName[] = {
		"Ket thuc chuong trinh",
		"Shell Sort",
		"Counting Sort",
		"Radix Sort",
		"Bucket Sort"
	};
	const int countSort = sizeof(SortingName) / sizeof(string);
	int userChoice, n;
	bool automatic;
	do
	{
		cls;
		Print_Function(SortingName, countSort);
		userChoice = Get_User_Choice(countSort);
		if (userChoice == 0)
			return 0;
		cls;
		cout << SortingName[userChoice] << endl;
		automatic = Change_mode("Nhap vao che do ban muon: ");
		n = Get_PositiveINT("Nhap so luong: ");
		cls;
		cout << "|*------------------------------------------------------------*|\n";
		cout << SortingName[userChoice] << "\n\t" << "Che do: " << (automatic ? "Automatic\n" : "Manual\n")
			<< "\tSo luong: " << n;
		cout << "\n|*------------------------------------------------------------*|\n";

		int* ptr = new int[n];
		Generate_array(ptr, n, automatic);
		Print_array(ptr, n, "Gia tri mang sau khi khoi tao");

		switch (userChoice)
		{
		case 1:
			ShellSort(ptr, n);
			break;
		case 2:
			CountingSort(ptr, n);
			break;
		case 3:
			// Radix_sort(ptr, n);
			break;
		case 4:
			
			break;
		}

		delete[] ptr;

	} while (userChoice != 0);
	return 0;
}
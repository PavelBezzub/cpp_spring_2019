#include "pch.h"
#include <iostream>
#include <fstream> 
#include <string.h>
#include <string>
#include <math.h>
#include "numbers.dat"
using namespace std;
int binarysearch(const int k) {
	int left = 0, right = Size - 1, middle;
	while (left <= right) {
		middle = (left + right) / 2;
		if (k < Data[middle])
			right = middle - 1;
		else if (k > Data[middle])
			left = middle + 1;
		else
			return middle;
	}
	return 0;
}
int simple_check(int a)
{
	float end;
	end = sqrt((float)a);
	for (int i = 2; i <= end; ++i) {
		if (a % i == 0)  return 1;
	}
	return 0;

}
int search_for_simple_numbers(const int a, const int b)
{
	int left = binarysearch(a);
	int right = binarysearch(b);
	
	for (int u = right; u < Size; u++)
	{
		if (Data[u] == Data[u + 1])
		{
			right = right + 1;
		}
		else break;
	}
	cout << left << ' ' << right;
	int n = 0;
	for (int j = left; j <= right; j++)
	{
		if (Data[j] == 1)
		{
			++n;
		}
		else {
			   if (simple_check(Data[j]) == 1)
			   {
				++n;
			   }
		}
	}
	return right - left + 1 - n;
}

int main(int argc, char* argv[])
{

	if (argc < 3) return -1;
	if ((argc + 1) % 2) return -1;
	int n = (argc - 1) / 2;
	for (int i = 0; i < n; ++i)
	{
		int left = atoi(argv[2 * i + 1]);
		int right = atoi(argv[2 * (i + 1)]);
		if (left > right) {
			cout << 0;
			return 0;
		}
		else
		{
			int result = search_for_simple_numbers(left, right);
			cout << result << endl;
		}
	}

	return 0;
}
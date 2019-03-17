#include <iostream>
#include <fstream> 
#include <string.h>
#include <string>
#include <math.h>
#include "numbers.dat"
using namespace std;
int bynarysearch(const int k) {
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

int search_for_simple_numbers(const int a, const int b)
{
	int aa = bynarysearch(a);
	int bb = bynarysearch(b);
	for (int u = bb; u < Size; u++)
	{
		if (Data[u] == Data[u + 1])
		{
			bb = bb + 1;
		}
		else break;
	}
	int n = 0;
	float end;
	for (int j = aa; j <= bb; j++)
	{
		end = sqrt((float)Data[j]);
		if (Data[j] == 1)
		{
			++n;
		}
		for (int i = 2; i <= end; ++i) {
			if (Data[j] % i == 0) {
				++n;
				break;
			}
		}
	}
	return bb - aa + 1 - n;
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
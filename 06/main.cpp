#include<fstream>
#include <iostream>
#include <cstdio>
#include<time.h>
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <stdio.h>
#include<random>
using namespace std;
const size_t Threads_numbers = 4;
void sort_arr(const char* F_name,const std::string &file_result, size_t number,size_t size)
{
	std::vector<std::uint64_t> arr;
	uint64_t z;
	ifstream in(F_name, ios::binary);
	in.seekg(number * sizeof(uint64_t), 0);
	for (size_t i = 0; i < size; ++i)
	{
		in.read((char*)&(z), sizeof(uint64_t));
		arr.push_back(z);
	}
	for (size_t i = 1; i < size; i++)
		for (size_t j = i; j > 0 && arr[j - 1] > arr[j]; j--) 
			swap(arr[j - 1], arr[j]);
	in.close();
	ofstream out( file_result, ios::binary);//!
	for (size_t i = 0; i < size; i++)
	{
		out.write((char*)&(arr[i]), sizeof(arr[i]));
	}
	out.close();
}

void merge(const std::string &f1,const std::string &f2,const std::string &file_result)
{
	uint64_t a;
	uint64_t b;
	ifstream inA(f1, ios::binary);//!
	ifstream inB(f2, ios::binary);//!

	inA.seekg(0, ios::end);
	size_t size_a = inA.tellg() / sizeof(uint64_t);
//	cout << " size_a = " << size_a << endl;
	inA.seekg(0, 0);

	inB.seekg(0, ios::end);
	size_t size_b = inB.tellg() / sizeof(uint64_t);
//	cout <<" size_b = " <<size_b << endl;
	inB.seekg(0, 0);

	inA.read((char*)&(a), sizeof(uint64_t));
	inB.read((char*)&(b), sizeof(uint64_t));
	size_t counter1 = 0;
	size_t counter2 = 0;
	ofstream out(file_result, ios::binary);//!
	for (int i = 0; i < size_a + size_b; ++i)
	{
		if (a > b)
		{
			out.write((char*)&(b), sizeof(uint64_t));
			counter2 += 1;
			if (counter2 < size_b) { inB.read((char*)&(b), sizeof(uint64_t)); }
			else { b = UINT64_MAX; }
		}
		else if (a < b)
		{
			out.write((char*)&(a), sizeof(uint64_t));
			counter1 += 1;
			if (counter1 < size_a) { inA.read((char*)&(a), sizeof(uint64_t)); }
			else { a = UINT64_MAX; }
		}
		else {
			out.write((char*)&(a), sizeof(uint64_t));
			out.write((char*)&(b), sizeof(uint64_t));
			counter2 += 1;
			counter1 += 1;
			if (counter1 < size_a) { inA.read((char*)&(a), sizeof(uint64_t)); }
			else { a = UINT64_MAX; }
			if (counter2 < size_b) { inB.read((char*)&(b), sizeof(uint64_t)); }
			else { b = UINT64_MAX; }
			i += 1;
		}
	}
	inA.close();
	inB.close();
	out.close();
	string str1 = f1;
	string str2 = f2;
	const char * A = str1.c_str();
	const char * B = str2.c_str();
	remove(A);
	remove(B);
}

void sort_file(const char* f1,const std::string &file_result, size_t number, size_t size)
{
	int cardinality = 100;
	int amounnt = size / cardinality;
	string str,str1,str2,str3;
	int i = 0;
	for (i= 0 ; i < amounnt; ++i)
	{
		str = to_string(i) +"0" + to_string(number);
		sort_arr("MyArr.txt",str + "_file.txt", number + i* cardinality, cardinality);
	}
	if (size % cardinality)
	{ 		
		str = to_string(i)+ "0" + to_string(number);
		sort_arr("MyArr.txt", str + "_file.txt", number + i * cardinality, size % cardinality);
		i++;
	}
	int am = 0;
	if (i == 1)
	{
		string File3 =  str + "_file.txt";//!
		const char * A = File3.c_str();
		string str_file_res =  file_result + ".txt";//!
		const char * B = str_file_res.c_str();
		rename(A, B);
	}
	else if (i == 2 )
	{
		//str1 = to_string(0)+to_string(0)+to_string(number);
		str1 = "00"  + to_string(number);
		//str2= to_string(1) + to_string(0) +to_string(number);
		str2 = "10" + to_string(number);
		merge(str1+"_file.txt",str2+ "_file.txt", file_result + ".txt");
	}
	else 
	{
		int n = 0;
		int nn = 1;
		int num = i;
		while (nn < i && !(num==1))
		{
			if (num % 2)
			{
				str1 = to_string(num-1) + to_string(n) + to_string(number);
				str2 = to_string(num - 2) + to_string(n) + to_string(number);
				str3 = to_string(num)+ to_string(num) + to_string(n)+  to_string(number);
				uint64_t z;
				merge(str1 + "_file.txt", str2 + "_file.txt", str3 + "A_file.txt");
				string a = (str3 + "A_file.txt");
				string b = (str2 + "_file.txt");
				const char * A = a.c_str();
				const char * B = b.c_str();
				rename(A,B);
				num--;
			}
			for (int u = 0; u < (num/2); u++)
			{
				str1 = to_string(2*u) + to_string(n) +to_string(number);
				str2 = to_string(2*u + 1) + to_string(n) + to_string(number);
				str3 = to_string(u) + to_string(n+1) + to_string(number);
				merge(str1 + "_file.txt", str2 + "_file.txt", str3 + "_file.txt");
				
			}
			n++;
			num /= 2;
			nn *= 2;
		}
		int result;
		string File3 =  str3 + "_file.txt";//!
		const char * A = File3.c_str();
		string str_file_res =file_result + ".txt";//!
		const char * B = str_file_res.c_str();
		result = rename(A, B);
	}
}
int main() {
	const char* FName = "MyArr.txt"; 
	const uint64_t n = 125000;
	uint64_t x;                                	
	ofstream out(FName, ios::binary);
	if (!out.is_open()) { cout << " file not found"; return 1; }
	for (auto i = 0; i < n; i++)
	{
	
		x= rand()%100;
		out.write((char*)&(x), sizeof(x));	
	}     
	out.close();
	uint64_t numbers = n/Threads_numbers;//50
	uint64_t pos;
	size_t res_number = 0;
	auto start = std::chrono::steady_clock::now();
	std::string str;
	std::vector<std::thread> results;
	results.reserve(Threads_numbers);
	for (size_t i = 0; i < Threads_numbers; i++) {
		str = to_string(res_number);
		pos = i * n / Threads_numbers;
		if (i==(Threads_numbers-1))  { numbers = (n/Threads_numbers) + (n%Threads_numbers); }
		results.emplace_back(sort_file,"MyArr.txt", "Result" + str+'0', pos, numbers);
		res_number++;
	}
	for (auto& f : results) {
		f.join();
	}
	int k = Threads_numbers;
	uint64_t file_index = 0;
	std::string str1, str2, s_res;
	while (k != 1) {
		int index = 1;
		for (int num = 0; num < k; num += Threads_numbers * 2) {
			std::vector <std::thread> threads;
			for (int j = 0; j < Threads_numbers; j++) {
				if (index - 1 < k / 2) {
					str1 = "Result" + std::to_string(2 * index - 2) + std::to_string(file_index) + ".txt";
					str2 = "Result" + std::to_string(2 * index - 1)  + std::to_string(file_index) + ".txt";
					s_res = "Result" + std::to_string(index - 1) + std::to_string(file_index + 1) + ".txt";
					std::thread th([str1, str2, s_res, index, file_index] {
						return merge(str1, str2, s_res);
					});
					threads.emplace_back(std::move(th));
					index = index + 1;
				}
			}
			for (auto& t : threads) {
					t.join();
			}
		}
		k /= 2;
		file_index += 1;
	}
	rename(s_res.c_str(), "Result.txt");
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << diff.count() << std::endl;
	cout << endl;
	uint64_t z;
	ifstream inA("Result.txt", ios::binary);
	for (int i = 0; i <n ; ++i)
	{
		inA.read((char*)&(z), sizeof(uint64_t));
		//cout << " " << z;
	}
	inA.close();
	cout << endl;
	cout << " done ";
	return 0;
}

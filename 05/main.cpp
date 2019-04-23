#include<iostream>
#include<thread>
#include<mutex>
#include <condition_variable>

std::condition_variable cond;
size_t flag = 1;
std::mutex m;
const size_t n = 500000;

void ping()
{
	for (size_t i = 0; i < n; i++) {
		std::unique_lock<std::mutex> lock(m);
		cond.wait(lock, [](){return flag > 0;});
		printf("ping\n");
		--flag;
		cond.notify_one();
	}
}

void pong()
{
	for (size_t i = 0; i < n; i++) {
		std::unique_lock<std::mutex> lock(m);
		cond.wait(lock, [](){return flag == 0;});
		printf("pong\n");
		++flag;
		cond.notify_one();
	}

}
int main() {
	std::thread ping_(ping);
	std::thread pong_(pong);
	ping_.join();
	pong_.join();
	return 0;
}

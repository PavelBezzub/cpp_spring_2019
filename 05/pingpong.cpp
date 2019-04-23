//long running code (13 seconds)
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable ping_done;
std::condition_variable pong_done;

void bar() {
	std::unique_lock <std::mutex> lock(m);
	for (size_t i = 0; i < 500000; ++i) {
		ping_done.wait(lock);
		printf("pong\n");
		pong_done.notify_one();
	}
}

void foo() {
	std::unique_lock <std::mutex> lock(m);
	for (size_t i = 0; i < 500000; ++i) {
		printf("ping\n");
		ping_done.notify_one();
		pong_done.wait(lock);
	}
}



int main(int argc, char const *argv[]) {
	std::thread T1(bar);
	T1.detach();
	std::thread T2(foo);
	T2.join();
	return 0;
}

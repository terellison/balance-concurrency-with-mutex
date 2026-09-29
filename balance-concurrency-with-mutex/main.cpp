#include <mutex>
#include <thread>
#include <iostream>
#include <vector>

int balance = 1000;
std::mutex balanceMutex;
void deposit(int amt);
void withdraw(int amt);

int main(size_t argc, char* argv[])
{
	std::vector<std::thread> depositThreadPool;
	std::vector<std::thread> withdrawThreadPool;

	if (argc < 2)
	{
		std::cout << "Missing number of transactions";
		return 1;
	}

	size_t threads = std::atoi(argv[1]);
	std::cout << "Number of threads for deposits and withdrawals: " << threads << std::endl;
	std::cout << "Starting balance: " << balance << std::endl;

	for (size_t i = 0; i < threads; ++i)
	{
		depositThreadPool.emplace_back(deposit, 100);
		withdrawThreadPool.emplace_back(withdraw, 100);
	}

	for (auto& d : depositThreadPool) d.join();
	for (auto& w : withdrawThreadPool) w.join();

	std::cout << "Final balance: " << balance << std::endl;
}

void deposit(int amt)
{
	for (size_t i = 0; i < 100; ++i)
	{
		std::lock_guard<std::mutex> lock(balanceMutex);
		balance += amt;
		std::cout << "Deposit - New balance: " << balance << std::endl;
	}
}

void withdraw(int amt)
{
	for (size_t i = 0; i < 100; ++i)
	{
		std::lock_guard<std::mutex> lock(balanceMutex);
		balance -= amt;
		std::cout << "Withdraw - New balance: " << balance << std::endl;
	}
}
#pragma once
#include "Customer.h"
#include "Withdraw.h"
#include<string>

void WithdrawOpt(Customer* User, std::string& money) {
	std::cout << "1. 10" << std::endl;
	std::cout << "2. 20" << std::endl;
	std::cout << "3. 50" << std::endl;
	std::cout << "4. 100" << std::endl;
	std::cout << "5. Other" << std::endl;
	int Option;
	std::cout << "Please input your option: ";
	std::cin >> Option;
	bool Success = false;
	switch (Option)
	{
	case 1:
		Success = Withdraw(User, "10", false);
		if (Success == true)
			std::cout << "Withdraw Successfully !" << std::endl;
		break;
	case 2:
		Success = Withdraw(User, "20", false);
		if (Success == true)
			std::cout << "Withdraw Successfully !" << std::endl;
		break;
	case 3:
		Success = Withdraw(User, "50", false);
		if (Success == true)
			std::cout << "Withdraw Successfully !" << std::endl;
		break;
	case 4:
		Success = Withdraw(User, "100", false);
		if (Success == true)
			std::cout << "Withdraw Successfully !" << std::endl;
		break;
	case 5:
		Success = Withdraw(User, money, false);
		if (Success == true)
			std::cout << "Withdraw Successfully !" << std::endl;
		break;
	default:
		std::cout << "Invalid choice !" << std::endl;
		break;
	}
}
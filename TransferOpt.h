#pragma once
#include "Transfer.h"

bool TransferOpt(Customer* customer1, std::string& money) {
	// kiểm tra friendly acc của đối tượng, nếu có thì hiện option cho chuyển friend hoặc người khác
		std::cout << "What kind of account do you want to transfer ?" << std::endl;
		std::cout << "1. Your friends" << std::endl;
		std::cout << "2. Other People" << std::endl;

		int Selection;
		std::cin >> Selection;
		std::vector<std::string> friendlyAccs;

		if (Selection == 1) {
			if (customer1->getFriendlyAcc().size() != 0) {
				friendlyAccs = customer1->getFriendlyAcc();
				for (int c = 0; c < friendlyAccs.size(); c++) {
					std::cout << c + 1 << ". " << friendlyAccs[c] << std::endl;				// lấy friend của đối tượng
				}
				int Number = 0;
				std::cout << "Account Number: ";
				std::cin >> Number;
				if (Number >= 1 && Number <= friendlyAccs.size()) {
					std::cout << "Please input the amount of Money: ";
					std::cin >> money;
					for (int c = 0; c < money.size(); c++) {
						if (money[c] > '9' || money[c] < '0') {
							std::cout << "Invalid Money !" << std::endl;
							return false;
						}
					}
					if (money.size() > 0)
						Transfer(customer1, money, friendlyAccs[Number - 1]);					// vì Index lấy từ không nên là sẽ phải trừ đi 1
					else {
						std::cout << "Invalid Money !" << std::endl;
						return false;
					}
				}
				else {
					std::cout << "Invalid choice" << std::endl;
					return false;
				}
			}
			else {
				std::cout << "You don't have any friend.. sadly :<" << std::endl;
				//std::system("pause");
				//std::cout << "\x1B[2J\x1B[H";
				//TransferOpt(customer1, money);
			}
		}
		else if (Selection == 2) {
			std::string user2;
			std::cout << "Please input account ID: ";
			std::cin >> user2;
			std::cout << "Please input the amount of Money: ";
			std::cin >> money;

			for (int c = 0; c < money.size(); c++) {
				if (money[c] > '9' || money[c] < '0') {
					std::cout << "Invalid Money !" << std::endl;
					return false;
				}
			}

			Transfer(customer1, money, user2);
		}
		else {
			std::cout << "Invalid choice !" << std::endl;
			return false;
		}
		return false;
}


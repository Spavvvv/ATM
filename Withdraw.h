#pragma once
#include "Customer.h"
#include "CreateFile.h"
#include "ReadId.h"
#include <string>

bool Withdraw(Customer* customer, std::string money, const bool& transferCheck) {
	if(money != "")
	for (int c = 0; c < money.size(); c++) {
		if (money[c] > '9' || money[c] < '0') {
			std::cout << "Invalid Money !"<<std::endl;
			return false;
		}
	}
	std::string filePath = Read(customer->getId());								// lấy id của đối tượng
	std::ifstream inFile(filePath);									// mở file, nhớ phải đóng file, không ăn cám đấy

	if (money == "0") {
		std::cout << "Please input the amount of money: ";
		std::cin >> money;
		for (int c = 0; c < money.size(); c++) {
			if (money[c] > '9' || money[c] < '0') {
				std::cout << "Invalid Money !" << std::endl;
				inFile.close();
				return false;
			}
		}
		if (stod(money) - 0 < 0) {										// kiểm soát tiền mà user đưa vào, nếu là số âm thì báo lỗi
			std::cout << "Invalid money !" << std::endl;
			inFile.close();
			return false;
		}
	}

	if (customer->getBalance() - stod(money) >= 0) {							// nếu đủ tiền				
		if (!transferCheck) {											// nếu đây chỉ là rút tiền mà không phải là transfer thì sẽ không cần kiểm tra
			if (!inFile.is_open()) {									// kiểm tra khả năng truy cập database
				std::cerr << "Something is wrong... Please Try Again Later !" << std::endl;
				inFile.close();
				return false;
			}
		}
		const double temp = customer->getBalance() - stod(money);
		customer->setBalance(temp);

		if (!transferCheck) {
			// update các thuộc tính của đối tượng lên database
			if (CreateFile(customer)) {			
				inFile.close();
				return true;
			}
			// update thất bại
			else {								
				inFile.close();
				return false;
			}
		}
		inFile.close();
		return true;
	}
	// nếu thiếu tiền
	else {											
		std::cout << "Not Enough Money!"<<std::endl;
		inFile.close();
		return false;
	}
	inFile.close();
	return true;
}
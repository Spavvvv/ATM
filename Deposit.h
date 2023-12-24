#pragma once
#include "Customer.h"
#include "CreateFile.h"
#include "ReadId.h"
#include <string>

bool Deposit(Customer* customer, std::string money, bool transferCheck) {
	std::string customerName = customer->getId();			// lấy id của đối tượng
	std::string filePath = Read(customerName);
	std::ifstream inFile(filePath);				// mo file

	if (!transferCheck) {											// nếu đây chỉ là thêm tiền mà không phải là transfer thì sẽ yêu cầu nhập User
		if (!inFile.is_open()) {
			std::cerr << "Something is wrong... Please Try Again Later !" << std::endl;		//cerr chỉ là cout nhưng mà nó k cần buffer, đại loại là có thể báo lỗi ngay cho dev	
			return false;
		}
		std::cout << "please input the money: ";
		std::cin >> money;

		for (int c = 0; c < money.size(); c++) {
			if (money[c] > '9' || money[c] < '0') {
				std::cout << "Invalid Money !" << std::endl;
				inFile.close();
				return false;
			}
		}

		if (stod(money) - 0 < 0) {
			std::cout << "Invalid money !";							// Kiểm soát tiền mà user đưa vào, nếu sai thì báo lỗi
			inFile.close();
			return false;
		}
	}

	const double newBalance = customer->getBalance() + stod(money);
	if (newBalance - 1000000000 > 0) {										// kiểm soát balance của đối tượng
		std::cout << "Your balance is exceed 1 Billion Dollars, please contact ADMIN to upgrade your account !" << std::endl;
		inFile.close();
		return false;
	}
	customer->setBalance(newBalance);									// thêm tiền vào đối tượng thành công

	if (!transferCheck) {											// nếu nó không phải transfer thì sẽ thông báo thành công hoặc thất bại
		if (CreateFile(customer)) {									// update thuộc tính của đối tượng lên database
			std::cout << "Deposit Successfully !" << std::endl;
			inFile.close();
			return true;
		}
		else {
			std::cout << "Server Down @@!" << std::endl;
			inFile.close();
			return false;
		}
	}
	inFile.close();
	return true;
}
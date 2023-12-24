#pragma once
#include "Customer.h"

void AccInfor(Customer* customer) {

	// lấy các thuộc tính của đối tượng, chỉ là các getter đơn giản
	std::cout << "Account ID: " << customer->getId() << std::endl;
	std::cout << "Account Balance: " << customer->getBalance() << std::endl;
	std::vector<std::string> tempVect = customer->getFriendlyAcc();


	// kiểm tra xem vector có phải rỗng không, nếu không rỗng thì in ra
	if (!tempVect.empty()) {	
		std::cout << "Friendly Accounts: " << std::endl;
		for (int c = 0; c < tempVect.size(); c++) {
			std::cout << tempVect[c] << std::endl;
		}
	}
}

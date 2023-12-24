#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Customer.h"
#include "ReadId.h"

bool CreateFile(Customer* customer) {

	std::string customerName = customer->getId();			// lấy id của đối tượng
	std::string filePath = Read(customerName);
	std::ofstream outFile(filePath);				// mo file
	if (!outFile.is_open()) {
		std::cerr << "Can't not open the file, please try again later !" << std::endl;
		return false;
	}
	else {
		outFile << customer->getPin() << " " << customer->getBalance() << std::endl;
		if (!customer->getFriendlyAcc().empty()) {							// Khi vector friendly có phần tử thì mới in vào file
			for (int c = 0; c < customer->getFriendlyAcc().size(); c++) {
				outFile << customer->getFriendlyAcc()[c] << std::endl;
			}
		}
		outFile.close();
		return true;
	}
	outFile.close();
	return true;
}

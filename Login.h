#pragma once
#include "Customer.h"
#include "ReadId.h"
#include <fstream>
#include <string>
#include <vector>


bool Login(Customer* User, const bool& isTransfer) {

	// Nhap ID tu ban phim
	std::string userName;
	if (!isTransfer) {
		std::cout << "ID: ";
		std::cin >> userName;
	}
	else {
		userName = User->getId();
	}

	// Tien hanh mo file trong database
	std::string filePath = Read(userName);
	std::fstream inFile(filePath);				// mo file

	if (!inFile.is_open()) {
		std::cerr << "No ID Found !" << std::endl;
		return false;
	}
	else {

		std::string PIN = "";
		if (!isTransfer) {
			std::cout << "PIN: ";
			std::cin >> PIN;
		}
		else {
			PIN = "000000";
		}
		if (PIN.size() == 6) {
			std::string line;
			getline(inFile, line);
			if (!isTransfer) {
				for (int c = 0; c < 6; c++) {
					if (line[c] != PIN[c]) {
						std::cout << "Wrong PIN !" << std::endl;
						inFile.close();
						return false;
					}
				}
			}
			else {
				PIN = "";
				for (int c = 0; c < 6; c++) {
					PIN += line[c];
				}
			}
			// tao balance
			std::string temp = "";
			for (int c = 7; c < line.size(); c++) {
				temp += line[c];
			}
			const double balance = stod(temp);

			// tạo vector để chứa friends List
			std::vector<std::string> List;
			while (getline(inFile, line)) {
				List.push_back(line);
			}

			// dung cac setter de gan gia tri cho doi tuong
			User->setId(userName);
			User->setPin(PIN);
			User->setBalance(balance);
			User->setFriendlyAcc(List);
			inFile.close();
			return true;
		}
	}
	inFile.close();
	return false;
}
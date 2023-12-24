#pragma once
#include "ReadId.h"
#include "Customer.h"
#include "CreateFile.h"
#include "Withdraw.h"
#include "Deposit.h"
#include "Login.h"
#include <string>
#include <vector>


bool Transfer(Customer* User1, std::string money, const std::string& Path) {
	// xét xem user2 id có tồn tại không bằng cách truy cập database và mở file có tên của customer
	std::string filePath = Read(Path);
	std::ifstream inFile(filePath);

	if (!inFile.is_open()) {							
		std::cerr << "No Account Found !" << std::endl;		
	}
	else {													
		// nếu user 2 có tồn tại thì đóng file
		inFile.close();
		if (Withdraw(User1, money, true)) {			// chuyển tiền trên đối tượng 1 thành công
			Customer* User2 = new Customer(Path);			// tạo đối tượng để nhận tiền, nhớ xoá đi không thì ăn đủ đấy
			const bool Session = Login(User2,true);

			if (!Session) {
				std::cout << "Something Went Wrong, please try again later !" << std::endl;
				User1->setBalance(User1->getBalance() + stod(money));
				return false;
			}

			// tạo cờ check Id có trong list friend chưa
			bool add = true;													

			// lấy danh sách bạn bè
			std::vector<std::string> friendlyAccs = User1->getFriendlyAcc();
			std::string idUser2 = User2->getId();

			if (friendlyAccs.size() != 0)									// kiểm tra xem vector có phần tử nào không
				for (int c = 0; c < friendlyAccs.size(); c++) {				// kiểm tra danh sách list friend
					if (friendlyAccs[c] == idUser2) {
						add = false;
						break;
					}
				}

			if (Deposit(User2, money, true)) {						//thêm tiền cho customer 2 thành công
				if (add && idUser2 != User1->getId()) {				// khi cờ (thêm bạn) == true và Id bạn khác với Id mình
					std::cout << "Do you want to add this account to your friendly account ? (Y/N)" << std::endl;
					char check;
					std::cin >> check;
					if (check == 'y' || check == 'Y') {
						User1->setEachFriendlyAcc(idUser2);
						CreateFile(User1);						// Update list friend và tiền của customer 1 lên database
					}
				}
				if (idUser2 == User1->getId()) {					// Nếu người dùng rảnh quá thích tự chuyển tiền cho chính mình :D
					User1->setBalance(User1->getBalance() + stod(money));
					User2->setBalance(User2->getBalance() - stod(money));
				}
				CreateFile(User1);								// đồng bộ customer 1 lên database
				CreateFile(User2);								// đồng bộ customer 2 lên database
				std::cout << "Transfer Complete !" << std::endl;	// giao dịch thành công
				delete User2;									// xoá đối tượng
				return true;
			}

			else {
				delete User2;									// xoá đối tượng
				std::cout << "Something Went Wrong.. Please Try Again Later !";		// nhận tiền thất bại thì database sẽ không được update
				return false;
			}
		}

		else {																// nếu chuyển tiền thất bại
			std::cout << "Something Went Wrong.. Please Try Again Later !";
			return false;
		}
	}
	inFile.close();
	return false;
}
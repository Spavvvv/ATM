#pragma once
#include "Customer.h"
#include "Login.h"
#include "Register.h"
#include "AccInfor.h"
#include "Deposit.h"
#include "Withdraw.h"
#include "TransferOpt.h"
#include "WithdrawOpt.h"
#include <string>


class ATM {
private:
	Customer* User;
	bool SessionLogin;
public:
	//tạo các giá trị mặc định
	ATM(Customer* User_ = new Customer, bool SessionLogin_ = false) : User(User_), SessionLogin(SessionLogin_) {}

	// Hiển thị giao diện ATM
	void mainMenu() {
		std::cout << "------------------ Super Vjp Pro Bank ------------------" << std::endl;
		std::cout << "1. Login" << std::endl;
		std::cout << "2. Register" << std::endl;
		std::cout << "3. Exit" << std::endl;
		int Selection;
		std::cout << "Please input your option: ";
		std::cin >> Selection;
		switch (Selection)
		{
		case 1:
			clearConsole();
			loginScreen();								// Đưa đến màn hình login
			break;
		case 2:
			clearConsole();
			registerScreen();							// Đưa đến màn hình đăng kí
			break;
		case 3:
			std::cout << "Wish you have a good day !"<<std::endl;		// Thoát
			break;
		default:
			std::cout << "Invalid Choice !"<<std::endl;			// Báo khi user nhập sai hoặc cố tình nhập sai option
			mainMenu();
			break;
		}
	}

	// Quản lí người dùng
	void registerScreen() {
		if (Register(User)) {
			clearSession(User,SessionLogin);
			std::cout << "Registed Successfully !" << std::endl;
			std::system("pause");
			clearConsole();
			mainMenu();
		}
		else {
			std::cout << "Invalid PIN !" << std::endl;
			mainMenu();						// đăng kí thất bại, đưa về màn hình bắt đầu
		}
	}
	void loginScreen() {
		if (Login(User,false)) {
			SessionLogin = true;
			std::cout << "Login Successfully!" << std::endl;
			std::system("pause");
			clearConsole();
			functionScreen(User, SessionLogin);
		}
		else {
			std::cout << "Login Failed !" << std::endl;
			std::system("pause");
			clearConsole();
			mainMenu();
		}
	}

	// Hiển thị giao diện chức năng của ATM
	void functionScreen(Customer* User, bool& SessionLogin) {
		if (SessionLogin) {
			std::cout << "1. Account Information" << std::endl;
			std::cout << "2. Withdraw Money" << std::endl;
			std::cout << "3. Deposit money" << std::endl;
			std::cout << "4. Transfer money" << std::endl;
			std::cout << "5. Logout" << std::endl;
			std::string money = "";			// money được cấp phát động, nhớ xoá khi dùng xong, không thì ăn đủ đấy
			int selection;
			std::cin >> selection;
			switch (selection)
			{
			case 1:
				AccInfor(User);					// lấy thông tin khách
				std::system("pause");
				clearConsole();
				functionScreen(User, SessionLogin);
				break;
			case 2:
				WithdrawOpt(User, money);		// đưa đến màn hình rút tiền với lựa chọn
				std::system("pause");
				clearConsole();
				functionScreen(User, SessionLogin);
				break;
			case 3:
				Deposit(User, money, false);		// đưa đến màn hình thêm tiền
				std::system("pause");
				clearConsole();
				functionScreen(User, SessionLogin);
				break;
			case 4:
				TransferOpt(User, money);			// đưa đến hàm lựa chọn chuyển tiền
				std::system("pause");
				clearConsole();
				functionScreen(User, SessionLogin);
				break;
			case 5:						
				clearSession(User, SessionLogin);				// hết login
				clearConsole();						// làm sạch màn hình console
				mainMenu();							// đưa về màn hình bắt đầu
				break;
			default:
				break;
			}
		}
		else {
			std::cout << "Invalid login!" << std::endl;
			mainMenu();
		}
	}
	
	//Hàm huỷ khi thoát chương trình, phải xoá User đi
	~ATM() {
		delete User;
		std::cout << "------------------ Super Vjp Pro Bank ------------------" << std::endl;
	}

	// Một số hàm phụ
	void clearConsole() {
		std::cout << "\x1B[2J\x1B[H";		// cái này có thể dùng std::system("cls") nhưng mà như này có vẻ mới hơn..

	}
	void clearSession(Customer *User, bool& SessionLogin) {
		SessionLogin = false;
		User->setBalance(0);
		User->setId("");
		User ->setPin("");
		User->setFriendlyAcc({});
	}
};
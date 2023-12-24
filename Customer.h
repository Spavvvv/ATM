#pragma once
#include <iostream>
#include <string>
#include <vector>

class Customer {
private:
	std::string id;
	std::string Pin;
	double Balance;
	std::vector<std::string> friendlyAcc;
public:
	Customer(const std::string& id_ = "", std::string Pin_ = "", double Balance_ = 0, const std::vector<std::string>& friendlyAccs_ = {})
		: id(id_), Pin(Pin_), Balance(Balance_), friendlyAcc(friendlyAccs_) {
		// Các xử lý khởi tạo khác tùy thuộc vào tham số đầu vào
	}

	void setId(const std::string& id_) {			// đoạn này là tạo các getter
		id = id_;
	}
	void setPin(const std::string& Pin_) {
		Pin = Pin_;
	}
	void setBalance(const double& Balance_) {
		Balance = Balance_;
	}
	void setEachFriendlyAcc(const std::string& friendlyAcc_) {
		friendlyAcc.push_back(friendlyAcc_);
	}
	void setFriendlyAcc(const std::vector<std::string>& friendlyAccs_) {
		friendlyAcc = friendlyAccs_;
	}


	std::string getId() const {					// đoạn này là các setter
		return id;
	}
	std::string getPin() const {
		return Pin;
	}
	double getBalance() const {
		return Balance;
	}
	std::vector<std::string> getFriendlyAcc() const {
		return friendlyAcc;
	}

	~Customer() {				// hàm huỷ, đoạn này thêm mới để debug code 
		//std::cout << "the object has been delete !" << std::endl;
		if (!friendlyAcc.empty()) {
			friendlyAcc.clear();
		}
	}


};
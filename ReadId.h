#pragma once
#include <string>

std::string Read(std::string User) {
	std::string filePath = "C:\\Users\\tiend\\source\\repos\\ATM ver2\\ATM ver2\\Customer Data\\" + User + ".txt"; // trả lại đường dẫn đến file thôi
	return filePath;
}

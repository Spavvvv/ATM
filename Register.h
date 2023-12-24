#pragma once
#include "Customer.h"
#include "CreateFile.h"
#include <random>

bool Register(Customer* customer) {
    // Lấy Random ID dựa trên phân phối chuẩn
    std::string userName;
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::mt19937_64 rng{ std::random_device{}() };
    std::uniform_int_distribution<std::size_t> distribution(0, characters.size() - 1);

    for (int i = 0; i < 10; ++i) {
        userName += characters[distribution(rng)];
    }

    // Show ID cho người dùng và bắt đầu tạo PIN
    std::cout << "Your ID: " << userName << std::endl;
    std::cout << "Please input your PIN (6 numbers): ";
    std::string PIN = "";
    std::cin >> PIN;
    if (PIN.size() == 6)
        for (int c = 0; c < 6; c++) {
            if (PIN[c] < '0' || PIN[c] > '9')
                return false;
        }
    else
        return false;

        customer->setId(userName);                      // Set các giá trị cho Id
        customer->setPin(PIN);                          // Set các giá trị cho PIN
        customer->setBalance(0);                        // Set các giá trị cho balance
        if (CreateFile(customer)) {
            return true;
        }
        else {
            return false;
        }
    return false;
}
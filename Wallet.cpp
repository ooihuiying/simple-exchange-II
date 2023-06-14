//
// Created by Hui Ying Ooi on 13/6/23.
//

#include <iostream>
#include "Wallet.h"
Wallet::Wallet() {

}

void Wallet::insertCurrency(std::string type, double amount){
    double balance;
    if(amount < 0){
        throw std::exception{};
    }
    if(currencies.count(type) == 0){
        balance = 0;
    } else {
        balance = currencies[type];
    }
    currencies[type] = balance + amount;
}

// Check if the wallet contains this much currency or more
bool Wallet::containsCurrency(std::string type, double amount){
    if(currencies.count(type) == 0){
        return false;
    }
    return currencies[type] >= amount;
}

bool Wallet::removeCurrency(std::string type, double amount) {
    if(amount < 0){
        return false;
    }
    if(currencies.count(type) == 0){
        std::cout << "No currency for " << type << std::endl;
        return false;
    }
    if(!containsCurrency(type, amount)){
        // not enough money
        return false;
    }
    std::cout << "Removing " << type << " " << amount << std::endl;
    currencies[type] -= amount;
    return true;
}

std::string Wallet::toString() {
    std::string s;
    for(std::pair<std::string, double> pair: currencies){
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) + "\n";
    }
    return s;
}

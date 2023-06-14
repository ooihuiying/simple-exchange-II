//
// Created by Hui Ying Ooi on 13/6/23.
//

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

std::string Wallet::toString() {
    return "hi";
}

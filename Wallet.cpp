//
// Created by Hui Ying Ooi on 13/6/23.
//

#include <iostream>
#include "Wallet.h"
#include "CSVReader.h"

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

bool Wallet::canFulfillOrder(OrderBookEntry order){
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    if(order.orderType == OrderBookType::ask){
        double amount = order.amount;
        std::string currency = currs[0];
        std::cout << "Wallet::canFulfillOrder ask" << currency << " " << amount;
        return containsCurrency(currency, amount);
    }
    if(order.orderType == OrderBookType::bid){
        double amount = order.amount * order.price;
        std::string currency = currs[1];
        std::cout << "Wallet::canFulfillOrder bid " << currency << " " << amount;
        return containsCurrency(currency, amount);
    }
    return false;
}

void Wallet::processSale(OrderBookEntry& sale){
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');
    if(sale.orderType == OrderBookType::asksale){
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];

        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
    if(sale.orderType == OrderBookType::bid){
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];

        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
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

//
// Created by Hui Ying Ooi on 13/6/23.
//

#ifndef TRADING_ENGINE_WALLET_H
#define TRADING_ENGINE_WALLET_H

#include <string>
#include <map>

class Wallet {
public:
    Wallet();
    // Insert currency into the wallet
    void insertCurrency(std::string type, double amount);
    // Check if the wallet contains this much currency or more
    bool containsCurrency(std::string type, double amount);
    bool removeCurrency(std::string type, double amount);
    // Generate a string representation of the wallet
    std::string toString();

private:
    std::map<std::string, double> currencies;
};


#endif //TRADING_ENGINE_WALLET_H

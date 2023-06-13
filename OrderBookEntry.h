//
// Created by Hui Ying Ooi on 10/6/23.
//
#include <iostream>
#include <string>

#ifndef TRADING_ENGINE_ORDERBOOKENTRY_H
#define TRADING_ENGINE_ORDERBOOKENTRY_H

enum OrderBookType{bid, ask, unknown};

class OrderBookEntry{
private:
    double price;
    double amount;
    std::string timestamp{};
    std::string product{};

public:
    OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _orderType);
    static OrderBookType stringToOrderBookType(std::string s);
    OrderBookType orderType;
};


#endif //TRADING_ENGINE_ORDERBOOKENTRY_H

//
// Created by Hui Ying Ooi on 10/6/23.
//
#include <iostream>
#include <string>

#ifndef TRADING_ENGINE_ORDERBOOKENTRY_H
#define TRADING_ENGINE_ORDERBOOKENTRY_H

enum OrderBookType{bid, ask};

class OrderBookEntry{
private:
    double price;
    double amount;
    std::string timestamp{};
    std::string product{};
    OrderBookType orderType;
public:
    OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _orderType);

};


#endif //TRADING_ENGINE_ORDERBOOKENTRY_H

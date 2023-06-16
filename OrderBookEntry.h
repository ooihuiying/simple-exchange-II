//
// Created by Hui Ying Ooi on 10/6/23.
//
#include <iostream>
#include <string>

#ifndef TRADING_ENGINE_ORDERBOOKENTRY_H
#define TRADING_ENGINE_ORDERBOOKENTRY_H

enum OrderBookType{bid, ask, unknown, asksale, bidsale};

class OrderBookEntry{
public:
    OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _orderType, std::string username="dataset");
    static OrderBookType stringToOrderBookType(std::string s);
    static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2){
        return e1.timestamp < e2.timestamp;
    }
    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2){
        return e1.price < e2.price;
    }
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2){
        return e1.price > e2.price;
    }

    OrderBookType orderType;
    double amount;
    std::string product{};
    double price;
    std::string username;
    std::string timestamp{};
};


#endif //TRADING_ENGINE_ORDERBOOKENTRY_H

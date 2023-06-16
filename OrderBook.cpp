//
// Created by Hui Ying Ooi on 16/6/23.
//

#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>
#include <iostream>

OrderBook::OrderBook(std::string filename){
    orders = CSVReader::readCSV(filename);
}

// Return vector of all known products in the dataset
std::vector<std::string> OrderBook::getKnownProducts() {
    std::vector<std::string> products;

    std::map<std::string, bool> prodMap;

    for(OrderBookEntry& e: orders){
        prodMap[e.product] = true;
    }

    // Now flatten the map into a vector of strings
    for(auto const& e: prodMap){
        products.push_back(e.first);
    }

    return products;
}

// return vector of Orders according to the sent filters
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp){
    std::vector<OrderBookEntry> orders_sub;
    for(OrderBookEntry& e: orders){
        if(e.orderType == type && e.product == product && e.timestamp == timestamp){
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders) {
    double max = orders[0].price;
    for(OrderBookEntry& e: orders){
        if(e.price > max) max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders){
    double min = orders[0].price;
    for(OrderBookEntry& e: orders){
        if(e.price < min) min = e.price;
    }
    return min;
}

std::string OrderBook::getEarliestTime() {
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp) {
    std::string next_timestamp = "";
    for(OrderBookEntry& e: orders){
        if(e.timestamp > timestamp){
            next_timestamp = e.timestamp;
            break;
        }
    }
    if(next_timestamp == ""){
        next_timestamp = orders[0].timestamp;
    }
    return next_timestamp;
}

void OrderBook::insertOrder(OrderBookEntry &order) {
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) {
    // asks = orderbook.ask
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    // bids = orderbook.bids
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    // sales = []
    std::vector<OrderBookEntry> sales;

    // sort asks lowest first
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    // sort bids highest first
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
    // For ask in asks
    std::cout << "max ask " << asks[asks.size()-1].price << std::endl;
    std::cout << "min ask " << asks[0].price << std::endl;
    std::cout << "max bid " << bids[0].price << std::endl;
    std::cout << "min bid " << bids[bids.size()-1].price << std::endl;

    for(OrderBookEntry& ask: asks){
        for(OrderBookEntry& bid: bids){
            if(bid.price >= ask.price){
                std::cout << "bid price is right " << std::endl;

                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::sale};

                if(bid.amount == ask.amount){
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }

                if(bid.amount > ask.amount){
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }

                if(bid.amount < ask.amount){
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }

    return sales;

}
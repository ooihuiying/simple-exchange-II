//
// Created by Hui Ying Ooi on 10/6/23.
//

#ifndef TRADING_ENGINE_MERKELMAIN_H
#define TRADING_ENGINE_MERKELMAIN_H


#include "OrderBookEntry.h"
#include "Wallet.h"
#include "OrderBook.h"

class MerkelMain{
public:
    MerkelMain();
    /** Call this to start **/
    void init();
private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void goToNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);

    std::string currentTime;

    OrderBook orderBook{"data.csv"};

    Wallet wallet;
};



#endif //TRADING_ENGINE_MERKELMAIN_H

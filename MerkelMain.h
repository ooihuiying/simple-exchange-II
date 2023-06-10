//
// Created by Hui Ying Ooi on 10/6/23.
//

#ifndef TRADING_ENGINE_MERKELMAIN_H
#define TRADING_ENGINE_MERKELMAIN_H


class MerkelMain{
public:
    MerkelMain();
    /** Call this to start **/
    void init();
private:
    void loadOrderBook();
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterOffer();
    void enterBid();
    void printWallet();
    void goToNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);
};



#endif //TRADING_ENGINE_MERKELMAIN_H

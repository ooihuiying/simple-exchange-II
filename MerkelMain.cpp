//
// Created by Hui Ying Ooi on 10/6/23.
//

#include "MerkelMain.h"
#include <iostream>
#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain() {

}

void MerkelMain::init(){
    int input;
    currentTime = orderBook.getEarliestTime();
    while(true){
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}


void MerkelMain::printMenu() {
    // print help
    std::cout << "1. Help " << std::endl;
    // print exchange stats
    std::cout << "2. Print exchange stats " << std::endl;
    // make an offer
    std::cout << "3. Make an offer " << std::endl;
    // make a bid
    std::cout << "4. Make a bid " << std::endl;
    // print wallet
    std::cout << "5. Print Wallet " << std::endl;
    // continue
    std::cout << "6. Continue " << std::endl;

    std::cout << "===============" << std::endl;
    std::cout << "Current time is: " << currentTime << std::endl;
    std::cout << "Type in 1-6" << std::endl;
}

void MerkelMain::printHelp() {
    std::cout << "Help - Your aim is to make money. Analyse the market and make bids and offers." << std::endl;
}

void MerkelMain::printMarketStats(){
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                  p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
    }
}

void MerkelMain::enterAsk(){
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if(tokens.size() != 3){
        std::cout << "MerkelMain::enterOffer Bad input! " << input << std::endl;
        return;
    } else {
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);
            if(wallet.canFulfillOrder(obe)){
                std::cout << "Wallet looks good. " <<std::endl;
                orderBook.insertOrder(obe);
            } else {
                std::cout << "Wallet has insufficient funds. " << std::endl;
            }
        } catch(const std::exception& e){
            std::cout << "MerkelMain::enterOffer Bad input " << std::endl;
        }
    }
    std::cout << "You typed: " << input << std::endl;

}

void MerkelMain::enterBid(){
    std::cout << "Make a bid - enter amount" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if(tokens.size() != 3){
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
        return;
    }
    try{
        OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);
        if(wallet.canFulfillOrder(obe)){
            std::cout << "Wallet looks good. " <<std::endl;
            orderBook.insertOrder(obe);
        } else {
            std::cout << "Wallet has insufficient funds. " << std::endl;
        }
    } catch(const std::exception& e){
        std::cout << "MerkelMain::enterBid Bad input " << std::endl;
    }
}

void MerkelMain::printWallet(){
    std::cout << "Your wallet is: " << wallet.toString() << std::endl;
}

void MerkelMain::goToNextTimeframe(){
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string& p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption(){
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-6" << std::endl;
    std::getline(std::cin, line);
    try{
        userOption = std::stoi(line);
    }catch(const std::exception& e)
    {
        //
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}


void MerkelMain::processUserOption(int userOption){
    if (userOption == 0) {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1) {
        printHelp();
    }
    if (userOption == 2) {
        printMarketStats();
    }
    if (userOption == 3) {
        enterAsk();
    }
    if (userOption == 4) {
        enterBid();
    }
    if (userOption == 5) {
        printWallet();
    }
    if (userOption == 6) {
        goToNextTimeframe();
    }
}

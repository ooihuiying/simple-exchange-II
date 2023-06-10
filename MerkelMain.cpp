//
// Created by Hui Ying Ooi on 10/6/23.
//

#include "MerkelMain.h"
#include <iostream>
#include<vector>
#include "OrderBookEntry.h"

MerkelMain::MerkelMain() {

}

void MerkelMain::init(){
    int input;
    while(true){
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::loadOrderBook() {

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
    std::cout << "Type in 1-6" << std::endl;
}

void MerkelMain::printHelp() {
    std::cout << "Help - Your aim is to make money. Analyse the market and make money." << std::endl;
}

void MerkelMain::printMarketStats(){
    std::cout << "Market looks good" << std::endl;
}

void MerkelMain::enterOffer(){
    std::cout << "Mark and offer - enter amount" << std::endl;
}

void MerkelMain::enterBid(){
    std::cout << "Make a bid - enter amount" << std::endl;
}

void MerkelMain::printWallet(){
    std::cout << "Your wallet is empty." << std::endl;
}

void MerkelMain::goToNextTimeframe(){
    std::cout << "Going to the next time frame" << std::endl;
}

int MerkelMain::getUserOption(){
    int userOption;
    std::cin >> userOption;
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
        enterOffer();
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

//
// Created by Hui Ying Ooi on 13/6/23.
//

#ifndef TRADING_ENGINE_CSVREADER_H
#define TRADING_ENGINE_CSVREADER_H
#include <vector>
#include <string>
#include "OrderBookEntry.h"

class CSVReader {

private:
    static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
public:
    CSVReader();
    static std::vector<OrderBookEntry> readCSV(std::string csvFile);

    static std::vector<std::string> tokenise(std::string csvLine, char separator);

    static OrderBookEntry stringsToOBE(std::string price,
                                       std::string amount,
                                       std::string timestamp,
                                       std::string product,
                                       OrderBookType OrderBookType);
};


#endif //TRADING_ENGINE_CSVREADER_H

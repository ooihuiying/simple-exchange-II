//
// Created by Hui Ying Ooi on 13/6/23.
//

#ifndef TRADING_ENGINE_CSVREADER_H
#define TRADING_ENGINE_CSVREADER_H
#include <vector>
#include <string>
#include "OrderBookEntry.h"

class CSVReader {
public:
    CSVReader();
    static std::vector<OrderBookEntry> readCSV(std::string csvFile);

private:
    static std::vector<std::string> tokenise(std::string csvLine, char separator);
    static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};


#endif //TRADING_ENGINE_CSVREADER_H

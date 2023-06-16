//
// Created by Hui Ying Ooi on 13/6/23.
//

#include "CSVReader.h"
#include <fstream>
#include <sstream>

CSVReader::CSVReader() {}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName){
    std::stringstream ss;
    ss << __FILE__; // to retrieve the full path to the current source fil
    std::string currentFile = ss.str();
    std::string currentDir = currentFile.substr(0, currentFile.find_last_of("/\\"));
    std::cout << csvFileName  << " " << currentDir+csvFileName << " " << std::endl;

    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile{ currentDir+csvFileName};
    std::string line;
    if(csvFile.is_open()){
        while(std::getline(csvFile, line)){
            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            } catch (const std::exception& e){
                std::cout << "CSVReader::readCSV bad data" << std::endl;
            }

        }// end of while
    }
    std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << std::endl;
    return entries;

}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator){
    std::vector<std::string> tokens;
    signed int start, end;
    start = csvLine.find_first_not_of(separator, 0);
    std::string token;
    do{
        end = csvLine.find_first_of(separator, start);
        if(start == csvLine.length() || start == end) break;
        if(end >= 0) token = csvLine.substr(start, end-start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while(end>0);

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens){

    double price, amount;
    if(tokens.size() != 5){
        throw std::exception{};
    }

    try{
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    } catch (std::exception& e){
        std::cout << "Bad float! " << tokens[3] << std::endl;
        std::cout << "Bad float! " << tokens[4] << std::endl;
        throw;
    }

    OrderBookEntry obe{price,amount,tokens[0],tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::string priceString,
                                       std::string amountString,
                                       std::string timestamp,
                                       std::string product,
                                       OrderBookType orderType)
{
    double price, amount;
    try {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }catch(const std::exception& e){
        std::cout << "CSVReader::stringsToOBE Bad float! " << priceString<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << amountString<< std::endl;
        throw;
    }
    OrderBookEntry obe{price,
                       amount,
                       timestamp,
                       product,
                       orderType};

    return obe;
}
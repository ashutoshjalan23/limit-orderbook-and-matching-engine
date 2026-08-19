#ifndef TRADE_H
#define TRADE_H

#include<string>
#include<vector>

struct Trade{
     int price;
     int qty;
     std::string sid;
     std::string bid;

};

std::vector<Trade> Tradebook;



#endif
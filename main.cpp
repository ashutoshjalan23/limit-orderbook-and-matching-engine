#include<iostream>
#include<map>
#include<unordered_map>
#include<utility>
#include<list>
#include<string>
#include<cstdint>
#include<iterator>
#include<vector>
#include "order.h"
#include "trade.h"
#include "orderbook.h"







int main(){
    OrderBook book;

    Order s1("s1",0,101.00,5);
    Order s2("s2",0,102.00,10);
    Order s3("s3",0,103.00,20);
    book.add(s1);
    book.add(s2);
    book.add(s3);

    Order rb1("rb1",1,95.00,20);
    Order rb2("rb2",1,94.00,15);
    book.add(rb1);
    book.add(rb2);

    std::cout<<"===== BEFORE ====="<<std::endl;
    book.printBook();

    Order b1("b1",1,102.00,12);
    std::cout<<"\nsubmitting b1 BUY 12 @ 102"<<std::endl;
    book.placeOrder(b1);

    std::cout<<"\n===== AFTER b1 ====="<<std::endl;
    book.printBook();

    Order sell1("sell1",0,90.00,10);
    std::cout<<"\nsubmitting sell1 SELL 10 @ 90"<<std::endl;
    book.placeOrder(sell1);

    std::cout<<"\n===== AFTER sell1 ====="<<std::endl;
    book.printBook();

    Order noMatch("nm1",1,80.00,5);
    std::cout<<"\nsubmitting nm1 BUY 5 @ 80"<<std::endl;
    book.placeOrder(noMatch);

    std::cout<<"\n===== AFTER nm1 ====="<<std::endl;
    book.printBook();

    std::cout<<"\n===== TRADES ====="<<std::endl;
    for(auto t:Tradebook){
        std::cout<<t.qty<<" @ "<<t.price<<" buyer="<<t.bid<<" seller="<<t.sid<<std::endl;
    }

    return 0;
}
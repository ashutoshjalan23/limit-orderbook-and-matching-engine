#ifndef ORDERBOOK_H
#define ORDERBOOK_H

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
class OrderBook{
private:
std::map<int64_t, std::list<Order>> askBook;  
std::map<int64_t, std::list<Order>, std::greater<int64_t>> bidBook; 

std::unordered_map<std::string, std::pair<std::list<Order>::iterator,std::pair<int64_t,int>>> uid_lookup;

public:
    OrderBook(){

    }
     
    void add( const Order& order){
        int64_t price=order.getPrice();
         std::list<Order>::iterator it;

         std::list<Order>::iterator endBID=(this->bidBook)[price].end();
          std::list<Order>::iterator endASK=(this->askBook)[price].end();


        if(order.getType()){
        it= (this->bidBook)[price].insert(endBID,order);

        }
        else{
             it= (this->askBook)[price].insert(endASK,order);
        }

        std::string uid=order.getUID();
        uid_lookup[uid]={it,{price,order.getType()}};
    }

void printBook() const{

    for(const auto& it: bidBook){
       const auto& l= it.second;
        for(const Order& order:l){
            order.printOrder();
        }
    }

for(const auto& it: askBook){
        const auto& l= it.second;
        for(const Order& order:l){
            order.printOrder();
        }
    }

}

    bool cancel(const std::string& uid) {
        if(uid_lookup.count(uid)){
        auto& info=uid_lookup[uid];
        auto& it=info.first;
        auto s2=info.second;
        auto price=s2.first;
        auto type=s2.second;
            
        if(type){
            auto& book=bidBook[price];
            book.erase(it);
            if(book.empty()){
                bidBook.erase(price);
            }
        }
        else{
            auto& book=askBook[price];
            book.erase(it);
            if(book.empty()){   
                askBook.erase(price);
            }
        }
        uid_lookup.erase(uid);

        return true;
    }
    else{
        return false;
    }
    }

    void placeOrder(Order& order){
            bool type= order.getType();
            int64_t price=order.getPrice();
            if(type) {  //buy
                std::map<int64_t,std::list<Order>>::iterator it=askBook.begin();
                while(it!=askBook.end() && price>=it->first && order.getQty() >0 ){
                        std::list<Order>::iterator it2=(it->second).begin();
                       
                        while(it2!=(it->second).end() && order.getQty()>0){
                        int qty_traded=std::min(order.getQty() ,it2->getQty() );
                        it2->canOrder(qty_traded);
                        order.canOrder(qty_traded);

                        Trade t;
                        t.price=(double)it->first/scale;
                        t.qty=qty_traded;
                        t.sid=it2->getUID();
                        t.bid=order.getUID();
                         Tradebook.push_back(t);

                        if(it2->getQty()<=0){
                            std::string suid=it2->getUID();
                            uid_lookup.erase(suid);
                         it2=(it->second).erase(it2);
                         continue;
                        }
                        it2++;
                    }
                    if(it->second.empty()){
                        it=askBook.erase(it);
                        continue;
                    }
                    it++;
                }
           if(order.getQty()>0){
            this->add(order);
           }

            }
            else{
                std::map<int64_t,std::list<Order>>::iterator it=bidBook.begin();

  while(it!=bidBook.end() && price<=it->first && order.getQty() >0 ){
                        std::list<Order>::iterator it2=(it->second).begin();
                       
                        while(it2!=(it->second).end() && order.getQty()>0){
                        int qty_traded=std::min(order.getQty() ,it2->getQty() );
                        it2->canOrder(qty_traded);
                        order.canOrder(qty_traded);

                        Trade t;
                        t.price=(double)(it->first)/scale;
                        t.qty=qty_traded;
                        t.bid=it2->getUID();
                        t.sid=order.getUID();
                        Tradebook.push_back(t);


                        if(it2->getQty()<=0){
                               std::string buid=it2->getUID();
                            uid_lookup.erase(buid);
                         it2=(it->second).erase(it2);
                         continue;
                        }
                        it2++;
                    }
                    if(it->second.empty()){
                        it=bidBook.erase(it);
                        continue;
                    }
                    it++;
                }
           if(order.getQty()>0){
            this->add(order);
           }

                



            }
    }

};


#endif
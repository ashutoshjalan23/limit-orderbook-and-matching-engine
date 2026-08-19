#ifndef ORDER_H
#define ORDER_H
#include<iostream>
#include<string>
#include<cstdint>
const int64_t scale=1e5;



class Order{
private:
    std::string uid;
    bool type; //0 for sell and 1 for buy
    int64_t price;
    int original_quantity;
    int remaining_quantity;
   
  
public:


    Order(std::string uid, bool type,double price,int quantity){
        this->uid=uid;
        this->type=type;
        this->price=price*scale;
        this->original_quantity=quantity;
        this->remaining_quantity=quantity;
         


    }

    bool canOrder(int quantity)  {
        if(quantity<=this->remaining_quantity){
            remaining_quantity-=quantity;
            return true;
        }
        else return false;

    }

    int64_t getPrice() const {
        return this->price;
    }
    int getQty() const {
        return this->remaining_quantity;
    }

    bool getType() const {
        return this->type;
    }
    
    std::string getUID() const {
        return this->uid;
    }



    void printOrder() const {
        std::string type;
        if(this->type){
            type="BID";
        }
        else type="ASK";
        std::cout<<"TYPE: "<<type<<std::endl;
        std::cout<<"Price: "<<(this->price)/scale<<std::endl;
        std::cout<<"Quantity: "<<this->remaining_quantity<<std::endl;
    }


    };
#endif
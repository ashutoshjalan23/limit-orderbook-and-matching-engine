#include<iostream>
#include<string>
#include<map>
#include<list>
#include<iterator>
#include<unordered_map>
#include<utility>
const int64_t scale =1e6;

class Order{
private:
    std::string uid;
    bool type; //0 for sell and 1 for buy
    int64_t price;
    int original_quantity;
    int remaining_quantity;
     int64_t current_seq;
  
public:
   static int64_t counter;

    Order(std::string uid, bool type,double price,int quantity){
        this->uid=uid;
        this->type=type;
        this->price=price*scale;
        this->original_quantity=quantity;
        this->remaining_quantity=quantity;
         
        counter++;
        this->current_seq=counter;

    }

    bool canOrder(int quantity) const {
        if(quantity<=this->remaining_quantity){
          
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

    int64_t getSequence() const{
        return this->current_seq;
    }

    void printOrder() const {
        std::cout<<"TYPE: "<<this->type<<std::endl;
        std::cout<<"Price: "<<(this->price)/scale<<std::endl;
        std::cout<<"Quantity: "<<this->remaining_quantity<<std::endl;
    }


    };



int64_t Order::counter =0;



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

};

int main(){
    OrderBook book;

    Order b1("bid_100_a", 1, 100.00, 10);
    Order b2("bid_100_b", 1, 100.00, 5);
    Order b3("bid_101",   1, 101.00, 7);

    Order a1("ask_102", 0, 102.00, 8);
    Order a2("ask_101", 0, 101.00, 3);

    book.add(b1);
    book.add(b2);
    book.add(b3);
    book.add(a1);
    book.add(a2);

    std::cout << "----- Before cancel -----" << std::endl;
    book.printBook();

    // Cancel one of the two orders sharing a price level.
    bool result1 = book.cancel("bid_100_a");
    std::cout << "\ncancel(bid_100_a) returned: " << result1 << std::endl;

    // Cancel the ONLY order at its price level - should also remove the empty level.
    bool result2 = book.cancel("ask_101");
    std::cout << "cancel(ask_101) returned: " << result2 << std::endl;

    // Cancel something that doesn't exist - should fail gracefully.
    bool result3 = book.cancel("does_not_exist");
    std::cout << "cancel(does_not_exist) returned: " << result3 << std::endl;

    // Try cancelling the same uid twice - second call should fail, not crash.
    bool result4 = book.cancel("bid_100_a");
    std::cout << "cancel(bid_100_a) AGAIN returned: " << result4 << std::endl;

    std::cout << "\n----- After cancels -----" << std::endl;
    book.printBook();

    return 0;
}
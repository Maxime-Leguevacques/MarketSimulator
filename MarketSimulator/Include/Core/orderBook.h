#pragma once
#include <map>


struct SOrder
{
    int id;
    double price;
    int quantity;
};


class OrderBook
{
private:
    // map is composed with <price, count>
    std::map<double, unsigned int, std::greater<unsigned int>> bids_;
    std::map<double, unsigned int> asks_;
        
public:
    OrderBook();
    ~OrderBook();

public:
    void Update();
    
    void AddBid(unsigned int _id, double _price, unsigned int _quantity);
    void AddAsk(unsigned int _id, double _price, unsigned int _quantity);

    void Print();
};

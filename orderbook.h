
#pragma once
#include "order.h"
#include <cstdint>
#include <deque>
#include <map>

class Orderbook {
    public:
        void addOrder(Order order);
        float_t bestBid() const;
        float_t bestAsk() const;
        float_t spread() const;
        void print() const;


    private:
        struct PriceLevel {
                std::deque<Order> orders;
                uint16_t qty;
        };
        
        std::map<float_t, PriceLevel, std::greater<double>> bids;
        std::map<float_t, PriceLevel> asks;

        void matchOrders(Order &order);
        void fillOrder(Order &incoming, PriceLevel &level); 
};

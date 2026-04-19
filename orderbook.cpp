#include "orderbook.h"
#include "order.h"
#include <iostream>
#include "raylib.h"

float_t Orderbook::bestBid() const {
   float_t bb = bids.begin()->first;
   return bb;
}

float_t Orderbook::bestAsk() const {
    float_t ba = asks.begin()->first;
    return ba;
}

float_t Orderbook::spread() const {
    float_t spread = bestAsk() - bestBid();
    return spread;
}


void Orderbook::fillOrder(Order &order, PriceLevel &level) {
    Order &front = level.orders.front();
    // Order qty > first level 
    if (order.qty >= front.qty) {
        order.qty -= front.qty;
        level.qty -= front.qty;
        level.orders.pop_front();
    }
    else {
        front.qty -= order.qty;
        level.qty -= order.qty;
        order.qty = 0;
    }
}    
void Orderbook::matchOrders(Order &order) {
    if (order.o_type == OType::MKT) {
        if (order.side == 'b') {
            while (!asks.empty() && order.qty > 0) {
                auto best = asks.begin(); // bestAsks/Bids was being called once in fillOrder and then again in the if statement to erase the level, causing the orderbook to cascaade
                fillOrder(order, best->second);
                if (best->second.qty == 0) {
                    asks.erase(best);
                }
            }
        }
        else {  // Ask order side
            while (!bids.empty() && order.qty > 0) {
                auto best = bids.begin();
                fillOrder(order, best->second);
                if (best->second.qty == 0) {
                    bids.erase(best);
                }
            }
        }
    }
    else { // LMT OType
        if (order.side == 'b') {
            while (!asks.empty() && order.price >= bestAsk() && order.qty > 0) {
                auto best = asks.begin();
                fillOrder(order, best->second);
                if (best->second.qty == 0) {
                    asks.erase(best);
                }

            }
        }
        else {
            while (!bids.empty() && order.price <= bestBid() && order.qty > 0) {
                    auto best = bids.begin();
                    fillOrder(order, best->second);
                    if (best->second.qty == 0) {
                        bids.erase(bestBid());
                }

            }
        }
    }
}

void Orderbook::addOrder(Order order) {
    if (order.o_type == OType::MKT) {
        matchOrders(order);
    }
    else {
        // Attempt to fill before adding to orderbook
        matchOrders(order);
        if (order.side == 'b') {
            if (order.qty > 0) {
                    bids[*order.price].orders.emplace_back(order);
                    bids[*order.price].qty += order.qty;
            }
        }
        else {
            if (order.qty > 0) {
                asks[*order.price].orders.emplace_back(order);
                asks[*order.price].qty += order.qty;
            }
        }
    }
}

void Orderbook::print() const {
    int y{};
    for (auto it = asks.rbegin(); it != asks.rend(); ++it) {
        std::string pricestr = std::to_string(it->first);
        std::string qtystr = std::to_string(it->second.qty);
        DrawText(pricestr.c_str(), 640, y, 20, BLACK);
        DrawText(qtystr.c_str(), 1220, y, 20, RED);
        y += 30;

    }
    for (auto& [price, level] : bids) {
        std::string pricestr = std::to_string(price);
        std::string qtystr = std::to_string(level.qty);
        DrawText(pricestr.c_str(), 640, y, 20, BLACK);
        DrawText(qtystr.c_str(), 300, y, 20, GREEN);
        y += 30;
    }
    std::string spreadstr = std::to_string(spread());
    DrawText(spreadstr.c_str(), 25, 25, 20, BLACK);

}

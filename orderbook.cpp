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
    
}

void Orderbook::matchOrders(Order &order) {
    
    if (order.o_type == OType::MKT) {
        if (order.side == 'b') {
            int bid_qty = order.qty;
            int ask_qty = asks[bestAsk()].qty;
            while (bid_qty != 0) {
                fillOrder(order, asks[bestAsk()]);
            }
        }
        else {  // Ask order type
            int ask_qty = order.qty;
            int bid_qty = bids[bestBid()].qty;
            while (ask_qty != 0) {
                fillOrder(order, bids[bestBid()]);
            }
        }
    }
    else {
        if (order.side == 'b') {
            int bid_qty = order.qty;
            int ask_qty = asks[bestAsk()].qty;
            if (order.price >= bestAsk()) {
                while (bid_qty != 0) {
                    fillOrder(order, asks[bestAsk()]);
                }
            }
        }
        else {
            int ask_qty = order.qty;
            int bid_qty = bids[bestBid()].qty;
            if (order.price <= bestBid()) {
                while (ask_qty != 0) {
                    fillOrder(order, bids[bestBid()]);
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
                    bids[order.price].orders.emplace_back(order);
                    bids[order.price].qty += order.qty;
            }
        }
        else {
            if (order.qty > 0) {
                asks[order.price].orders.emplace_back(order);
                asks[order.price].qty += order.qty;
            }
        }
    }
}

void Orderbook::print() const {
    int y{};
    std::cout << "-----------------------------------\n";
    std::cout << "ASKS:\n";
    for (auto it = asks.rbegin(); it != asks.rend(); ++it) {
        std::cout << "  " << it->first << ": " << it->second.qty << "\n";
        std::cout << "  " << it->first << ": " << it->second.qty << "\n";
        std::string pricestr = std::to_string(it->first);
        std::string qtystr = std::to_string(it->second.qty);
        DrawText(pricestr.c_str(), 640, y, 20, GREEN);
        DrawText(qtystr.c_str(), 1220, y, 20, GREEN);
        y += 30;

    }
    std::cout << "BIDS:\n";
    for (auto& [price, level] : bids) {
        std::cout << "BEST BID:" << bestBid() << "\n";
        std::cout << "  " << price << ": " << level.qty << "\n";
        std::string pricestr = std::to_string(price);
        std::string qtystr = std::to_string(level.qty);
        DrawText(pricestr.c_str(), 640, y, 20, GREEN);
        DrawText(qtystr.c_str(), 300, y, 20, GREEN);
        y += 30;
    }

}

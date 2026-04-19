
#pragma once
#include "order.h"
#include <cstdint>
#include <deque>
#include <map>
#include <vector>

class Orderbook {
public:
  void addOrder(Order order);
  float_t bestBid() const;
  float_t bestAsk() const;
  float_t spread() const;
  void print() const;
  void logTrade() const;

private:
  struct PriceLevel {
    std::deque<Order> orders;
    uint16_t qty;
  };

  struct Trade {
    char makerSide;
    char takerSide;
    uint16_t qty;
    float_t price;
    std::chrono::system_clock::time_point ts;
  };

  std::map<float_t, PriceLevel, std::greater<double>> bids;
  std::map<float_t, PriceLevel> asks;
  std::vector<Trade> trades;
  void matchOrders(Order &order);
  void fillOrder(Order &incoming, PriceLevel &level);
};

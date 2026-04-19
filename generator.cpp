#include "order.h"
#include <cstdlib>
#include <chrono>
#include <random>

Order generateOrder() {
    Order order{};

    order.side = (rand() % 2) ? 'a' : 'b';
    order.o_type = (rand() % 10 == 0) ? OType::MKT : OType::LMT;
    if (order.o_type == OType::LMT) { order.price = rand() % (120 - 80 + 1) + 80; }
    else { order.price = std::nullopt; }
    order.qty = (rand() % 50 + 1) * 100;
    order.ts = std::chrono::system_clock::now();
    return order;
}

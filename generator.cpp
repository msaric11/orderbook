#include "order.h"
#include <random>
#include <cstdlib>
#include <chrono>

Order generateOrder() {
    Order order{};

    order.side = (rand() % 2) ? 'a' : 'b';
    order.price = rand() % (100 - 80 + 1) + 80;
    order.qty = (rand() % 50 + 1) * 100;
    order.o_type = rand() % 2 ? OType::MKT : OType::LMT;
    order.ts = std::chrono::system_clock::now();
    return order;
}

#pragma once

#include <cstdint>
#include <cmath>
#include <chrono>

enum class OType { MKT, LMT };

struct Order {
    char side;
    OType o_type;
    std::optional<float_t> price; 
    std::uint16_t qty;
    std::chrono::system_clock::time_point ts;
    
};



Order generateOrder();


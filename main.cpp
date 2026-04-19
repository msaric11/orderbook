#include "order.h"
#include "orderbook.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"


int main() {

    SetTargetFPS(30);
    InitWindow(1280, 720, "ORDERBOOK");
    Orderbook orderbook;

    double lastOrderTime = 0.0;
    double orderInterval = 0.5;
    while (!WindowShouldClose())
    {
        if (GetTime() - lastOrderTime >= orderInterval) {
            Order order = generateOrder();
            orderbook.addOrder(order);
            lastOrderTime = GetTime();
        }
        
        BeginDrawing();
        ClearBackground(WHITE);
        orderbook.print();
        EndDrawing();
    }
    CloseWindow();
}

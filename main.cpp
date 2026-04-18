#include "order.h"
#include "orderbook.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

void drawOrderbook(const Orderbook &orderbook) {
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
}

int main() {

    SetTargetFPS(10);
    InitWindow(1280, 720, "ORDERBOOK");
    Orderbook orderbook;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Order order = generateOrder();
        orderbook.addOrder(order);
        orderbook.print();
        EndDrawing();
    }
    CloseWindow();
}

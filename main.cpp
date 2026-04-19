#include "order.h"
#include "orderbook.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {

  SetTargetFPS(30);
  InitWindow(1280, 720, "ORDERBOOK");
  Font font = LoadFontEx("assets/roboto.ttf", 20, nullptr, 0);

  Orderbook orderbook;

  double lastOrderTime = 0.0;
  double orderInterval = 0.5;
  while (!WindowShouldClose()) {
    if (GetTime() - lastOrderTime >= orderInterval) {
      Order order = generateOrder();
      orderbook.addOrder(order);
      lastOrderTime = GetTime();
    }

    BeginDrawing();
    ClearBackground(BLACK);
    orderbook.print();
    EndDrawing();
  }
  CloseWindow();
}

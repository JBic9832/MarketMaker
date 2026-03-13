#include <iostream>
#include "OrderBook.h"
#include "ProRata.h"

void debugOrderBook(const std::string& message, OrderBook& ob) {
    std::cout << std::endl;

    std::cout << message << std::endl;

    for (const auto &[k, v] : ob.GetBidLevels()) {
        std::cout << "Bid orders at level: " << k << std::endl;
        for (const auto &order : v) {
          order->Print();
        }
    }
    for (const auto &[k, v] : ob.GetAskLevels()) {
        std::cout << "Ask orders at level: " << k << std::endl;
        for (const auto &order : v) {
          order->Print();
        }
    }

    std::cout << std::endl;
}

int main() {
    Order order1{10.5, 150, Side::ASK};
    Order order2{10.5, 100, Side::BID};
    Order order3{10.5,  50, Side::ASK};

    order1.Print();
    order2.Print();
    order3.Print();

    // select the matching algorithm we want
    ProRata matchingAlgo{};
    OrderBook orderBook{matchingAlgo};

    // Add asks
    orderBook.AddOrder(order1);
    orderBook.AddOrder(order3);

    // Add bid
    orderBook.AddOrder(order2);

    debugOrderBook("Checking order book after orders", orderBook);



    std::cin.get();

    return 0;
}
#include <iostream>
#include "Order.h"
#include "OrderBook.h"
#include "ProRata.h"

void debugOrderBook(const std::string& message, OrderBook& ob) {
    std::cout << std::endl;

    std::cout << message << std::endl;

    for (const auto &[k, v] : ob.GetBidLevels()) {
        std::cout << "Bid orders at level: " << static_cast<double>(k) / 100 << std::endl;
        if (!v.empty()) {
            for (const auto &order : v) {
                std::cout << "\t\033[32m";
                order->Print();
                std::cout << "\033[0m";
            }
        } else {
            std::cout << "\tNo orders found." << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for (const auto &[k, v] : ob.GetAskLevels()) {
        std::cout << "Ask orders at level: " << static_cast<double>(k) / 100 << std::endl;
        if (!v.empty()) {
            for (const auto &order : v) {
                std::cout << "\t\033[31m";
                order->Print();
                std::cout << "\033[0m";
            }
        } else {
            std::cout << "\tNo orders found." << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

int main() {
    Order order1{1050, 150, Side::ASK};
    Order order2{1050, 100, Side::BID};
    Order order3{1050,  50, Side::ASK};

    Order order4{1000, 100, Side::BID};
    Order order5{1000, 100, Side::ASK};
    Order order6{1000, 100, Side::BID};

    Order order7{1000, 100, Side::ASK};
    Order order8{1050, 100, Side::BID};

    // select the matching algorithm we want
    ProRata matchingAlgo{};
    OrderBook orderBook{matchingAlgo};

    // Add asks
    orderBook.AddLimitOrder(order1);
    orderBook.AddLimitOrder(order3);

    // Add bid
    orderBook.AddLimitOrder(order2);

    orderBook.AddLimitOrder(order5);
    orderBook.AddLimitOrder(order4);
    orderBook.AddLimitOrder(order6);

    orderBook.AddLimitOrder(order7);
    orderBook.AddLimitOrder(order8);

    debugOrderBook("Checking order book after orders", orderBook);

    std::cin.get();

    return 0;
}

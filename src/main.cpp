#include <iostream>
#include <memory>
#include "Order.h"
#include "OrderBook.h"
#include "ProRata.h"

void debugOrderBook(const std::string& message, OrderBook& ob) {
    std::cout << std::endl;

    std::cout << message << std::endl;

    for (const auto &[k, v] : ob.GetBidLevels()) {
        std::cout << "Bid orders at level: " << k << std::endl;
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
        std::cout << "Ask orders at level: " << k << std::endl;
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

/*
TODO: DEBUG WHY THE LAST ORDER IS NOT BEING REMOVED FROM THE ORDER BOOK WHEN ITS FILLED
*/

int main() {
    Order order1{10.5, 150, Side::ASK};
    Order order2{10.5, 100, Side::BID};
    Order order3{10.5,  50, Side::ASK};

    Order order4{10, 100, Side::BID};
    Order order5{10, 100, Side::ASK};
    Order order6{10, 100, Side::BID};

    Order order7{10, 100, Side::ASK};
    Order order8{10.5, 100, Side::BID};

    // select the matching algorithm we want
    ProRata matchingAlgo{};
    OrderBook orderBook{matchingAlgo};

    // Add asks
    orderBook.AddOrder(order1);
    orderBook.AddOrder(order3);

    // Add bid
    orderBook.AddOrder(order2);

    orderBook.AddOrder(order5);
    orderBook.AddOrder(order4);
    orderBook.AddOrder(order6);

    orderBook.AddOrder(order7);
    orderBook.AddOrder(order8);

    debugOrderBook("Checking order book after orders", orderBook);

    std::cin.get();

    return 0;
}
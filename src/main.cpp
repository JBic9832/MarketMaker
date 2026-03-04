#include <iostream>
#include "OrderBook.h"
#include "ProRata.h"

int main() {
    Order order1{10.5, 100, Side::ASK};
    Order order2{14.1,  20, Side::BID};
    Order order3{12.1,  49, Side::ASK};

    order1.Print();
    order2.Print();
    order3.Print();

    // select the matching algorithm we want
    ProRata matchingAlgo{};
    OrderBook orderBook{matchingAlgo};

    std::cin.get();

    return 0;
}
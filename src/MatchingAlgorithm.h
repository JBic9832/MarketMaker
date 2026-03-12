#pragma once
#include "OrderBook.h"

class MatchingAlgorithm {
public:
    MatchingAlgorithm() {};
    virtual void Match(OrderBook& orderBook, Order& incomingOrder) = 0;
};
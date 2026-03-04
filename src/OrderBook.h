#pragma once
#include "MatchingAlgorithm.h"
#include "Order.h"
#include "Types.h"


class OrderBook
{
public:
	OrderBook(MatchingAlgorithm& matchingAlgorithm);
    void AddOrder(Order& order);

    double GetBestBid() const;
    double GetBestAsk() const;

private:
    bidLevelsContainer m_BidLevels{};
    askLevelsContainer m_AskLevels{};

    MatchingAlgorithm* m_MatchingAlgorithm;
};
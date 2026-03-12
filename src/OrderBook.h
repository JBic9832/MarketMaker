#pragma once
#include "Order.h"
#include "Types.h"

class MatchingAlgorithm;

class OrderBook
{
public:
	OrderBook(MatchingAlgorithm& matchingAlgorithm);
    void AddOrder(Order& order);

    double GetBestBid() const;
    double GetBestAsk() const;
    int BidQuantityAtLevel(double priceLevel) const;
    int AskQuantityAtLevel(double priceLevel) const;
    std::vector<Order> BidsAtLevel(double priceLevel) const;
    std::vector<Order> AsksAtLevel(double priceLevel) const;
    bool IsEmpty(Side side) const;

private:
    bidLevelsContainer m_BidLevels{};
    askLevelsContainer m_AskLevels{};

    MatchingAlgorithm* m_MatchingAlgorithm;
};
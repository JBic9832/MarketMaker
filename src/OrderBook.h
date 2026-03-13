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
    std::list<std::shared_ptr<Order>>& BidsAtLevel(double priceLevel);
    std::list<std::shared_ptr<Order>>& AsksAtLevel(double priceLevel);
    bool IsEmpty(Side side) const;
    bidLevelsContainer GetBidLevels() const { return m_BidLevels; }
    askLevelsContainer GetAskLevels() const { return m_AskLevels; }

private:
    bidLevelsContainer m_BidLevels{};
    askLevelsContainer m_AskLevels{};

    MatchingAlgorithm* m_MatchingAlgorithm;
};
#pragma once
#include "Order.h"
#include "Types.h"
#include <queue>

class MatchingAlgorithm;

class OrderBook
{
public:
	OrderBook(MatchingAlgorithm& matchingAlgorithm);
    void AddLimitOrder(Order& order);

	std::int64_t GetBestBid() const;
	std::int64_t GetBestAsk() const;
    int BidQuantityAtLevel(std::int64_t priceLevel) const;
    int AskQuantityAtLevel(std::int64_t priceLevel) const;
    std::list<std::shared_ptr<Order>>& BidsAtLevel(double priceLevel);
    std::list<std::shared_ptr<Order>>& AsksAtLevel(double priceLevel);
    bool IsEmpty(Side side) const;
    bidLevelsContainer GetBidLevels() const { return m_BidLevels; }
    askLevelsContainer GetAskLevels() const { return m_AskLevels; }

private:
    bidLevelsContainer m_BidLevels{};
    askLevelsContainer m_AskLevels{};

	// Make this a queue for all orders and when a limit order comes in
	// Send it to the front for immediate processing
	std::queue<std::shared_ptr<Order>> m_OrderQueue{};

    MatchingAlgorithm* m_MatchingAlgorithm;
};

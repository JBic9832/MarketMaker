#include "OrderBook.h"
#include "MatchingAlgorithm.h"
#include <memory>
#include <numeric>

OrderBook::OrderBook(MatchingAlgorithm& matchingAlgorithm) {
    m_MatchingAlgorithm = &matchingAlgorithm;
}

void OrderBook::AddOrder(Order& order) {

    // Look for potential matches
    m_MatchingAlgorithm->Match(*this, order);

    // Make sure we didn't fully fill the order before resting it on the book
    if (order.Quantity <= 0)
        return;

    // Insert based on side
    if (order.OrderSide == Side::BID) {
        m_BidLevels[order.Price].push_back(std::make_shared<Order>(order));
    } else {
        m_AskLevels[order.Price].push_back(std::make_shared<Order>(order));
    }
}

bool OrderBook::IsEmpty(Side side) const {
    return (side == Side::BID) ? m_BidLevels.empty() : m_AskLevels.empty();
}

// Return the lowest ask price
double OrderBook::GetBestAsk() const {
    if (!m_AskLevels.empty())
        return m_AskLevels.begin()->first;

    return 0;
}

// Return the highest bid price
double OrderBook::GetBestBid() const {
    if(!m_BidLevels.empty())
        return m_BidLevels.begin()->first;

    return 0;
}

int OrderBook::BidQuantityAtLevel(double priceLevel) const {
    // Accumulate all of the quantities for orders at a given price level
    return std::accumulate(m_BidLevels.find(priceLevel)->second.begin(), m_BidLevels.find(priceLevel)->second.end(), 0, 
            [] (int total, const std::shared_ptr<Order>& order) { return total + order->Quantity; });

}

int OrderBook::AskQuantityAtLevel(double priceLevel) const {
    return std::accumulate(m_AskLevels.find(priceLevel)->second.begin(), m_AskLevels.find(priceLevel)->second.end(), 0, 
            [] (int total, const std::shared_ptr<Order>& order) { return total + order->Quantity; });
}

std::vector<std::shared_ptr<Order>> OrderBook::BidsAtLevel(double priceLevel) const {
    return m_BidLevels.find(priceLevel)->second;
}

std::vector<std::shared_ptr<Order>> OrderBook::AsksAtLevel(double priceLevel) const {
    return m_AskLevels.find(priceLevel)->second;
}

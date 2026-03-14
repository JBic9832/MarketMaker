#include "OrderBook.h"
#include "MatchingAlgorithm.h"
#include "Order.h"
#include <memory>
#include <numeric>

OrderBook::OrderBook(MatchingAlgorithm& matchingAlgorithm) {
    m_MatchingAlgorithm = &matchingAlgorithm;
}

void OrderBook::AddOrder(Order& order) {
    std::string color = (order.OrderSide == Side::BID) ? "\033[32m" : "\033[31m";
    std::cout << color;
    order.Print();

    if (order.Quantity <= 0) return; // No zero quantity orders

    // Look for potential matches
    m_MatchingAlgorithm->Match(*this, order);

    // Make sure we didn't fully fill the order before resting it on the book
    if (order.Quantity <= 0) {
        std::cout << "Filled\033[0m" << std::endl;
        return;
    }

    // Insert based on side
    if (order.OrderSide == Side::BID) {
        m_BidLevels[order.Price].push_back(std::make_shared<Order>(order));
    } else {
        m_AskLevels[order.Price].push_back(std::make_shared<Order>(order));
    }

    std::cout << "\033[0m";
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

std::list<std::shared_ptr<Order>>& OrderBook::BidsAtLevel(double priceLevel) {
    auto it = m_BidLevels.find(priceLevel);
    if (it != m_BidLevels.end()) {
        return it->second;
    }

    static std::list<std::shared_ptr<Order>> emptyList;
    return emptyList;
}

std::list<std::shared_ptr<Order>>& OrderBook::AsksAtLevel(double priceLevel) {
    auto it = m_AskLevels.find(priceLevel);
    if (it != m_AskLevels.end()) {
        return it->second;
    }

    static std::list<std::shared_ptr<Order>> emptyList;
    return emptyList;
}

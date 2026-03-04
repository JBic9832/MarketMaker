#include "OrderBook.h"

OrderBook::OrderBook(MatchingAlgorithm& matchingAlgorithm) {
    m_MatchingAlgorithm = &matchingAlgorithm;
}

void OrderBook::AddOrder(Order& order) {
    // Insert based on side
    if (order.OrderSide == Side::BID) {
        m_BidLevels[order.Price].push_back(order);
    } else {
        m_AskLevels[order.Price].push_back(order);
    }

    // Look for potential matches
    m_MatchingAlgorithm->Match(m_BidLevels, m_AskLevels);
}

double OrderBook::GetBestAsk() const {
    if (!m_AskLevels.empty())
        return m_AskLevels.begin()->first;

    return 0;
}

double OrderBook::GetBestBid() const {
    if(!m_BidLevels.empty())
        return m_BidLevels.begin()->first;

    return 0;
}


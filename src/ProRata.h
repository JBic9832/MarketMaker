#pragma once

#include "MatchingAlgorithm.h"
#include "Order.h"
#include "OrderBook.h"
#include <memory>

class ProRata : public MatchingAlgorithm {
public:
    ProRata() {}

    /* This will match incoming order to orders in the order book
    *  This function will modify the incoming orders quantity as a side effect
    */
    void Match(OrderBook& orderBook, Order& incomingOrder) override {
		matchOrder(orderBook, incomingOrder);

    }

    // TO debug this I would see what the outcome balance for both orders is at the end and log their ids as well. Turn off all other prints to make this easier
private:
    void matchOrder(OrderBook& orderBook, Order& incomingOrder) {
		bool isBid = incomingOrder.OrderSide == Side::BID;
        auto& levels = isBid ? orderBook.AsksAtLevel(incomingOrder.Price) : orderBook.BidsAtLevel(incomingOrder.Price);
        // Match found for price level
        if (!levels.empty()) {
            // if so prorate allocation of quantities at that level
            const int priceLevelQuantity = isBid ? orderBook.AskQuantityAtLevel(incomingOrder.Price) : orderBook.BidQuantityAtLevel(incomingOrder.Price); 
            const int initialIncomingQuantity = incomingOrder.Quantity;

            // For each order in the level, pro rate a percentage of the incoming order quantity
            for (auto it = levels.begin(); it != levels.end();) {
                // Check if this is the last order
                if (it == std::prev(levels.end())) {
                    // Remove the remaining quantity since we are at the last order
                    if ((*it)->Quantity > incomingOrder.Quantity) {
                        (*it)->Quantity -= incomingOrder.Quantity;
                        incomingOrder.Quantity = 0;
                        return;
                    } else {
                        incomingOrder.Quantity -= (*it)->Quantity;
                        (*it)->Quantity = 0;
                        // Remove the order from the book
                        it = levels.erase(it);
                        return;
                    }
                }
                
                // Find the percentage the order is granted
                double percent = static_cast<double>((*it)->Quantity) / priceLevelQuantity;
                int share = static_cast<int>(initialIncomingQuantity * percent);

                // Take the share
                (*it)->Quantity -= share;
                if ((*it)->Quantity <= 0) {
                    // Remove it from the book
                    it = levels.erase(it);
                } else {
                    ++it;
                }
                incomingOrder.Quantity -= share;
            }
        }
    }
};

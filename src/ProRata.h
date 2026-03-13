#pragma once

#include "MatchingAlgorithm.h"

class ProRata : public MatchingAlgorithm {
public:
    ProRata() {}

    /* This will match incoming order to orders in the order book
    *  This function will modify the incoming orders quantity as a side effect
    */
    void Match(OrderBook& orderBook, Order& incomingOrder) override {
        Side side = incomingOrder.OrderSide;
        if (side == Side::BID) {
            // Match found for price level
            if (!orderBook.AsksAtLevel(incomingOrder.Price).empty()) {
                // if so prorate allocation of quantities at that level
                const int priceLevelQuantity = orderBook.AskQuantityAtLevel(incomingOrder.Price); 
                const int initialIncomingQuantity = incomingOrder.Quantity;

                // For each order in the level, pro rate a percentage of the incoming order quantity
                for (auto& order : orderBook.AsksAtLevel(incomingOrder.Price)) {
                    // Check if this is the last order
                    if (&order == &orderBook.AsksAtLevel(incomingOrder.Price).back()) {
                        // Remove the remaining quantity since we are at the last order
                        if (order->Quantity >= incomingOrder.Quantity) {
                            order->Quantity -= incomingOrder.Quantity;
                            incomingOrder.Quantity = 0;
                            return;
                        } else {
                            incomingOrder.Quantity -= order->Quantity;
                            order->Quantity = 0;
                            // Remove the order from the book
                            return;
                        }
                    }
                    
                    // Find the percentage the order is granted
                    double percent = static_cast<double>(order->Quantity) / priceLevelQuantity;
                    int share = static_cast<int>(initialIncomingQuantity * percent);

                    // Take the share
                    order->Quantity -= share;
                    if (order->Quantity <= 0) {
                        // Remove it from the book
                    }
                    incomingOrder.Quantity -= share;

                }
            }

        } else {
            // Match found for price level
            if (!orderBook.BidsAtLevel(incomingOrder.Price).empty()) {
                // if so prorate allocation of quantities at that level
                const int priceLevelQuantity = orderBook.BidQuantityAtLevel(incomingOrder.Price);
                const int initialIncomingQuantity = incomingOrder.Quantity;

                for (auto& order : orderBook.BidsAtLevel(incomingOrder.Price)) {
                    if (&order == &orderBook.BidsAtLevel(incomingOrder.Price).back()) {
                        if (order->Quantity >= incomingOrder.Quantity) {
                            order->Quantity -= incomingOrder.Quantity;
                            incomingOrder.Quantity = 0;
                            return;
                        } else {
                            incomingOrder.Quantity -= order->Quantity;
                            order->Quantity = 0;
                            // Remove the order from the book
                            return;
                        }

                    }

                    // Find the percentage the order is granted
                    double percent = static_cast<double>(order->Quantity) / priceLevelQuantity;
                    int share = static_cast<int>(initialIncomingQuantity * percent);

                    // Take the share
                    order->Quantity -= share;
                    if (order->Quantity <= 0) {
                        // Remove it from the book
                    }
                    incomingOrder.Quantity -= share;
                }
            }
        }

    }

private:
    template <typename T>
    void prorateAllocationOfQuantities(T ordersAtLevel, const Order& order) {

    }
};
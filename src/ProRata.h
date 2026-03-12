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
            // Exit early if there are no orders in the book
            if (orderBook.IsEmpty(incomingOrder.OrderSide)) return;

            // Determine if lowest ask price is less than or equal to bid
            double lowestAsk = orderBook.GetBestAsk();

            // Match found for price level
            if (incomingOrder.Price >= lowestAsk) {
                // if so prorate allocation of quantities at that level
                const int priceLevelQuantity = orderBook.BidQuantityAtLevel(incomingOrder.Price); 

                // For each order in the level, pro rate a percentage of the incoming order quantity
                for (Order& order : orderBook.BidsAtLevel(incomingOrder.Price)) {
                    // Check if this is the last order
                    if (&order == &orderBook.BidsAtLevel(incomingOrder.Price).back()) {
                        // Remove the remaining quantity since we are at the last order
                        if (order.Quantity >= incomingOrder.Quantity) {
                            order.Quantity -= incomingOrder.Quantity;
                            incomingOrder.Quantity = 0;
                            return;
                        } else {
                            incomingOrder.Quantity -= order.Quantity;
                            order.Quantity = 0;
                            return;
                        }
                    }
                    
                    // Find the percentage the order is granted
                    double share = static_cast<double>(order.Quantity) / priceLevelQuantity;

                    // Take the share
                    order.Quantity -= static_cast<int>(incomingOrder.Quantity * share);
                    incomingOrder.Quantity -= static_cast<int>(incomingOrder.Quantity * share);
                }
            }

        } else {
            // No need to do anything
            if (orderBook.IsEmpty(incomingOrder.OrderSide)) return; 

            // Determine if highest bid is greater than or equal to ask price
            double highestBid = orderBook.GetBestBid();

            // Match found for price level
            if (incomingOrder.Price <= highestBid) {
                // if so prorate allocation of quantities at that level
                const int priceLevelQuantity = orderBook.AskQuantityAtLevel(incomingOrder.Price);

                for (Order& order : orderBook.AsksAtLevel(incomingOrder.Price)) {
                    if (&order == &orderBook.AsksAtLevel(incomingOrder.Price).back()) {
                        if (order.Quantity >= incomingOrder.Quantity) {
                            order.Quantity -= incomingOrder.Quantity;
                            incomingOrder.Quantity = 0;
                            return;
                        } else {
                            incomingOrder.Quantity -= order.Quantity;
                            order.Quantity = 0;
                            return;
                        }

                    }

                    // Find the percentage the order is granted
                    double share = static_cast<double>(order.Quantity) / priceLevelQuantity;

                    // Take the share
                    order.Quantity -= static_cast<int>(incomingOrder.Quantity * share);
                    incomingOrder.Quantity -= static_cast<int>(incomingOrder.Quantity * share);
                }
            }
        }

    }

private:
    template <typename T>
    void prorateAllocationOfQuantities(T ordersAtLevel, const Order& order) {

    }
};
#pragma once
#include <iostream>

enum Side {
	ASK = 0,
	BID
};

struct Order {
	Order(double price, int quantity, Side side) : Price{ price }, Quantity{ quantity }, OrderSide{ side } { }

	void Print() {
		std::string sSide = (OrderSide == Side::ASK) ? "Ask" : "Bid";

		std::cout << sSide << ": " << Price << " x " << Quantity << std::endl;
	}

	bool operator>(const Order& other) const {
		return Price > other.Price;
	}

	bool operator<(const Order& other) const {
		return Price < other.Price;
	}

	bool operator<=(const Order& other) const {
		return Price <= other.Price;
	}

	bool operator>=(const Order& other) const {
		return Price >= other.Price;
	}

    bool operator==(const Order& other) const {
        return Price == other.Price;
    }

	const double Price;
	int Quantity;
	const Side OrderSide;
};
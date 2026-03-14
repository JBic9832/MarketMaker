#pragma once
#include <iostream>

enum Side {
	ASK = 0,
	BID
};

static int ORDER_COUNTER = 0;

struct Order {
	
	Order(double price, int quantity, Side side) : Price{ price }, Quantity{ quantity }, OrderSide{ side } { 
		Id = ORDER_COUNTER;
		++ORDER_COUNTER;
	}

	void Print() const {
		std::string sSide = (OrderSide == Side::ASK) ? "Ask" : "Bid";

		std::cout << sSide << ": " << Price << " x " << Quantity << " ID: " << Id << std::endl;
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
	int Id;
};
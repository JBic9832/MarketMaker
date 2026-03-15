#pragma once
#include <iostream>
#include <cstdint>
#include <iomanip>
#include <chrono>

enum Side {
	ASK = 0,
	BID
};



struct Order {
	
	Order(std::int64_t price, int quantity, Side side) : Price{ price }, Quantity{ quantity }, OrderSide{ side }, Id {ORDER_COUNTER}, Timestamp{ unixTimestampMicros() } { 
		++ORDER_COUNTER;
	}

	void Print() const {
		std::string sSide = (OrderSide == Side::ASK) ? "Ask" : "Bid";

		std::cout << sSide << ": " 
			<< std::fixed << std::setprecision(2) << static_cast<double>(Price) / 100 
			<< " x " << std::setw(5) << Quantity << " ID: " << Id << std::endl;
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
	
	inline static int ORDER_COUNTER = 0;
	inline static std::uint64_t unixTimestampMicros() {
		return std::chrono::duration_cast<std::chrono::microseconds>(
					std::chrono::system_clock::now().time_since_epoch()
			   ).count();

	}

	const std::int64_t Price;
	int Quantity;
	const Side OrderSide;
	const int Id;
	const std::uint64_t Timestamp;
	//const std::uint64_t ParticipantId;
};

#pragma once
#include <map>
#include <vector>
#include "Order.h"


using bidLevelsContainer = std::map<double, std::vector<Order>, std::greater<double>>;
using askLevelsContainer = std::map<double, std::vector<Order>>;
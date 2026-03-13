#pragma once
#include <map>
#include <memory>
#include <vector>
#include "Order.h"


using bidLevelsContainer = std::map<double, std::vector<std::shared_ptr<Order>>, std::greater<double>>;
using askLevelsContainer = std::map<double, std::vector<std::shared_ptr<Order>>>;
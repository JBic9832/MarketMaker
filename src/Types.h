#pragma once
#include <map>
#include <memory>
#include <list>
#include "Order.h"

using bidLevelsContainer = std::map<double, std::list<std::shared_ptr<Order>>, std::greater<double>>;
using askLevelsContainer = std::map<double, std::list<std::shared_ptr<Order>>>;
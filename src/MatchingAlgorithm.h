#pragma once
#include "Types.h"

class MatchingAlgorithm {
public:
    MatchingAlgorithm() {};
    virtual void Match(bidLevelsContainer bidLevels, askLevelsContainer askLevels) = 0;

};
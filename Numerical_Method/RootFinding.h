#ifndef ROOTFINDING_H
#define ROOTFINDING_H

#include "ExpressionParser.h"
#include <vector>

struct MethodResult
{
    std::string methodName;
    double root;
    int iterations;
};

extern std::vector<MethodResult> comparisonResults;

void bisectionMethod(ExpressionParser &parser);
void falsePositionMethod(ExpressionParser &parser);
void newtonRaphsonMethod(ExpressionParser &parser);
void secantMethod(ExpressionParser &parser);
void showMethodComparison();
void rootFindingMenu();

#endif

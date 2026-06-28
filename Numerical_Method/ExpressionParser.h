#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include <string>
#include <vector>

using namespace std;

class ExpressionParser
{
private:
    string expression;

public:
    void setExpression(string expr);
    double evaluate(double x);
};

#endif

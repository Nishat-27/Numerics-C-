#include "ExpressionParser.h"

#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

void ExpressionParser::setExpression(string expr)
{
    expression = expr;
}

double ExpressionParser::evaluate(double x)
{
    string expr = expression;

    string clean = "";

    for(char c : expr)
    {
        if(c != ' ')
            clean += c;
    }

    double result = 0;

    string current = "";

    for(int i=0;i<(int)clean.size();i++)
    {
        if(i>0 && (clean[i]=='+' || clean[i]=='-'))
        {
            current += '|';
        }

        current += clean[i];
    }

    vector<string> terms;

    string token = "";

    for(char c : current)
    {
        if(c=='|')
        {
            terms.push_back(token);
            token="";
        }
        else
        {
            token+=c;
        }
    }

    terms.push_back(token);

    for(string term : terms)
    {
        double value = 0;

        if(term.find("x^") != string::npos)
        {
            size_t pos = term.find("x^");

            double coeff = 1;

            string left = term.substr(0,pos);

            if(left=="")
                coeff=1;

            else if(left=="-")
                coeff=-1;

            else
            {
                if(left.back()=='*')
                    left.pop_back();

                coeff = stod(left);
            }

            int power = stoi(term.substr(pos+2));

            value = coeff * pow(x,power);
        }

        else if(term.find("x") != string::npos)
        {
            size_t pos = term.find("x");

            double coeff = 1;

            string left = term.substr(0,pos);

            if(left=="")
                coeff=1;

            else if(left=="-")
                coeff=-1;

            else
            {
                if(left.back()=='*')
                    left.pop_back();

                coeff = stod(left);
            }

            value = coeff*x;
        }

        else
        {
            value = stod(term);
        }

        result += value;
    }

    return result;
}

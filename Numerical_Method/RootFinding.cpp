#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

#include "RootFinding.h"
#include "Utility.h"

using namespace std;

vector<MethodResult> comparisonResults;


void bisectionMethod(ExpressionParser &parser)
{
    double a, b, c;
    double fa, fb, fc;

    int iteration = 0;

    double previousC = 0;
    double error = 0;

    double tolerance = 0.001;

    cout << "\nEnter lower bound a: ";
    cin >> a;

    cout << "Enter upper bound b: ";
    cin >> b;

    fa = parser.evaluate(a);
    fb = parser.evaluate(b);

    if(fa * fb > 0)
    {
        cout << "\nInvalid Interval.\n";
        cout << "f(a) and f(b) must have opposite signs.\n";
        return;
    }

    cout << "\n==============================================================\n";
    cout << "            Bisection Iteration Table\n";
    cout << "==============================================================\n";

    cout << fixed << setprecision(3);

    cout << left
         << setw(8)  << "Iter"
         << setw(12) << "a"
         << setw(12) << "b"
         << setw(12) << "c"
         << setw(15) << "f(c)"
         << setw(15) << "Error"
         << endl;

    cout << "--------------------------------------------------------------\n";

    while(iteration < 20)
    {
        c = (a + b) / 2.0;

        fc = parser.evaluate(c);

        if(iteration == 0)
        {
            error = 0;
        }
        else
        {
            error = fabs(c - previousC);
        }

        cout << left
             << setw(8)  << iteration + 1
             << setw(12) << a
             << setw(12) << b
             << setw(12) << c
             << setw(15) << fc
             << setw(15) << error
             << endl;

        if(iteration > 0 && error < tolerance)
        {
            break;
        }

        if(fabs(fc) < 0.0001)
        {
            break;
        }

        if(fa * fc < 0)
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }

        previousC = c;
        iteration++;
    }

    cout << "\nApproximate Root = " << c << endl;
    cout << "Total Iterations = " << iteration + 1 << endl;
    MethodResult result;

    result.methodName = "Bisection";
    result.root = c;
    result.iterations = iteration + 1;

    comparisonResults.push_back(result);
}

void falsePositionMethod(ExpressionParser &parser)
{
    double a,b,c;
    double fa,fb,fc;

    int iteration = 0;

    double previousC = 0;
    double error = 0;

    double tolerance = 0.001;

    cout << "\nEnter lower bound a: ";
    cin >> a;

    cout << "Enter upper bound b: ";
    cin >> b;

    fa = parser.evaluate(a);
    fb = parser.evaluate(b);

    if(fa * fb > 0)
    {
        cout << "\nInvalid Interval.\n";
        cout << "f(a) and f(b) must have opposite signs.\n";
        return;
    }

    cout << "\n==============================================================\n";
    cout << "         False Position Iteration Table\n";
    cout << "==============================================================\n";

    cout << fixed << setprecision(3);

    cout << left
         << setw(8)  << "Iter"
         << setw(12) << "a"
         << setw(12) << "b"
         << setw(12) << "c"
         << setw(15) << "f(c)"
         << setw(15) << "Error"
         << endl;

    cout << "--------------------------------------------------------------\n";

    while(iteration < 50)
    {
        c = (a*fb - b*fa)/(fb-fa);

        fc = parser.evaluate(c);

        if(iteration == 0)
        {
            error = 0;
        }
        else
        {
            error = fabs(c - previousC);
        }

        cout << left
             << setw(8)  << iteration + 1
             << setw(12) << a
             << setw(12) << b
             << setw(12) << c
             << setw(15) << fc
             << setw(15) << error
             << endl;

        if(iteration > 0 && error < tolerance)
        {
            break;
        }

        if(fabs(fc) < 0.0001)
        {
            break;
        }

        if(fa * fc < 0)
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }

        previousC = c;

        iteration++;
    }

    cout << "\nApproximate Root = " << c << endl;
    cout << "Total Iterations = " << iteration + 1 << endl;
    MethodResult result;

    result.methodName = "False Position";
    result.root = c;
    result.iterations = iteration + 1;

    comparisonResults.push_back(result);
}

void newtonRaphsonMethod(ExpressionParser &parser)
{
    ExpressionParser derivativeParser;

    string derivativeExpr;

    double x0;
    double x1;

    double error = 0;

    double tolerance = 0.001;

    int iteration = 0;

    cin.ignore();

    cout << "\nEnter f'(x): ";
    getline(cin, derivativeExpr);

    derivativeParser.setExpression(derivativeExpr);

    cout << "Enter Initial Guess: ";
    cin >> x0;

    cout << "\n==============================================================\n";
    cout << "         Newton-Raphson Iteration Table\n";
    cout << "==============================================================\n";

    cout << fixed << setprecision(3);

    cout << left
         << setw(8)  << "Iter"
         << setw(15) << "x"
         << setw(15) << "f(x)"
         << setw(15) << "f'(x)"
         << setw(15) << "Error"
         << endl;

    cout << "--------------------------------------------------------------\n";

    while(iteration < 50)
    {
        double fx = parser.evaluate(x0);

        double dfx = derivativeParser.evaluate(x0);

        if(fabs(dfx) < 0.000001)
        {
            cout << "\nDerivative became zero.\n";
            return;
        }

        x1 = x0 - (fx/dfx);

        error = fabs(x1-x0);

        cout << left
             << setw(8)  << iteration+1
             << setw(15) << x0
             << setw(15) << fx
             << setw(15) << dfx
             << setw(15) << error
             << endl;

        if(error < tolerance)
        {
            x0 = x1;
            break;
        }

        x0 = x1;

        iteration++;
    }

    cout << "\nApproximate Root = " << x0 << endl;
    cout << "Total Iterations = " << iteration+1 << endl;
    MethodResult result;

    result.methodName = "Newton-Raphson";
    result.root = x0;
    result.iterations = iteration + 1;

    comparisonResults.push_back(result);
}

void secantMethod(ExpressionParser &parser)
{
    double x0, x1, x2;
    double fx0, fx1;

    double error = 0;
    double tolerance = 0.001;

    int iteration = 0;

    cout << "\nEnter first guess x0: ";
    cin >> x0;

    cout << "Enter second guess x1: ";
    cin >> x1;

    cout << "\n==============================================================\n";
    cout << "          Secant Method Iteration Table\n";
    cout << "==============================================================\n";

    cout << fixed << setprecision(3);

    cout << left
         << setw(8)  << "Iter"
         << setw(12) << "x0"
         << setw(12) << "x1"
         << setw(12) << "x2"
         << setw(15) << "Error"
         << endl;

    cout << "--------------------------------------------------------------\n";

    while(iteration < 50)
    {
        fx0 = parser.evaluate(x0);
        fx1 = parser.evaluate(x1);

        if(fabs(fx1 - fx0) < 0.000001)
        {
            cout << "\nDivision by zero detected.\n";
            return;
        }

        x2 = x1 - (fx1 * (x1 - x0)) / (fx1 - fx0);

        if(iteration == 0)
            error = 0;
        else
            error = fabs(x2 - x1);

        cout << left
             << setw(8)  << iteration + 1
             << setw(12) << x0
             << setw(12) << x1
             << setw(12) << x2
             << setw(15) << error
             << endl;

        if(iteration > 0 && error < tolerance)
        {
            break;
        }

        x0 = x1;
        x1 = x2;

        iteration++;
    }

    cout << "\nApproximate Root = " << x2 << endl;
    cout << "Total Iterations = " << iteration + 1 << endl;
    MethodResult result;

    result.methodName = "Secant";
    result.root = x2;
    result.iterations = iteration + 1;

    comparisonResults.push_back(result);
}

void showMethodComparison()
{
    if(comparisonResults.empty())
    {
        cout << "\nNo methods executed yet.\n";
        return;
    }

    cout << "\n============================================================\n";
    cout <<                  "METHOD COMPARISON TABLE\n";
    cout << "==============================================================\n";

    cout << fixed << setprecision(3);

    cout << left
         << setw(20) << "Method"
         << setw(15) << "Root"
         << setw(15) << "Iterations"
         << endl;

    cout << "------------------------------------------------------------\n";

    for(auto result : comparisonResults)
    {
        cout << left
             << setw(20) << result.methodName
             << setw(15) << result.root
             << setw(15) << result.iterations
             << endl;
    }
}

void rootFindingMenu()
{
    ExpressionParser parser;

    string equation;

    int choice;

    cout << "\nEnter Equation: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, equation);

    parser.setExpression(equation);

    while(true)
    {
        printTitle("    ROOT FINDING METHODS");

        cout << "Current Equation : " << equation << endl;

        cout << "\n1. Bisection Method\n";
        cout << "2. False Position Method\n";
        cout << "3. Newton-Raphson Method\n";
        cout << "4. Secant Method\n";
        cout << "5. Method Comparison\n";
        cout << "6. Change Equation\n";
        cout << "7. Back to Main Menu\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
        case 1:
            bisectionMethod(parser);
            break;

        case 2:
            falsePositionMethod(parser);
            break;

        case 3:
            newtonRaphsonMethod(parser);
            break;

        case 4:
            secantMethod(parser);
            break;

        case 5:
            showMethodComparison();
            break;

        case 6:

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nEnter New Equation: ";

            getline(cin, equation);

            parser.setExpression(equation);

            comparisonResults.clear();

            break;

        case 7:

            return;

        default:

            cout << "\nInvalid Choice.\n";
        }
    }
}

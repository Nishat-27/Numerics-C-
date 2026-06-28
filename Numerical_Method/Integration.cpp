#include <iostream>
#include <iomanip>
#include <vector>

#include "Integration.h"
#include "ExpressionParser.h"
#include "Utility.h"

using namespace std;

void integrationMenu()
{
    int choice;

    while(true)
    {
        printTitle("     NUMERICAL INTEGRATION");

        cout<<"1. Trapezoidal Rule\n";
        cout<<"2. Simpson's 1/3 Rule\n";
        cout<<"3. Back To Main Menu\n";

        cout<<"\nEnter Choice : ";
        cin>>choice;

        switch(choice)
        {
        case 1:

            trapezoidalRule();

            break;

        case 2:

            simpsonOneThirdRule();

            break;

        case 3:

            return;

        default:

            cout<<"\nInvalid Choice.\n";
        }
    }
}

void trapezoidalRule()
{
    ExpressionParser parser;

    string equation;

    double a, b;
    int n;

    printTitle("     TRAPEZOIDAL RULE");

    cin.ignore();

    cout << "Enter Equation : ";
    getline(cin, equation);

    parser.setExpression(equation);

    cout << "Enter Lower Limit : ";
    cin >> a;

    cout << "Enter Upper Limit : ";
    cin >> b;

    cout << "Enter Number of Subintervals : ";
    cin >> n;

    double h = (b - a) / n;

    vector<double> x(n + 1);
    vector<double> fx(n + 1);

    for(int i = 0; i <= n; i++)
    {
        x[i] = a + i * h;
        fx[i] = parser.evaluate(x[i]);
    }

    printTitle("     CALCULATION TABLE");

    cout << left
         << setw(10) << "i"
         << setw(15) << "x"
         << setw(15) << "f(x)"
         << endl;

    drawLine(40);

    for(int i = 0; i <= n; i++)
    {
        cout << left
             << setw(10) << i
             << setw(15) << formatNumber(x[i])
             << setw(15) << formatNumber(fx[i])
             << endl;
    }

    drawLine(40);

    double sum = fx[0] + fx[n];

    for(int i = 1; i < n; i++)
    {
        sum += 2 * fx[i];
    }

    double answer = (h / 2.0) * sum;

    printTitle("   RESULT");

    cout << "Step Size (h) : "
         << formatNumber(h)
         << endl;

    cout << "Approximate Integral : "
         << formatNumber(answer)
         << endl;
}

void simpsonOneThirdRule()
{
    ExpressionParser parser;

    string equation;

    double a, b;
    int n;

    printTitle("     SIMPSON'S 1/3 RULE");

    cin.ignore();

    cout << "Enter Equation : ";
    getline(cin, equation);

    parser.setExpression(equation);

    cout << "Enter Lower Limit : ";
    cin >> a;

    cout << "Enter Upper Limit : ";
    cin >> b;

    cout << "Enter Number of Subintervals : ";
    cin >> n;

    if(n % 2 != 0)
    {
        cout << "\nError : Simpson's 1/3 Rule requires EVEN number of intervals.\n";
        return;
    }

    double h = (b - a) / n;

    vector<double> x(n + 1);
    vector<double> fx(n + 1);

    for(int i = 0; i <= n; i++)
    {
        x[i] = a + i * h;
        fx[i] = parser.evaluate(x[i]);
    }

    printTitle("     CALCULATION TABLE");

    cout << left
         << setw(10) << "i"
         << setw(15) << "x"
         << setw(15) << "f(x)"
         << endl;

    drawLine(40);

    for(int i = 0; i <= n; i++)
    {
        cout << left
             << setw(10) << i
             << setw(15) << formatNumber(x[i])
             << setw(15) << formatNumber(fx[i])
             << endl;
    }

    drawLine(40);

    double sum = fx[0] + fx[n];

    for(int i = 1; i < n; i++)
    {
        if(i % 2 == 0)
            sum += 2 * fx[i];
        else
            sum += 4 * fx[i];
    }

    double answer = (h / 3.0) * sum;

    printTitle("    RESULT");

    cout << "Step Size (h) : "
         << formatNumber(h)
         << endl;

    cout << "Approximate Integral : "
         << formatNumber(answer)
         << endl;
}

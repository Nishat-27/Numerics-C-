/*#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>

#include "Interpolation.h"
#include "Utility.h"

using namespace std;

void interpolationMenu()
{
    int choice;

    while(true)
    {
        printTitle("      INTERPOLATION METHODS");

        cout<<"1. Lagrange Interpolation\n";
        cout<<"2. Newton Divided Difference\n";
        cout<<"3. Back To Main Menu\n";

        cout<<"\nEnter Choice : ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            lagrangeInterpolation();
            break;

        case 2:
            newtonInterpolation();
            break;

        case 3:
            return;

        default:
            cout<<"\nInvalid Choice.\n";
        }
    }
}


void lagrangeInterpolation()
{
    const int MAX = 20;

    int n;

    double x[MAX];
    double y[MAX];

    double value;

    printTitle("     LAGRANGE INTERPOLATION");

    cout<<"Enter Number of Data Points : ";
    cin>>n;

    cout<<"\nEnter x and y values\n\n";

    for(int i=0; i<n; i++)
    {
        cout<<"x["<<i<<"] = ";
        cin>>x[i];

        cout<<"y["<<i<<"] = ";
        cin>>y[i];

        cout<<endl;
    }

    cout<<"Enter Interpolation Point : ";
    cin>>value;

    printTitle("    INPUT DATA");

    cout<<left
        <<setw(12)<<"x"
        <<setw(12)<<"y"
        <<endl;

    drawLine(24);

    for(int i=0; i<n; i++)
    {
        cout<<left
            <<setw(12)<<formatNumber(x[i])
            <<setw(12)<<formatNumber(y[i])
            <<endl;
    }

    drawLine(24);


    double answer = 0;

    vector<double> basis(n);

    for(int i=0; i<n; i++)
    {
        double term = 1;

        for(int j=0; j<n; j++)
        {
            if(i!=j)
            {
                term *=
                    (value-x[j])/(x[i]-x[j]);
            }
        }

        basis[i]=term;

        answer += term*y[i];
    }



    printTitle("     LAGRANGE BASIS VALUES");

    cout<<left
        <<setw(12)<<"Basis"
        <<setw(15)<<"Value"
        <<endl;

    drawLine(27);

    for(int i=0; i<n; i++)
    {
        cout<<left
            <<setw(12)
            <<("L"+to_string(i)+"(x)")
            <<setw(15)
            <<formatNumber(basis[i])
            <<endl;
    }

    drawLine(27);



    printTitle("     INTERPOLATED VALUE");

    cout<<"Interpolation Point : "
        <<formatNumber(value)
        <<endl;

    cout<<"Interpolated Value : "
        <<formatNumber(answer)
        <<endl;

    printTitle("     STATISTICS");

    cout<<"Method : Lagrange Interpolation\n";

    cout<<"Number of Points : "
        <<n
        <<endl;
}


void newtonInterpolation()
{
    const int MAX = 20;

    int n;

    double x[MAX];
    double y[MAX];

    double table[MAX][MAX];

    double value;

    auto start = chrono::high_resolution_clock::now();

    printTitle("     NEWTON DIVIDED DIFFERENCE");

    cout<<"Enter Number of Data Points : ";
    cin>>n;

    cout<<"\nEnter x and y values\n\n";

    for(int i=0; i<n; i++)
    {
        cout<<"x["<<i<<"] = ";
        cin>>x[i];

        cout<<"y["<<i<<"] = ";
        cin>>y[i];

        cout<<endl;
    }

    cout<<"Enter Interpolation Point : ";
    cin>>value;

    printTitle("INPUT DATA");

    cout<<left
        <<setw(12)<<"x"
        <<setw(12)<<"y"
        <<endl;

    drawLine(24);

    for(int i=0; i<n; i++)
    {
        cout<<left
            <<setw(12)<<formatNumber(x[i])
            <<setw(12)<<formatNumber(y[i])
            <<endl;
    }

    drawLine(24);


    for(int i=0; i<n; i++)
    {
        table[i][0]=y[i];
    }



    for(int j=1; j<n; j++)
    {
        for(int i=0; i<n-j; i++)
        {
            table[i][j]=
                (table[i+1][j-1]-table[i][j-1])/
                (x[i+j]-x[i]);
        }
    }



    printTitle("     POLYNOMIAL EVALUATION");

    cout << left
         << setw(8) << "Term"
         << setw(20) << "Coefficient"
         << setw(20) << "Product"
         << endl;

    drawLine(48);

     double product = 1.0;

    cout << left
         << setw(8) << "0"
         << setw(20) << formatNumber(table[0][0])
         << setw(20) << "1"
         << endl;

    for(int i = 1; i < n; i++)
    {
        product *= (value - x[i - 1]);

        cout << left
             << setw(8) << i
             << setw(20) << formatNumber(table[0][i])
             << setw(20) << formatNumber(product)
             << endl;
    }

    drawLine(48);



    printTitle("    INTERPOLATED VALUE");

    cout << "Interpolation Point : "
         << formatNumber(value)
         << endl;

    cout << "Interpolated Value : "
         << formatNumber(answer)
         << endl;

    auto stop = chrono::high_resolution_clock::now();

    auto duration =
        chrono::duration_cast<chrono::microseconds>
        (stop - start);

    printTitle("STATISTICS");

    cout << "Method              : Newton Divided Difference" << endl;

    cout << "Number of Points    : "
         << n
         << endl;

    cout << "Interpolation Point : "
         << formatNumber(value)
         << endl;

    cout << "Interpolated Value  : "
         << formatNumber(answer)
         << endl;

    cout << "Execution Time      : "
         << duration.count()
         << " microseconds"
         << endl;
}*/

/*#include <iostream>
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
}*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>

#include "Interpolation.h"
#include "Utility.h"

using namespace std;

void interpolationMenu()
{
    int choice;

    while(true)
    {
        printTitle("      INTERPOLATION METHODS");

        cout<<"1. Lagrange Interpolation\n";
        cout<<"2. Newton Divided Difference\n";
        cout<<"3. Back To Main Menu\n";

        cout<<"\nEnter Choice : ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            lagrangeInterpolation();
            break;

        case 2:
            newtonInterpolation();
            break;

        case 3:
            return;

        default:
            cout<<"\nInvalid Choice.\n";
        }
    }
}


void lagrangeInterpolation()
{
    const int MAX = 20;

    int n;

    double x[MAX];
    double y[MAX];

    double value;

    printTitle("     LAGRANGE INTERPOLATION");

    cout<<"Enter Number of Data Points : ";
    cin>>n;

    cout<<"\nEnter x and y values\n\n";

    for(int i=0; i<n; i++)
    {
        cout<<"x["<<i<<"] = ";
        cin>>x[i];

        cout<<"y["<<i<<"] = ";
        cin>>y[i];

        cout<<endl;
    }

    cout<<"Enter Interpolation Point : ";
    cin>>value;

    printTitle("    INPUT DATA");

    cout<<left
        <<setw(12)<<"x"
        <<setw(12)<<"y"
        <<endl;

    drawLine(24);

    for(int i=0; i<n; i++)
    {
        cout<<left
            <<setw(12)<<formatNumber(x[i])
            <<setw(12)<<formatNumber(y[i])
            <<endl;
    }

    drawLine(24);

// Lagrange Algorithm

    double answer = 0;

    vector<double> basis(n);

    for(int i=0; i<n; i++)
    {
        double term = 1;

        for(int j=0; j<n; j++)
        {
            if(i!=j)
            {
                term *=
                    (value-x[j])/(x[i]-x[j]);
            }
        }

        basis[i]=term;

        answer += term*y[i];
    }


// Basis Polynomial Table
    printTitle("     LAGRANGE BASIS VALUES");

    cout<<left
        <<setw(12)<<"Basis"
        <<setw(15)<<"Value"
        <<endl;

    drawLine(27);

    for(int i=0; i<n; i++)
    {
        cout<<left
            <<setw(12)
            <<("L"+to_string(i)+"(x)")
            <<setw(15)
            <<formatNumber(basis[i])
            <<endl;
    }

    drawLine(27);


// Final Result

    printTitle("     INTERPOLATED VALUE");

    cout<<"Interpolation Point : "
        <<formatNumber(value)
        <<endl;

    cout<<"Interpolated Value : "
        <<formatNumber(answer)
        <<endl;

    printTitle("     STATISTICS");

    cout<<"Method : Lagrange Interpolation\n";

    cout<<"Number of Points : "
        <<n
        <<endl;
}


void newtonInterpolation()
{
    const int MAX = 20;

    int n;

    double x[MAX];
    double y[MAX];

    double table[MAX][MAX];

    double value;

    auto start = chrono::high_resolution_clock::now();

    printTitle("     NEWTON DIVIDED DIFFERENCE");

    cout<<"Enter Number of Data Points : ";
    cin>>n;

    cout<<"\nEnter x and y values\n\n";

    for(int i=0; i<n; i++)
    {
        cout<<"x["<<i<<"] = ";
        cin>>x[i];

        cout<<"y["<<i<<"] = ";
        cin>>y[i];

        cout<<endl;
    }

    cout<<"Enter Interpolation Point : ";
    cin>>value;

    printTitle("INPUT DATA");

    cout<<left
        <<setw(12)<<"x"
        <<setw(12)<<"y"
        <<endl;

    drawLine(24);

    for(int i=0; i<n; i++)
    {
        cout<<left
            <<setw(12)<<formatNumber(x[i])
            <<setw(12)<<formatNumber(y[i])
            <<endl;
    }

    drawLine(24);

    // Initialize Difference Table

    for(int i=0; i<n; i++)
    {
        table[i][0]=y[i];
    }


// Build Divided Difference Table

    for(int j=1; j<n; j++)
    {
        for(int i=0; i<n-j; i++)
        {
            table[i][j]=
                (table[i+1][j-1]-table[i][j-1])/
                (x[i+j]-x[i]);
        }
    }


    //------------------------------------------------
// Print Divided Difference Table

    printTitle("     POLYNOMIAL EVALUATION");

    cout << left
         << setw(8) << "Term"
         << setw(20) << "Coefficient"
         << setw(20) << "Product"
         << endl;

    drawLine(48);

    double answer  = table[0][0];
    double product = 1.0;

    cout << left
         << setw(8) << "0"
         << setw(20) << formatNumber(table[0][0])
         << setw(20) << "1"
         << endl;

    for(int i = 1; i < n; i++)
    {
        product *= (value - x[i - 1]);

        answer += table[0][i] * product;

        cout << left
             << setw(8) << i
             << setw(20) << formatNumber(table[0][i])
             << setw(20) << formatNumber(product)
             << endl;
    }

    drawLine(48);


// Final Result

    printTitle("    INTERPOLATED VALUE");

    cout << "Interpolation Point : "
         << formatNumber(value)
         << endl;

    cout << "Interpolated Value : "
         << formatNumber(answer)
         << endl;

    auto stop = chrono::high_resolution_clock::now();

    auto duration =
        chrono::duration_cast<chrono::microseconds>
        (stop - start);

    printTitle("STATISTICS");

    cout << "Method              : Newton Divided Difference" << endl;

    cout << "Number of Points    : "
         << n
         << endl;

    cout << "Interpolation Point : "
         << formatNumber(value)
         << endl;

    cout << "Interpolated Value  : "
         << formatNumber(answer)
         << endl;

    cout << "Execution Time      : "
         << duration.count()
         << " microseconds"
         << endl;
}

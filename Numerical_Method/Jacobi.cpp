#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include <chrono>

#include "Jacobi.h"
#include "LinearHelper.h"
#include "Utility.h"

using namespace std;

void printJacobiHeader(int n)
{
    cout<<left;

    cout<<setw(8)<<"Iter";

    for(int i=0; i<n; i++)
    {
        cout<<setw(12)
            <<("x"+to_string(i+1));
    }

    cout<<setw(12)
        <<"Error";

    cout<<endl;

    drawLine(8+12*n+12);
}

void printJacobiRow(int iter,
                    vector<double>& x,
                    double error)
{
    cout<<left;

    cout<<setw(8)
        <<iter;

    for(double value:x)
    {
        cout<<setw(12)
            <<formatNumber(value);
    }

    cout<<setw(12)
        <<formatNumber(error);

    cout<<endl;
}

void jacobiMethod()
{
    const int MAX=20;

    int n;

    double a[MAX][MAX+1];

    printTitle("     JACOBI ITERATION");
    auto start = chrono::high_resolution_clock::now();

    cout<<"Enter Number of Variables : ";
    cin>>n;

    cout<<"\nEnter Augmented Matrix\n\n";

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<=n; j++)
        {
            cin>>a[i][j];
        }
    }

    printTitle("    INPUT MATRIX");

    printMatrix(a,n);


    bool dominant=true;

    for(int i=0; i<n; i++)
    {
        double diagonal=fabs(a[i][i]);

        double sum=0;

        for(int j=0; j<n; j++)
        {
            if(i!=j)
                sum+=fabs(a[i][j]);
        }

        if(diagonal<sum)
        {
            dominant=false;
            break;
        }
    }

    printTitle("     DIAGONAL DOMINANCE CHECK");

    if(dominant)
    {
        cout<<"Matrix is Diagonally Dominant.\n";
        cout<<"Jacobi Method is expected to converge.\n";
    }
    else
    {
        cout<<"Warning!\n";
        cout<<"Matrix is NOT Diagonally Dominant.\n";
        cout<<"Jacobi may not converge.\n";
    }


    vector<double> x(n);
    vector<double> newX(n);

    printTitle("     INITIAL GUESS");

    cout << "Enter Initial Guess for Variables\n\n";

    for(int i=0; i<n; i++)
    {
        cout << "x" << i+1 << " = ";
        cin >> x[i];
    }

    double tolerance = 0.001;

    cout << "\nEnter Tolerance : ";
    cin >> tolerance;

    int maxIteration = 100;

    cout << "Enter Maximum Iterations : ";
    cin >> maxIteration;

    vector<JacobiIteration> history;

    for(int i=0; i<n; i++)
    {
        newX[i]=x[i];
    }

    printTitle("     INITIAL VALUES");

    cout << left
         << setw(10) << "Variable"
         << setw(15) << "Value"
         << endl;

    drawLine(25);

    for(int i=0; i<n; i++)
    {
        cout << left
             << setw(10) << ("x"+to_string(i+1))
             << setw(15) << formatNumber(x[i])
             << endl;
    }

    drawLine(25);

    cout << endl;

    cout << "Tolerance        : "
         << tolerance
         << endl;

    cout << "Max Iterations   : "
         << maxIteration
         << endl;


    int iteration = 0;
    double error = 0;

    while(iteration < maxIteration)
    {
        for(int i=0; i<n; i++)
        {
            double sum = 0;

            for(int j=0; j<n; j++)
            {
                if(i != j)
                {
                    sum += a[i][j] * x[j];
                }
            }

            newX[i] = (a[i][n] - sum) / a[i][i];
        }


        error = 0;

        for(int i=0; i<n; i++)
        {
            double currentError = fabs(newX[i] - x[i]);

            if(currentError > error)
                error = currentError;
        }


        JacobiIteration step;

        step.iteration = iteration + 1;
        step.values = newX;
        step.error = error;

        history.push_back(step);


        for(int i=0; i<n; i++)
        {
            x[i] = newX[i];
        }


        if(error < tolerance)
            break;

        iteration++;
    }



    printTitle("    JACOBI ITERATION TABLE");

    printJacobiHeader(n);

    for(size_t i=0; i<history.size(); i++)
    {
        printJacobiRow(
            history[i].iteration,
            history[i].values,
            history[i].error
        );
    }

    drawLine(8 + 12*n + 12);



    printTitle("     FINAL SOLUTION");

    cout<<left
        <<setw(12)<<"Variable"
        <<setw(15)<<"Value"
        <<endl;

    drawLine(27);

    for(int i=0; i<n; i++)
    {
        cout<<left
            <<setw(12)
            <<("x"+to_string(i+1))
            <<setw(15)
            <<formatNumber(x[i])
            <<endl;
    }

    drawLine(27);


    printTitle("     STATISTICS");

    cout<<"Total Iterations : "
        <<history.size()
        <<endl;

    cout<<"Tolerance : "
        <<formatNumber(tolerance)
        <<endl;

    cout<<"Final Error : "
        <<formatNumber(error)
        <<endl;

    if(error<tolerance)
    {
        cout<<"Status : Converged Successfully."
            <<endl;
    }
    else
    {
        cout<<"Status : Maximum Iteration Reached."
            <<endl;
    }

    auto stop = chrono::high_resolution_clock::now();

    auto duration =
        chrono::duration_cast<chrono::milliseconds>
        (stop-start);

    cout<<"Execution Time : "
        <<duration.count()
        <<" ms"
        <<endl;
}

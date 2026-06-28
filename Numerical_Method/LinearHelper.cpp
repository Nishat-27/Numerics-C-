#include <iostream>
#include <iomanip>
#include <cmath>

#include "LinearHelper.h"
#include "Utility.h"

using namespace std;

void printMatrix(double a[MAX][MAX+1], int n)
{
    cout << endl;

    cout << setw(5) << " ";

    for(int i=0; i<n; i++)
    {
        cout << setw(10) << ("x" + to_string(i+1));
    }

    cout << setw(10) << "B" << endl;

    drawLine(5 + 10*(n+1));

    for(int i=0; i<n; i++)
    {
        cout << setw(5) << i+1;

        for(int j=0; j<=n; j++)
        {
            cout << setw(10) << formatNumber(a[i][j]);
        }

        cout << endl;
    }

    drawLine(5 + 10*(n+1));

    cout << endl;
}

void printSolution(double x[],int n)
{
    printTitle("     FINAL SOLUTION");

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
}

void swapRows(double a[MAX][MAX+1],int r1,int r2,int n)
{
    for(int j=0; j<=n; j++)
    {
        swap(a[r1][j],a[r2][j]);
    }
}

/*void printSquareMatrix(double matrix[][20], int n)
{
    cout << left;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << setw(10)
                 << formatNumber(matrix[i][j]);
        }

        cout << endl;
    }
}*/

void printSquareMatrix(double matrix[][MAX], int n)
{
    cout << left;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << setw(10)
                 << formatNumber(matrix[i][j]);
        }

        cout << endl;
    }
}

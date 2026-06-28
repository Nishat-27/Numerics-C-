#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

#include "GaussJordan.h"
#include "LinearHelper.h"
#include "Utility.h"

using namespace std;

void gaussJordan()
{
    const double EPS = 1e-9;

    int n;

    double a[MAX][MAX+1];

    printTitle("     GAUSS JORDAN ELIMINATION");

    auto start = chrono::high_resolution_clock::now();

    int rowOperations = 0;

    cout << "Enter Number of Variables : ";
    cin >> n;

    cout << "\nEnter Augmented Matrix\n\n";

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<=n; j++)
        {
            cin >> a[i][j];
        }
    }

    printTitle("     AUGMENTED MATRIX");

    printMatrix(a,n);

    for(int k=0; k<n; k++)
    {
        if(fabs(a[k][k])<EPS)
        {
            cout<<"\nZero Pivot Found.\n";
            return;
        }

        printTitle("STEP-"+to_string(k+1));

        cout<<"Normalize Pivot Row (R"<<k+1<<")"<<endl;

        double pivot=a[k][k];

        cout<<"\nOperation :\n";

        cout<<"R"<<k+1
            <<" = R"<<k+1
            <<" / "
            <<formatNumber(pivot)
            <<endl;

        for(int j=0; j<=n; j++)
            a[k][j]/=pivot;

        printTitle("     UPDATED MATRIX");

        printMatrix(a,n);


        for(int i=0; i<n; i++)
        {
            if(i==k)
                continue;

            double factor=a[i][k];

            if(fabs(factor)<EPS)
                continue;

            cout<<"\nEliminate R"<<i+1<<endl;

            cout<<"Operation :\n";

            cout<<"R"<<i+1
                <<" = R"<<i+1
                <<" - "
                <<formatNumber(factor)
                <<" * R"
                <<k+1
                <<endl;

            for(int j=0; j<=n; j++)
            {
                a[i][j]-=factor*a[k][j];
            }
            rowOperations++;

            printTitle("     UPDATED MATRIX");

            printMatrix(a,n);
        }
    }

    printTitle("     REDUCED ROW ECHELON FORM");

    printMatrix(a,n);


    bool singular = false;

    for(int i=0; i<n; i++)
    {
        bool allZero = true;

        for(int j=0; j<n; j++)
        {
            if(fabs(a[i][j]) > EPS)
            {
                allZero = false;
                break;
            }
        }

        if(allZero && fabs(a[i][n]) > EPS)
        {
            printTitle("     RESULT");
            cout << "No Solution Exists.\n";

            auto stop = chrono::high_resolution_clock::now();

            auto duration =
                chrono::duration_cast<chrono::milliseconds>(stop-start);

            cout<<"\nExecution Time : "
                <<duration.count()
                <<" ms\n";

            return;
        }

        if(allZero && fabs(a[i][n]) < EPS)
        {
            singular = true;
        }
    }

    if(singular)
    {
        printTitle("     RESULT");

        cout<<"Infinite Solutions Exist.\n";

        auto stop = chrono::high_resolution_clock::now();

        auto duration =
            chrono::duration_cast<chrono::milliseconds>(stop-start);

        cout<<"\nExecution Time : "
            <<duration.count()
            <<" ms\n";

        return;
    }


    printTitle("     FINAL SOLUTION");

    for(int i=0; i<n; i++)
    {
        cout<<"x"<<i+1<<" = "
            <<formatNumber(a[i][n])
            <<endl;
    }

    auto stop = chrono::high_resolution_clock::now();

    auto duration =
        chrono::duration_cast<chrono::milliseconds>(stop-start);

    printTitle("     STATISTICS");

    cout<<"Total Row Operations : "
        <<rowOperations
        <<endl;

    cout<<"Execution Time : "
        <<duration.count()
        <<" ms"
        <<endl;
}

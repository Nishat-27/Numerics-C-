#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>


#include "LinearMethods.h"
#include "Utility.h"
#include "GaussJordan.h"
#include "LinearHelper.h"
#include "Jacobi.h"

using namespace std;

//const int MAX = 20;

void gaussElimination()
{
    int n;

    double a[MAX][MAX+1];

    printTitle("       GAUSS ELIMINATION");

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

    printTitle("        AUGMENTED MATRIX");

    printMatrix(a,n);

    // Forward Elimination
    for(int k = 0; k < n - 1; k++)
    {
        // Partial Pivoting
        int pivotRow = k;

        for(int i = k + 1; i < n; i++)
        {
            if(fabs(a[i][k]) > fabs(a[pivotRow][k]))
            {
                pivotRow = i;
            }
        }

        if(pivotRow != k)
        {
            swapRows(a, k, pivotRow, n);

            cout << "\nRows Swapped : R"
                 << k + 1
                 << " <-> R"
                 << pivotRow + 1
                 << endl;

            printMatrix(a, n);
        }

        cout << "\nCurrent Pivot = "
             << formatNumber(a[k][k])
             << endl;

        // Eliminate rows
        for(int i = k + 1; i < n; i++)
        {
            if(fabs(a[k][k]) < 1e-12)
            {
                cout << "\nZero Pivot Found.\n";
                return;
            }

            double factor = a[i][k] / a[k][k];

            cout << "\n---------------------------------------------\n";

            cout << "Eliminate Row R"
                 << i + 1
                 << endl;

            cout << "Factor = "
                 << formatNumber(factor)
                 << endl;

            cout << "Operation : ";

            cout << "R"
                 << i + 1
                 << " = R"
                 << i + 1
                 << " - ("
                 << formatNumber(factor)
                 << " * R"
                 << k + 1
                 << ")"
                 << endl;

            for(int j = k; j <= n; j++)
            {
                a[i][j] = a[i][j] - factor * a[k][j];
            }

            cout << "\nUpdated Matrix\n";

            printMatrix(a, n);
        }
    }

    /*printTitle("UPPER TRIANGULAR MATRIX");

    printMatrix(a, n);

    cout << "\nBack Substitution will be implemented in Part-3.\n";*/
    printTitle("   UPPER TRIANGULAR MATRIX");

    printMatrix(a,n);


    // Back Substitution
    double x[MAX];

    printTitle("   BACK SUBSTITUTION");

    for(int i=n-1; i>=0; i--)
    {
        double sum = 0;

        cout << "\nFinding x" << i+1 << endl;

        if(fabs(a[i][i]) < 1e-12)
        {
            cout << "Zero Pivot Found.\n";
            return;
        }

        for(int j=i+1; j<n; j++)
        {
            sum += a[i][j] * x[j];

            cout
                    << "a[" << i+1 << "][" << j+1 << "]"
                    << " * x" << j+1
                    << " = "
                    << formatNumber(a[i][j])
                    << " * "
                    << formatNumber(x[j])
                    << endl;
        }

        cout << "\nFormula:\n";

        cout << "x" << i+1
             << " = ("
             << formatNumber(a[i][n])
             << " - "
             << formatNumber(sum)
             << ") / "
             << formatNumber(a[i][i])
             << endl;

        x[i]=(a[i][n]-sum)/a[i][i];

        cout << "x"
             << i+1
             << " = "
             << formatNumber(x[i])
             << endl;
    }

    printSolution(x,n);
}

void linearAlgebraMenu()
{
    int choice;

    while(true)
    {
        printTitle("     LINEAR ALGEBRA METHODS");

        cout << "1. Gauss Elimination\n";
        cout << "2. Gauss Jordan\n";
        cout << "3. Jacobi Iteration\n";
        cout << "4. LU Decomposition (Doolittle)\n";
        cout << "5. Back to Main Menu\n";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch(choice)
        {
        case 1:
            gaussElimination();
            break;

        case 2:
            gaussJordan();
            break;

        case 3:
            jacobiMethod();
            break;

        case 4:
            doolittleLU();
            break;

        case 5:
            return;

        default:
            cout << "\nInvalid Choice.\n";
        }
    }
}

void doolittleLU()
{
    const int MAX = 20;

    int n;

    double A[MAX][MAX];
    double L[MAX][MAX];
    double U[MAX][MAX];

    printTitle("    LU DECOMPOSITION (DOOLITTLE METHOD)");

    auto start = chrono::high_resolution_clock::now();

    cout<<"Enter Number of Variables : ";
    cin>>n;

    cout<<"\nEnter Coefficient Matrix\n\n";

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin>>A[i][j];
        }
    }


    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            L[i][j]=0;
            U[i][j]=0;
        }
    }


    printTitle("     MATRIX");

    cout<<left;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<setw(10)
                <<formatNumber(A[i][j]);
        }

        cout<<endl;
    }



    for(int i=0; i<n; i++)
    {
        for(int k=i; k<n; k++)
        {
            double sum = 0;

            for(int j=0; j<i; j++)
            {
                sum += L[i][j] * U[j][k];
            }

            U[i][k] = A[i][k] - sum;
        }

        for(int k=i; k<n; k++)
        {
            if(i == k)
            {
                L[i][i] = 1;
            }
            else
            {
                double sum = 0;

                for(int j=0; j<i; j++)
                {
                    sum += L[k][j] * U[j][i];
                }

                if(fabs(U[i][i]) < 1e-12)
                {
                    cout << "\nLU Decomposition Failed.\n";
                    cout << "Pivot became zero.\n";
                    return;
                }

                L[k][i] =
                    (A[k][i] - sum) / U[i][i];
            }
        }
    }


    printTitle("    LOWER TRIANGULAR MATRIX (L)");
    printSquareMatrix(L, n);


    printTitle("    UPPER TRIANGULAR MATRIX (U)");
    printSquareMatrix(U, n);



    double V[MAX][MAX];

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            V[i][j]=0;

            for(int k=0; k<n; k++)
            {
                V[i][j]+=L[i][k]*U[k][j];
            }
        }
    }



    printTitle("    VERIFICATION MATRIX (L x U)");
    printSquareMatrix(V, n);


    bool verified = true;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(fabs(A[i][j]-V[i][j]) > 0.001)
            {
                verified = false;
                break;
            }
        }

        if(!verified)
            break;
    }

    printTitle("VERIFICATION RESULT");

    if(verified)
    {
        cout<<"LU Decomposition Verified Successfully.\n";
        cout<<"Status : PASS\n";
    }
    else
    {
        cout<<"Verification Failed.\n";
        cout<<"Status : FAIL\n";
    }


// Statistics

   /* auto stop = chrono::high_resolution_clock::now();

    auto duration =
        chrono::duration_cast<chrono::milliseconds>
        (stop-start);

    printTitle("     STATISTICS");

    cout<<"Matrix Size : "
        <<n<<" x "<<n
        <<endl;

    cout<<"Method : Doolittle LU Decomposition"
        <<endl;

    cout<<"Execution Time : "
        <<duration.count()
        <<" ms"
        <<endl;*/
}

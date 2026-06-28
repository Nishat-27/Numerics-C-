#include <iostream>

#include "Utility.h"
#include "RootFinding.h"
#include "LinearMethods.h"
//#include "Jacobi.h"
#include "Interpolation.h"
#include "Integration.h"

using namespace std;

void rootFindingMenu();
void linearAlgebraMenu();

int main()
{
    int choice;

    while(true)
    {

        printTitle("       INTERACTIVE NUMERICAL METHODS");

        cout << "\n1. Root Finding Methods\n";
        cout << "2. Linear Algebra Methods\n";
        cout << "3. Interpolation Methods\n";
        cout << "4. Numerical Integration\n";
        cout << "5. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch(choice)
        {
        case 1:
            rootFindingMenu();
            break;

        case 2:
            linearAlgebraMenu();
            break;

        case 3:
            interpolationMenu();
            break;

        case 4:

            integrationMenu();

            break;


        case 5:
            return 0;

        default:
            cout << "\nInvalid Choice.\n";
        }
    }
}


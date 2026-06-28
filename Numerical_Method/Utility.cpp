#include "Utility.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <limits>

using namespace std;

string formatNumber(double num)
{
    if(fabs(num-round(num))<0.000001)
    {
        return to_string((int)round(num));
    }

    stringstream ss;

    ss<<fixed<<setprecision(2)<<num;

    return ss.str();
}

void drawLine(int length)
{
    for(int i=0;i<length;i++)
    {
        cout<<"=";
    }

    cout<<endl;
}

void printTitle(string title)
{
    cout<<endl;

    drawLine();

    cout<<title<<endl;

    drawLine();
}

void pressEnterToContinue()
{
    cout<<"\nPress Enter to Continue...";

    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    cin.get();
}

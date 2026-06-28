#ifndef JACOBI_H
#define JACOBI_H

#include <vector>

struct JacobiIteration
{
    int iteration;
    std::vector<double> values;
    double error;
};

void jacobiMethod();

#endif

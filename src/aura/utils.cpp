#include "main.h"
#include "aura/utils.hpp"

double linearToCubed(double input, double maxInput, double k)
{
    return k * (pow(input, 3) / pow(maxInput, 2)) + ( (1 -  k )* input);
}

double pctToVoltage(double input)
{
    return 12000 * (input / 127);
}

int sign(double num)
{
    return (num >= 0) ? 1 : -1;
}
#include "MathFunctions.h"

double MathFunctions::joystickCurve(double x, double a) {
    return x / (1 + a * (1 - x));
}
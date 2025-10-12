#include "Math.h"

int Math::Floor(float V)
{
    return (int)V - ((int)V > V); // Stolen... :)
    // Proof:
    // (int)V = V.trunc()
    // false = 0
    // true = 1
    // 
    // V = 0.0
    //  0 - (0 > 0) = 0 - false = 0
    // 
    // V = 2.9
    //  2 - (2 > 2.9) = 2 - false = 2
    // 
    // V = -1.7
    //  -1 - (-1 > -1.7) = -1 - true = -2
}

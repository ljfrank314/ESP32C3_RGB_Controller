#include "Step.h"

float robjohn(float t, float d, float a) //weird blend curve found on stack overflow, i just named it after OP. higher values of a produce a steeper slope in the middle. d is the duration of the step
{
    float pwr = pow( t , a );
    return pwr/( pwr + pow( (d-t) , a ) );
}
#include "Step.h"
/* weird blend curve found on stack overflow,
* i just named it after OP. higher values of
* a produce a steeper slope in the middle,
* which starts linear at 1 and equals a step
* function at infinity
* d is the duration of the step
*/

float robjohn(float t, float d, float a)
{
    t=t+0.0001; //prevent overflow, t CANNOT equal 0
    float pwr = pow( t , a );
    return pwr/( pwr + pow( (d-t) , a ) );
}
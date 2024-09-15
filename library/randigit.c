#include "randigit.h"
#include "time.h"

long randigit (long divider)
{
    clock_t now;
    now = clock ();
    long digit = now;
    if (digit < 0)
    {
       	digit *= -1;
    }
    if (digit >= divider)
    {
       	digit %= divider;
    }
    return digit;
}
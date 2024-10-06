#include "randigit.h"
#include "time.h"

long randigit (long divider)
{
	clock_t now;
	now = clock ();
	long digit = now;
	if (digit > divider)
	{
		digit = digit % divider;
	}
	return digit;
}

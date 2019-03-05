//Adam Cole
//randlibhw.c
//assn 7

#include "randlib.h"
#include <immintrin.h>

//implement the interface described by randlib.h

/* Hardware implementation.  */

/* Return a random value, using hardware operations.  */
extern unsigned long long
hardware_rand64 (void)
{
  unsigned long long int x;
  while (! _rdrand64_step (&x))
    continue;
  return x;
}
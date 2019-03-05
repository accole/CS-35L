//Adam Cole
//randlibsw.c
//assn 7

#include "randlib.h"
#include <stdio.h>
#include <stdlib.h>

//implement the interface described by randlib.h
//and should also define a constructor and destructor

/* Software implementation.  */

/* Input stream containing random bytes.  */
static FILE *urandstream;

/* Initialize the software rand64 implementation.  */
__attribute__ ((__constructor__))
static void
software_rand64_init (void)
{
  urandstream = fopen ("/dev/urandom", "r");
  if (! urandstream)
    abort ();
}

/* Return a random value, using software operations.  */
extern unsigned long long
software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1)
    abort ();
  return x;
}

/* Finalize the software rand64 implementation.  */
__attribute__ ((__destructor__))
static void
software_rand64_fini (void)
{
  fclose (urandstream);
}



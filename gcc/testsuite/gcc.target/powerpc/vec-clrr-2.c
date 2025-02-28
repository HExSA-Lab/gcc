/* { dg-do compile } */
/* { dg-options "-mdejagnu-cpu=future" } */

#include <altivec.h>

extern void abort (void);

/* Vector string clear right-most bytes of unsigned char.  */
vector signed char
clrr (vector signed char arg, int n)
{
  return vec_clrr (arg, n);
}

/* { dg-final { scan-assembler {\mvclrrb\M} { target be } } } */
/* { dg-final { scan-assembler {\mvclrlb\M} { target le } } } */

/* { dg-do compile } */
/* { dg-options "-O2 -mdejagnu-cpu=future" } */

#define NAME eq
#define CODE ==

#include "setbc.h"

/* { dg-final { scan-assembler-times {\msetbc\M} 20 } } */

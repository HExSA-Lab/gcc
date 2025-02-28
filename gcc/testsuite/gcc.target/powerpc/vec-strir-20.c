/* { dg-do run } */
/* { dg-require-effective-target powerpc_future_hw } */
/* { dg-options "-O1 -mdejagnu-cpu=future" } */
/* See vec-strir-21.c for the same test with -O2 optimization.  */

#include <altivec.h>

extern void abort (void);

vector unsigned short
doString(vector unsigned short *vp)
{
  /* Though two built-in functions are called, the implementation
     should use a single instruction to implement both with -O1.  */
  vector unsigned short result = vec_strir (*vp);
  if (vec_strir_p (*vp))
    return result;
  else
    return doString (vp + 1);
}

int main (int argc, short *argv [])
{
  vector unsigned short composed_string [4] = {
    { 0x1, 0x3, 0x5, 0x7, 0x9, 0xb, 0xd, 0xf },
    { 0x1, 0x0, 0x5, 0x7, 0x9, 0xb, 0xd, 0xf },
    { 0x1, 0x0, 0x5, 0x7, 0x9, 0xb, 0xd, 0x0 },
    { 0x1, 0x3, 0x5, 0x7, 0x9, 0x0, 0xd, 0xe }
  };

  vector unsigned short expected0 =
    { 0x1, 0x3, 0x5, 0x7, 0x9, 0xb, 0xd, 0xf };
  vector unsigned short expected1 =
    { 0x0, 0x0, 0x5, 0x7, 0x9, 0xb, 0xd, 0xf };
  vector unsigned short expected2 =
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
  vector unsigned short expected3 =
    { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xd, 0xe };

  if (!vec_all_eq (doString (&composed_string[0]), expected1))
    abort ();
  if (!vec_all_eq (doString (&composed_string[1]), expected1))
    abort ();
  if (!vec_all_eq (doString (&composed_string[2]), expected2))
    abort ();
  if (!vec_all_eq (doString (&composed_string[3]), expected3))
    abort ();
}

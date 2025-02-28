/* { dg-do run } */
/* { dg-require-effective-target powerpc_future_hw } */
/* { dg-options "-mdejagnu-cpu=future" } */

#include <altivec.h>

extern void abort (void);

/* Vector string isolate right-justified on array of unsigned char.  */
int
sirj_p (vector unsigned char arg)
{
  return vec_strir_p (arg);
}

int main (int argc, char *argv [])
{
  vector unsigned char input1 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x11 };
  vector unsigned char input2 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0x0, 0xf, 0x11 };
  vector unsigned char input3 =
    { 0x1, 0x2, 0x0, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0x0, 0xf, 0x11 };
  vector unsigned char input4 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0x0, 0xf, 0x11 };

  if (sirj_p (input1))
    abort ();
  if (!sirj_p (input2))
    abort ();
  if (!sirj_p (input3))
    abort ();
  if (!sirj_p (input4))
    abort ();
}

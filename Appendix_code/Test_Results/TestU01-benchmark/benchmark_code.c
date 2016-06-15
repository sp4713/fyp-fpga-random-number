#include "swrite.h"
#include "bbattery.h"
#include "usoft.h"
#include "unif01.h"
#include "ulcg.h"
#include "unif01.h"

int main (void)
{
   unif01_Gen *gen;
   gen = ulcg_CreateLCG2e31 (16807, 0, 12345);	//creates RANDU RNG
   bbattery_Alphabit(gen, 68719476736, 0, 32);	//calls Alphabit battery of tests
   ulcg_DeleteGen (gen);
   return 0;
}

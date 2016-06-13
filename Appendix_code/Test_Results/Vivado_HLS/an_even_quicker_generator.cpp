//An Even Quicker Generator
/*
  In C, if you multiply two unsigned long int integers on a machine with a 32-bit long
  integer representation, the value returned is the low-order 32 bits of the true 64-bit product. If
  we now choose m = 232, the “mod” in equation (7.1.1) is free, and we have simply
  Ij+1 = aIj + c (7.1.6)
  Knuth suggests a = 1664525 as a suitable multiplier for this value of m. H.W. Lewis
  has conducted extensive tests of this value of a with c = 1013904223, which is a prime close
  to (
  √
  5 − 2)m. The resulting in-line generator (we will call it ranqd1) is simply
  unsigned long idum;
  ...
  idum = 1664525L*idum + 1013904223L;
  This is about as good as any 32-bit linear congruential generator, entirely adequate for many
  uses. And, with only a single multiply and add, it is very fast.
  To check whether your machine has the desired integer properties, see if you can
  generate the following sequence of 32-bit values (given here in hex): 00000000, 3C6EF35F,
  47502932, D1CCF6E9, AAF95334, 6252E503, 9F2EC686, 57FE6C2D, A3D95FA8, 81FDBEE7,
  94F0AF1A, CBF633B1
*/

//RNG Code

ap_uint<32> seedNext(ap_uint<32> seed){
	return 1664525L * seed + 1013904223L;
}

//Test Results

Frequency Test
Bit 0: Observed: 128. Expected: 128
Bit 1: Observed: 128. Expected: 128
Bit 2: Observed: 128. Expected: 128
Bit 3: Observed: 128. Expected: 128
Bit 4: Observed: 128. Expected: 128
Bit 5: Observed: 128. Expected: 128
Bit 6: Observed: 128. Expected: 128
Bit 7: Observed: 128. Expected: 128
Bit 8: Observed: 128. Expected: 128
Bit 9: Observed: 128. Expected: 128
Bit 10: Observed: 128. Expected: 128
Bit 11: Observed: 128. Expected: 128
Bit 12: Observed: 128. Expected: 128
Bit 13: Observed: 128. Expected: 128
Bit 14: Observed: 128. Expected: 128
Bit 15: Observed: 128. Expected: 128
Bit 16: Observed: 128. Expected: 128
Bit 17: Observed: 128. Expected: 128
Bit 18: Observed: 128. Expected: 128
Bit 19: Observed: 128. Expected: 128
Bit 20: Observed: 128. Expected: 128
Bit 21: Observed: 128. Expected: 128
Bit 22: Observed: 128. Expected: 128
Bit 23: Observed: 128. Expected: 128
Bit 24: Observed: 128. Expected: 128
Bit 25: Observed: 127. Expected: 128
Bit 26: Observed: 127. Expected: 128
Bit 27: Observed: 127. Expected: 128
Bit 28: Observed: 127. Expected: 128
Bit 29: Observed: 127. Expected: 128
Bit 30: Observed: 128. Expected: 128
Bit 31: Observed: 128. Expected: 128
2-Tuple Test
Bit 0, tuple 0: Observed: 0. Expected: 64
Bit 0, tuple 1: Observed: 0. Expected: 64
Bit 0, tuple 2: Observed: 256. Expected: 64
Bit 0, tuple 3: Observed: 0. Expected: 64
Bit 1, tuple 0: Observed: 128. Expected: 64
Bit 1, tuple 1: Observed: 0. Expected: 64
Bit 1, tuple 2: Observed: 0. Expected: 64
Bit 1, tuple 3: Observed: 128. Expected: 64
Bit 2, tuple 0: Observed: 0. Expected: 64
Bit 2, tuple 1: Observed: 128. Expected: 64
Bit 2, tuple 2: Observed: 128. Expected: 64
Bit 2, tuple 3: Observed: 0. Expected: 64
Bit 3, tuple 0: Observed: 64. Expected: 64
Bit 3, tuple 1: Observed: 64. Expected: 64
Bit 3, tuple 2: Observed: 64. Expected: 64
Bit 3, tuple 3: Observed: 64. Expected: 64
Bit 4, tuple 0: Observed: 96. Expected: 64
Bit 4, tuple 1: Observed: 32. Expected: 64
Bit 4, tuple 2: Observed: 32. Expected: 64
Bit 4, tuple 3: Observed: 96. Expected: 64
Bit 5, tuple 0: Observed: 48. Expected: 64
Bit 5, tuple 1: Observed: 80. Expected: 64
Bit 5, tuple 2: Observed: 80. Expected: 64
Bit 5, tuple 3: Observed: 48. Expected: 64
Bit 6, tuple 0: Observed: 64. Expected: 64
Bit 6, tuple 1: Observed: 64. Expected: 64
Bit 6, tuple 2: Observed: 64. Expected: 64
Bit 6, tuple 3: Observed: 64. Expected: 64
Bit 7, tuple 0: Observed: 60. Expected: 64
Bit 7, tuple 1: Observed: 68. Expected: 64
Bit 7, tuple 2: Observed: 68. Expected: 64
Bit 7, tuple 3: Observed: 60. Expected: 64
Bit 8, tuple 0: Observed: 62. Expected: 64
Bit 8, tuple 1: Observed: 66. Expected: 64
Bit 8, tuple 2: Observed: 66. Expected: 64
Bit 8, tuple 3: Observed: 62. Expected: 64
Bit 9, tuple 0: Observed: 62. Expected: 64
Bit 9, tuple 1: Observed: 66. Expected: 64
Bit 9, tuple 2: Observed: 66. Expected: 64
Bit 9, tuple 3: Observed: 62. Expected: 64
Bit 10, tuple 0: Observed: 64. Expected: 64
Bit 10, tuple 1: Observed: 64. Expected: 64
Bit 10, tuple 2: Observed: 64. Expected: 64
Bit 10, tuple 3: Observed: 64. Expected: 64
Bit 11, tuple 0: Observed: 64. Expected: 64
Bit 11, tuple 1: Observed: 63. Expected: 64
Bit 11, tuple 2: Observed: 63. Expected: 64
Bit 11, tuple 3: Observed: 66. Expected: 64
Bit 12, tuple 0: Observed: 64. Expected: 64
Bit 12, tuple 1: Observed: 64. Expected: 64
Bit 12, tuple 2: Observed: 64. Expected: 64
Bit 12, tuple 3: Observed: 64. Expected: 64
Bit 13, tuple 0: Observed: 64. Expected: 64
Bit 13, tuple 1: Observed: 64. Expected: 64
Bit 13, tuple 2: Observed: 64. Expected: 64
Bit 13, tuple 3: Observed: 64. Expected: 64
Bit 14, tuple 0: Observed: 64. Expected: 64
Bit 14, tuple 1: Observed: 64. Expected: 64
Bit 14, tuple 2: Observed: 64. Expected: 64
Bit 14, tuple 3: Observed: 64. Expected: 64
Bit 15, tuple 0: Observed: 64. Expected: 64
Bit 15, tuple 1: Observed: 63. Expected: 64
Bit 15, tuple 2: Observed: 63. Expected: 64
Bit 15, tuple 3: Observed: 66. Expected: 64
Bit 16, tuple 0: Observed: 64. Expected: 64
Bit 16, tuple 1: Observed: 64. Expected: 64
Bit 16, tuple 2: Observed: 64. Expected: 64
Bit 16, tuple 3: Observed: 64. Expected: 64
Bit 17, tuple 0: Observed: 63. Expected: 64
Bit 17, tuple 1: Observed: 64. Expected: 64
Bit 17, tuple 2: Observed: 64. Expected: 64
Bit 17, tuple 3: Observed: 65. Expected: 64
Bit 18, tuple 0: Observed: 64. Expected: 64
Bit 18, tuple 1: Observed: 63. Expected: 64
Bit 18, tuple 2: Observed: 63. Expected: 64
Bit 18, tuple 3: Observed: 66. Expected: 64
Bit 19, tuple 0: Observed: 63. Expected: 64
Bit 19, tuple 1: Observed: 64. Expected: 64
Bit 19, tuple 2: Observed: 64. Expected: 64
Bit 19, tuple 3: Observed: 65. Expected: 64
Bit 20, tuple 0: Observed: 63. Expected: 64
Bit 20, tuple 1: Observed: 63. Expected: 64
Bit 20, tuple 2: Observed: 64. Expected: 64
Bit 20, tuple 3: Observed: 66. Expected: 64
Bit 21, tuple 0: Observed: 63. Expected: 64
Bit 21, tuple 1: Observed: 63. Expected: 64
Bit 21, tuple 2: Observed: 63. Expected: 64
Bit 21, tuple 3: Observed: 67. Expected: 64
Bit 22, tuple 0: Observed: 63. Expected: 64
Bit 22, tuple 1: Observed: 64. Expected: 64
Bit 22, tuple 2: Observed: 63. Expected: 64
Bit 22, tuple 3: Observed: 66. Expected: 64
Bit 23, tuple 0: Observed: 63. Expected: 64
Bit 23, tuple 1: Observed: 63. Expected: 64
Bit 23, tuple 2: Observed: 64. Expected: 64
Bit 23, tuple 3: Observed: 66. Expected: 64
Bit 24, tuple 0: Observed: 64. Expected: 64
Bit 24, tuple 1: Observed: 63. Expected: 64
Bit 24, tuple 2: Observed: 63. Expected: 64
Bit 24, tuple 3: Observed: 66. Expected: 64
Bit 25, tuple 0: Observed: 64. Expected: 64
Bit 25, tuple 1: Observed: 63. Expected: 64
Bit 25, tuple 2: Observed: 64. Expected: 64
Bit 25, tuple 3: Observed: 65. Expected: 64
Bit 26, tuple 0: Observed: 64. Expected: 64
Bit 26, tuple 1: Observed: 64. Expected: 64
Bit 26, tuple 2: Observed: 64. Expected: 64
Bit 26, tuple 3: Observed: 64. Expected: 64
Bit 27, tuple 0: Observed: 64. Expected: 64
Bit 27, tuple 1: Observed: 64. Expected: 64
Bit 27, tuple 2: Observed: 64. Expected: 64
Bit 27, tuple 3: Observed: 64. Expected: 64
Bit 28, tuple 0: Observed: 64. Expected: 64
Bit 28, tuple 1: Observed: 63. Expected: 64
Bit 28, tuple 2: Observed: 63. Expected: 64
Bit 28, tuple 3: Observed: 66. Expected: 64
Bit 29, tuple 0: Observed: 64. Expected: 64
Bit 29, tuple 1: Observed: 64. Expected: 64
Bit 29, tuple 2: Observed: 63. Expected: 64
Bit 29, tuple 3: Observed: 65. Expected: 64
Bit 30, tuple 0: Observed: 63. Expected: 64
Bit 30, tuple 1: Observed: 63. Expected: 64
Bit 30, tuple 2: Observed: 64. Expected: 64
Bit 30, tuple 3: Observed: 66. Expected: 64
Bit 31, tuple 0: Observed: 63. Expected: 64
Bit 31, tuple 1: Observed: 63. Expected: 64
Bit 31, tuple 2: Observed: 64. Expected: 64
Bit 31, tuple 3: Observed: 66. Expected: 64
3-Tuple Test
Bit 1, tuple 0: Observed: 0. Expected: 21
Bit 1, tuple 1: Observed: 42. Expected: 21
Bit 1, tuple 2: Observed: 0. Expected: 21
Bit 1, tuple 3: Observed: 42. Expected: 21
Bit 1, tuple 4: Observed: 42. Expected: 21
Bit 1, tuple 5: Observed: 0. Expected: 21
Bit 1, tuple 6: Observed: 42. Expected: 21
Bit 1, tuple 7: Observed: 2. Expected: 21
Bit 3, tuple 0: Observed: 10. Expected: 21
Bit 3, tuple 1: Observed: 21. Expected: 21
Bit 3, tuple 2: Observed: 32. Expected: 21
Bit 3, tuple 3: Observed: 21. Expected: 21
Bit 3, tuple 4: Observed: 21. Expected: 21
Bit 3, tuple 5: Observed: 32. Expected: 21
Bit 3, tuple 6: Observed: 21. Expected: 21
Bit 3, tuple 7: Observed: 12. Expected: 21
Bit 5, tuple 0: Observed: 13. Expected: 21
Bit 5, tuple 1: Observed: 21. Expected: 21
Bit 5, tuple 2: Observed: 29. Expected: 21
Bit 5, tuple 3: Observed: 21. Expected: 21
Bit 5, tuple 4: Observed: 21. Expected: 21
Bit 5, tuple 5: Observed: 29. Expected: 21
Bit 5, tuple 6: Observed: 21. Expected: 21
Bit 5, tuple 7: Observed: 15. Expected: 21
Bit 7, tuple 0: Observed: 20. Expected: 21
Bit 7, tuple 1: Observed: 19. Expected: 21
Bit 7, tuple 2: Observed: 24. Expected: 21
Bit 7, tuple 3: Observed: 19. Expected: 21
Bit 7, tuple 4: Observed: 20. Expected: 21
Bit 7, tuple 5: Observed: 24. Expected: 21
Bit 7, tuple 6: Observed: 20. Expected: 21
Bit 7, tuple 7: Observed: 24. Expected: 21
Bit 9, tuple 0: Observed: 21. Expected: 21
Bit 9, tuple 1: Observed: 21. Expected: 21
Bit 9, tuple 2: Observed: 21. Expected: 21
Bit 9, tuple 3: Observed: 21. Expected: 21
Bit 9, tuple 4: Observed: 21. Expected: 21
Bit 9, tuple 5: Observed: 21. Expected: 21
Bit 9, tuple 6: Observed: 21. Expected: 21
Bit 9, tuple 7: Observed: 23. Expected: 21
Bit 11, tuple 0: Observed: 21. Expected: 21
Bit 11, tuple 1: Observed: 21. Expected: 21
Bit 11, tuple 2: Observed: 21. Expected: 21
Bit 11, tuple 3: Observed: 21. Expected: 21
Bit 11, tuple 4: Observed: 21. Expected: 21
Bit 11, tuple 5: Observed: 21. Expected: 21
Bit 11, tuple 6: Observed: 21. Expected: 21
Bit 11, tuple 7: Observed: 23. Expected: 21
Bit 13, tuple 0: Observed: 21. Expected: 21
Bit 13, tuple 1: Observed: 21. Expected: 21
Bit 13, tuple 2: Observed: 21. Expected: 21
Bit 13, tuple 3: Observed: 21. Expected: 21
Bit 13, tuple 4: Observed: 21. Expected: 21
Bit 13, tuple 5: Observed: 21. Expected: 21
Bit 13, tuple 6: Observed: 21. Expected: 21
Bit 13, tuple 7: Observed: 23. Expected: 21
Bit 15, tuple 0: Observed: 21. Expected: 21
Bit 15, tuple 1: Observed: 21. Expected: 21
Bit 15, tuple 2: Observed: 21. Expected: 21
Bit 15, tuple 3: Observed: 21. Expected: 21
Bit 15, tuple 4: Observed: 21. Expected: 21
Bit 15, tuple 5: Observed: 21. Expected: 21
Bit 15, tuple 6: Observed: 21. Expected: 21
Bit 15, tuple 7: Observed: 23. Expected: 21
Bit 17, tuple 0: Observed: 21. Expected: 21
Bit 17, tuple 1: Observed: 21. Expected: 21
Bit 17, tuple 2: Observed: 21. Expected: 21
Bit 17, tuple 3: Observed: 21. Expected: 21
Bit 17, tuple 4: Observed: 21. Expected: 21
Bit 17, tuple 5: Observed: 21. Expected: 21
Bit 17, tuple 6: Observed: 21. Expected: 21
Bit 17, tuple 7: Observed: 23. Expected: 21
Bit 19, tuple 0: Observed: 21. Expected: 21
Bit 19, tuple 1: Observed: 21. Expected: 21
Bit 19, tuple 2: Observed: 21. Expected: 21
Bit 19, tuple 3: Observed: 21. Expected: 21
Bit 19, tuple 4: Observed: 21. Expected: 21
Bit 19, tuple 5: Observed: 21. Expected: 21
Bit 19, tuple 6: Observed: 21. Expected: 21
Bit 19, tuple 7: Observed: 23. Expected: 21
Bit 21, tuple 0: Observed: 21. Expected: 21
Bit 21, tuple 1: Observed: 21. Expected: 21
Bit 21, tuple 2: Observed: 21. Expected: 21
Bit 21, tuple 3: Observed: 21. Expected: 21
Bit 21, tuple 4: Observed: 21. Expected: 21
Bit 21, tuple 5: Observed: 21. Expected: 21
Bit 21, tuple 6: Observed: 21. Expected: 21
Bit 21, tuple 7: Observed: 23. Expected: 21
Bit 23, tuple 0: Observed: 21. Expected: 21
Bit 23, tuple 1: Observed: 21. Expected: 21
Bit 23, tuple 2: Observed: 21. Expected: 21
Bit 23, tuple 3: Observed: 21. Expected: 21
Bit 23, tuple 4: Observed: 21. Expected: 21
Bit 23, tuple 5: Observed: 21. Expected: 21
Bit 23, tuple 6: Observed: 21. Expected: 21
Bit 23, tuple 7: Observed: 23. Expected: 21
Bit 25, tuple 0: Observed: 21. Expected: 21
Bit 25, tuple 1: Observed: 21. Expected: 21
Bit 25, tuple 2: Observed: 21. Expected: 21
Bit 25, tuple 3: Observed: 21. Expected: 21
Bit 25, tuple 4: Observed: 21. Expected: 21
Bit 25, tuple 5: Observed: 21. Expected: 21
Bit 25, tuple 6: Observed: 21. Expected: 21
Bit 25, tuple 7: Observed: 23. Expected: 21
Bit 27, tuple 0: Observed: 21. Expected: 21
Bit 27, tuple 1: Observed: 21. Expected: 21
Bit 27, tuple 2: Observed: 21. Expected: 21
Bit 27, tuple 3: Observed: 21. Expected: 21
Bit 27, tuple 4: Observed: 21. Expected: 21
Bit 27, tuple 5: Observed: 21. Expected: 21
Bit 27, tuple 6: Observed: 21. Expected: 21
Bit 27, tuple 7: Observed: 23. Expected: 21
Bit 29, tuple 0: Observed: 21. Expected: 21
Bit 29, tuple 1: Observed: 21. Expected: 21
Bit 29, tuple 2: Observed: 21. Expected: 21
Bit 29, tuple 3: Observed: 21. Expected: 21
Bit 29, tuple 4: Observed: 21. Expected: 21
Bit 29, tuple 5: Observed: 21. Expected: 21
Bit 29, tuple 6: Observed: 21. Expected: 21
Bit 29, tuple 7: Observed: 23. Expected: 21
Bit 31, tuple 0: Observed: 21. Expected: 21
Bit 31, tuple 1: Observed: 21. Expected: 21
Bit 31, tuple 2: Observed: 21. Expected: 21
Bit 31, tuple 3: Observed: 21. Expected: 21
Bit 31, tuple 4: Observed: 21. Expected: 21
Bit 31, tuple 5: Observed: 21. Expected: 21
Bit 31, tuple 6: Observed: 21. Expected: 21
Bit 31, tuple 7: Observed: 23. Expected: 21
INFO: [SIM 1] CSim done with 0 errors.

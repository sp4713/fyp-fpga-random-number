//RNG code
ap_uint<32> seedNext(ap_uint<32> seed){
	//insert custom RNG here
	if(seed==SEEDMAX){
		return 0;
	}else{
		return seed+1;
	}
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
Bit 20: Observed: 0. Expected: 128
Bit 21: Observed: 0. Expected: 128
Bit 22: Observed: 0. Expected: 128
Bit 23: Observed: 0. Expected: 128
Bit 24: Observed: 0. Expected: 128
Bit 25: Observed: 0. Expected: 128
Bit 26: Observed: 0. Expected: 128
Bit 27: Observed: 0. Expected: 128
Bit 28: Observed: 0. Expected: 128
Bit 29: Observed: 0. Expected: 128
Bit 30: Observed: 0. Expected: 128
Bit 31: Observed: 0. Expected: 128
2-Tuple Test
Bit 0, tuple 0: Observed: 0. Expected: 64
Bit 0, tuple 1: Observed: 0. Expected: 64
Bit 0, tuple 2: Observed: 256. Expected: 64
Bit 0, tuple 3: Observed: 0. Expected: 64
Bit 1, tuple 0: Observed: 0. Expected: 64
Bit 1, tuple 1: Observed: 128. Expected: 64
Bit 1, tuple 2: Observed: 128. Expected: 64
Bit 1, tuple 3: Observed: 0. Expected: 64
Bit 2, tuple 0: Observed: 64. Expected: 64
Bit 2, tuple 1: Observed: 64. Expected: 64
Bit 2, tuple 2: Observed: 64. Expected: 64
Bit 2, tuple 3: Observed: 64. Expected: 64
Bit 3, tuple 0: Observed: 96. Expected: 64
Bit 3, tuple 1: Observed: 32. Expected: 64
Bit 3, tuple 2: Observed: 32. Expected: 64
Bit 3, tuple 3: Observed: 96. Expected: 64
Bit 4, tuple 0: Observed: 112. Expected: 64
Bit 4, tuple 1: Observed: 16. Expected: 64
Bit 4, tuple 2: Observed: 16. Expected: 64
Bit 4, tuple 3: Observed: 112. Expected: 64
Bit 5, tuple 0: Observed: 120. Expected: 64
Bit 5, tuple 1: Observed: 8. Expected: 64
Bit 5, tuple 2: Observed: 8. Expected: 64
Bit 5, tuple 3: Observed: 120. Expected: 64
Bit 6, tuple 0: Observed: 124. Expected: 64
Bit 6, tuple 1: Observed: 4. Expected: 64
Bit 6, tuple 2: Observed: 4. Expected: 64
Bit 6, tuple 3: Observed: 124. Expected: 64
Bit 7, tuple 0: Observed: 126. Expected: 64
Bit 7, tuple 1: Observed: 2. Expected: 64
Bit 7, tuple 2: Observed: 2. Expected: 64
Bit 7, tuple 3: Observed: 126. Expected: 64
Bit 8, tuple 0: Observed: 127. Expected: 64
Bit 8, tuple 1: Observed: 1. Expected: 64
Bit 8, tuple 2: Observed: 1. Expected: 64
Bit 8, tuple 3: Observed: 127. Expected: 64
Bit 9, tuple 0: Observed: 127. Expected: 64
Bit 9, tuple 1: Observed: 0. Expected: 64
Bit 9, tuple 2: Observed: 0. Expected: 64
Bit 9, tuple 3: Observed: 129. Expected: 64
Bit 10, tuple 0: Observed: 127. Expected: 64
Bit 10, tuple 1: Observed: 0. Expected: 64
Bit 10, tuple 2: Observed: 0. Expected: 64
Bit 10, tuple 3: Observed: 129. Expected: 64
Bit 11, tuple 0: Observed: 127. Expected: 64
Bit 11, tuple 1: Observed: 0. Expected: 64
Bit 11, tuple 2: Observed: 0. Expected: 64
Bit 11, tuple 3: Observed: 129. Expected: 64
Bit 12, tuple 0: Observed: 127. Expected: 64
Bit 12, tuple 1: Observed: 0. Expected: 64
Bit 12, tuple 2: Observed: 0. Expected: 64
Bit 12, tuple 3: Observed: 129. Expected: 64
Bit 13, tuple 0: Observed: 127. Expected: 64
Bit 13, tuple 1: Observed: 0. Expected: 64
Bit 13, tuple 2: Observed: 0. Expected: 64
Bit 13, tuple 3: Observed: 129. Expected: 64
Bit 14, tuple 0: Observed: 127. Expected: 64
Bit 14, tuple 1: Observed: 0. Expected: 64
Bit 14, tuple 2: Observed: 0. Expected: 64
Bit 14, tuple 3: Observed: 129. Expected: 64
Bit 15, tuple 0: Observed: 127. Expected: 64
Bit 15, tuple 1: Observed: 0. Expected: 64
Bit 15, tuple 2: Observed: 0. Expected: 64
Bit 15, tuple 3: Observed: 129. Expected: 64
Bit 16, tuple 0: Observed: 127. Expected: 64
Bit 16, tuple 1: Observed: 0. Expected: 64
Bit 16, tuple 2: Observed: 0. Expected: 64
Bit 16, tuple 3: Observed: 129. Expected: 64
Bit 17, tuple 0: Observed: 127. Expected: 64
Bit 17, tuple 1: Observed: 0. Expected: 64
Bit 17, tuple 2: Observed: 0. Expected: 64
Bit 17, tuple 3: Observed: 129. Expected: 64
Bit 18, tuple 0: Observed: 127. Expected: 64
Bit 18, tuple 1: Observed: 0. Expected: 64
Bit 18, tuple 2: Observed: 0. Expected: 64
Bit 18, tuple 3: Observed: 129. Expected: 64
Bit 19, tuple 0: Observed: 127. Expected: 64
Bit 19, tuple 1: Observed: 0. Expected: 64
Bit 19, tuple 2: Observed: 0. Expected: 64
Bit 19, tuple 3: Observed: 129. Expected: 64
Bit 20, tuple 0: Observed: 255. Expected: 64
Bit 20, tuple 1: Observed: 0. Expected: 64
Bit 20, tuple 2: Observed: 0. Expected: 64
Bit 20, tuple 3: Observed: 1. Expected: 64
Bit 21, tuple 0: Observed: 256. Expected: 64
Bit 21, tuple 1: Observed: 0. Expected: 64
Bit 21, tuple 2: Observed: 0. Expected: 64
Bit 21, tuple 3: Observed: 0. Expected: 64
Bit 22, tuple 0: Observed: 256. Expected: 64
Bit 22, tuple 1: Observed: 0. Expected: 64
Bit 22, tuple 2: Observed: 0. Expected: 64
Bit 22, tuple 3: Observed: 0. Expected: 64
Bit 23, tuple 0: Observed: 256. Expected: 64
Bit 23, tuple 1: Observed: 0. Expected: 64
Bit 23, tuple 2: Observed: 0. Expected: 64
Bit 23, tuple 3: Observed: 0. Expected: 64
Bit 24, tuple 0: Observed: 256. Expected: 64
Bit 24, tuple 1: Observed: 0. Expected: 64
Bit 24, tuple 2: Observed: 0. Expected: 64
Bit 24, tuple 3: Observed: 0. Expected: 64
Bit 25, tuple 0: Observed: 256. Expected: 64
Bit 25, tuple 1: Observed: 0. Expected: 64
Bit 25, tuple 2: Observed: 0. Expected: 64
Bit 25, tuple 3: Observed: 0. Expected: 64
Bit 26, tuple 0: Observed: 256. Expected: 64
Bit 26, tuple 1: Observed: 0. Expected: 64
Bit 26, tuple 2: Observed: 0. Expected: 64
Bit 26, tuple 3: Observed: 0. Expected: 64
Bit 27, tuple 0: Observed: 256. Expected: 64
Bit 27, tuple 1: Observed: 0. Expected: 64
Bit 27, tuple 2: Observed: 0. Expected: 64
Bit 27, tuple 3: Observed: 0. Expected: 64
Bit 28, tuple 0: Observed: 256. Expected: 64
Bit 28, tuple 1: Observed: 0. Expected: 64
Bit 28, tuple 2: Observed: 0. Expected: 64
Bit 28, tuple 3: Observed: 0. Expected: 64
Bit 29, tuple 0: Observed: 256. Expected: 64
Bit 29, tuple 1: Observed: 0. Expected: 64
Bit 29, tuple 2: Observed: 0. Expected: 64
Bit 29, tuple 3: Observed: 0. Expected: 64
Bit 30, tuple 0: Observed: 256. Expected: 64
Bit 30, tuple 1: Observed: 0. Expected: 64
Bit 30, tuple 2: Observed: 0. Expected: 64
Bit 30, tuple 3: Observed: 0. Expected: 64
Bit 31, tuple 0: Observed: 256. Expected: 64
Bit 31, tuple 1: Observed: 0. Expected: 64
Bit 31, tuple 2: Observed: 0. Expected: 64
Bit 31, tuple 3: Observed: 0. Expected: 64
3-Tuple Test
Bit 1, tuple 0: Observed: 0. Expected: 21
Bit 1, tuple 1: Observed: 42. Expected: 21
Bit 1, tuple 2: Observed: 0. Expected: 21
Bit 1, tuple 3: Observed: 42. Expected: 21
Bit 1, tuple 4: Observed: 42. Expected: 21
Bit 1, tuple 5: Observed: 0. Expected: 21
Bit 1, tuple 6: Observed: 42. Expected: 21
Bit 1, tuple 7: Observed: 2. Expected: 21
Bit 3, tuple 0: Observed: 64. Expected: 21
Bit 3, tuple 1: Observed: 10. Expected: 21
Bit 3, tuple 2: Observed: 0. Expected: 21
Bit 3, tuple 3: Observed: 10. Expected: 21
Bit 3, tuple 4: Observed: 10. Expected: 21
Bit 3, tuple 5: Observed: 0. Expected: 21
Bit 3, tuple 6: Observed: 10. Expected: 21
Bit 3, tuple 7: Observed: 66. Expected: 21
Bit 5, tuple 0: Observed: 80. Expected: 21
Bit 5, tuple 1: Observed: 2. Expected: 21
Bit 5, tuple 2: Observed: 0. Expected: 21
Bit 5, tuple 3: Observed: 2. Expected: 21
Bit 5, tuple 4: Observed: 2. Expected: 21
Bit 5, tuple 5: Observed: 0. Expected: 21
Bit 5, tuple 6: Observed: 2. Expected: 21
Bit 5, tuple 7: Observed: 82. Expected: 21
Bit 7, tuple 0: Observed: 84. Expected: 21
Bit 7, tuple 1: Observed: 0. Expected: 21
Bit 7, tuple 2: Observed: 0. Expected: 21
Bit 7, tuple 3: Observed: 0. Expected: 21
Bit 7, tuple 4: Observed: 0. Expected: 21
Bit 7, tuple 5: Observed: 0. Expected: 21
Bit 7, tuple 6: Observed: 0. Expected: 21
Bit 7, tuple 7: Observed: 86. Expected: 21
Bit 9, tuple 0: Observed: 85. Expected: 21
Bit 9, tuple 1: Observed: 0. Expected: 21
Bit 9, tuple 2: Observed: 0. Expected: 21
Bit 9, tuple 3: Observed: 0. Expected: 21
Bit 9, tuple 4: Observed: 0. Expected: 21
Bit 9, tuple 5: Observed: 0. Expected: 21
Bit 9, tuple 6: Observed: 0. Expected: 21
Bit 9, tuple 7: Observed: 85. Expected: 21
Bit 11, tuple 0: Observed: 85. Expected: 21
Bit 11, tuple 1: Observed: 0. Expected: 21
Bit 11, tuple 2: Observed: 0. Expected: 21
Bit 11, tuple 3: Observed: 0. Expected: 21
Bit 11, tuple 4: Observed: 0. Expected: 21
Bit 11, tuple 5: Observed: 0. Expected: 21
Bit 11, tuple 6: Observed: 0. Expected: 21
Bit 11, tuple 7: Observed: 85. Expected: 21
Bit 13, tuple 0: Observed: 85. Expected: 21
Bit 13, tuple 1: Observed: 0. Expected: 21
Bit 13, tuple 2: Observed: 0. Expected: 21
Bit 13, tuple 3: Observed: 0. Expected: 21
Bit 13, tuple 4: Observed: 0. Expected: 21
Bit 13, tuple 5: Observed: 0. Expected: 21
Bit 13, tuple 6: Observed: 0. Expected: 21
Bit 13, tuple 7: Observed: 85. Expected: 21
Bit 15, tuple 0: Observed: 85. Expected: 21
Bit 15, tuple 1: Observed: 0. Expected: 21
Bit 15, tuple 2: Observed: 0. Expected: 21
Bit 15, tuple 3: Observed: 0. Expected: 21
Bit 15, tuple 4: Observed: 0. Expected: 21
Bit 15, tuple 5: Observed: 0. Expected: 21
Bit 15, tuple 6: Observed: 0. Expected: 21
Bit 15, tuple 7: Observed: 85. Expected: 21
Bit 17, tuple 0: Observed: 85. Expected: 21
Bit 17, tuple 1: Observed: 0. Expected: 21
Bit 17, tuple 2: Observed: 0. Expected: 21
Bit 17, tuple 3: Observed: 0. Expected: 21
Bit 17, tuple 4: Observed: 0. Expected: 21
Bit 17, tuple 5: Observed: 0. Expected: 21
Bit 17, tuple 6: Observed: 0. Expected: 21
Bit 17, tuple 7: Observed: 85. Expected: 21
Bit 19, tuple 0: Observed: 85. Expected: 21
Bit 19, tuple 1: Observed: 0. Expected: 21
Bit 19, tuple 2: Observed: 0. Expected: 21
Bit 19, tuple 3: Observed: 0. Expected: 21
Bit 19, tuple 4: Observed: 0. Expected: 21
Bit 19, tuple 5: Observed: 0. Expected: 21
Bit 19, tuple 6: Observed: 0. Expected: 21
Bit 19, tuple 7: Observed: 85. Expected: 21
Bit 21, tuple 0: Observed: 170. Expected: 21
Bit 21, tuple 1: Observed: 0. Expected: 21
Bit 21, tuple 2: Observed: 0. Expected: 21
Bit 21, tuple 3: Observed: 0. Expected: 21
Bit 21, tuple 4: Observed: 0. Expected: 21
Bit 21, tuple 5: Observed: 0. Expected: 21
Bit 21, tuple 6: Observed: 0. Expected: 21
Bit 21, tuple 7: Observed: 0. Expected: 21
Bit 23, tuple 0: Observed: 170. Expected: 21
Bit 23, tuple 1: Observed: 0. Expected: 21
Bit 23, tuple 2: Observed: 0. Expected: 21
Bit 23, tuple 3: Observed: 0. Expected: 21
Bit 23, tuple 4: Observed: 0. Expected: 21
Bit 23, tuple 5: Observed: 0. Expected: 21
Bit 23, tuple 6: Observed: 0. Expected: 21
Bit 23, tuple 7: Observed: 0. Expected: 21
Bit 25, tuple 0: Observed: 170. Expected: 21
Bit 25, tuple 1: Observed: 0. Expected: 21
Bit 25, tuple 2: Observed: 0. Expected: 21
Bit 25, tuple 3: Observed: 0. Expected: 21
Bit 25, tuple 4: Observed: 0. Expected: 21
Bit 25, tuple 5: Observed: 0. Expected: 21
Bit 25, tuple 6: Observed: 0. Expected: 21
Bit 25, tuple 7: Observed: 0. Expected: 21
Bit 27, tuple 0: Observed: 170. Expected: 21
Bit 27, tuple 1: Observed: 0. Expected: 21
Bit 27, tuple 2: Observed: 0. Expected: 21
Bit 27, tuple 3: Observed: 0. Expected: 21
Bit 27, tuple 4: Observed: 0. Expected: 21
Bit 27, tuple 5: Observed: 0. Expected: 21
Bit 27, tuple 6: Observed: 0. Expected: 21
Bit 27, tuple 7: Observed: 0. Expected: 21
Bit 29, tuple 0: Observed: 170. Expected: 21
Bit 29, tuple 1: Observed: 0. Expected: 21
Bit 29, tuple 2: Observed: 0. Expected: 21
Bit 29, tuple 3: Observed: 0. Expected: 21
Bit 29, tuple 4: Observed: 0. Expected: 21
Bit 29, tuple 5: Observed: 0. Expected: 21
Bit 29, tuple 6: Observed: 0. Expected: 21
Bit 29, tuple 7: Observed: 0. Expected: 21
Bit 31, tuple 0: Observed: 170. Expected: 21
Bit 31, tuple 1: Observed: 0. Expected: 21
Bit 31, tuple 2: Observed: 0. Expected: 21
Bit 31, tuple 3: Observed: 0. Expected: 21
Bit 31, tuple 4: Observed: 0. Expected: 21
Bit 31, tuple 5: Observed: 0. Expected: 21
Bit 31, tuple 6: Observed: 0. Expected: 21
Bit 31, tuple 7: Observed: 0. Expected: 21
INFO: [SIM 1] CSim done with 0 errors.

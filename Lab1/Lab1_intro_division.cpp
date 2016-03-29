void divide(unsigned char N, unsigned char D, unsigned char *Q, unsigned char *R){

	if(D){
		//initialise quotient & remainder to zero
		*Q = 0;
		*R = 0;
		//count down from 7 to 0
		for(int i=7; i>=0; i--){
			//shift R left by 1-bit
			*R = *R << 1;
			//return i-th bit
			char iBitN = (N & (1<<i)) >> i;
			
			//set LSB of R to the value in iBitN
			//R(0) := N(i)
			*R ^= (-iBitN ^ (*R)) & (1<<0);
			
			if (*R >= D){
				*R = *R - D;
				*Q |= 1<<i;
			}
		}
	}
}

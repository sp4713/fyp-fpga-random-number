#include <stdio.h>
#include "core.h"

unsigned char someMem[100];
int main(){
	setMem(55, someMem, 100);
	for(int idx=0; idx<100; idx++){
		printf("Value someMem[%d]=0x%X\n",idx,someMem[idx]);
	}
	return 0;
}
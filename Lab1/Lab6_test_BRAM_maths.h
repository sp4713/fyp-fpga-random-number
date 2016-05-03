#include <stdio.h>
#include <hls_math.h>
void crazyFunction(float x[100], float y, float res[100]);

int main(){
	float XVec[100];
	float res[100];
	for(int idxX = 0; idxX<100; idxX++){
		XVec[idxX]=idxX;
	}

	crazyFunction(XVec, 0.01f, res);

	for(int idx=0; idx<100; idx++){
		printf("Result[%d]=%f\n",idx,res[idx]);
	}
	return 0;
}
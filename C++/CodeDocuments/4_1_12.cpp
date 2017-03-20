#include "fourier.h"

int main(){
	int M = 512;
	double f1[M] = {0},f2[M] = {1};
	f[0] = 1;
	double F1[M] = {0},F2[M] = {0},F3[M] = {0},F4[M] = {0};
	Fourier(f1,F1,F2,M);//4-1-1
	Fourier(f2,F3,F4,M);//4-1-2
	double FA[M],FB[M];
	for(int i = 0;i < M;i++){
		FA[i] = sqrt(F1[i]*F1[i]+F2[i]*F2[i]);
		FB[i] = sqrt(F3[i]*F3[i]+F4[i]*F4[i]);
	}
	//show the images
	return 0;
}
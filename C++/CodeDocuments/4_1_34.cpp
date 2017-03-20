#include "fourier.h"

int main(){
	int M = 512;
	double f1[M],f2[M];
	for(int i = 0;i < M;i++){
		f1 = cos(2*PI/16*i);
		f2 = cos(2*PI*0.065*i);
	}
	double F1[M] = {0},F2[M] = {0},F3[M] = {0},F4[M] = {0};
	Fourier(f1,F1,F2,M);//4-1-3
	Fourier(f2,F3,F4,M);//4-1-4
	double FA[M],FB[M];
	for(int i = 0;i < M;i++){
		FA[i] = sqrt(F1[i]*F1[i]+F2[i]*F2[i]);
		FB[i] = sqrt(F3[i]*F3[i]+F4[i]*F4[i]);
	}
	//show the images
	complex<double> if1[M] = {complex<double>(0,0)};
	complex<double> if2[M] = {complex<double>(0,0)};
	complex<double> iFA[M],iFB[M];
	for(int i = 0;i < M;i++){
		iFA[i] = complex<double>(F1[i],-1*F2[i]);
		iFB[i] = complex<double>(F3[i],-1*F4[i]);
	}
	iFourier(if1,iFA,M);
	iFourier(if2,iFB,M);
	//show the inverse images
	
	//show the difference between original and now
	return 0;
}
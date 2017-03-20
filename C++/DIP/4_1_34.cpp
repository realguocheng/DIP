#include "fourier.h"
int main(){
	int M = 512;
	double f1[M],f2[M];
	for(int i = 0;i < M;i++){
		f1[i] = cos(2*PI/16*i);
		f2[i] = cos(2*PI*0.065*i);
	}
	draw(f1,M);
	draw(f2,M);
	double F1[M] = {0},F2[M] = {0},F3[M] = {0},F4[M] = {0};
	Fourier(f1,F1,F2,M);//4-1-3
	Fourier(f2,F3,F4,M);//4-1-4
	double FA[M],FB[M];
	for(int i = 0;i < M;i++){
		FA[i] = sqrt(F1[i]*F1[i]+F2[i]*F2[i]);
		FB[i] = sqrt(F3[i]*F3[i]+F4[i]*F4[i]);
	}
	//show the images
	draw(FA,M);
	draw(FB,M);
	complex<double> if1[M],if2[M],iFA[M],iFB[M];
	for(int i = 0;i < M;i++){
		iFA[i] = complex<double>(F1[i],-1*F2[i]);
		iFB[i] = complex<double>(F3[i],-1*F4[i]);
        if1[i] = {complex<double>(0,0)};
        if2[i] = {complex<double>(0,0)};
	}
	iFourier(if1,iFA,M);
	iFourier(if2,iFB,M);
	double if1r[M],if2r[M];
	for(int i = 0;i < M;i++){
        if1r[i] = if1[i].real();
        if2r[i] = if2[i].real();
	}
	//show the inverse images
	draw(if1r,M);
	draw(if2r,M);
	//show the difference between original and now
	double dif1[M],dif2[M];
	for(int i = 0;i < M;i++){
        dif1[i] = f1[i] - if1r[i];
        dif2[i] = f2[i] - if2r[i];
	}
	draw(dif1,M);
	draw(dif2,M);
	cout<<f1[0]<<" "<<if1r[0]<<endl;
	cout<<f2[0]<<" "<<if2r[0]<<endl;
	cout<<f1[100]<<" "<<if1r[100]<<endl;
	cout<<f2[100]<<" "<<if2r[100]<<endl;
	return 0;
}

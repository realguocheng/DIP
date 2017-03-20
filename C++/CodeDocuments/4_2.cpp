#include "fourier.h"

double sinc(double x){
	return ;
}

int main(){
	double r[5] = {1,2,0.5,1.5,2/3};
	int M = 300;
	
	for(int i = 0;i < 5;i++){
		double size = M/r[i];
		double f[size];
		double F1[size],F2[size];
		for(double j = 0;j < M;j+=r[i]){
			f[j] = sinc(j);
		}
		//show the original image
		Fourier(f,F1,F2,M);
		double FA[size];
		for(int j = 0;j < M;j++){
			FA[j] = sqrt(F1[j]*F1[j]+F2[j]*F2[j]);
		}
		//show the fourier FA images
	}
	return 0;
}
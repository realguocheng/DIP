#include "fourier.h"

double sinc(double x){
	return sin(x)/x;
}

int main(){
	double r[5] = {1,2,0.5,1.5,(double)2/3};
	int M = 300;

	for(int i = 0;i < 5;i++){
		int size = M/r[i];
		cout<<size<<endl;
		double f[size];
		double F1[size] = {0},F2[size] = {0};
		for(int j = 0;j < size;j++){
			f[j] = sinc(j*r[i]);
		}
		//show the original image
		draw(f,size);
		Fourier(f,F1,F2,size);
		double FA[size];
		for(int j = 0;j < size;j++){
			FA[j] = sqrt(F1[j]*F1[j]+F2[j]*F2[j]);
		}
		//show the fourier FA images
		draw(FA,size);
	}
	return 0;
}

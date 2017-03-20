#include"cv.h"
#include"highgui.h"
#include<iostream>
#include<math.h>
#include<complex>
#include "plot.h"
using namespace std;
#define PI 3.1415926
int fcount = 0;
char fname[2];
void Fourier(double *f,double *F1,double *F2,int M)  //Fourier Transform
{
    for(int i = 0; i < M; i++)
    {
        for(int j =0; j < M; j++)
        {
            F1[i] += f[j]*cos(2*PI*i*j/M);
            F2[i] += f[j]*sin(2*PI*i*j/M);
        }
        F1[i] /= M;
        F2[i] /= M;
    }
}
void iFourier(complex<double> *f,complex<double> *F,int M) //inverse Fourier
{
    for(int i = 0; i < M; i++)
    {
        for(int j =0; j < M; j++)
        {
            f[i] += F[j]*complex<double>(cos(2*PI*i*j/M),sin(2*PI*i*j/M));
        }
    }
}
void draw(double *data,int M){
    CPlot plot;
	plot.plot(data, M, CV_RGB(0, 0, 255),'l');
	sprintf(fname,"%d",fcount);
	fname[1] = '\0';
	cvShowImage(fname, plot.Figure);
	cvWaitKey(0);
	fcount++;
}


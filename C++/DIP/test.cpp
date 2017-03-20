
#include "cv.h"
#include "highgui.h"
#include "plot.h"
#include<iostream>

int main(int argc, char* argv[])
{
	const int Cnt = 80;
	double X[Cnt] = {0};
	double Y[Cnt] = {0};
	for(int i = 0; i < Cnt; i++)
	{
		X[i] = (double)i;
		Y[i] = (double)i - 20;
	}

	//cvNamedWindow("hello",1);
	CPlot plot;
	plot.plot(Y, Cnt, CV_RGB(0, 0, 0),'l'); //����ֻ����Yֵ XĬ�ϴ�0��ʼ
	cvShowImage("hello", plot.Figure);
	cvWaitKey(0);

	return 0;
}

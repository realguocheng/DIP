#include"cv.h"
#include"highgui.h"
#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>
using namespace std;

int main(int argc, char** argv)
{
	//initialization
	IplImage* src[2];
	src[0] = cvLoadImage("D:\\1-1.tif", CV_LOAD_IMAGE_GRAYSCALE);
	src[1] = cvLoadImage("D:\\1-1.tif", CV_LOAD_IMAGE_GRAYSCALE);
	int width = src[0]->width;//width
	int height = src[0]->height;//height
	double c = 1, v = 70, gama = 0.4;

	//2-1
	cvShowImage("original", src[0]);//original picture
	cvWaitKey(0);
	for (size_t row = 0; row < height; row++)
	{
		uchar* ptr0 = (uchar*)src[0]->imageData + row*src[0]->width;//获得灰度值数据指针
		uchar* ptr1 = (uchar*)src[1]->imageData + row*src[1]->width;
		for (size_t cols = 0; cols < width; cols++)
		{
			ptr0[cols] = c * log(1+v*ptr0[cols])/log(v+1);
			ptr1[cols] = c * pow(ptr1[cols],gama);
		}
	}
	cvShowImage("logtrans",src[0]);//show log transformation
	cvWaitKey(0);//press key '0' to see next gray level
	cvShowImage("gama", src[1]);
	cvWaitKey(0);
	return 0;
}
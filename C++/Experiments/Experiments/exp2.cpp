#include"cv.h"
#include"highgui.h"
#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>
using namespace std;

int getMax(int *arr) {
	int max = 0;
	for (int i = 0; i < 256; i++) {
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}
	int main(int argc, char** argv)
	{
	//initialization
	IplImage* src[2];
	src[0] = cvLoadImage("2-1.tif", CV_LOAD_IMAGE_GRAYSCALE);
	src[1] = cvLoadImage("2-1.tif", CV_LOAD_IMAGE_GRAYSCALE);
	int width = src[0]->width;//width
	int height = src[0]->height;//height
	double c = 1, v = 70, gama = 0.4;

	//2-1
	//cvNamedWindow("original", 0);
	cvShowImage("original", src[0]);//original picture
	cvWaitKey(0);
	for (size_t row = 0; row < height; row++)
	{
		uchar* ptr0 = (uchar*)src[0]->imageData + row*src[0]->widthStep;//获得灰度值数据指针
		uchar* ptr1 = (uchar*)src[1]->imageData + row*src[1]->widthStep;
		for (size_t cols = 0; cols < width; cols++)
		{
			ptr0[cols] = c * log(1+v*ptr0[cols]/255.0)/log(v+1)*255;
			ptr1[cols] = c * pow((ptr1[cols]/255.0),gama)*255;
		}
	}
	cvShowImage("logtrans",src[0]);//show log transformation
	cvWaitKey(0);//press key '0' to see next gray level
	cvShowImage("gama", src[1]);
	cvWaitKey(0);

	//2-2
	IplImage* image = cvLoadImage("2-1.tif", CV_LOAD_IMAGE_GRAYSCALE);
	int step = image->widthStep;
	width = image->width;
	height = image->height;
	uchar* data = (uchar *)image->imageData;
	int hist[256] = {0};
	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			hist[data[i*step + j]]++;
		}
	}
	IplImage* dst = cvCreateImage(cvSize(400, 300), 8, 3);
	cvSet(dst, cvScalarAll(255), 0);
	double bin_width = (double)dst->width / 256;
	double bin_unith = (double)dst->height / getMax(hist);
	for (int i = 0; i<256; i++)
	{
		CvPoint p0 = cvPoint(i*bin_width, dst->height);
		CvPoint p1 = cvPoint((i + 1)*bin_width, dst->height - hist[i] * bin_unith);
		cvRectangle(dst, p0, p1, cvScalar(0), -1, 8, 0);
	}
	cvShowImage("dst1", dst);
	cvWaitKey(0);
	int num = height*width;
	double hist2[256];
	hist2[0] = hist[0];
	for (int i = 1; i < 256; i++) {
		hist2[i] = hist2[i-1] + hist[i];
	}
	for (int i = 0; i < 256; i++) {
		hist2[i] = hist2[i] / num * 255;
	}
	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			data[i*step + j] = (uchar)hist2[data[i*step + j]];
		}
	}
	cvShowImage("changed",image);
	cvWaitKey(0);
	int hist3[256] = { 0 };
	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			hist3[data[i*step + j]]++;
		}
	}
	cvSet(dst, cvScalarAll(255), 0);
	double bin_width1 = (double)dst->width / 256;
	double bin_unith1 = (double)dst->height / getMax(hist3);
	for (int i = 0; i<256; i++)
	{
		CvPoint p0 = cvPoint(i*bin_width1, dst->height);
		CvPoint p1 = cvPoint((i + 1)*bin_width1, dst->height - hist3[i] * bin_unith1);
		cvRectangle(dst, p0, p1, cvScalar(0), -1, 8, 0);
	}
	cvShowImage("dst2", dst);
	cvWaitKey(0);

	//2-3
	int H[3][3] = { {-1,-1,-1},{-1,8,-1},{-1,-1,-1} };
	IplImage* moon = cvLoadImage("2-2.tif", CV_LOAD_IMAGE_GRAYSCALE);
	uchar * pixel = (uchar*)moon->imageData;
	int hei = moon->height;
	int wid = moon->width;
	int *m1 = new int[hei*wid];
	int *m2 = new int[(hei+2)*(wid+2)];
	int step1 = moon->widthStep;
	
	//fill the center
	for (int i = 1; i < hei+1; i++) {
		for (int j = 1; j < wid+1; j++) {
			m2[i*(wid+2) + j] = pixel[(i-1)*step1 + j-1];
		}
	}
	//fill the edges
	for (int i = 1; i < wid + 1; i++) {
		m2[i] = m2[wid + 2 + i];
		m2[(wid + 2)*(hei + 1) + i] = m2[(wid + 2)*hei + i];
	}
	for (int j = 1; j < hei; j++) {
		m2[(wid + 2)*j] = m2[(wid + 2)*j + 1];
		m2[(wid + 2)*(j+1)-1] = m2[(wid + 2)*(j + 1) - 2];
	}
	//fill the cornor
	m2[0] = m2[wid + 3]; 
	m2[wid + 1] = m2[(wid + 2) * 2 - 2];
	m2[(wid + 2)*(hei + 1)] = m2[(wid + 2)*hei + 1];
	m2[(wid + 2)*(hei + 2) - 1] = m2[(wid + 2)*(hei + 1) - 2];
	//calculate the new image
	for (int i = 1; i < hei + 1; i++) {
		for (int j = 1; j < wid + 1; j++) {
			int psum = 0;
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					psum += H[m][n] * m2[(i+m-1)*(wid + 2) + j+n-1];
				}
			}
			if (psum < 0) psum = 0;
			if (psum > 255) psum = 255;
			pixel[(i - 1)*step1 + j - 1] = psum;
		}
	}
	cvShowImage("lap1", moon);
	cvWaitKey(0);
	for (int i = 1; i < hei + 1; i++) {
		for (int j = 1; j < wid + 1; j++) {
			int psum = 0;
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					psum += H[m][n] * m2[(i + m - 1)*(wid + 2) + j + n - 1];
				}
			}
			m1[(i-1)*wid+j-1] = psum;
		}
	}
	double min = 1000000;
	double max = -1000000;
	for (int i = 0; i < hei; i++) {
		for (int j = 0; j < wid; j++) {
			if (m1[i*wid + j] < min) min = m1[i*wid + j];
			if (m1[i*wid + j] > max && m1[i*wid + j] <1000) max = m1[i*wid + j];
		}
	}
	int count = 0;
	for (int i = 0; i < hei; i++) {
		for (int j = 0; j < wid; j++) {
			pixel[i*step1 + j] = (uchar)((m1[i*wid + j] - min) / (max - min) * 255);
		}
	}
	cvShowImage("lap2", moon);
	cvWaitKey(0);
	IplImage* moon2 = cvLoadImage("2-2.tif", CV_LOAD_IMAGE_GRAYSCALE);
	uchar * pixel2 = (uchar*)moon2->imageData;
	int temp = 0;
	for (int i = 0; i < hei; i++) {
		for (int j = 0; j < wid; j++) {
			temp = pixel2[i*step1 + j] + m1[i*wid + j];
			if (temp < 0) temp = 0;
			if (temp > 255) temp = 255;
			pixel2[i*step1 + j] = temp;
		}
	}
	cvShowImage("lap3", moon2);
	cvWaitKey(0);
	return 0;
}
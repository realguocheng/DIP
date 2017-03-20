#include"cv.h"
#include"highgui.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main() {
	//3-1
	IplImage* src = cvLoadImage("2-3.tif", CV_LOAD_IMAGE_GRAYSCALE);
	int height = src->height;
	int width = src->width;
	int step = src->widthStep;
	IplImage* copy = cvLoadImage("2-3.tif", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* copy_s = cvLoadImage("2-3.tif", CV_LOAD_IMAGE_GRAYSCALE);
	uchar * sp = (uchar*)src->imageData;
	uchar * cp = (uchar*)copy->imageData;
	uchar * cp_s = (uchar*)copy_s->imageData;
	/*for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cp[i*width + j] = sp[i*step + j];
		}
	}*/
	cvShowImage("3-1-1", src);//原图
	cvWaitKey(0);
	int pixels[256] = { 0 };
	int spixels[256] = { 0 };
	int temp = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			memset(pixels, 0, sizeof(int) * 256);
			memset(spixels, 0, sizeof(int) * 256);
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					if (i + m - 1 < 0 || i + m - 1 >= height || j + n - 1 < 0 || j + n - 1 >= width) temp = 0;
					else temp = sp[(i + m - 1)*step + j + n - 1];
					pixels[temp] ++;
				}
			}
			spixels[0] = pixels[0];
			for (int k = 1; k < 256; k++) {
				spixels[k] = spixels[k - 1] + pixels[k];
			}
			cp[i*step + j] = round(spixels[sp[i*step + j]]/9.0*255);
		}
	}
	cvShowImage("3-1-2", copy);//局部直方图均衡化
	cvWaitKey(0);
	memset(pixels, 0, sizeof(int) * 256);
	memset(spixels, 0, sizeof(int) * 256);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[sp[i*step + j]]+=1;
		}
	}
	spixels[0] = pixels[0];
	for (int k = 1; k < 256; k++) {
		spixels[k] = spixels[k - 1] + pixels[k];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cp_s[i*step + j] = round(spixels[sp[i*step + j]] / (double)(height*width) * 255);
		}
	}
	cvShowImage("3-1-3", copy_s);//全局直方图均衡化
	cvWaitKey(0);

	//3-2
	IplImage* image = cvLoadImage("2-4.tif", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* icopy = cvLoadImage("2-4.tif", CV_LOAD_IMAGE_GRAYSCALE);
	IplImage* icopy_s = cvLoadImage("2-4.tif", CV_LOAD_IMAGE_GRAYSCALE);
	int iheight = image->height;
	int iwidth = image->width;
	int istep = image->widthStep;
	uchar * ip = (uchar*)image->imageData;
	uchar * icp = (uchar*)icopy->imageData;
	uchar * icp_s = (uchar*)icopy_s->imageData;
	cvShowImage("3-2-1", image);//原图
	cvWaitKey(0);
	int sum = 0;
	for (int i = 0; i < iheight; i++) {
		for (int j = 0; j < iwidth; j++) {
			sum = 0;
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					if (i + m - 1 < 0 || i + m - 1 >= iheight || j + n - 1 < 0 || j + n - 1 >= iwidth) temp = 0;
					else temp = ip[(i + m - 1)*istep + j + n - 1];
					sum += temp;
				}
			}
			icp[i*istep + j] = round(sum / 9);
		}
	}
	cvShowImage("3-2-2", icopy);//平均值过滤器
	cvWaitKey(0);
	int sort_rs[9] = { 0 };
	for (int i = 0; i < iheight; i++) {
		for (int j = 0; j < iwidth; j++) {
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					if (i + m - 1 < 0 || i + m - 1 >= iheight || j + n - 1 < 0 || j + n - 1 >= iwidth) temp = 0;
					else temp = ip[(i + m - 1)*istep + j + n - 1];
					sort_rs[m * 3 + n] = temp;
				}
			}
			sort(&sort_rs[0],&sort_rs[8]);
			icp_s[i*istep + j] = sort_rs[4];
		}
	}
	cvShowImage("3-2-3", icopy_s);//中间值过滤器
	cvWaitKey(0);

	//3-3
	int *gmask = new int[iheight*iwidth];
	for (int i = 0; i < iheight; i++) {
		for (int j = 0; j < iwidth; j++) {
			gmask[i*iwidth+j] = ip[i*istep + j] - icp[i*istep + j];
		}
	}
	IplImage* image_s = cvLoadImage("2-4.tif", CV_LOAD_IMAGE_GRAYSCALE);
	uchar * ip_s = (uchar*)image_s->imageData;
	int k = 4;
	for (int i = 0; i < iheight; i++) {
		for (int j = 0; j < iwidth; j++) {
			temp = ip[i*istep + j] + gmask[i*iwidth + j] * k;
			if (temp < 0) temp = 0;
			if (temp > 255) temp = 255;
			ip_s[i*istep + j] = temp;
		}
	}
	cvShowImage("3-3-1", image_s);//锐化后
	cvWaitKey(0);
	return 0;
}
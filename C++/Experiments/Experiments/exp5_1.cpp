#include"cv.h"
#include"highgui.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main(){
	
	IplImage* src = cvLoadImage("2-3.tif", CV_LOAD_IMAGE_GRAYSCALE);
	int height = src->height;
	int width = src->width;
	int step = src->widthStep;
	uchar * ptr = (uchar*)src->imageData;
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}
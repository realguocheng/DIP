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
	IplImage* src[9];
	for(int i = 0;i < 9;i++)
		src[i] = cvLoadImage("1-1.tif", CV_LOAD_IMAGE_GRAYSCALE);//load picture
	int width = src[0]->width;//width
	int height = src[0]->height;//height
	int level[8] = { 256,128,64,32,16,8,4,2 };//gray level
	double temp = 0;
	char iname[12] = "image_";//used for saving images
	char buffer[5];

	//execution-1
	size_t pos = height * 3 / 4;
	uchar* ptr0 = (uchar*)src[8]->imageData + pos*src[8]->width;
	for (size_t i = 0;i < width;i++)
	{
		ptr0[i] = 0;
	}
	cvShowImage("Image-x", src[8]);
	cvWaitKey(0);//press key '0' to continue
	cvSaveImage("GL.jpg", src[8]);


	//execution-2
	for (int i = 7; i >= 0; i--) {
		temp = 255 / (level[i] - 1);
		for (size_t row = 0; row<height; row++)
		{
			uchar* ptr = (uchar*)src[i]->imageData + row*src[i]->width;//获得灰度值数据指针
			for (size_t cols = 0; cols<width; cols++)
			{
				ptr[cols] = round(ptr[cols]/temp)*temp;
			}
		}
		sprintf(buffer, "%d", i);
		iname[6] = buffer[0];
		iname[7] = '\0';
		cvShowImage(iname, src[i]);
		cvWaitKey(0);//press key '0' to see next gray level
		iname[7] = '.'; iname[8] = 'j'; iname[9] = 'p'; 
		iname[10] = 'g';iname[11] = '\0';
		cvSaveImage(iname, src[i]);
		
	}
	return 0;
}
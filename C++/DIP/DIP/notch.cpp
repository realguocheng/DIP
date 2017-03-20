#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  

using namespace cv;
using namespace std;

void addSinNoise(Mat& I, double A, double u, double v) {
	int i, j;
	uchar *p;
	for (i = 0; i < I.rows; ++i) {
		p = I.ptr<uchar>(i);
		for (j = 0; j < I.cols; ++j) {
			double val = p[j] + A * sin(u * i + v * j);
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;
			p[j] = (uchar)val;
		}
	}
}

void shiftDFT(Mat& fImage)
{
	Mat tmp, q0, q1, q2, q3;

	// first crop the image, if it has an odd number of rows or columns

	fImage = fImage(Rect(0, 0, fImage.cols & -2, fImage.rows & -2));

	int cx = fImage.cols / 2;
	int cy = fImage.rows / 2;

	// rearrange the quadrants of Fourier image
	// so that the origin is at the image center

	q0 = fImage(Rect(0, 0, cx, cy));
	q1 = fImage(Rect(cx, 0, cx, cy));
	q2 = fImage(Rect(0, cy, cx, cy));
	q3 = fImage(Rect(cx, cy, cx, cy));

	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

Mat create_spectrum_magnitude_display(Mat& complexImg, bool rearrange)
{
	Mat planes[2];

	split(complexImg, planes);
	magnitude(planes[0], planes[1], planes[0]);

	Mat mag = (planes[0]).clone();
	mag += Scalar::all(1);
	log(mag, mag);

	if (rearrange)
	{
		// re-arrange the quaderants
		shiftDFT(mag);
	}

	normalize(mag, mag, 0, 1, CV_MINMAX);

	namedWindow("SinNoiseSpectrum", WINDOW_AUTOSIZE);
	imshow("SinNoiseSpectrum", mag);
	waitKey(0);

	return mag;
}

double getD1D2(int x, int y, int u1, int v1, int u2, int v2) {
	double D1 = sqrt(pow(x - u1, 2) + pow(y - v1, 2));
	double D2 = sqrt(pow(x - u2, 2) + pow(y - v2, 2));
	return D1 * D2;
}

void createGaussianNotchFilter(Mat& filter, double radius,
		int u1, int v1, int u2, int v2) {

	Mat tmp = Mat::zeros(size(filter), CV_32F);

	int i, j;
	for (i = 0; i < filter.rows; ++i) {
		for (j = 0; j < filter.cols; ++j) {
			/*double val = getD1D2(i, j, u1, v1, u2, v2) / pow(radius, 2) / (-2);
			tmp.at<float>(i, j) = 1 - exp(val);*/
			/*if(i >= u1 - 1 && i <= u1 + 1 && (j < v1 -15 || j > v1 + 15))
				tmp.at<float>(i, j) = 0;
			else if(i >= u2 - 1 && i <= u2 + 1 && (j < v2 - 15 || j > v2 + 15))
				tmp.at<float>(i, j) = 0;
			else {}*/
				double val = pow(pow(radius, 2) / getD1D2(i, j, u1, v1, u2, v2), 2);
				tmp.at<float>(i, j) = 1 / (1 + val);
			
		}
	}

	Mat toMerge[] = {tmp, tmp};
	merge(toMerge, 2, filter);
	
}

int main() {
	Mat image = imread("4-1.tif", CV_LOAD_IMAGE_GRAYSCALE);
	addSinNoise(image, 70, image.rows / 2, 0);
	
	namedWindow("SinNoise", WINDOW_AUTOSIZE);
	imshow("SinNoise", image);
	waitKey();

	int M = getOptimalDFTSize(image.rows);
	int N = getOptimalDFTSize(image.cols);

	Mat padded, planes[2], complexImg, mag, filter, result, filterOut;
	copyMakeBorder(image, padded, 0, M - image.rows, 0, 
		N - image.cols, BORDER_CONSTANT, Scalar::all(0));

	planes[0] = Mat_<float>(padded);
	planes[1] = Mat::zeros(padded.size(), CV_32F);

	merge(planes, 2, complexImg);
	dft(complexImg, complexImg);

	mag = create_spectrum_magnitude_display(complexImg, true);

	int u1 = 68;
	int v1 = mag.cols / 2;
	int u2 = 382;
	int v2 = mag.cols / 2;

	filter = complexImg.clone();

	createGaussianNotchFilter(filter, 100, u1, v1, u2, v2);

	shiftDFT(complexImg); 
	mulSpectrums(complexImg, filter, complexImg, 0);
	shiftDFT(complexImg);

	split(filter, planes);
	normalize(planes[0], filterOut, 0, 1, CV_MINMAX);
	imshow("filterGaussian", filterOut);
	waitKey(0);

	create_spectrum_magnitude_display(complexImg, true);

	idft(complexImg, complexImg);

	split(complexImg, planes);
	normalize(planes[0], result, 0, 1, NORM_MINMAX);
	result = result(Rect(0, 0, image.cols, image.rows));

	

	namedWindow("NoiseRemoval", WINDOW_AUTOSIZE);
	imshow("NoiseRemoval", result);
	waitKey(0);

	return 0;
}
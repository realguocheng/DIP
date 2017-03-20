#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  
#include <time.h>
#include <random>
using namespace cv;
using namespace std;

//Gaussian  Noise --(mu - 3*sig, mu + 3*sig)
double generateGaussianNoise(double mu, double sig)
{

	static double V1, V2, S;
	static int phase = 0;
	double X;

	if (phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);

	phase = 1 - phase;

	return X * sig + mu;
}

void addGaussianNoise(char * name, double mu, double sig)
{
	int i, j;
	uchar* p;
	Mat I = imread(name, CV_LOAD_IMAGE_GRAYSCALE);
	for (i = 0; i < I.rows; ++i) {
		p = I.ptr<uchar>(i);
		for (j = 0; j < I.cols; ++j) {
			double val = p[j] + generateGaussianNoise(mu, sig) * 50;
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;

			p[j] = (uchar)val;
		}
	}
	namedWindow("GaussianNoisy Image", WINDOW_AUTOSIZE);
	imshow("GaussianNoisy Image", I);
	waitKey(0);
}
//Uniform Noise
double generateUniformNoise(double a, double b) {
	double rseed = rand() / ((double)RAND_MAX);
	return a + (b - a) * rseed;
}

void addUniformNoise(char * name, int a, int b) {
	int i, j;
	uchar *p;
	Mat I = imread(name, CV_LOAD_IMAGE_GRAYSCALE);
	for (i = 0; i < I.rows; ++i) {
		p = I.ptr<uchar>(i);
		for (j = 0; j < I.cols; ++j) {
			double val = p[j] + generateUniformNoise(a, b);
			if (val < 0)
				val = 0;
			if (val > 255)
				val = 255;

			p[j] = (uchar)val;
		}
	}
	namedWindow("AverageNoisy Image", WINDOW_AUTOSIZE);
	imshow("AverageNoisy Image", I);
	waitKey(0);
}
//Salt & Pepper Noise
double generateSaltPepperNoise(double a, double b) {
	double rseed = rand() / ((double)RAND_MAX);
	if (rseed <= a)
		return 0;
	else if (rseed > a && rseed <= (a + b))
		return 255;
	else
		return -1;
}

void addSaltPepperNoise(char * name, double a, double b) {
	int i, j;
	uchar *p;
	Mat I = imread(name, CV_LOAD_IMAGE_GRAYSCALE);
	for (i = 0; i < I.rows; ++i) {
		p = I.ptr<uchar>(i);
		for (j = 0; j < I.cols; ++j) {
			double val = generateSaltPepperNoise(a, b);
			p[j] = (val == -1) ? p[j] : (uchar)val;
		}
	}
	namedWindow("SaltPepperNoisy Image", WINDOW_AUTOSIZE);
	imshow("SaltPepperNoisy Image", I);
	waitKey(0);
}
//Sin Noise
void addSinNoise(char * name, double A, double u, double v) {
	int i, j;
	uchar *p;
	Mat I = imread(name, CV_LOAD_IMAGE_GRAYSCALE);
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
	namedWindow("SinNoisy Image", WINDOW_AUTOSIZE);
	imshow("SinNoisy Image", I);
	waitKey(0);
}
//control
int main()
{
	char * imname = "4-1.tif";
	Mat image = imread(imname, CV_LOAD_IMAGE_GRAYSCALE);

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);
	waitKey(0);

	srand((unsigned int)time(NULL));

	addGaussianNoise(imname, 0, 1);
	addUniformNoise(imname, -50, 50);
	addSaltPepperNoise(imname, 0.04, 0.02);
	addSinNoise(imname, 70, 1, 0);
	return 0;
}
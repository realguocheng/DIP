#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  

using namespace cv;
using namespace std;

#define eps 0.00000000000000000000001
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

void addGaussianNoise(Mat& I, double mu, double sig)
{
	int i, j;
	uchar* p;
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
}
//degradate image
void imageDegradation(Mat& filter, double a, double b, double T) {
	Mat image = Mat(filter.size(), CV_32F), 
		real = Mat(filter.size(), CV_32F);

	double u, v;
	for (int i = 0; i < filter.rows; ++i) {
		for (int j = 0; j < filter.cols; ++j) {
			u = i + 1 - floor(filter.rows / 2);
			v = j + 1 - floor(filter.cols / 2);
			double share = CV_PI * (u * a + v * b + eps);
			real.at<float>(i, j) = T / share * sin(share) * cos(share);
			image.at<float>(i, j) = T / share * sin(share) * sin(share) * (-1);
		}
	}
	Mat toMerge[] = { real, image };
	merge(toMerge, 2, filter);
}

void shiftDFT(Mat& fImage)
{
	Mat tmp, q0, q1, q2, q3;

	fImage = fImage(Rect(0, 0, fImage.cols & -2, fImage.rows & -2));

	int cx = fImage.cols / 2;
	int cy = fImage.rows / 2;

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

void createRHFilter(Mat& f, Mat h, Mat dft, double k) {

	Mat hsplit[] = { Mat::zeros(size(f), CV_32F), Mat::zeros(size(f), CV_32F)},
		dftsplit[] = { Mat::zeros(size(f), CV_32F), Mat::zeros(size(f), CV_32F)},
		resplit[] = { Mat::zeros(size(f), CV_32F), Mat::zeros(size(f), CV_32F)};
	split(h, hsplit);
	split(dft, dftsplit);

	for (int i = 0; i < f.rows; ++i) {
		for (int j = 0; j < f.cols; ++j) {
			double hreal = hsplit[0].at<float>(i, j);
			double himag = hsplit[1].at<float>(i, j);
			double dreal = dftsplit[0].at<float>(i, j);
			double dimag = dftsplit[1].at<float>(i, j);

			double square = pow(hreal, 2) + pow(himag, 2);
			//cout << square << endl;
			double divReal = (dreal * hreal + dimag * himag) / square;
			double divImag = (dimag * hreal - dreal * himag) / square;

			resplit[0].at<float>(i, j) = divReal * square / (square + k);
			resplit[1].at<float>(i, j) = divImag * square / (square + k);;
		}
	}
	merge(resplit, 2, f);
}

int main() {

	Mat image = imread("4-1.tif", CV_LOAD_IMAGE_GRAYSCALE);
	int M = getOptimalDFTSize(image.rows);
	int N = getOptimalDFTSize(image.cols);

	Mat padded, planes[2], complexImg, filter, result;
	copyMakeBorder(image, padded, 0, M - image.rows, 0,
		N - image.cols, BORDER_CONSTANT, Scalar::all(0));

	planes[0] = Mat_<float>(padded);
	planes[1] = Mat::zeros(padded.size(), CV_32F);

	merge(planes, 2, complexImg);
	dft(complexImg, complexImg);

	filter = complexImg.clone();

	imageDegradation(filter, 0.1, 0.1, 1);
	shiftDFT(filter);

	mulSpectrums(complexImg, filter, complexImg, 0);

	//create_spectrum_magnitude_display(complexImg, true);

	idft(complexImg, complexImg);

	split(complexImg, planes);
	normalize(planes[0], result, 0, 255, NORM_MINMAX);
	//result = result(Rect(0, 0, image.cols, image.rows));
	result.convertTo(result, CV_8U);
	
	namedWindow("imageDegradation", WINDOW_NORMAL);
	imshow("imageDegradation", result);
	waitKey(0);

	addGaussianNoise(result, 0, 0.3);
	namedWindow("gaussian noise adding", WINDOW_NORMAL);
	imshow("gaussian noise adding", result);
	waitKey(0);

	//restore
	Mat aisle[] = {Mat_<float>(result), Mat::zeros(size(result), CV_32F)};
	Mat imback, rf = filter.clone();
	merge(aisle, 2, imback);

	dft(imback, imback);
	
	createRHFilter(rf, filter, imback, 0.01);

	idft(rf, rf);

	split(rf, aisle);
	normalize(aisle[0], imback, 0, 255, NORM_MINMAX);
	imback.convertTo(imback, CV_8U);

	imback = imback(Rect(0, 0, image.cols, image.rows));

	namedWindow("restore image", WINDOW_NORMAL);
	imshow("restore image", imback);
	waitKey(0);

	return 0;
}
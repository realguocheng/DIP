#include "HighPassFilters.h"
#include "LowPassFilters.h"

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

	// compute magnitude spectrum (N.B. for display)
	// compute log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))

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

	return mag;

}


/******************************************************************************/

int main(int argc, char** argv)
{

	Mat img, imgGray, imgOutput;	// image object(s)

	Mat padded;		// fourier image objects and arrays
	Mat complexImg, complexImg0, filter, filterOutput;
	Mat planes[2], mag;

	int N, M; // fourier image sizes

	int radius[] = { 10, 30, 60, 160, 460 };				// low pass filter parameter
	int order = 2;				// low pass filter parameter

	const char * originalName = "Input Image"; // window name
	const char * spectrumName = "Spectrum Image"; // window name
	const char * inverseName = "IDFT Image"; // window name
	const char * lowPassName = "Filtered Image"; // window name
	const char * filterName = "Filter Image"; // window nam

	// create window object (use flag=0 to allow resize, 1 to auto fix size)

	namedWindow(originalName, 0);
	namedWindow(spectrumName, 0);
	namedWindow(inverseName, 0);
	

	imgGray = imread("3-1.tif", CV_LOAD_IMAGE_GRAYSCALE);
	
	// setup the DFT image sizes

	M = getOptimalDFTSize(imgGray.rows);
	N = getOptimalDFTSize(imgGray.cols);


	// setup the DFT images

	copyMakeBorder(imgGray, padded, 0, M - imgGray.rows, 0,
		N - imgGray.cols, BORDER_CONSTANT, Scalar::all(0));
	planes[0] = Mat_<float>(padded);
	planes[1] = Mat::zeros(padded.size(), CV_32F);

	merge(planes, 2, complexImg);

	// do the DFT

	dft(complexImg, complexImg);

	//show the original image
	imshow(originalName, imgGray);
	//show the spectrum
	mag = create_spectrum_magnitude_display(complexImg, true);
	imshow(spectrumName, mag);
	//show the IDFT image
	Mat inverse;
	idft(complexImg, inverse, DFT_REAL_OUTPUT);
	normalize(inverse, inverse, 0, 1, CV_MINMAX);
	imshow(inverseName, inverse);

	
	waitKey();
	destroyAllWindows();
	namedWindow(lowPassName, 0);
	namedWindow(filterName, 0);
	// construct the filter (same size as complex image)
	filter = complexImg.clone();

	for (int i = 0; i < 5; i++) {

		GHPF(filter, radius[i]);
		complexImg0 = complexImg.clone();

		// apply filter
		shiftDFT(complexImg0);
		mulSpectrums(complexImg0, filter, complexImg0, 0);
		shiftDFT(complexImg0);

		// do inverse DFT on filtered image

		idft(complexImg0, complexImg0);

		// split into planes and extract plane 0 as output image

		split(complexImg0, planes);
		normalize(planes[0], imgOutput, 0, 1, CV_MINMAX);
		imgOutput = imgOutput(Rect(0, 0, imgGray.rows, imgGray.cols));
		// do the same with the filter image

		split(filter, planes);
		normalize(planes[0], filterOutput, 0, 1, CV_MINMAX);

		// display image in window
		imshow(lowPassName, imgOutput);
		imshow(filterName, filterOutput);


		waitKey(0);
	}

	return 0;
}
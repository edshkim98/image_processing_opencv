#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

//	Mat noise(src.size(), CV_32SC1);
//	randn(noise, 0, 5);
//	add(src, noise, src, Mat(), CV_8U);

	TickMeter tm;
	tm.start();

	Mat dst1;
	GaussianBlur(src, dst1, Size(), 5);

	tm.stop(); 
	cout << "Gaussian: " << tm.getTimeMilli() << endl;

	tm.reset();
	tm.start();

	Mat dst2;
	bilateralFilter(src, dst2, -1, 10, 5);

	tm.stop();
	cout << "Bilateral: " << tm.getTimeMilli() << endl;

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey(0);
	return 0;
}
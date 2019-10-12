#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void sobel_impl();
void sobel_func();

int main()
{
	sobel_impl();
	sobel_func();

	return 0;
}

void sobel_impl()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dx = Mat::zeros(src.size(), CV_8UC1);
	Mat dy = Mat::zeros(src.size(), CV_8UC1);
	Mat mag = Mat::zeros(src.size(), CV_8UC1);

	for (int j = 1; j < src.rows - 1; j++) {
		for (int i = 1; i < src.cols - 1; i++) {
			int v1 = src.at<uchar>(j - 1, i + 1)
				+ src.at<uchar>(j, i + 1) * 2
				+ src.at<uchar>(j + 1, i + 1)
				- src.at<uchar>(j - 1, i - 1)
				- src.at<uchar>(j, i - 1) * 2
				- src.at<uchar>(j + 1, i - 1);
			int v2 = src.at<uchar>(j + 1, i + 1)
				+ src.at<uchar>(j + 1, i) * 2
				+ src.at<uchar>(j + 1, i + 1)
				- src.at<uchar>(j - 1, i + 1)
				- src.at<uchar>(j - 1, i) * 2
				- src.at<uchar>(j - 1, i + 1);
			dx.at<uchar>(j, i) = saturate_cast<uchar>(v1 + 128);
			dy.at<uchar>(j, i) = saturate_cast<uchar>(v2 + 128);
			mag.at<uchar>(j, i) = saturate_cast<uchar>(sqrt(v1 * v1 + v2 * v2));
		}
	}

	Mat edge = mag > 120;

	imshow("src", src);
	imshow("dx", dx);
	imshow("dy", dy);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey(0);
	destroyAllWindows();
}

void sobel_func()
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dx, dy;
	Sobel(src, dx, CV_32FC1, 1, 0);
	Sobel(src, dy, CV_32FC1, 0, 1);

	Mat mag;
	magnitude(dx, dy, mag);
	mag.convertTo(mag, CV_8UC1);

	Mat edge = mag > 150;

	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey(0);
	destroyAllWindows();
}
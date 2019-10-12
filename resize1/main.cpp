#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void forward_mapping();
void backward_mapping();

int main()
{
	forward_mapping();
	backward_mapping();

	return 0;
}

void forward_mapping()
{
	Mat src = imread("camera.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst = Mat::zeros(src.rows * 2, src.cols * 2, src.type());

	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			int x_ = x * 2;
			int y_ = y * 2;
			dst.at<uchar>(y_, x_) = src.at<uchar>(y, x);
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
}

void backward_mapping()
{
	Mat src = imread("camera.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Mat dst = Mat::zeros(src.rows * 2, src.cols * 2, src.type());

	for (int y_ = 0; y_ < dst.rows; y_++) {
		for (int x_ = 0; x_ < dst.cols; x_++) {
			int x = x_ / 2;
			int y = y_ / 2;
			dst.at<uchar>(y_, x_) = src.at<uchar>(y, x);
		}
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	destroyAllWindows();
}
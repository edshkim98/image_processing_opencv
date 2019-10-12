#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void sharpen_mean();
void sharpen_gaussin();

int main(void)
{
	sharpen_mean();
	sharpen_gaussin();

	return 0;
}

void sharpen_mean()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	float sharpen[] = {
		-1 / 9.f, -1 / 9.f, -1 / 9.f,
		-1 / 9.f, 17 / 9.f, -1 / 9.f,
		-1 / 9.f, -1 / 9.f, -1 / 9.f
	};
	Mat filter(3, 3, CV_32F, sharpen);

	Mat dst;
	filter2D(src, dst, -1, filter);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void sharpen_gaussin()
{
	Mat src = imread("rose.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	imshow("src", src);

	for (int sigma = 1; sigma <= 5; sigma++) {
		Mat blurred;
		GaussianBlur(src, blurred, Size(), sigma);

		float alpha = 1.f;
		Mat dst = (1.f + alpha) * src - alpha * blurred;

		String desc = format("sigma: %d", sigma);
		putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);

		imshow("dst", dst);
		waitKey();
	}

	destroyAllWindows();
}
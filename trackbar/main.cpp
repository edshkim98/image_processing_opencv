#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int gBrightness = 100;
Mat src, dst;

void on_brightness(int, void*)
{

}

int main()
{
	src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src", src);

	namedWindow("dst");
	createTrackbar("Brightness", "dst", &gBrightness, 200, on_brightness);
	on_brightness(0, 0);

	waitKey(0);
	return 0;
}
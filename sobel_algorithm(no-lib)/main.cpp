#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);

	Mat dx = Mat::zeros(src.size(), CV_8UC1);
	Mat dy = Mat::zeros(src.size(), CV_8UC1);
	Mat mag = Mat::zeros(src.size(), CV_8UC1);

	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {
			int v1 = src.at<uchar>(y - 1, x + 1) + src.at<uchar>(y, x+1) * 2 + src.at<uchar>(y + 1, x + 1) - src.at<uchar>(y + 1, x - 1) - src.at<uchar>(y, x - 1) * 2 - src.at<uchar>(y -1 , x -1 );
			int v2 = src.at<uchar>(y - 1, x + 1) + src.at<uchar>(y - 1, x) * 2 + src.at<uchar>(y - 1, x - 1) - src.at<uchar>(y + 1, x - 1) - src.at<uchar>(y +1, x) * 2 - src.at<uchar>(y + 1, x + 1);
			dx.at<uchar>(y, x) = saturate_cast<uchar>(v1 + 128);
			dy.at<uchar>(y, x) = saturate_cast<uchar>(v1 + 128);
			mag.at<uchar>(y, x) = saturate_cast<uchar>(sqrt(v1*v1 + v2 * v2));
		}
	}

	Mat edge = mag > 120; // threshold 값 설정

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}
	imshow("src", src);
	imshow("dst", dx);
	imshow("dst2", dy);
	imshow("mag", mag);
	imshow("edge", edge);
	
	waitKey(0);
	return 0;
}

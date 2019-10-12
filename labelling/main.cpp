#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
	Mat src = imread("keyboard.bmp", IMREAD_GRAYSCALE);

	Mat src_bin;
	threshold(src, src_bin, 0, 255, THRESH_BINARY | THRESH_OTSU); //이진화

	Mat labels, stats, centroids;
	int cnt= connectedComponentsWithStats(src_bin, labels, stats, centroids);
	
	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	vector<vector<Point>> contours; //여러 객체의 외각선
	findContours(src_bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	
	for (int i = 0; i < contours.size(); i++) {
		vector<Point> cts = contours[i];
		if (cts.size() < 10) continue;
		drawContours(dst, contours, i, Scalar(0, 0, 255), 2); // 그림 출력
		
	}

	/*for (int i = 1; i < cnt; i++) {
		int area = stats.at<int>(i, 4);

		if (area < 100) continue;
		
		Rect rc(stats.at<int>(i, 0), stats.at<int>(i, 1), stats.at<int>(i, 2), stats.at<int>(i, 3));
		rectangle(dst, rc, Scalar(0, 0, 255), 2);
	}
	cout << cnt << endl;*/
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}

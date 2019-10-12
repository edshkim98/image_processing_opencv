#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void setSrcQuad(vector<Point> corners, Point2f srcQuad[4]);

int main()
{
	VideoCapture cap(0);

	if (!cap.isOpened()) {
		cerr << "Failed to open camera!" << endl;
		return -1;
	}

	int frame_width = (int)cap.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = (int)cap.get(CAP_PROP_FRAME_HEIGHT);
	cout << "width: " << frame_width << ", height: " << frame_height << endl;

	namedWindow("camera");
	namedWindow("namecard");

	int w = 450, h = 250;
	Point2f srcQuad[4], dstQuad[4];
	dstQuad[0] = Point2f(0, 0);
	dstQuad[1] = Point2f(0, h);
	dstQuad[2] = Point2f(w, h);
	dstQuad[3] = Point2f(w, 0);

	Mat src, src_gray, src_bin;
	Mat namecard(Size(w, h), CV_8UC3, Scalar(255, 255, 255));

	while (true) {
		cap >> src;
		if (src.empty()) {
			cerr << "Empty frame!" << endl;
			break;
		}

		cvtColor(src, src_gray, COLOR_BGR2GRAY);
		threshold(src_gray, src_bin, 0, 255, THRESH_BINARY | THRESH_OTSU);

		vector<vector<Point> > contours;
		findContours(src_bin, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);

		for (unsigned i = 0; i < contours.size(); i++) {
			vector<Point> approx;
			approxPolyDP(contours[i], approx, arcLength(contours[i], true)*0.02, true);

			if (fabs(contourArea(contours[i])) < 1000 || !isContourConvex(approx))
				continue;

			if (approx.size() == 4) {
				polylines(src, approx, true, Scalar(0, 255, 0), 2, LINE_AA);
				setSrcQuad(approx, srcQuad);

				Mat pers = getPerspectiveTransform(srcQuad, dstQuad);
				warpPerspective(src, namecard, pers, Size(w, h));
			}
		}

		imshow("camera", src);
		imshow("namecard", namecard);

		if (waitKey(1) >= 0)
			break;
	}

	return 0;
}

void setSrcQuad(vector<Point> corners, Point2f srcQuad[4])
{
	CV_Assert(corners.size() == 4);

	sort(corners.begin(), corners.end(), [](Point u, Point v) {
		return u.x < v.x;
	});

	if (corners[0].y < corners[1].y) {
		srcQuad[0] = Point2f(corners[0].x, corners[0].y);
		srcQuad[1] = Point2f(corners[1].x, corners[1].y);
	}
	else {
		srcQuad[1] = Point2f(corners[0].x, corners[0].y);
		srcQuad[0] = Point2f(corners[1].x, corners[1].y);
	}

	if (corners[2].y < corners[3].y) {
		srcQuad[3] = Point2f(corners[2].x, corners[2].y);
		srcQuad[2] = Point2f(corners[3].x, corners[3].y);
	}
	else {
		srcQuad[2] = Point2f(corners[2].x, corners[2].y);
		srcQuad[3] = Point2f(corners[3].x, corners[3].y);
	}
}


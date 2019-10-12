#include "opencv2/opencv.hpp"
#include <iostream>
#include "opencv2/core/ocl.hpp"

using namespace cv;
using namespace std;


void overlay(Mat& frame, Mat& cat, Point pos) {
	int sx = pos.x;
	int ex = pos.x + cat.cols;
	int sy = std::max(pos.y, 0);
	int ey = pos.y + cat.rows;

	for (int y = sy; y < ey; y++) {
		for (int x = sx; x < ex; x++) {
			Vec3b& p1 = frame.at<Vec3b>(y, x);
			Vec4b& p2 = cat.at<Vec4b>(y - sy, x - sx);

			float w = p2[3] / 255.f;

			p1[0] = p1[0] * (1 - w) + p2[0] * w;
			p1[1] = p1[1] * (1 - w) + p2[1] * w;
			p1[2] = p1[2] * (1 - w) + p2[2] * w;
		}

	}
}

int main(void)
{	
	ocl::setUseOpenCL(false);
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	
	Mat cat = imread("cat.png", IMREAD_UNCHANGED);//4CHANNEL BGR+ALPHA->TRANSPARENCY

	CascadeClassifier classifier;
	classifier.load("haarccascade_frontalface_alt2.xml");

	if (classifier.empty()) {
		cerr << "XML load failed!" << endl;
		return -1;
	}
	VideoCapture cap(0);
	Mat frame;
		while (true) {
			cap >> frame;
			cvtColor(frame, src, COLOR_BGR2GRAY);

			TickMeter tm;
			tm.start();

			vector<Rect> faces;
			classifier.detectMultiScale(src, faces, 1.2, 3, 0, Size(100, 100), Size(400, 400));

			tm.stop();
			cout << tm.getTimeMilli() << endl;
			if (src.empty()) {
				cerr << "Image load failed!" << endl;
				return -1;
			}

			Mat dst;
			dst = frame.clone();
			//cvtColor(src, dst, COLOR_GRAY2BGR);//3CHANNEL CONVERSION

			for (Rect face : faces) {
				float fx = (float)face.width / cat.cols;

				Mat cat2;
				resize(cat, cat2, Size(), fx, fx);

				overlay(dst, cat2, Point(face.x, face.y - face.height / 4));
				rectangle(dst, face, Scalar(0, 0, 255), 2);
			}

			imshow("src", src);
			imshow("dst", dst);

			if (waitKey(1) == 27) break;
		}

	waitKey(0);
	return 0;
}

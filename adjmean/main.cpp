#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cerr << "Usage: adjmean.exe <filename>" << endl;
		return -1;
	}

	// 1. argv[1] 영상을 그레이스케일 형태로 불러오기 (src)
	Mat src = imread(argv[1], IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	// 2. 입력 영상의 평균 밝기 구하여 mean에 저장.
	int s = 0;
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			s += src.at<uchar>(j, i);
		}
	}

	int m = s / (src.rows * src.cols);
	cout << "Mean value: " << m << endl;

	// OpenCV 함수를 이용하여 아래와 같이 구할 수도 있음
	//int m = sum(src)[0] / src.total();
	//int m = mean(src)[0];

	// 3. 평균 밝기가 128이 되도록 결과 영상 구하기 (dst)
	Mat dst = src + (128 - m);
	
	// 4. 화면 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cerr << "Usage: adjcont.exe <filename>" << endl;
		return -1;
	}

	// 1. argv[1] 영상을 그레이스케일 형태로 불러오기 (src)
	Mat src = imread(argv[1], IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	// 2. 입력 영상의 평균 밝기 구하여 mean에 저장.
	int m = int(mean(src)[0]);
	cout << "Mean value: " << m << endl;
	
	// 3. 평균 밝기를 기준으로 명암비 향상시키기
	float alpha = 1.0f;
	Mat dst = src + (src - m) * alpha;
	
	// 4. 화면 출력
	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}
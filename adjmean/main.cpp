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

	// 1. argv[1] ������ �׷��̽����� ���·� �ҷ����� (src)
	Mat src = imread(argv[1], IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	// 2. �Է� ������ ��� ��� ���Ͽ� mean�� ����.
	int s = 0;
	for (int j = 0; j < src.rows; j++) {
		for (int i = 0; i < src.cols; i++) {
			s += src.at<uchar>(j, i);
		}
	}

	int m = s / (src.rows * src.cols);
	cout << "Mean value: " << m << endl;

	// OpenCV �Լ��� �̿��Ͽ� �Ʒ��� ���� ���� ���� ����
	//int m = sum(src)[0] / src.total();
	//int m = mean(src)[0];

	// 3. ��� ��Ⱑ 128�� �ǵ��� ��� ���� ���ϱ� (dst)
	Mat dst = src + (128 - m);
	
	// 4. ȭ�� ���
	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}
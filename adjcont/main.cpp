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

	// 1. argv[1] ������ �׷��̽����� ���·� �ҷ����� (src)
	Mat src = imread(argv[1], IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return -1;
	}

	// 2. �Է� ������ ��� ��� ���Ͽ� mean�� ����.
	int m = int(mean(src)[0]);
	cout << "Mean value: " << m << endl;
	
	// 3. ��� ��⸦ �������� ��Ϻ� ����Ű��
	float alpha = 1.0f;
	Mat dst = src + (src - m) * alpha;
	
	// 4. ȭ�� ���
	imshow("src", src);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}
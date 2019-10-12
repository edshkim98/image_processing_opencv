#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void ScalarOp();
void InputArrayOp();
void printMat(InputArray _mat);

int main()
{
	ScalarOp();
	InputArrayOp();

	return 0;
}

void ScalarOp()
{
	Scalar gray = 128;
	cout << "gray: " << gray << endl;

	Scalar yellow(0, 255, 255);
	cout << "yellow: " << yellow << endl;

	Mat img1(256, 256, CV_8UC3, yellow);

	for (int i = 0; i < 4; i++)
		cout << yellow.val[i] << ", " << yellow[i] << endl;
}

void InputArrayOp()
{
	uchar data1[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat1(2, 3, CV_8UC1, data1);
	printMat(mat1);

	vector<float> vec1 = { 1.2f, 3.4f, -2.1f };
	printMat(vec1);
}

void printMat(InputArray _mat)
{
	Mat mat = _mat.getMat();
	cout << mat << endl;
}
#include "stdafx.h"
#include <opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

int main()
{
	cv::Mat src1 = imread("C://Users//1234//Desktop//rimg.jpg", 0);
	cv::Mat src2 = imread("C://Users//1234//Desktop//timg.jpg", 0);
	cv::Mat dst1, dst2, dst;

	//��ʼ��ʱ
	double start = static_cast<double>(cvGetTickCount());

	ifftDemo(src1, dst1, 0);         //��Ƶ
	imshow("dst1", dst1);

	ifftDemo(src2, dst2, 1);         //��Ƶ
	imshow("dst2", dst2);

	add(dst2, dst1, dst);
	imshow("dst", dst);
	//������ʱ
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//��ʾʱ��
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//�ȴ�������Ӧ�����������������
	system("pause");
	return 0;
}


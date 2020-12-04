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

	//开始计时
	double start = static_cast<double>(cvGetTickCount());

	ifftDemo(src1, dst1, 0);         //低频
	imshow("dst1", dst1);

	ifftDemo(src2, dst2, 1);         //高频
	imshow("dst2", dst2);

	add(dst2, dst1, dst);
	imshow("dst", dst);
	//结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing time:" << time / 1000 << "ms" << endl;

	//等待键盘响应，按任意键结束程序
	system("pause");
	return 0;
}


#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat dst;
	cv::Mat src = cv::imread("C://Users//1234//Desktop//pict.jpg", 1);
	if (src.empty())
		return -1;
	cv::Point2f center(src.cols / 2, src.rows / 2);
	float angle = -10, scale = 1;
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, scale);
	//获取外接四边形
	cv::Rect rectangle = cv::RotatedRect(center, src.size(), angle).boundingRect();
	rot.at<double>(0, 2) += rectangle.width / 2.0 - center.x;
	rot.at<double>(1, 2) += rectangle.height / 2.0 - center.y;
	cv::warpAffine(src, dst, rot, rectangle.size());
	imshow("dst", dst);
	waitKey(0);
	return 0;
}
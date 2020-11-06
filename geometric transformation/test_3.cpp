#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat img, dst;
	Point pt_1, pt_2, pt_3;     //需要找到的三个点

    img = cv::imread("C://Users//1234//Desktop//pict.jpg",1);
	if (img.empty())
		return -1;
	
	int height = img.rows;
	int width = img.cols;

	for (int i = 0; i < width; i++)           //左上角
	{
		if (img.at<uchar>(i, 0) < 250)
		{
			pt_1.x = width - i;
			pt_1.y = 0;
		}
	}
	cout << "pt_1:" << pt_1 << endl;

	for (int i = 0; i < width; i++)            //右下角
	{
		if (img.at<uchar>(i, height) < 250)
		{
			pt_2.x = i;
			pt_2.y = height;
		}
	}
	cout << "pt_2:" << pt_2 << endl;

	for (int i = 0; i < height; i++)            //左下角
	{
		if (img.at<uchar>(0, i) < 250)
		{
			pt_3.x = 0;
			pt_3.y = i;
		}
	}
	cout << "pt_3:" << pt_3 << endl;

	circle(img, pt_1, 5, CV_RGB(255, 0, 0), 1, 8, 0);
	circle(img, pt_2, 5, CV_RGB(255, 0, 0), 1, 8, 0);
	circle(img, pt_3, 5, CV_RGB(255, 0, 0), 1, 8, 0);
	imshow("img", img);
	//仿射还原
	const cv::Point2f img_pt[] = { pt_1,pt_2,pt_3 };
	const cv::Point2f dst_pt[] = { cv::Point2f(0,0),cv::Point2f(width,height),cv::Point2f(0,height) };
	const cv::Mat affine_matrix = cv::getAffineTransform(img_pt, dst_pt);
	cv::warpAffine(img, dst, affine_matrix, img.size());
	cv::imshow("仿射还原", dst);

	cv::waitKey(0);
	return 0;
}
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat dst_1, dst_2, dst_3;
	cv::Mat src = cv::imread("C://Users//1234//Desktop//pict.jpg",1);
	if (src.empty())
		return -1;

	//旋转
	float angle = 40.0, scale = 1;      //旋转40°，不缩放
	//以图像中心为旋转中心
	cv::Point2f center(src.cols*0.5, src.rows*0.5);
	const cv::Mat affine_matrix_r = cv::getRotationMatrix2D(center, angle, scale);
	cv::warpAffine(src, dst_1, affine_matrix_r, src.size());

	cv::imshow("src", src);
	cv::imshow("旋转", dst_1);

	//仿射
	const cv::Point2f src_pt[] = { cv::Point2f(200,200),cv::Point2f(250,200),cv::Point2f(200,100) };
	const cv::Point2f dst_2_pt[] = { cv::Point2f(300,100),cv::Point2f(300,50),cv::Point2f(200,100) };
	const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_2_pt);
	cv::warpAffine(src, dst_2, affine_matrix, src.size());

	cv::imshow("仿射", dst_2);

	//投影
	const cv::Point2f pts1[] = { cv::Point2f(150,150),cv::Point2f(150,300),cv::Point2f(350,300),cv::Point2f(350,150) };
	const cv::Point2f pts2[] = { cv::Point2f(200,150),cv::Point2f(200,300),cv::Point2f(340,270),cv::Point2f(340,180) };
	cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);
	cv::warpPerspective(src, dst_3, perspective_matrix, src.size());

	cv::imshow("投影", dst_3);

	cv::waitKey(0);
	return 0;

}
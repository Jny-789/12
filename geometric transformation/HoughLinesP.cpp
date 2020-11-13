#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat img, canny_dst, img_dx, img_dy;
	cv::Mat src = imread("C://Users//1234//Desktop//111.jpg");
	cv::Mat src_gray = imread("C://Users//1234//Desktop//111.jpg", 0);
	threshold(src_gray, img, 100, 255, THRESH_BINARY);
	Sobel(img, img_dx, CV_16SC1, 1, 0, 3);
	Sobel(img, img_dy, CV_16SC1, 0, 1, 3);
	Canny(img_dx, img_dy, canny_dst, 30, 150);
	imshow("边缘检测", canny_dst);

	std::vector<cv::Vec4i>lines;
	cv::HoughLinesP(canny_dst, lines, 1, CV_PI / 180, 35, 15, 10);  //检测
	                             //第6个参数为最小线段长度，低于这个值线段就不显示
	                             //第7个参数为允许同一行的点连起来的最大间隔，超过这个值点就不能连成线
	
	std::vector<Vec4i>::const_iterator it = lines.begin();
	for (; it != lines.end(); ++it)         //画线
	{
		cv::Point pt1, pt2;
		pt1.x = (*it)[0];
		pt1.y = (*it)[1];
		pt2.x = (*it)[2];
		pt2.y = (*it)[3];
		line(src, pt1, pt2, Scalar(255, 255, 255), 2, CV_AA);
	}
	imshow("src", src);
	waitKey(0);
	return 0;
}
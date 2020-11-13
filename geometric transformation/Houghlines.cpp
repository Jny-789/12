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
	Canny(img_dx, img_dy,canny_dst, 30, 150);
	imshow("±ßÔµ¼ì²â",canny_dst);

	std::vector<cv::Vec2f>lines;
	cv::HoughLines(canny_dst, lines, 1, CV_PI / 180, 92);      //¼ì²â

	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for (; it != lines.end(); ++it)              //»­Ïß
	{
		float rho = (*it)[0], theta = (*it)[1];
		cv::Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		cv::line(src, pt1, pt2, cv::Scalar(255, 255, 255), 2, CV_AA);
	}

	imshow("src", src);
	waitKey(0);

	return 0;
}



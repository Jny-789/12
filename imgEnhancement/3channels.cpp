#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() {
	cv::Mat src = imread("E://vs_work//imgEnhancement//img1.jpg");
	cv::Mat dst;

	//分离通道
	std::vector<cv::Mat> channels;
	cv::split(src, channels);

	equalizeHist(channels.at(0), channels.at(0));
	equalizeHist(channels.at(0), channels.at(1));
	equalizeHist(channels.at(0), channels.at(2));
	//合并通道
	merge(channels,dst);

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}
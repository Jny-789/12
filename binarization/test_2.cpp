#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() {
	Mat src, img, labels, stats, centroids;
	src = imread("C://Users//1234//Desktop//1.jpg",0);
	threshold(src, img, 100, 255, THRESH_BINARY);      //二值化

	int n = connectedComponentsWithStats(img, labels, stats, centroids, 8, CV_32S);      //连通域标记

	cout << "n=" << n << endl;                     //连通域总数

	for (int i = 0; i < n; i++) {
		cout << "x=" << stats.at<int>(i,0) << endl;
		cout << "y=" << stats.at<int>(i,1) << endl;
		cout << "width=" << stats.at<int>(i,2) << endl;
		cout << "height=" << stats.at<int>(i,3) << endl;
		cout << "s=" << stats.at<int>(i,4) << endl;
	}

	//画矩形
	cv::Rect rect;
	for (int i = 1; i < n ; i++) {
		rect.x = stats.at<int>(i, 0);
		rect.y = stats.at<int>(i, 1);
		rect.width = stats.at<int>(i, 2);
		rect.height = stats.at<int>(1, 3);
		rectangle(img, rect, CV_RGB(255, 255, 255, ), 1, 8, 0);
	}

	imshow("img", img);
	waitKey(0);
	return 0;
}

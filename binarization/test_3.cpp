#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() {
	Mat src, img, dst;
	Mat labels, stats, centroids;
	src = imread("C://Users//1234//Desktop//3.jpg",0);

	int height = src.rows;                 //色彩转换
	int width = src.cols;
	/*for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = src.at<Vec3b>(j, i)[0] + src.at<Vec3b>(j, i)[1] + src.at<Vec3b>(j, i)[2] / 3;
			if (average >100)
				average = 0;
			else
				average = 255;
			src.at<Vec3b>(j, i)[0] = average;
			src.at<Vec3b>(j, i)[1] = average;
			src.at<Vec3b>(j, i)[2] = average;
		}
	}*/
	
	for (int j = 0; j < height; j++) 
	{
		for (int i = 0; i < width; i++) 
		{
			src.at<uchar>(j, i) = 255 - src.at<uchar>(j, i);
		}
	}
	imshow("色彩转换之后", src);

	threshold(src, img, 100, 255, THRESH_BINARY);
	Mat element = getStructuringElement(MORPH_RECT, Size(20,20), Point(-1, -1));
	morphologyEx(img, dst, MORPH_OPEN, element);      //开运算去除连接线
	imshow("去除连接线", dst);

	int n = connectedComponentsWithStats(dst, labels, stats, centroids, 8, CV_32S);      //连通域标记
	cout << "原点个数" << n-1 << endl;                     //n为连通域总数

	cv::Rect rect;
	for (int i = 1; i < n ; i++) 
	{
			rect.x = stats.at<int>(i, 0);
			rect.y = stats.at<int>(i, 1);
		    rect.width = stats.at<int>(i, 2);
		    rect.height = stats.at<int>(1, 3);
			rectangle(dst, rect, CV_RGB(255, 255, 255, ), 1, 8, 0);
	}
	imshow("区域标记后", dst);
	waitKey(0);
	return 0;
}
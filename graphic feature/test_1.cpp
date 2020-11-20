#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat img, after_erode, labels, stats, centroids;
	cv::Mat src_gray = imread("C://Users//1234//Desktop//20.png", 0);
	cv::Mat src = imread("C://Users//1234//Desktop//20.png");
	threshold(src_gray, img, 100, 255, THRESH_BINARY);

	//反色
	int height = img.rows;
	int width = img.cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			img.at<uchar>(j, i) = 255 - img.at<uchar>(j, i);
		}
	}

	//连通域
	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;
	findContours(img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	//获取最小外接四边形
	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		float width = (float)rbox.size.width;
		float height = (float)rbox.size.height;
		float ratio = width / height;
		if (ratio > 0.8&&ratio < 1.2&&width>20)         //筛选
		{
			drawContours(src, contours, i, Scalar(0, 255, 255), -1, 8);      //画轮廓
			cv::Point2f vtx[4];
			rbox.points(vtx);
			for (int i = 0; i < 4; ++i)
			{
				cv::line(src, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);  //画外接四边形
			}
		}
	}

	imshow("结果", src);
	waitKey(0);
	return 0;
}
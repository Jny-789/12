#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat rsrc, rsrc_gray, img;
	cv::Mat src = imread("C://Users//1234//Desktop//23.jpg");
	cv::Mat src_gray = imread("C://Users//1234//Desktop//23.jpg", 0);

	//缩小，原图尺寸太大
	resize(src, rsrc, Size(src.cols*0.1, src.rows*0.1), INTER_LINEAR);   
	resize(src_gray, rsrc_gray, Size(src_gray.cols*0.1, src_gray.rows*0.1), INTER_LINEAR);  
	
    int h = rsrc.rows;
	int w = rsrc.cols;
	//遍历灰度图，降低较亮区域的灰度，区分杯盖与白色的桌面
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (rsrc_gray.at<uchar>(i, j) > 139 )
			{
				rsrc_gray.at <uchar>(i, j) = 50;
			}
		}
	}
	imshow("灰度图重置", rsrc_gray);

	threshold(rsrc_gray, img, 90, 255, THRESH_BINARY);
	imshow("二值化", img);

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
		float ratio = height / width;
		if (ratio < 2 && width < 130 && width>40) //筛选
		{
			cv::Point2f vtx[4];
			rbox.points(vtx);
			for (int i = 0; i < 4; ++i)
			{
				cv::line(rsrc, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);  //画外接四边形
			}
		}
	}
	imshow("结果", rsrc);
	waitKey(0);
	return 0;
}
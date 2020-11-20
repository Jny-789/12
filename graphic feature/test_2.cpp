#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat img;
	cv::Mat src_gray = imread("C://Users//1234//Desktop//22.jpg", 0);
	cv::Mat src = imread("C://Users//1234//Desktop//22.jpg");
	threshold(src_gray, img, 170, 255, THRESH_BINARY);

	//��ͨ��
	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;
	findContours(img, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);  //�����������

	//��ȡ��С����ı���
	for (int i = 0; i < contours.size(); i++)
	{
		RotatedRect rbox = minAreaRect(contours[i]);
		float width = (float)rbox.size.width;
		float height = (float)rbox.size.height;
		float ratio = width / height;
		if (ratio > 0.8&&ratio < 1.2&&width>50)     //ɸѡ
		{
			drawContours(src, contours, i, Scalar(0, 255, 255), 1, 8);
			cv::Point2f vtx[4];
			rbox.points(vtx);
			for (int i = 0; i < 4; ++i)
			{
				cv::line(src, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);  
			}
		}
	}

	imshow("���", src);
	waitKey(0);
	return 0;
}
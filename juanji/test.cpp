#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;

	cap.open(0);

	if (!cap.isOpened()) 
	{
		std::cout << "不能打开视频文件" << std::endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;
	while (1) 
	{
		cv::Mat frame, dst_1, dst_2, dst_3, dst_4, dx, dy, dst_5;
		bool rSucess = cap.read(frame);
		if (!rSucess)
		{
			std::cout << "不能从视频文件中读取帧" << std::endl;
			break;
		}
		else 
		{
			cv::imshow("frame", frame);
			//中值滤波
			medianBlur(frame, dst_1, 5);
			imshow("中值滤波", dst_1);
		    //均值滤波
			blur(frame, dst_2, Size(3, 3));
			imshow("均值滤波", dst_2);
			//高斯滤波
			GaussianBlur(frame, dst_3, Size(3, 3), 0, 0);
			imshow("高斯滤波", dst_3);
			//边缘检测
			Sobel(frame, dx, CV_8UC1, 1, 0, 3);
			Sobel(frame, dy, CV_8UC1, 0, 1, 3);
			convertScaleAbs(dx, dy);
			imshow("边缘检测x", dx);
			imshow("边缘检测y", dy);
			//磨皮			
			bilateralFilter(frame, dst_5, 10, 20, 20);
			imshow("磨皮", dst_5);
		}
		waitKey(30);
	}
	return 0;
}

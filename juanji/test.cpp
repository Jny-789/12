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
		std::cout << "���ܴ���Ƶ�ļ�" << std::endl;
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
			std::cout << "���ܴ���Ƶ�ļ��ж�ȡ֡" << std::endl;
			break;
		}
		else 
		{
			cv::imshow("frame", frame);
			//��ֵ�˲�
			medianBlur(frame, dst_1, 5);
			imshow("��ֵ�˲�", dst_1);
		    //��ֵ�˲�
			blur(frame, dst_2, Size(3, 3));
			imshow("��ֵ�˲�", dst_2);
			//��˹�˲�
			GaussianBlur(frame, dst_3, Size(3, 3), 0, 0);
			imshow("��˹�˲�", dst_3);
			//��Ե���
			Sobel(frame, dx, CV_8UC1, 1, 0, 3);
			Sobel(frame, dy, CV_8UC1, 0, 1, 3);
			convertScaleAbs(dx, dy);
			imshow("��Ե���x", dx);
			imshow("��Ե���y", dy);
			//ĥƤ			
			bilateralFilter(frame, dst_5, 10, 20, 20);
			imshow("ĥƤ", dst_5);
		}
		waitKey(30);
	}
	return 0;
}

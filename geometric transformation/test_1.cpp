#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;

	cap.open(0);

	if (!cap.isOpened()) {
		std::cout << "���ܴ���Ƶ�ļ�" << std::endl;
		return -1;
	}

	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;
	while (1) {
		cv::Mat frame, dst, dx, dy;
		bool rSucess = cap.read(frame);
		if (!rSucess) {
			std::cout << "���ܴ���Ƶ�ļ��ж�ȡ֡" << std::endl;
			break;
		}
		else {
			Sobel(frame, dx, CV_16SC1, 1, 0, 3);
			Sobel(frame, dy, CV_16SC1, 0, 1, 3);
			Canny(dx, dy, dst, 30, 150);
			imshow("canny��Ե���", dst);	
		}
		waitKey(30);
	}

	return 0;
}
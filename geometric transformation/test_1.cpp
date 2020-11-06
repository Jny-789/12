#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;

	cap.open(0);

	if (!cap.isOpened()) {
		std::cout << "不能打开视频文件" << std::endl;
		return -1;
	}

	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;
	while (1) {
		cv::Mat frame, dst, dx, dy;
		bool rSucess = cap.read(frame);
		if (!rSucess) {
			std::cout << "不能从视频文件中读取帧" << std::endl;
			break;
		}
		else {
			Sobel(frame, dx, CV_16SC1, 1, 0, 3);
			Sobel(frame, dy, CV_16SC1, 0, 1, 3);
			Canny(dx, dy, dst, 30, 150);
			imshow("canny边缘检测", dst);	
		}
		waitKey(30);
	}

	return 0;
}
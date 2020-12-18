//#include<opencv2/opencv.hpp>
//#include<iostream>
//using namespace cv;
//using namespace std;
//
//int main() {
//	VideoCapture cap;
//
//	cap.open(0);
//
//	if (!cap.isOpened()) {
//		std::cout << "不能打开视频文件" << std::endl;
//		return -1;
//	}
//	double fps = cap.get(CAP_PROP_FPS);      //获取视频帧率
//
//	Mat bgMat, subMat, bnyMat;
//	while (1) {
//		cv::Mat frame;
//		bool rSucess = cap.read(frame);
//		if (!rSucess) {
//			std::cout << "不能从视频文件中读取帧" << std::endl;
//			break;
//		}
//		else {
//			int count = 0;
//			while (1) {
//				cap >> frame;
//				cvtColor(frame, frame, COLOR_BGR2GRAY);
//
//				if (count == 0) {
//					frame.copyTo(bgMat);        //将第一帧作为背景
//				}
//				else {
//					absdiff(frame, bgMat, subMat);
//					threshold(subMat, bnyMat, 100, 255, CV_THRESH_BINARY);    //二值化
//
//					imshow("frame", frame);
//					imshow("bnyMat", bnyMat);
//					waitKey(30);
//				}
//				count++;
//			}
//		}
//	}
//	return 0;
//}

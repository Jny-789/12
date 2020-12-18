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
//		std::cout << "���ܴ���Ƶ�ļ�" << std::endl;
//		return -1;
//	}
//	double fps = cap.get(CAP_PROP_FPS);      //��ȡ��Ƶ֡��
//
//	Mat bgMat, subMat, bnyMat;
//	while (1) {
//		cv::Mat frame;
//		bool rSucess = cap.read(frame);
//		if (!rSucess) {
//			std::cout << "���ܴ���Ƶ�ļ��ж�ȡ֡" << std::endl;
//			break;
//		}
//		else {
//			int count = 0;
//			while (1) {
//				cap >> frame;
//				cvtColor(frame, frame, COLOR_BGR2GRAY);
//
//				if (count == 0) {
//					frame.copyTo(bgMat);        //����һ֡��Ϊ����
//				}
//				else {
//					absdiff(frame, bgMat, subMat);
//					threshold(subMat, bnyMat, 100, 255, CV_THRESH_BINARY);    //��ֵ��
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

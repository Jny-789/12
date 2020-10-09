//#include<iostream>
//#include<opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//	Mat srcMat, result_1,result_2;
//	srcMat=imread("C://Users//1234//Desktop//pic.png",0);   //»Ò¶È»¯
//	threshold(srcMat, result_1, 100, 255, THRESH_BINARY);
//
//	adaptiveThreshold(srcMat, result_2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV,15,10);
//
//
//	//imshow("result", result_1);
//	imshow("result", result_2);
//	waitKey(0);
//	return 0;
//}
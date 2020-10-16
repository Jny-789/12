//#include<opencv2/opencv.hpp>
//#include<iostream>
//using namespace cv;
//using namespace std;
//
//int main() {
//	Mat src, img, dst;
//	src = imread("C://Users//1234//Desktop//3.jpg");
//	threshold(src, img, 100, 255, THRESH_BINARY);
//	Mat getStructuringElement(int shape, Size esize, Point anchor = Point(-1, -1));
//	int g_nStructElementSize = 20;           
//	Mat element = getStructuringElement(MORPH_RECT, Size(g_nStructElementSize, g_nStructElementSize));
//	//morphologyEx(img, dst, MORPH_OPEN, element);  //开运算
//	erode(img, dst, element);
//	imshow("原点",dst);
//	waitKey(0);
//	return 0;
//}
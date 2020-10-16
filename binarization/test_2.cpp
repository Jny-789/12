//#include<opencv2/opencv.hpp>
//#include<iostream>
//using namespace cv;
//using namespace std;
//
//int main() {
//	cv::Mat src, img, dst, stats, centroids;
//	src = imread("C://Users//1234//Desktop//1.jpg");
//	cv::threshold(src, img, 100, 255, THRESH_BINARY);      //二值化
//
//	imshow("img", img);
//
//	CV_EXPORTS_W int connectedComponentsWithStats(cv::Mat img , cv::Mat dst, OutputArray stats,OutputArray centroids,
//		                           int connectivity= 8, int ltype=CV_32S);       //连通域标记
//
//	imshow("dst", dst);
//	waitKey(0);
//	return 0;
//
//	////矩形
//	//Mat dispMat_rect;
//	//cv::Rect rect;
//	//dispMat_rect.create(500, 500, CV_8UC3);
//	//rect.x = 150;
//	//rect.y = 150;
//	//rect.width = 200;
//	//rect.height = 100;
//	//rectangle(dispMat_rect, rect, CV_RGB(255, 0, 0, ), 1, 8, 0);
//}

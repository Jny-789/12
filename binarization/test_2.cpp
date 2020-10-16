#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() {
	Mat src,img, dst;
	src = imread("C://Users//1234//Desktop//1.jpg");
	threshold(src, img, 100, 255, THRESH_BINARY);    //二值化

	CV_EXPORTS_W int connectedComponentsWithStats(Mat img, Mat dst, OutputArray stats, 
		         OutputArray centroids,int connectivity = 8, int ltype = CV_32S);       //连通域标记


	////矩形
	//Mat dispMat_rect;
	//cv::Rect rect;
	//dispMat_rect.create(500, 500, CV_8UC3);
	//rect.x = 150;
	//rect.y = 150;
	//rect.width = 200;
	//rect.height = 100;
	//rectangle(dispMat_rect, rect, CV_RGB(255, 0, 0, ), 1, 8, 0);


}
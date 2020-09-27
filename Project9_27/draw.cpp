#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(){

	cv::Point pt,pt1,pt2;
	cv::Mat dispMat_circle,dispMat_line,dispMat_rect;
	cv::Rect rect;
	dispMat_circle.create(500, 500,CV_8UC3);
	dispMat_line.create(500, 500, CV_8UC3);
	dispMat_rect.create(500, 500, CV_8UC3);
	
	//»­Ô²
	pt.x = 250;                      //Ô²ÐÄÎ»ÖÃ
	pt.y = 250;
	circle(dispMat_circle, pt, 50, CV_RGB(255, 0, 0, ), 1, 8, 0);      //°ë¾¶50

	//»­Ïß¶Î
	pt1.x = 150;
	pt1.y = 50;
	pt2.x = 300;
	pt2.y = 300;
	line(dispMat_line, pt1,pt2,CV_RGB(255, 0, 0, ), 1, 8, 0);  

	//»­¾ØÐÎ
	rect.x = 150;
	rect.y = 150;
	rect.width = 200;
	rect.height = 100;
	rectangle(dispMat_rect, rect, CV_RGB(255, 0, 0, ), 1, 8, 0);

	//ÏÔÊ¾Í¼Ïñ
	imshow("circle", dispMat_circle);
	imshow("line", dispMat_line);
	imshow("rectangle", dispMat_rect);
	waitKey(0);

	return 0;

}
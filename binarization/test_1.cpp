#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() {
	Mat src,result_1,dst_1,dst_2,dst_3,dst_4;
	src = imread("C://Users//1234//Desktop//1.jpg");
	threshold(src, result_1, 100, 255, THRESH_BINARY);    //二值化
	Mat getStructuringElement(int shape, Size esize, Point anchor = Point(-1, -1));
	int g_nStructElementSize = 3;           //结构元素(内核矩阵)的尺寸
	Mat element = getStructuringElement(MORPH_RECT,Size(g_nStructElementSize, g_nStructElementSize));

	erode(result_1, dst_1, element);               //腐蚀
	dilate(result_1, dst_2, element);                //膨胀

	morphologyEx(result_1, dst_3, MORPH_OPEN,element);  //开运算
	morphologyEx(result_1, dst_4, MORPH_CLOSE, element);   //闭运算

	imshow("腐蚀", dst_1);
	imshow("膨胀", dst_2);
	imshow("开运算",dst_3);
	imshow("闭运算",dst_4);
	waitKey(0);
	return 0;
}


#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() {
	Mat src,result_1,dst_1,dst_2,dst_3,dst_4;
	src = imread("C://Users//1234//Desktop//1.jpg");
	threshold(src, result_1, 100, 255, THRESH_BINARY);    //��ֵ��
	Mat getStructuringElement(int shape, Size esize, Point anchor = Point(-1, -1));
	int g_nStructElementSize = 3;           //�ṹԪ��(�ں˾���)�ĳߴ�
	Mat element = getStructuringElement(MORPH_RECT,Size(g_nStructElementSize, g_nStructElementSize));

	erode(result_1, dst_1, element);               //��ʴ
	dilate(result_1, dst_2, element);                //����

	morphologyEx(result_1, dst_3, MORPH_OPEN,element);  //������
	morphologyEx(result_1, dst_4, MORPH_CLOSE, element);   //������

	imshow("��ʴ", dst_1);
	imshow("����", dst_2);
	imshow("������",dst_3);
	imshow("������",dst_4);
	waitKey(0);
	return 0;
}


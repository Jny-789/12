#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() 
{
	Mat src, img, dst;
	Mat labels, stats, centroids;
	src = imread("C://Users//1234//Desktop//4.jpg",0);
	threshold(src, img, 100, 255, THRESH_BINARY);

	//�ڰ�ɫ��ת��
	int height = img.rows;                 
	int width = img.cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			img.at<uchar>(j, i) = 255 - img.at<uchar>(j, i);
		}
	}
	imshow("ɫ��ת��֮��", img);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	erode(img, dst, element);               //��ʴ��ȥ����

	int n = connectedComponentsWithStats(dst, labels, stats, centroids, 8, CV_32S);  //nΪ��ͨ������    

	int a = 100;                                    //����һ����ʼֵa=100���뻭���ľ��ε���ͨ��Ƚ�
	for (int i = 1; i < 10; i++) 
	{	
		if (a > stats.at<int>(i, 2))                //�����ο��С��a��ѿ�ȸ�ֵ��a
			a = stats.at<int>(i, 2);                //ѭ����ɵõ�������ͨ���ȵ���Сֵ������Ҫȥ������߿�Ŀ��				 
	}

    //ȥ����߿�ĸ���
	for (int j = 0; j < height; j++)
	{
		for(int i=0;i<10;i++)
			dst.at<uchar>(j, i) = 0;
	}
    imshow("����߿��", dst);	

	int n2 = connectedComponentsWithStats(dst, labels, stats, centroids, 8, CV_32S);  //n2Ϊȥ����߿�����ͨ������

    //��ͨ����
	cv::Rect rect;
	for (int i = 1; i < n2 ; i++) 
	{
				rect.x = stats.at<int>(i, 0);
				rect.y = stats.at<int>(i, 1);
			    rect.width = stats.at<int>(i, 2);
			    rect.height = stats.at<int>(i, 3);
				rectangle(dst, rect, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	imshow("�����Ǻ�", dst);
	cout << "���������=" << n2-1 << endl;                     //nΪ��ͨ������
	waitKey(0);
	return 0;
}
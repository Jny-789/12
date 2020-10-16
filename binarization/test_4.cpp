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

	//黑白色彩转换
	int height = img.rows;                 
	int width = img.cols;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			img.at<uchar>(j, i) = 255 - img.at<uchar>(j, i);
		}
	}
	imshow("色彩转换之后", img);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	erode(img, dst, element);               //腐蚀，去杂质

	int n = connectedComponentsWithStats(dst, labels, stats, centroids, 8, CV_32S);  //n为连通域数量    

	int a = 100;                                    //定义一个初始值a=100，与画出的矩形的连通域比较
	for (int i = 1; i < 10; i++) 
	{	
		if (a > stats.at<int>(i, 2))                //若矩形宽度小于a则把宽度赋值给a
			a = stats.at<int>(i, 2);                //循环后可得到矩形连通域宽度的最小值，即需要去除的左边框的宽度				 
	}

    //去除左边框的干扰
	for (int j = 0; j < height; j++)
	{
		for(int i=0;i<10;i++)
			dst.at<uchar>(j, i) = 0;
	}
    imshow("处理边框后", dst);	

	int n2 = connectedComponentsWithStats(dst, labels, stats, centroids, 8, CV_32S);  //n2为去除左边框后的连通域数量

    //连通域标记
	cv::Rect rect;
	for (int i = 1; i < n2 ; i++) 
	{
				rect.x = stats.at<int>(i, 0);
				rect.y = stats.at<int>(i, 1);
			    rect.width = stats.at<int>(i, 2);
			    rect.height = stats.at<int>(i, 3);
				rectangle(dst, rect, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	imshow("区域标记后", dst);
	cout << "回形针个数=" << n2-1 << endl;                     //n为连通域总数
	waitKey(0);
	return 0;
}
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

 Mat gammaTransform(Mat &src,float gamma){
	int height = src.rows;
	int width = src.cols;
	int Lut[256];           //定义数组用于存放归一化后的像素值
	
	for (int i = 0; i < 256; i++) {          //gamma矫正
		float f = (float(i) / 255);
		f = (float)pow(f, gamma);
		Lut[i] = saturate_cast<uchar>(f * 255);
		//cout << Lut[i] << endl;
	}

	cv::Mat dst;
	src.copyTo(dst);                  //深复制
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dst.at<uchar>(i, j) = Lut[dst.at<uchar>(i, j)];       
		}
	}
	return dst;
}

int main() {
	cv::Mat img1 = imread("E://vs_work//imgEnhancement//img1.jpg",0);
	cv::Mat img3 = imread("E://vs_work//imgEnhancement//img2.jpg", 0);   
	cv::Mat dst1_1, dst1_2, dst3;
	float gamma1 = 0.4;
	float gamma2 = 2;
	float gamma3 = 0.49;

	//练习1
	dst1_1=gammaTransform(img1, gamma1);      //gamma<1,增强灰度较低区域
	dst1_2 = gammaTransform(img1, gamma2);     //gamma>1,增强灰度较高区域

	imshow("原图", img1);
	imshow("gamma<1", dst1_1);
	imshow("gamma>1", dst1_2);

	//练习3
    dst3 = gammaTransform(img3, gamma3);    
	imshow("原图", img3);
	imshow("dst", dst3);
	cout << "老师超级帅" << endl;

	waitKey(0);
	return 0;
}
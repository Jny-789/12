#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

 Mat gammaTransform(Mat &src,float gamma){
	int height = src.rows;
	int width = src.cols;
	int Lut[256];           //�����������ڴ�Ź�һ���������ֵ
	
	for (int i = 0; i < 256; i++) {          //gamma����
		float f = (float(i) / 255);
		f = (float)pow(f, gamma);
		Lut[i] = saturate_cast<uchar>(f * 255);
		//cout << Lut[i] << endl;
	}

	cv::Mat dst;
	src.copyTo(dst);                  //���
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

	//��ϰ1
	dst1_1=gammaTransform(img1, gamma1);      //gamma<1,��ǿ�ҶȽϵ�����
	dst1_2 = gammaTransform(img1, gamma2);     //gamma>1,��ǿ�ҶȽϸ�����

	imshow("ԭͼ", img1);
	imshow("gamma<1", dst1_1);
	imshow("gamma>1", dst1_2);

	//��ϰ3
    dst3 = gammaTransform(img3, gamma3);    
	imshow("ԭͼ", img3);
	imshow("dst", dst3);
	cout << "��ʦ����˧" << endl;

	waitKey(0);
	return 0;
}
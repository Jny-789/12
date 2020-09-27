#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

void test_1() {

	cv::Mat srcMat = imread("C:/users/1234/Desktop/pic.png");

	int hight = srcMat.rows;                 //行数
	int width = srcMat.cols;                  //列数

	for (int j = 0; j < hight; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2] / 3;
			srcMat.at<Vec3b>(j, i)[0] = average;
			srcMat.at<Vec3b>(j, i)[1] = average;
			srcMat.at<Vec3b>(j, i)[2] = average;
		}
	}
	imshow("src", srcMat);
	waitKey(0);

}

void test_2() {
	Mat img = imread("C:/users/1234/Desktop/pic.png", 0);

	imshow("img", img);
	waitKey(0);
}

void test_3() {
	Mat img = imread("C:/users/1234/Desktop/pic.png");
	int hight = img.rows;
	int width = img.cols;
	uchar threshold = 100;
	for (int j = 0; j < hight; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = img.at<Vec3b>(j, i)[0] + img.at<Vec3b>(j, i)[1] + img.at<Vec3b>(j, i)[2] / 3;
			if (average > threshold)
				average = 255;
			else
				average = 0;
			img.at<Vec3b>(j, i)[0] = average;
			img.at<Vec3b>(j, i)[1] = average;
			img.at<Vec3b>(j, i)[2] = average;
		}
	}

	imshow("img", img);
	waitKey(0);

}

void test_4() {
	cv::Mat deepMat, shallowMat, srcMat;
	srcMat = imread("C:/users/1234/Desktop/pic.png");
	srcMat.copyTo(deepMat);
	shallowMat = srcMat;
	int hight = srcMat.rows;
	int width = srcMat.cols;
	uchar threshold = 100;
	for (int j = 0; j < hight; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2] / 3;
			if (average > threshold)
				average = 255;
			else
				average = 0;
			srcMat.at<Vec3b>(j, i)[0] = average;
			srcMat.at<Vec3b>(j, i)[1] = average;
			srcMat.at<Vec3b>(j, i)[2] = average;
		}
	}


	imshow("src", srcMat);
	waitKey(0);

}

int main()
{
	test_1();
	//test_2();
	//test_3();
	//test_4();
	return 0;
}

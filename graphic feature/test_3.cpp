//#include<opencv2/opencv.hpp>
//#include<iostream>
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	Mat rsrc, rsrc_gray, img;
//	cv::Mat src = imread("C://Users//1234//Desktop//23.jpg");
//	cv::Mat src_gray = imread("C://Users//1234//Desktop//23.jpg", 0);
//
//	//缩小，原图尺寸太大
//	resize(src, rsrc, Size(src.cols*0.1, src.rows*0.1), INTER_LINEAR);   
//	resize(src_gray, rsrc_gray, Size(src_gray.cols*0.1, src_gray.rows*0.1), INTER_LINEAR);  
//	
//    int h = rsrc.rows;
//	int w = rsrc.cols;
//	//遍历灰度图，降低较亮区域的灰度，区分杯盖与白色的桌面
//	for (int i = 0; i < h; i++)
//	{
//		for (int j = 0; j < w; j++)
//		{
//			if (rsrc_gray.at<uchar>(i, j) > 139 )
//			{
//				rsrc_gray.at <uchar>(i, j) = 50;
//			}
//		}
//	}
//	imshow("灰度图重置", rsrc_gray);
//
//	threshold(rsrc_gray, img, 90, 255, THRESH_BINARY);
//	imshow("二值化", img);
//
//	/********************尝试分离出图片的R通道，但分离后杯盖与桌面颜色相近无法区分***********
//	for (int j = 0; j < h; j++)
//	{
//		for (int i = 0; i < w; i++)
//		{
//			uchar average = (rsrc.at<Vec3b>(j, i)[0] + rsrc.at<Vec3b>(j, i)[1] + rsrc.at<Vec3b>(j, i)[2]) / 3;
//			if (average > 150)                     //遍历像素，将像素值较亮的桌面部分转化成较暗像素，与杯盖区分开
//			{
//				rsrc.at<Vec3b>(j, i)[0] = 30;
//				rsrc.at<Vec3b>(j, i)[1] = 30;
//				rsrc.at<Vec3b>(j, i)[2] = 30;
//			}
//		}
//	}
//	imshow("rsrc", rsrc);
//
//	//分离R通道
//	std::vector<cv::Mat> channels;
//	cv::split(rsrc, channels);
//	cv::Mat R = channels.at(2);
//	imshow("red", R);
//	threshold(R, img, 120, 255, THRESH_BINARY);
//	*************************分离R通道**************************************/
//
//	//连通域
//	vector<vector<Point>> contours;
//	vector<Vec4i>hierarchy;
//	findContours(img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//
//	//获取最小外接四边形
//	for (int i = 0; i < contours.size(); i++)
//	{
//		RotatedRect rbox = minAreaRect(contours[i]);
//		float width = (float)rbox.size.width;
//		float height = (float)rbox.size.height;
//		float ratio = height / width;
//		if (ratio < 2 && width < 130 && width>40) //筛选
//		{
//			cv::Point2f vtx[4];
//			rbox.points(vtx);
//			for (int i = 0; i < 4; ++i)
//			{
//				cv::line(rsrc, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);  //画外接四边形
//			}
//		}
//	}
//	imshow("结果", rsrc);
//	waitKey(0);
//	return 0;
//}
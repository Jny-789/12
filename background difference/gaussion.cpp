#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() {
	VideoCapture cap;
	cap.open(0);

	if (!cap.isOpened()) {
		std::cout << "打开视频失败" << std::endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);

	cv::Mat frame, bgMat, subMat, averMat, varMat;
	
	bool rSucess = cap.read(frame);
	int width = frame.cols;
	int height = frame.rows;
	if (!rSucess) {
		std::cout << "读取帧失败" << std::endl;
		return -1;
	}
	else {
		std::vector<Mat> bgMats;
		int count = 0;
		int sum = 0;
		int var = 0;

		while (1) {
			cap >> frame;
			cvtColor(frame, frame, COLOR_BGR2GRAY);

			if (count == 0) {
				frame.copyTo(bgMat);        //将第一帧作为背景
				frame.copyTo(averMat);        //初始化，否则会报错
				frame.copyTo(varMat);
			}
			else if(count<20){              //将20帧图像存入bgMats中，只计算20帧
				bgMats.push_back(frame);
			}
			count++;
			if(count==20){
				/*********求均值、方差*********/
				for (int i = 0; i < height; i++) {
					for (int j = 0; j < width; j++) {
						for (int n = 0; n < bgMats.size(); n++) {
							sum += bgMats[n].at<uchar>(i, j); 	
						}
						averMat.at<uchar>(i,j) = sum / bgMats.size();      //均值
						for (int n = 0; n < bgMats.size(); n++) {
							var += pow(bgMats[n].at<uchar>(i, j) - averMat.at<uchar>(i, j), 2);
						}
						varMat.at<uchar>(i, j) = sqrt(var / bgMats.size());     //方差
					}
				}	
				/**********求均值、方差***********/

				for (int i = 0; i < height; i++) {
					for (int j = 0; j < width; j++) {					
						if (abs(frame.at<uchar>(i, j) - averMat.at<uchar>(i, j)) > 3 * varMat.at<uchar>(i, j)) {					
							frame.at<uchar>(i, j) = 255;
					    }
					    else frame.at<uchar>(i, j) = 0;
				    }
			    }
				imshow("均值", averMat);
				imshow("方差", varMat);
				imshow("高斯", frame);
			    waitKey(30);
		    }			
		}			
	}
	return 0;
}

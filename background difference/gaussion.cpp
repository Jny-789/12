#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() {
	VideoCapture cap;
	cap.open(0);

	if (!cap.isOpened()) {
		std::cout << "����Ƶʧ��" << std::endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);

	cv::Mat frame, bgMat, subMat, averMat, varMat;
	
	bool rSucess = cap.read(frame);
	int width = frame.cols;
	int height = frame.rows;
	if (!rSucess) {
		std::cout << "��ȡ֡ʧ��" << std::endl;
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
				frame.copyTo(bgMat);        //����һ֡��Ϊ����
				frame.copyTo(averMat);        //��ʼ��������ᱨ��
				frame.copyTo(varMat);
			}
			else if(count<20){              //��20֡ͼ�����bgMats�У�ֻ����20֡
				bgMats.push_back(frame);
			}
			count++;
			if(count==20){
				/*********���ֵ������*********/
				for (int i = 0; i < height; i++) {
					for (int j = 0; j < width; j++) {
						for (int n = 0; n < bgMats.size(); n++) {
							sum += bgMats[n].at<uchar>(i, j); 	
						}
						averMat.at<uchar>(i,j) = sum / bgMats.size();      //��ֵ
						for (int n = 0; n < bgMats.size(); n++) {
							var += pow(bgMats[n].at<uchar>(i, j) - averMat.at<uchar>(i, j), 2);
						}
						varMat.at<uchar>(i, j) = sqrt(var / bgMats.size());     //����
					}
				}	
				/**********���ֵ������***********/

				for (int i = 0; i < height; i++) {
					for (int j = 0; j < width; j++) {					
						if (abs(frame.at<uchar>(i, j) - averMat.at<uchar>(i, j)) > 3 * varMat.at<uchar>(i, j)) {					
							frame.at<uchar>(i, j) = 255;
					    }
					    else frame.at<uchar>(i, j) = 0;
				    }
			    }
				imshow("��ֵ", averMat);
				imshow("����", varMat);
				imshow("��˹", frame);
			    waitKey(30);
		    }			
		}			
	}
	return 0;
}

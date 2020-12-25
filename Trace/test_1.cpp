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
	int count = 0;
	cv::Mat frame, tempMat, refMat, resultMat;

	while (1) {
		cap >> frame;
		if (count == 0) {
		    Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
		}
		
		int match_method = 0;
		matchTemplate(frame, refMat, resultMat, match_method);
		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());  //归一化
		
		double minVal, maxVal;
		Point minLoc, maxLoc, matchLoc;
		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		if (match_method == TM_SQDIFF||match_method==TM_SQDIFF_NORMED) {
			matchLoc = minLoc;
		}
		else {
			matchLoc = maxLoc;
		}
		Point resultLoc;
		resultLoc.x = matchLoc.x + refMat.cols;
		resultLoc.y = matchLoc.y + refMat.rows;
		rectangle(frame, matchLoc, resultLoc, CV_RGB(0, 255, 255), 1, 8, 0);
		
		count++;
		imshow("frame", frame);

		waitKey(30);
	}
	return 0;
}
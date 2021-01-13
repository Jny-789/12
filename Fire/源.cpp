#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void FireMark(Mat &frame, Mat &grayMat, Mat &hsvMat) {

	//����HSV��ͨ��
	std::vector<cv::Mat> hsv_channels;
	cv::split(hsvMat, hsv_channels);
	cv::Mat H = hsv_channels.at(0);
	cv::Mat S = hsv_channels.at(1);
	cv::Mat V = hsv_channels.at(2);
	Mat bnyMat;
	threshold(S, bnyMat, 120, 255, THRESH_BINARY);
	
	int height = frame.rows;
	int width = frame.cols;
	//���ϰ벿�֡��ײ��Ҷ���0���ų�����
	for (int i = 0; i < height*0.8; i++) {
		for (int j = 0; j < width; j++) {
			bnyMat.at<uchar>(i, j) = 0;
		}
	}
	for (int i = 250; i < height; i++) {
		for (int j = 0; j < width; j++) {
			bnyMat.at<uchar>(i, j) = 0;
		}
	}

	//��ʴȥ����
	Mat element_1 = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	erode(bnyMat, bnyMat, element_1);

	double kx = 0.8;
	double ky = 0.85;
	//����Ƶ�����½�ɸѡ��������
	for (int j = width * kx; j < width; j++) {
		for (int i = height * ky; i < height; i++) {
			if (grayMat.at<uchar>(i, j) >= 150 && S.at<uchar>(i, j) >= 120) {
				bnyMat.at<uchar>(i, j) = 255;
			}
		}
	}

	//�������㣬ʹ�����뵹Ӱ�ϳ�һ��
	Mat element_2 = getStructuringElement(MORPH_RECT, Size(13, 13), Point(-1, -1));
	dilate(bnyMat, bnyMat, element_2);
	
	//��ǻ���
	Mat labels, stats, centroids;
	int n = connectedComponentsWithStats(bnyMat, labels, stats, centroids, 8, CV_32S);

	cv::Rect rect;
	for (int i = 1; i < n; i++) {
		rect.x = stats.at<int>(i, 0);
		rect.y = stats.at<int>(i, 1);
		rect.width = stats.at<int>(i, 2);
		rect.height = stats.at<int>(i, 3);
		rectangle(frame, rect, CV_RGB(255, 0, 0), 3, 8, 0);
	}

}

//������Ϻ���
void curveFit(std::vector<cv::Point>& key_point,int n, Mat&A) {
	//ˮ���ϵ������
	int N = key_point.size();
	//�������X
	cv::Mat X = cv::Mat::zeros(n + 1, n + 1, CV_64FC1);
	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n + 1; j++){
			for (int k = 0; k < N; k++){
				X.at<double>(i, j) = X.at<double>(i, j) + std::pow(key_point[k].x, i + j);
			}
		}
	}
	//�������Y
	cv::Mat Y = cv::Mat::zeros(n + 1, 1, CV_64FC1);
	for (int i = 0; i < n + 1; i++){
		for (int k = 0; k < N; k++){
			Y.at<double>(i, 0) = Y.at<double>(i, 0) + std::pow(key_point[k].x, i) * key_point[k].y;
		}
	}
	A = cv::Mat::zeros(n + 1, 1, CV_64FC1);
	//������A
	cv::solve(X, Y, A, cv::DECOMP_LU);
}

int main() {
	VideoCapture cap("E://vs_work//Fire//����3.mp4");
	if (!cap.isOpened()) {
		cout << "����Ƶʧ��" << endl;
		return -1;
	}

	Mat frame, grayMat, hsvMat, bnyMat;
	Mat bgMat, subMat, bny_subMat;
	Mat A;

	int count = 0;
	while (1) {
		cap >> frame;
		cvtColor(frame, grayMat, CV_BGR2GRAY);   //�ҶȻ�
		cvtColor(frame, hsvMat, COLOR_BGR2HSV);  //ת��HSVģʽ

		if (count == 0) {
			grayMat.copyTo(bgMat);    //����һ֡��Ϊ����
		}
		//80֮֡ǰˮǹδ����ˮ����ֻ��ǻ���
		else if (count < 80) {
			FireMark(frame, grayMat, hsvMat);
			imshow("frame", frame);
			waitKey(10);
		}
		if (count == 80) {
			grayMat.copyTo(bgMat);   //ˮǹ��ʼ��ˮ�����±���ͼ��
		}
		else if (count > 80) {
			absdiff(grayMat, bgMat, subMat);
			threshold(subMat, bny_subMat, 120, 255, CV_THRESH_BINARY);

			//��ˮ���Ϸ������Ҷ���0���ų���������
			for (int i = 0; i < bny_subMat.rows; i++) {
				for (int j = 0; j < 175; j++) {
					bny_subMat.at<uchar>(i, j) = 0;
				}
			}
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 480; j++) {
					bny_subMat.at<uchar>(i, j) = 0;
				}
			}
			for (int i = 125; i < 265; i++) {
				for (int j = 175; j < 270; j++) {
					bny_subMat.at<uchar>(i, j) = 0;
				}
			}
			Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
			morphologyEx(bny_subMat, bny_subMat, MORPH_CLOSE, element, Point(-1, -1), 3);

			//��ȡˮ���ϵĵ�
			vector<Point>points;
			for (int i = 35; i < 240; i++) {      //ˮ����ʼ���꣨175,35�����������꣨428,245��
				for (int j = 175; j < 420; j++) {
					if (bny_subMat.at<uchar>(i, j) == 255) {
						points.push_back(cv::Point(j, i));
						break;
					}
				}
			}

			FireMark(frame, grayMat, hsvMat);
			curveFit(points, 3, A);
			std::cout << "A = " << A << std::endl;

			//��������
			std::vector<cv::Point>points_fitted;
			for (int x = 170; x < 432; x++){
				double y = A.at<double>(0, 0) + A.at<double>(1, 0) * x +
					A.at<double>(2, 0)*std::pow(x, 2) + A.at<double>(3, 0)*std::pow(x, 3);
				points_fitted.push_back(cv::Point(x, y));
			}
			
			polylines(frame, points_fitted, false, cv::Scalar(0, 255, 255), 2, 8, 0);
			imshow("frame", frame);
			waitKey(20);
		}
		//��ʾ���ս��
		if (count == 150) {
			imshow("result", frame);
			waitKey(0);
		}
		count++;
		
	}
	return 0;
}

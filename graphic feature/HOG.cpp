#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

float calcHOG(Mat src, float *hist) 
{
	int blocksize = 16;
	int nAngle = 8;
	int nX = src.cols / blocksize;
	int nY = src.rows / blocksize;

	//�����ݶȼ��Ƕ�
	Mat gx, gy;
	Mat mag, angle;
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);  //�����ֵ���Ƕ�

	Rect roi;
	roi.x = 0;
	roi.y = 0;
	roi.width = blocksize;
	roi.height = blocksize;

	for (int i = 0; i < nY; i++){
		for (int j = 0; j < nX; j++){
			cv::Mat roiMat, roiMag, roiAgl;
			roi.x = j * blocksize;
			roi.y = i * blocksize;
			//��ԭͼһ��һ�鸴�Ƹ�Mat
			roiMat = src(roi);
			roiMag = mag(roi);
			roiAgl = angle(roi);

			int head = (i*nX + j)*nAngle;  //��ǰcell��ֱ��ͼ�ж�Ӧ��λ��
			int binAngle = 360 / nAngle;

			for (int n = 0; n < roiMat.rows; n++) {
				for (int m = 0; m < roiMat.cols; m++) {
					//����Ƕ����ĸ�bin��ͨ��int�Զ�ȡ��ʵ��
					int pos = (int)(roiAgl.at<float>(n, m) / binAngle);
					//�����ص��ֵΪȨ��
					hist[head + pos] += roiMag.at<float>(n, m);
				}
			}
		}
	}
	return 0;
}
float normL2(float *x1, float *x2, int n) {
	float dis = 0;
	for (int i = 0; i < n; i++){
		dis = dis + (x1[i] - x2[i])*(x1[i] - x2[i]);   //ŷ����þ���
	}
	dis = sqrt(dis);

	return dis;
}

int main() {
	cv::Mat refMat = imread("C://Users//1234//Desktop//hogTemplate.jpg",0);
	cv::Mat plMat = imread("C://Users//1234//Desktop//img1.jpg",0);
	cv::Mat bgMat = imread("C://Users//1234//Desktop//img2.jpg",0);
    
	//��ͼƬ�ֳ�16*16��cell
	int nAngle = 8;
	int blocksize = 16;
	int nX = refMat.cols / blocksize;
	int nY = refMat.rows / blocksize;
	
	int bins = nX * nY*nAngle;
    //�����ڴ�
	float *ref_hist = new float[bins];
	memset(ref_hist, 0, sizeof(float)*bins);
	float *pl_hist = new float[bins];
	memset(pl_hist, 0, sizeof(float)*bins);
	float *bg_hist = new float[bins];
	memset(bg_hist, 0, sizeof(float)*bins);

	int reCode = 0;
	reCode = calcHOG(refMat, ref_hist);
	reCode = calcHOG(plMat, pl_hist);
	reCode = calcHOG(bgMat, bg_hist);

	if (reCode != 0) {
		cout << "��������ʧ��" << endl;
		delete[] ref_hist;      //�ͷ��ڴ�
		delete[] pl_hist;
		delete[] bg_hist;
		return -1;
	}

	//����ֱ��ͼ����
	float dis_1 = normL2(ref_hist, pl_hist, bins);
	float dis_2 = normL2(ref_hist, bg_hist, bins);
	cout << "dis_1=" << dis_1 << endl;
	cout << "dis_2=" << dis_2 << endl;

	if (dis_1 < dis_2) {
		cout << "img1��ԭͼ������" << endl;
		imshow("plMat", plMat);
	}
	else{
		cout << "img2��ԭͼ������" << endl;
		imshow("bgMat", bgMat);
	}

	delete[] ref_hist;      //�ͷ��ڴ�
	delete[] pl_hist;
	delete[] bg_hist;

	waitKey(0);
	return 0;
}
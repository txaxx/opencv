#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;

int main() {
	
		//����һ��ͼƬ
		cv::Mat mat1= cv::imread("lena.jpg");
		cv::Mat mat2 = cv::imread("logo.jpg");
		//����ROIλ��
		cv::Rect roi(0, 0, mat2.cols, mat2.rows);
		cv::Mat mat1_roi = mat1(roi);
		//����logo��ROI����ROI����������������޸�ԭͼ�Ļ����ϲ�����
		mat2.copyTo(mat1_roi);

		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //ѡ��jpeg
		compression_params.push_back(100); //�����������Ҫ��ͼƬ����
		cv::imwrite("homework.jpg", mat1, compression_params);

		//��ʾԭͼ��ROI�Ĳ��ֱ��޸���
		cv::imshow("mat1", mat1);
		cv::waitKey(0);

		return 0;
}
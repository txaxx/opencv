#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;

int main() {
	
		//输入一张图片
		cv::Mat mat1= cv::imread("lena.jpg");
		cv::Mat mat2 = cv::imread("logo.jpg");
		//设置ROI位置
		cv::Rect roi(0, 0, mat2.cols, mat2.rows);
		cv::Mat mat1_roi = mat1(roi);
		//复制logo到ROI，对ROI的任意操作都是在修改原图的基础上操作的
		mat2.copyTo(mat1_roi);

		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //选择jpeg
		compression_params.push_back(100); //在这个填入你要的图片质量
		cv::imwrite("homework.jpg", mat1, compression_params);

		//显示原图，ROI的部分被修改了
		cv::imshow("mat1", mat1);
		cv::waitKey(0);

		return 0;
}
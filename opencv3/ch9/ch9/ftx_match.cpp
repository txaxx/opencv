///形状匹配---比较两个形状或轮廓间的相似度
#include "opencv2/opencv.hpp"
using namespace cv;
#include <iostream>
using namespace std;
int main()
{
	//1.查找模版图像的轮廓
	Mat templateImg = imread("er2.png", CV_LOAD_IMAGE_COLOR);
	Mat copyImg1 = templateImg.clone();
	cvtColor(templateImg, templateImg, CV_BGR2GRAY);

	Canny(templateImg, templateImg, 135, 255, 3, false);
	imshow("canny detection1", templateImg);

	vector<vector<Point>> contours1;
	findContours(templateImg, contours1, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//最外层轮廓
	drawContours(copyImg1, contours1, -1, Scalar(0, 255, 0), 2, 8);
	//2.查找待测试图像的轮廓
	Mat testImg = imread("er4.jpg", CV_LOAD_IMAGE_COLOR);
	Mat copyImg2 = testImg.clone();
	cvtColor(testImg, testImg, CV_BGR2GRAY);

	Canny(testImg, testImg, 170, 255, 3, false);
	imshow("canny detection2", testImg);
	
	vector<vector<Point>> contours2;
	findContours(testImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//最外层轮廓
	//3.形状匹配---比较两个形状或轮廓间的相似度
	for (int i = 0; i < contours2.size(); i++)//遍历待测试图像的轮廓
	{
		//返回此轮廓与模版轮廓之间的相似度,a0越小越相似
		double a0 = matchShapes(contours1[0], contours2[i], CV_CONTOURS_MATCH_I1, 0);
		cout << "模版轮廓与待测试图像轮廓" << i << "的相似度:" << a0 << endl;//输出两个轮廓间的相似度
		if (a0 < 0.1)//如果此轮廓与模版轮廓的相似度小于0.1
		{
			drawContours(copyImg2, contours2, i, Scalar(0, 255, 0), 2, 8);//则在待测试图像上画出此轮廓
		}
		imshow("copyImg2", copyImg2);
		if (waitKey(0) == 27)//等待按键进行下一个轮廓，ESC则退出
		{
			cout << "ESC退出" << endl;
			break;
		}
	}
	waitKey(0);
	return 0;
}
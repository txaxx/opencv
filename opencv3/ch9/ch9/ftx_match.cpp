///��״ƥ��---�Ƚ�������״������������ƶ�
#include "opencv2/opencv.hpp"
using namespace cv;
#include <iostream>
using namespace std;
int main()
{
	//1.����ģ��ͼ�������
	Mat templateImg = imread("er2.png", CV_LOAD_IMAGE_COLOR);
	Mat copyImg1 = templateImg.clone();
	cvtColor(templateImg, templateImg, CV_BGR2GRAY);

	Canny(templateImg, templateImg, 135, 255, 3, false);
	imshow("canny detection1", templateImg);

	vector<vector<Point>> contours1;
	findContours(templateImg, contours1, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//���������
	drawContours(copyImg1, contours1, -1, Scalar(0, 255, 0), 2, 8);
	//2.���Ҵ�����ͼ�������
	Mat testImg = imread("er4.jpg", CV_LOAD_IMAGE_COLOR);
	Mat copyImg2 = testImg.clone();
	cvtColor(testImg, testImg, CV_BGR2GRAY);

	Canny(testImg, testImg, 170, 255, 3, false);
	imshow("canny detection2", testImg);
	
	vector<vector<Point>> contours2;
	findContours(testImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//���������
	//3.��״ƥ��---�Ƚ�������״������������ƶ�
	for (int i = 0; i < contours2.size(); i++)//����������ͼ�������
	{
		//���ش�������ģ������֮������ƶ�,a0ԽСԽ����
		double a0 = matchShapes(contours1[0], contours2[i], CV_CONTOURS_MATCH_I1, 0);
		cout << "ģ�������������ͼ������" << i << "�����ƶ�:" << a0 << endl;//�����������������ƶ�
		if (a0 < 0.1)//�����������ģ�����������ƶ�С��0.1
		{
			drawContours(copyImg2, contours2, i, Scalar(0, 255, 0), 2, 8);//���ڴ�����ͼ���ϻ���������
		}
		imshow("copyImg2", copyImg2);
		if (waitKey(0) == 27)//�ȴ�����������һ��������ESC���˳�
		{
			cout << "ESC�˳�" << endl;
			break;
		}
	}
	waitKey(0);
	return 0;
}
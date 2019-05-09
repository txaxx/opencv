#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

//-----------------------------------���궨�岿�֡�-------------------------------------------- 
//  ����������һЩ������ 
//----------------------------------------------------------------------------------------------
#define WINDOW_NAME "��Shi-Tomasi�ǵ��⡿"        //Ϊ���ڱ��ⶨ��ĺ� 



//-----------------------------------��ȫ�ֱ����������֡�--------------------------------------
//          ������ȫ�ֱ�������
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
RNG g_rng(12345);//��ʼ�������������


//-----------------------------��on_GoodFeaturesToTrack( )������----------------------------
//          ��������Ӧ�������ƶ���Ϣ�Ļص�����
//----------------------------------------------------------------------------------------------
void on_GoodFeaturesToTrack(int, void*)
{
	//��1���Ա���С�ڵ���1ʱ�Ĵ���
	if (g_maxCornerNumber <= 1) { g_maxCornerNumber = 1; }

	//��2��Shi-Tomasi�㷨��goodFeaturesToTrack�������Ĳ���׼��
	vector<Point2f> corners;
	double qualityLevel = 0.01;//�ǵ���ɽ��ܵ���С����ֵ
	double minDistance = 10;//�ǵ�֮�����С����
	int blockSize = 3;//���㵼������ؾ���ʱָ��������Χ
	double k = 0.04;//Ȩ��ϵ��
	Mat copy = g_srcImage.clone();	//����Դͼ��һ����ʱ�����У���Ϊ����Ȥ����

	//��3������Shi-Tomasi�ǵ���
	goodFeaturesToTrack(g_grayImage,//����ͼ��
		corners,//��⵽�Ľǵ���������
		g_maxCornerNumber,//�ǵ���������
		qualityLevel,//�ǵ���ɽ��ܵ���С����ֵ
		minDistance,//�ǵ�֮�����С����
		Mat(),//����Ȥ����
		blockSize,//���㵼������ؾ���ʱָ��������Χ
		false,//��ʹ��Harris�ǵ���
		k);//Ȩ��ϵ��


	//��4�����������Ϣ
	cout << "\t>�˴μ�⵽�Ľǵ�����Ϊ��" << corners.size() << endl;

	//��5�����Ƽ�⵽�Ľǵ�
	int r = 4;
	for (int i = 0; i < corners.size(); i++)
	{
		//���������ɫ���Ƴ��ǵ�
		circle(copy, corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255),
			g_rng.uniform(0, 255)), -1, 8, 0);
	}

	//��6����ʾ�����£�����
	imshow(WINDOW_NAME, copy);
}


//-----------------------------------��ShowHelpText( )������----------------------------------
//          ���������һЩ������Ϣ
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//�����ӭ��Ϣ��OpenCV�汾
	printf("\n\n\t\t\t�ǳ���л����OpenCV3������š�һ�飡\n");
	printf("\n\n\t\t\t��Ϊ����OpenCV3��ĵ�87������ʾ������\n");
	printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//���һЩ������Ϣ
	printf("\n\n\n\t��ӭ������Shi-Tomasi�ǵ��⡿ʾ������\n");
	printf("\n\t������������۲�ͼ��Ч��\n\n");

}


//--------------------------------------��main( )������-----------------------------------------
//          ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼִ��
//-----------------------------------------------------------------------------------------------
int main()
{
	//��0���ı�console������ɫ
	system("color 2F");

	//��0����ʾ��������
	ShowHelpText();

	//��1������Դͼ�񲢽���ת��Ϊ�Ҷ�ͼ
	g_srcImage = imread("8.jpg", 1);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

	//��2���������ںͻ���������������ʾ�ͻص�������ʼ��
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar("���ǵ���", WINDOW_NAME, &g_maxCornerNumber, g_maxTrackbarNumber, on_GoodFeaturesToTrack);
	imshow(WINDOW_NAME, g_srcImage);
	on_GoodFeaturesToTrack(0, 0);

	waitKey(0);
	return(0);
}
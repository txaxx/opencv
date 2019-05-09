#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  
using namespace std;
using namespace cv;



//-----------------------------------��ȫ�ֺ����������֡�-----------------------------------
//		������ȫ�ֺ������� UseIteratorAccessPixel
//-----------------------------------------------------------------------------------------------
void colorReduce(Mat& inputImage, Mat& outputImage, int div);
void ShowHelpText();



//--------------------------------------��main( )������--------------------------------------
//		����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼִ��
//-----------------------------------------------------------------------------------------------
int main()
{
	//��1������ԭʼͼ����ʾ
	Mat srcImage = imread("1.jpg");
	imshow("ԭʼͼ��", srcImage);

	//��2����ԭʼͼ�Ĳ����������������Ч��ͼ
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());//Ч��ͼ�Ĵ�С��������ԭͼƬ��ͬ 

	ShowHelpText();

	//��3����¼��ʼʱ��
	double time0 = static_cast<double>(getTickCount());

	//��4��������ɫ�ռ���������
	colorReduce(srcImage, dstImage, 32);

	//��5����������ʱ�䲢���
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "�˷�������ʱ��Ϊ�� " << time0 << "��" << endl;  //�������ʱ��

	//��6����ʾЧ��ͼ
	imshow("Ч��ͼ", dstImage);
	waitKey(0);
}




//-------------------------------------��colorReduce( )������-----------------------------
//		������ʹ�á������������������ɫ�ռ���������
//----------------------------------------------------------------------------------------------
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	//����׼��
	outputImage = inputImage.clone();  //����ʵ�ε���ʱ����
	//��ȡ������
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();  //��ʼλ�õĵ�����
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();  //��ֹλ�õĵ�����

	//��ȡ��ɫͼ������
	for (; it != itend; ++it)
	{
		// ------------------------����ʼ����ÿ�����ء�--------------------
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
		// ------------------------������������----------------------------
	}
}



//-----------------------------------��ShowHelpText( )������----------------------------------
//          ���������һЩ������Ϣ
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//�����ӭ��Ϣ��OpenCV�汾
	printf("\n\n\t\t\t�ǳ���л����OpenCV3������š�һ�飡\n");
	printf("\n\n\t\t\t��Ϊ����OpenCV3��ĵ�22������ʾ������\n");
	printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");
}
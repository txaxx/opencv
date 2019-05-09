#include "opencv2/core/core.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 
using namespace cv;

//-----------------------------------��main( )������--------------------------------------------
//	����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ
//-----------------------------------------------------------------------------------------------
int main()
{
	// ����ԭͼ
	Mat image = imread("1.jpg");


	//��ʾԭͼ
	imshow("�����˲���ԭͼ��", image);

	//���з����˲�����
	Mat out1, out2, out3;
	boxFilter(image, out1, -1, Size(5, 5));
	//��ֵ�˲�
	blur(image, out2, Size(5, 5));
	//��˹�˲�
	GaussianBlur(image, out3, Size(5, 5), 0, 0);
	//��ʾЧ��ͼ
	imshow("�����˲���Ч��ͼ��", out1);
	imshow("��ֵ�˲���Ч��ͼ��", out2);
	imshow("��˹�˲���Ч��ͼ��", out3);
	waitKey(0);
}
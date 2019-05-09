#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;


//-----------------------------------��ȫ�ֱ����������֡�--------------------------------------
//		������ȫ�ֱ�������
//-----------------------------------------------------------------------------------------------
//ԭͼ��ԭͼ�ĻҶȰ棬Ŀ��ͼ
Mat g_srcImage, g_srcGrayImage, g_dstImage,dst;

//Canny��Ե�����ر���
Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1;//TrackBarλ�ò���  

//Sobel��Ե�����ر���
Mat g_sobelGradient_X, g_sobelGradient_Y;
Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
int g_sobelKernelSize = 1;//TrackBarλ�ò���  
int g_laplacianDepth = 1;

//Scharr�˲�����ر���
Mat g_scharrGradient_X, g_scharrGradient_Y;
Mat g_scharrAbsGradient_X, g_scharrAbsGradient_Y;


//-----------------------------------��ȫ�ֺ����������֡�--------------------------------------
//		������ȫ�ֺ�������
//-----------------------------------------------------------------------------------------------
static void ShowHelpText();
static void on_Canny(int, void*);//Canny��Ե��ⴰ�ڹ������Ļص�����
static void on_Sobel(int, void*);//Sobel��Ե��ⴰ�ڹ������Ļص�����
static void on_Laplacian(int, void*);//Laplacian��Ե��ⴰ�ڹ������Ļص�����
void Scharr();//��װ��Scharr��Ե�����ش���ĺ���


//-----------------------------------��main( )������--------------------------------------------
//		����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ
//-----------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//�ı�console������ɫ
	system("color 2F");

	//��ʾ��ӭ��
	ShowHelpText();

	//����ԭͼ
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) { printf("Oh��no����ȡsrcImage����~�� \n"); return false; }

	//��ʾԭʼͼ
	namedWindow("��ԭʼͼ��");
	imshow("��ԭʼͼ��", g_srcImage);

	// ������srcͬ���ͺʹ�С�ľ���(dst)
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());

	// ��ԭͼ��ת��Ϊ�Ҷ�ͼ��
	/*cvtColor(g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY);
	printf("%d ", g_srcImage.depth());
	Laplacian(g_srcImage, g_dstImage, 9);
	imshow("��Ч��ͼ��Laplacian��Ե���", g_dstImage);
	waitKey(0);*/
	// ������ʾ����
	namedWindow("��Ч��ͼ��Canny��Ե���", WINDOW_AUTOSIZE);
	namedWindow("��Ч��ͼ��Sobel��Ե���", WINDOW_AUTOSIZE);
	namedWindow("��Ч��ͼ��Laplacian��Ե���", WINDOW_AUTOSIZE);

	// ����trackbar
	createTrackbar("����ֵ��", "��Ч��ͼ��Canny��Ե���", &g_cannyLowThreshold, 120, on_Canny);
	createTrackbar("����ֵ��", "��Ч��ͼ��Sobel��Ե���", &g_sobelKernelSize, 3, on_Sobel);
	createTrackbar("����ֵ��", "��Ч��ͼ��Laplacian��Ե���", &g_laplacianDepth, 5, on_Laplacian);

	// ���ûص�����
	on_Canny(g_cannyLowThreshold, 0);
	on_Sobel(g_sobelKernelSize, 0);
	on_Laplacian(g_laplacianDepth, 0);
	//���÷�װ��Scharr��Ե������ĺ���
	Scharr();

	//��ѯ��ȡ������Ϣ��������Q�������˳�
	while ((char(waitKey(1)) != 'q')) {}

	return 0;
}


//-----------------------------------��ShowHelpText( )������----------------------------------
//		���������һЩ������Ϣ
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//�����ӭ��Ϣ��OpenCV�汾
	printf("\n\n\t\t\t�ǳ���л����OpenCV3������š�һ�飡\n");
	printf("\n\n\t\t\t��Ϊ����OpenCV3��ĵ�60������ʾ������\n");
	printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//���һЩ������Ϣ
	printf("\n\n\t���гɹ���������������۲�ͼ��Ч��~\n\n"
		"\t���¡�q����ʱ�������˳���\n");
}


//-----------------------------------��on_Canny( )������----------------------------------
//		������Canny��Ե��ⴰ�ڹ������Ļص�����
//-----------------------------------------------------------------------------------------------
void on_Canny(int, void*)
{
	// ��ʹ�� 3x3�ں�������
	blur(g_srcGrayImage, g_cannyDetectedEdges, Size(3, 3));

	// �������ǵ�Canny����
	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);

	//�Ƚ�g_dstImage�ڵ�����Ԫ������Ϊ0 
	g_dstImage = Scalar::all(0);

	//ʹ��Canny��������ı�Եͼg_cannyDetectedEdges��Ϊ���룬����ԭͼg_srcImage����Ŀ��ͼg_dstImage��
	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);

	//��ʾЧ��ͼ
	imshow("��Ч��ͼ��Canny��Ե���", g_dstImage);
}



//-----------------------------------��on_Sobel( )������----------------------------------
//		������Sobel��Ե��ⴰ�ڹ������Ļص�����
//-----------------------------------------------------------------------------------------
void on_Sobel(int, void*)
{
	// �� X�����ݶ�
	Sobel(g_srcImage, g_sobelGradient_X, CV_16S, 1, 0, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_X, g_sobelAbsGradient_X);//�������ֵ���������ת����8λ

	// ��Y�����ݶ�
	Sobel(g_srcImage, g_sobelGradient_Y, CV_16S, 0, 1, (2 * g_sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_sobelGradient_Y, g_sobelAbsGradient_Y);//�������ֵ���������ת����8λ

	// �ϲ��ݶ�
	addWeighted(g_sobelAbsGradient_X, 0.5, g_sobelAbsGradient_Y, 0.5, 0, g_dstImage);

	//��ʾЧ��ͼ
	imshow("��Ч��ͼ��Sobel��Ե���", g_dstImage);

}

void on_Laplacian(int, void*) {
	int depth=0;
	switch (g_laplacianDepth)
	{
	case 0:depth = 0; break;
	case 1:depth = 2; break;
	case 2:depth = 3; break;
	case 3:depth = 5; break;
	case 4:depth = 6; break;
	case 5:depth = 8; break;
	default:
		break;
	}
	//��3��ʹ�ø�˹�˲���������
	//GaussianBlur(g_srcImage, g_srcImage, Size(3, 3), 0, 0, BORDER_DEFAULT);

	Laplacian(g_srcImage, g_dstImage, depth, 3);
	//��6���������ֵ���������ת����8λ
	//convertScaleAbs(g_dstImage, dst);
	imshow("��Ч��ͼ��Laplacian��Ե���", g_dstImage);

}
//-----------------------------------��Scharr( )������----------------------------------
//		��������װ��Scharr��Ե�����ش���ĺ���
//-----------------------------------------------------------------------------------------
void Scharr()
{
	// �� X�����ݶ�
	Scharr(g_srcImage, g_scharrGradient_X, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_X, g_scharrAbsGradient_X);//�������ֵ���������ת����8λ

	// ��Y�����ݶ�
	Scharr(g_srcImage, g_scharrGradient_Y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(g_scharrGradient_Y, g_scharrAbsGradient_Y);//�������ֵ���������ת����8λ

	// �ϲ��ݶ�
	addWeighted(g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage);

	//��ʾЧ��ͼ
	imshow("��Ч��ͼ��Scharr�˲���", g_dstImage);
}

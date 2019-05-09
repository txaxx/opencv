#include<opencv2/opencv.hpp>
using namespace cv;

int main() {
	Mat img = imread("lena.jpg");
	Mat dst_erode, dst_blur,gray,dst_canny;
	//��ʴ
	erode(img, dst_erode, Mat(), Point(-1, -1), 2);
	
	//�˲�
	blur(img, dst_blur, Size(5, 5), Point(-1, -1), BORDER_DEFAULT);
	
	//�Ҷ�
	cvtColor(img, gray, COLOR_BGR2GRAY);
	//�˲�
	blur(gray, gray, Size(3, 3));
	//��Ե���
	Canny(gray, dst_canny, 30, 120, 3);
	imshow("ԭͼ",img);
	imshow("��ʴ���ͼ", dst_erode);
	imshow("�˲����ͼ", dst_blur);
	imshow("�Ҷ�ͼ", gray);
	imshow("��Ե���ͼ", dst_canny);
	waitKey(0);
	return 0;
}
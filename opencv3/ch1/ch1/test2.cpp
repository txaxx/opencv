#include<opencv2/opencv.hpp>
using namespace cv;

int main() {
	//VideoCapture cap;
	//cap.open("bike.avi");
	
	Mat frame;
	VideoCapture cap(0);
	while (1)
	{
		cap >> frame;

		Mat dst_blur, gray, dst_canny;
		
		//�Ҷ�
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		//��Ե���
		Canny(gray, dst_canny, 30, 120, 3);
		imshow("ԭͼ", frame);
		imshow("�Ҷ�ͼ", gray);
		imshow("��Ե���ͼ", dst_canny);

		waitKey(30);
	}
	return 0;
}
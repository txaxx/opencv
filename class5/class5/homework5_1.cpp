#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

int main() {
	Mat image = imread("algori_hw.jpg");
	resize(image, image, Size(image.cols/2, image.rows/2));
	Mat gray;
	cvtColor(image, gray, CV_RGB2GRAY);
	erode(gray, gray, cv::Mat(), cv::Point(-1, -1), 1);
	//blur(gray, gray, Size(2,2),Point(-1,-1),BORDER_DEFAULT);
	vector<Vec3f> circles;
	HoughCircles(gray, circles, HOUGH_GRADIENT, 1, 10,
		100, 60, 1, 80);

	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		circle(image, Point(c[0], c[1]), c[2], Scalar(0, 0, 255), 3, LINE_AA);
		circle(image, Point(c[0], c[1]), 2, Scalar(0, 255, 0), 3, LINE_AA);
	}

	//����ͼƬ
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	//�����������Ҫ��ͼƬ�������ϸߵ�ֵ��ζ�Ÿ�С�ĳߴ�͸�����ѹ��ʱ��
	compression_params.push_back(100);
	cv::imwrite("homework5_1.jpg", image, compression_params);


	imshow("show", image);
	waitKey(0);

	return 0;
}
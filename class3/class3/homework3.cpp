#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;

int main() {

	//--1.����ͼƬ
	cv::Mat image = cv::imread("horse_hw.jpg");

	//--2.ת���Ҷ�ͼ
	cv::Mat gray;
	cv::cvtColor(image, gray, CV_RGB2GRAY);
	cv::imshow("gray", gray);

	//--3.��ֵ���Ҷ�ͼ
	cv::Mat dst;
	cv::threshold(gray, dst, 15, 255, cv::THRESH_BINARY_INV);
	//ƽ������(ƽ��/��˹ƽ������)
	//cv::blur(dst,dst,cv::Size(3,3));
	cv::GaussianBlur(dst,dst,cv::Size(3,3),0,0); //��˹ƽ��

	//��̬ѧ�������˴�Ч�����ã�ֻ����չʾ��ǿ��⣩
	cv::erode(dst,dst,cv::Mat(),cv::Point(-1,-1),1);
	cv::dilate(dst,dst,cv::Mat(),cv::Point(-1,-1),1);

	//�����ο�
	cv::Mat image_roi=image(cv::Rect(0, 0, image.cols / 3, image.rows / 4));
	image_roi = { cv::Scalar(255,255,255) };//��ROI�е�����ֵ��Ϊ��ɫ
	//��ͼƬ��д����
	cv::putText(image_roi, "hello tx!", cv::Point(20, 60), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 23, 0), 4, 8);
	//��rectangle�����ο�
	cv::rectangle(dst, cv::Point(image.cols / 3, image.rows / 4),
		cv::Point(image.cols / 2, image.rows / 2), 
		cv::Scalar(255, 255, 255), -1,8, 0);
	//--4.��ʾ���(ԭͼ�ͽ��ͼ��ʾ��һ��)
	const int width = image.cols;
	const int height = image.rows;
	cv::Mat show_image(cv::Size(width,2 *  height), CV_8UC3);
	//��image��������ʾͼƬָ��λ��
	image.copyTo(show_image(cv::Rect(0, 0, width, height)));
	//��dstת��Ϊ3ͨ����ʹ��show_image��dstͨ����һ�£�����ʹ��convertTo()����������
	cv::cvtColor(dst, dst, CV_GRAY2RGB);
	//��dst����imageָ��λ��
	dst.copyTo(show_image(cv::Rect(0, height, width, height)));

	//����ͼƬ
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //ѡ��jpeg
	compression_params.push_back(9); //�����������Ҫ��ͼƬ����
	cv::imwrite("homework3.jpg", show_image, compression_params);

	//��ʾ
	cv::imshow("show", show_image);
	cv::waitKey(0);
}

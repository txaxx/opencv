#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int main() {

	//����ͼƬ
	cv::Mat image = cv::imread("raccoon_hw.jpg");

	cv::Mat gray;
	//ת��Ϊ�Ҷ�ͼ
	cv::cvtColor(image, gray, CV_RGB2GRAY);
	cv::threshold(gray, gray, 180, 255, cv::THRESH_BINARY_INV);
	
	cv::erode(gray, gray, cv::Mat(), cv::Point(-1, -1), 1);//��ʴ
	cv::dilate(gray, gray, cv::Mat(), cv::Point(-1, -1), 1);//����

	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(gray, contours, CV_RETR_EXTERNAL/*��ȡ������*/,
		CV_CHAIN_APPROX_NONE/*��ȡÿ��������ÿ������*/, cv::Point());
	
	std::vector<std::vector<cv::Point> >::const_iterator it = contours.begin();
	while (it != contours.end()) {
		if (it->size() < 1000)
			it = contours.erase(it);
		else
			++it;
	}
	cv::drawContours(gray, contours, -1/*������������*/, cv::Scalar(255)/*����Ϊ��ɫ*/, CV_FILLED/*����ȫ�����*/);
	
	cv::cvtColor(gray, gray, CV_GRAY2RGB);

	cv::Mat show_image(cv::Size(2 * image.cols, image.rows), CV_8UC3);
	image.copyTo(show_image(cv::Rect(0,0,image.cols,image.rows)));
	gray.copyTo(show_image(cv::Rect(image.cols, 0, image.cols, image.rows)));
	
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);					    compression_params.push_back(100); //�����������Ҫ��ͼƬ����
	cv::imwrite("homework4_1.jpg", show_image, compression_params);


	cv::imshow("show", show_image);
	cv::waitKey(0);
}
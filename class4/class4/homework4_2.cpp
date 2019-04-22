#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
cv::Mat show(cv::Mat img);
int main() {

	//����ͼƬ
	cv::Mat image = cv::imread("raccoon_hw.jpg");
	cv::resize(image, image, cv::Size(image.cols/2, image.rows/2));

	cv::Mat R,G,B;
	std::vector<cv::Mat>rgb;
	cv::split(image, rgb);
	R = rgb[0];
	G = rgb[1];
	B = rgb[2];

	R = show(R);
	G = show(G);
	B = show(B);

	cv::Mat show_image(cv::Size(3* R.cols, R.rows), CV_8U);
	//image.copyTo(show_image(cv::Rect(0, 0, image.cols, image.rows)));
	R.copyTo(show_image(cv::Rect(0, 0, R.cols, R.rows)));
	G.copyTo(show_image(cv::Rect(R.cols, 0, R.cols, R.rows)));
	B.copyTo(show_image(cv::Rect(2* R.cols, 0, R.cols, R.rows)));

	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	//�����������Ҫ��ͼƬ�������ϸߵ�ֵ��ζ�Ÿ�С�ĳߴ�͸�����ѹ��ʱ��
	compression_params.push_back(100);
	cv::imwrite("homework4_2.jpg", show_image, compression_params);

	cv::imshow("show", show_image);
	cv::waitKey(0);
}


cv::Mat show(cv::Mat img) {
	int histsize[] = { 256 }; //���������Ҳ����ֱ��ͼ�ĸ�
	float range[] = { 0, 256 }; //����ֵ�ķ�Χ
	const float *ranges[] = { range };
	int channels[] = { 0 }; //ͨ��

	cv::Mat hist; //ֱ��ͼ���
	calcHist(&img, 1, channels, cv::Mat() /*��ʹ��ͼ����Ϊ����*/, hist, 1, histsize, ranges);

	//��ͼ�η�ʽ��ʾֱ��ͼ
	//��ȡ���ֵ����Сֵ
	double maxVal = 0;
	double minVal = 0;
	cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	//��ʾֱ��ͼ��ͼ��
	cv::Mat hist_img(histsize[0], histsize[0], CV_8U, cv::Scalar(255));
	//������ߵ�Ϊͼ�ߵ�90%
	int high_pt = static_cast<int>(0.9*histsize[0]);
	//ÿ����Ŀ����һ����ֱ��
	for (int h = 0; h < histsize[0]; h++) {
		float binVal = hist.at<float>(h);
		//��ֱ�ߵĸ߶�
		int intensity = static_cast<int>(binVal*high_pt / maxVal);
		//����֮�����һ����
		cv::line(hist_img, cv::Point(h, histsize[0]), cv::Point(h, histsize[0] - intensity), cv::Scalar::all(0));
	}
	return hist_img;
}
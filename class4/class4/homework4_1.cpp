#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int main() {

	//读入图片
	cv::Mat image = cv::imread("raccoon_hw.jpg");

	cv::Mat gray;
	//转化为灰度图
	cv::cvtColor(image, gray, CV_RGB2GRAY);
	cv::threshold(gray, gray, 180, 255, cv::THRESH_BINARY_INV);
	
	cv::erode(gray, gray, cv::Mat(), cv::Point(-1, -1), 1);//腐蚀
	cv::dilate(gray, gray, cv::Mat(), cv::Point(-1, -1), 1);//膨胀

	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(gray, contours, CV_RETR_EXTERNAL/*获取外轮廓*/,
		CV_CHAIN_APPROX_NONE/*获取每个轮廓的每个像素*/, cv::Point());
	
	std::vector<std::vector<cv::Point> >::const_iterator it = contours.begin();
	while (it != contours.end()) {
		if (it->size() < 1000)
			it = contours.erase(it);
		else
			++it;
	}
	cv::drawContours(gray, contours, -1/*绘制所有轮廓*/, cv::Scalar(255)/*绘制为白色*/, CV_FILLED/*轮廓全部填充*/);
	
	cv::cvtColor(gray, gray, CV_GRAY2RGB);

	cv::Mat show_image(cv::Size(2 * image.cols, image.rows), CV_8UC3);
	image.copyTo(show_image(cv::Rect(0,0,image.cols,image.rows)));
	gray.copyTo(show_image(cv::Rect(image.cols, 0, image.cols, image.rows)));
	
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);					    compression_params.push_back(100); //在这个填入你要的图片质量
	cv::imwrite("homework4_1.jpg", show_image, compression_params);


	cv::imshow("show", show_image);
	cv::waitKey(0);
}
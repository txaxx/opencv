#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
cv::Mat show(cv::Mat img);
int main() {

	//读入图片
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
	//在这个填入你要的图片质量，较高的值意味着更小的尺寸和更长的压缩时间
	compression_params.push_back(100);
	cv::imwrite("homework4_2.jpg", show_image, compression_params);

	cv::imshow("show", show_image);
	cv::waitKey(0);
}


cv::Mat show(cv::Mat img) {
	int histsize[] = { 256 }; //项的数量，也就是直方图的高
	float range[] = { 0, 256 }; //像素值的范围
	const float *ranges[] = { range };
	int channels[] = { 0 }; //通道

	cv::Mat hist; //直方图结果
	calcHist(&img, 1, channels, cv::Mat() /*不使用图像作为掩码*/, hist, 1, histsize, ranges);

	//以图形方式显示直方图
	//获取最大值和最小值
	double maxVal = 0;
	double minVal = 0;
	cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	//显示直方图的图像
	cv::Mat hist_img(histsize[0], histsize[0], CV_8U, cv::Scalar(255));
	//设置最高点为图高的90%
	int high_pt = static_cast<int>(0.9*histsize[0]);
	//每个条目绘制一条垂直线
	for (int h = 0; h < histsize[0]; h++) {
		float binVal = hist.at<float>(h);
		//垂直线的高度
		int intensity = static_cast<int>(binVal*high_pt / maxVal);
		//两点之间绘制一条线
		cv::line(hist_img, cv::Point(h, histsize[0]), cv::Point(h, histsize[0] - intensity), cv::Scalar::all(0));
	}
	return hist_img;
}
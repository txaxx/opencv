#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;

int main() {

	//--1.读入图片
	cv::Mat image = cv::imread("horse_hw.jpg");

	//--2.转换灰度图
	cv::Mat gray;
	cv::cvtColor(image, gray, CV_RGB2GRAY);
	cv::imshow("gray", gray);

	//--3.二值化灰度图
	cv::Mat dst;
	cv::threshold(gray, dst, 15, 255, cv::THRESH_BINARY_INV);
	//平滑处理(平滑/高斯平滑两种)
	//cv::blur(dst,dst,cv::Size(3,3));
	cv::GaussianBlur(dst,dst,cv::Size(3,3),0,0); //高斯平滑

	//形态学操作（此处效果不好，只用来展示加强理解）
	cv::erode(dst,dst,cv::Mat(),cv::Point(-1,-1),1);
	cv::dilate(dst,dst,cv::Mat(),cv::Point(-1,-1),1);

	//画矩形框
	cv::Mat image_roi=image(cv::Rect(0, 0, image.cols / 3, image.rows / 4));
	image_roi = { cv::Scalar(255,255,255) };//把ROI中的像素值改为白色
	//在图片上写文字
	cv::putText(image_roi, "hello tx!", cv::Point(20, 60), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 23, 0), 4, 8);
	//用rectangle画矩形框
	cv::rectangle(dst, cv::Point(image.cols / 3, image.rows / 4),
		cv::Point(image.cols / 2, image.rows / 2), 
		cv::Scalar(255, 255, 255), -1,8, 0);
	//--4.显示结果(原图和结果图显示在一起)
	const int width = image.cols;
	const int height = image.rows;
	cv::Mat show_image(cv::Size(width,2 *  height), CV_8UC3);
	//将image拷贝到显示图片指定位置
	image.copyTo(show_image(cv::Rect(0, 0, width, height)));
	//将dst转换为3通道，使得show_image和dst通道数一致，或者使用convertTo()函数做操作
	cv::cvtColor(dst, dst, CV_GRAY2RGB);
	//将dst拷贝image指定位置
	dst.copyTo(show_image(cv::Rect(0, height, width, height)));

	//保存图片
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //选择jpeg
	compression_params.push_back(9); //在这个填入你要的图片质量
	cv::imwrite("homework3.jpg", show_image, compression_params);

	//显示
	cv::imshow("show", show_image);
	cv::waitKey(0);
}

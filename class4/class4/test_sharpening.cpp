/*
 *
 * 功能：使用算子对图片进行锐化
 *
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(){

	//读入图片
	cv::Mat image = cv::imread("lena.jpg");

	//基于拉普拉斯算子的图像锐化
	//拉普拉斯滤波核3*3 
	//  0  -1   0 
	// -1   5  -1 
	//  0  -1   0  
	cv::Mat kernel = (cv::Mat_<float>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
	cv::Mat sharpen_laplace;
	cv::filter2D(image,sharpen_laplace,image.depth(),kernel);

	cv::Mat show_image(cv::Size(2 * image.cols, image.rows), CV_8UC3);
	image.copyTo(show_image(cv::Rect(0, 0, image.cols, image.rows)));
	sharpen_laplace.copyTo(show_image(cv::Rect(image.cols, 0, image.cols, image.rows)));

	cv::imshow("show", show_image);
	cv::waitKey(0);
}

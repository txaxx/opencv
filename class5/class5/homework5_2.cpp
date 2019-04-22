#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;


void lsn5_HoughLines(void);
typedef vector<Point> contour_t;
Mat gray;
Mat img;
float srcScale = 0.5;
	
int main() {
	img = imread("algori_hw.jpg");
	resize(img, img, Size(img.cols/2, img.rows/2));
	cvtColor(img, gray, CV_RGB2GRAY);
	Canny(gray, gray, 50, 200, 3);
	/*vector<Vec4i> lines;
	HoughLinesP(gray, lines, 1, CV_PI / 180, 50, 50, 5);

	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}

	*/
	lsn5_HoughLines();


	return 0;
}


void lsn5_HoughLines(void)
{
	//创建掩码，将文字部分单独出来
	Mat mask(gray.rows, gray.cols, CV_8UC1, Scalar(0));
	//mask = mask.zeros(mask.size(), mask.type());
	vector<contour_t> mContours;

	contour_t sub_contour;
	sub_contour.push_back(Point(430 * srcScale, 150 * srcScale));
	sub_contour.push_back(Point(18 * srcScale, 979 * srcScale));
	sub_contour.push_back(Point(700 * srcScale, 979 * srcScale));
	sub_contour.push_back(Point(590 * srcScale, 747 * srcScale));
	sub_contour.push_back(Point(866 * srcScale, 425 * srcScale));
	sub_contour.push_back(Point(430 * srcScale, 150 * srcScale));

	mContours.push_back(sub_contour);
	drawContours(mask, mContours, -1, Scalar(255), CV_FILLED, 8);
	//imshow("mask", mask);

	Mat mask2(gray.rows, gray.cols, CV_8UC1, Scalar(255));
	drawContours(mask2, mContours, -1, Scalar(0), CV_FILLED, 8);
	//imshow("mask_r", mask2);

	waitKey();

	//霍夫直线检测
	vector<Vec4i> lines;
	HoughLinesP(gray, lines, 1, CV_PI / 180, 30, 20, 5);

	//画线
	Mat dst= img.clone(),dst2 = img.clone();

	for (size_t i = 0; i < lines.size(); i++)
	{
		//获取一条直线的端点坐标，并画出直线
		Vec4i L = lines[i];
		line(dst, Point(L[0], L[1]), Point(L[2], L[3]), Scalar(0, 255, 0), 1, LINE_AA);
		line(dst2, Point(L[0], L[1]), Point(L[2], L[3]), Scalar(255, 0, 0), 1, LINE_AA);
	}

	Mat result;
	dst.copyTo(result, mask);
	dst2.copyTo(result, mask2);

	//保存图片
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	//在这个填入你要的图片质量，较高的值意味着更小的尺寸和更长的压缩时间
	compression_params.push_back(100);
	cv::imwrite("homework5_2.jpg",result,compression_params);

	imshow("HoughLinesP", result);

	waitKey();
}
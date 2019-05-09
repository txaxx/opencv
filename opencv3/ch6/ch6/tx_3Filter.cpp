#include "opencv2/core/core.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 
using namespace cv;

//-----------------------------------【main( )函数】--------------------------------------------
//	描述：控制台应用程序的入口函数，我们的程序从这里开始
//-----------------------------------------------------------------------------------------------
int main()
{
	// 载入原图
	Mat image = imread("1.jpg");


	//显示原图
	imshow("方框滤波【原图】", image);

	//进行方框滤波操作
	Mat out1, out2, out3;
	boxFilter(image, out1, -1, Size(5, 5));
	//均值滤波
	blur(image, out2, Size(5, 5));
	//高斯滤波
	GaussianBlur(image, out3, Size(5, 5), 0, 0);
	//显示效果图
	imshow("方框滤波【效果图】", out1);
	imshow("均值滤波【效果图】", out2);
	imshow("高斯滤波【效果图】", out3);
	waitKey(0);
}
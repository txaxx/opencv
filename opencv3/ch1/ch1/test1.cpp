#include<opencv2/opencv.hpp>
using namespace cv;

int main() {
	Mat img = imread("lena.jpg");
	Mat dst_erode, dst_blur,gray,dst_canny;
	//¸¯Ê´
	erode(img, dst_erode, Mat(), Point(-1, -1), 2);
	
	//ÂË²¨
	blur(img, dst_blur, Size(5, 5), Point(-1, -1), BORDER_DEFAULT);
	
	//»Ò¶È
	cvtColor(img, gray, COLOR_BGR2GRAY);
	//ÂË²¨
	blur(gray, gray, Size(3, 3));
	//±ßÔµ¼ì²â
	Canny(gray, dst_canny, 30, 120, 3);
	imshow("Ô­Í¼",img);
	imshow("¸¯Ê´ºóµÄÍ¼", dst_erode);
	imshow("ÂË²¨ºóµÄÍ¼", dst_blur);
	imshow("»Ò¶ÈÍ¼", gray);
	imshow("±ßÔµ¼ì²âÍ¼", dst_canny);
	waitKey(0);
	return 0;
}
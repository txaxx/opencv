#include<opencv2/opencv.hpp>
using namespace cv;

int main() {
	//VideoCapture cap;
	//cap.open("bike.avi");
	
	Mat frame;
	VideoCapture cap(0);
	while (1)
	{
		cap >> frame;

		Mat dst_blur, gray, dst_canny;
		
		//ª“∂»
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		//±ﬂ‘µºÏ≤‚
		Canny(gray, dst_canny, 30, 120, 3);
		imshow("‘≠Õº", frame);
		imshow("ª“∂»Õº", gray);
		imshow("±ﬂ‘µºÏ≤‚Õº", dst_canny);

		waitKey(30);
	}
	return 0;
}
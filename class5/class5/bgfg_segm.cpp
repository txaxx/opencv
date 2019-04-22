#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

static void help()
{
 printf("\nDo background segmentation, especially demonstrating the use of cvUpdateBGStatModel().\n"
"Learns the background at the start and then segments.\n"
"Learning is togged by the space key. Will read from file or camera\n"
"Usage: \n"
"			./bgfg_segm [--camera]=<use camera, if this key is present>, [--file_name]=<path to movie file> \n\n");
}

const char* keys =
{
    "{c  camera   |         | use camera or not}"
    "{m  method   |mog2     | method (knn or mog2) }"
    "{s  smooth   |         | smooth the mask }"
    "{fn file_name|tree.avi | movie file        }"
};

//this is a sample for foreground detection functions
int main(int argc, const char** argv)
{
    help();

    /*CommandLineParser parser(argc, argv, keys);
    bool useCamera = parser.has("camera");
    bool smoothMask = parser.has("smooth");
    string file = parser.get<string>("bike_hw.avi");
    string method = parser.get<string>("method");
    VideoCapture cap;
    bool update_bg_model = true;

    if( useCamera )
        cap.open(0);
    else
        cap.open(file.c_str());

    parser.printMessage();*/

	bool smoothMask = true;
	bool update_bg_model = true;
	string method="mog2";
	string file = "walk.avi";
	VideoCapture cap;
	cap.open(file.c_str());

    if( !cap.isOpened() )
    {
        printf("can not open camera or video file\n");
        return -1;
    }
	namedWindow("image", WINDOW_NORMAL);
    namedWindow("foreground mask", WINDOW_NORMAL);
    namedWindow("foreground image", WINDOW_NORMAL);
    namedWindow("mean background image", WINDOW_NORMAL);

	//用于背景/前景分割的基类：
    Ptr<BackgroundSubtractor> bg_model = method == "knn" ?
		//创建KNN背景减法器 像素和样本之间距离的阈值，以确定像素是否接近该样本。
            createBackgroundSubtractorKNN().dynamicCast<BackgroundSubtractor>() :
        //创建MOG2背景减法器 像素和模型之间平方距离的阈值，以确定背景模型是否很好地描述了像素。
			createBackgroundSubtractorMOG2().dynamicCast<BackgroundSubtractor>();

    Mat img0, img, fgmask, fgimg;

    for(;;)
    {
		//读取每一帧到img0
        cap >> img0;

        if( img0.empty() )
            break;

        resize(img0, img, Size(640, 640*img0.rows/img0.cols), INTER_LINEAR);

        if( fgimg.empty() )
          fgimg.create(img.size(), img.type());

        //update the model 计算前景蒙版（an 8-bit binary image）
		//负参数值使算法使用一些自动选择的学习速率。 0表示背景模型根本不更新，1表示背景模型从最后一帧完全重新初始化
        bg_model->apply(img, fgmask, update_bg_model ? -1 : 0);

        if( smoothMask )
        {
			//对前景蒙版进行高斯滤波、阈值分割
			//erode(fgmask, fgmask, Mat(), Point(-1, -1), 3);//腐蚀
			GaussianBlur(fgmask, fgmask, Size(11, 11), 3.5, 3.5);
            threshold(fgmask, fgmask, 10, 255, THRESH_BINARY);
        }

		//--4.寻找轮廓
		std::vector<std::vector<cv::Point> > contours(10000);
		cv::findContours(fgmask, contours, CV_RETR_EXTERNAL/*获取外轮廓*/,
			CV_CHAIN_APPROX_NONE/*获取每个轮廓的每个像素*/, cv::Point());
		//遍历每一个轮廓，把多余的轮廓去掉
		std::vector<std::vector<cv::Point> >::const_iterator it = contours.begin();
		while (it != contours.end()) {
			if (it->size() < 40)
				it = contours.erase(it);
			else
				++it;
		}
		//重新绘制轮廓
		Mat dst(fgmask.size(), CV_8U, Scalar(0));
		drawContours(dst, contours, -1/*绘制所有轮廓*/, Scalar(255)/*绘制为白色*/, CV_FILLED/*轮廓全部填充*/);
		//dilate(dst, dst, Mat(), Point(-1, -1), 3);//膨胀

		dst.copyTo(fgmask);

		//把前景图片设为黑色
        fgimg = Scalar::all(0);
		//把图像复制到黑色的前景图片的特定部位（此时图中只有运动的人）
        img.copyTo(fgimg, dst);

        Mat bgimg;
		//计算背景图像。
        bg_model->getBackgroundImage(bgimg);
		
        imshow("image", img);
        imshow("foreground mask", fgmask);
        imshow("foreground image", fgimg);
        if(!bgimg.empty())
          imshow("mean background image", bgimg );

        char k = (char)waitKey(30);
        if( k == 27 ) break;
        if( k == ' ' )
        {
            update_bg_model = !update_bg_model;
            if(update_bg_model)
                printf("Background update is on\n");
            else
                printf("Background update is off\n");
        }
    }

    return 0;
}

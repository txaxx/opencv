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

	//���ڱ���/ǰ���ָ�Ļ��ࣺ
    Ptr<BackgroundSubtractor> bg_model = method == "knn" ?
		//����KNN���������� ���غ�����֮��������ֵ����ȷ�������Ƿ�ӽ���������
            createBackgroundSubtractorKNN().dynamicCast<BackgroundSubtractor>() :
        //����MOG2���������� ���غ�ģ��֮��ƽ���������ֵ����ȷ������ģ���Ƿ�ܺõ����������ء�
			createBackgroundSubtractorMOG2().dynamicCast<BackgroundSubtractor>();

    Mat img0, img, fgmask, fgimg;

    for(;;)
    {
		//��ȡÿһ֡��img0
        cap >> img0;

        if( img0.empty() )
            break;

        resize(img0, img, Size(640, 640*img0.rows/img0.cols), INTER_LINEAR);

        if( fgimg.empty() )
          fgimg.create(img.size(), img.type());

        //update the model ����ǰ���ɰ棨an 8-bit binary image��
		//������ֵʹ�㷨ʹ��һЩ�Զ�ѡ���ѧϰ���ʡ� 0��ʾ����ģ�͸��������£�1��ʾ����ģ�ʹ����һ֡��ȫ���³�ʼ��
        bg_model->apply(img, fgmask, update_bg_model ? -1 : 0);

        if( smoothMask )
        {
			//��ǰ���ɰ���и�˹�˲�����ֵ�ָ�
			//erode(fgmask, fgmask, Mat(), Point(-1, -1), 3);//��ʴ
			GaussianBlur(fgmask, fgmask, Size(11, 11), 3.5, 3.5);
            threshold(fgmask, fgmask, 10, 255, THRESH_BINARY);
        }

		//--4.Ѱ������
		std::vector<std::vector<cv::Point> > contours(10000);
		cv::findContours(fgmask, contours, CV_RETR_EXTERNAL/*��ȡ������*/,
			CV_CHAIN_APPROX_NONE/*��ȡÿ��������ÿ������*/, cv::Point());
		//����ÿһ���������Ѷ��������ȥ��
		std::vector<std::vector<cv::Point> >::const_iterator it = contours.begin();
		while (it != contours.end()) {
			if (it->size() < 40)
				it = contours.erase(it);
			else
				++it;
		}
		//���»�������
		Mat dst(fgmask.size(), CV_8U, Scalar(0));
		drawContours(dst, contours, -1/*������������*/, Scalar(255)/*����Ϊ��ɫ*/, CV_FILLED/*����ȫ�����*/);
		//dilate(dst, dst, Mat(), Point(-1, -1), 3);//����

		dst.copyTo(fgmask);

		//��ǰ��ͼƬ��Ϊ��ɫ
        fgimg = Scalar::all(0);
		//��ͼ���Ƶ���ɫ��ǰ��ͼƬ���ض���λ����ʱͼ��ֻ���˶����ˣ�
        img.copyTo(fgimg, dst);

        Mat bgimg;
		//���㱳��ͼ��
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

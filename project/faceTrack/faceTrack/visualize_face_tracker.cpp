/*****************************************************************************
*   Non-Rigid Face Tracking
******************************************************************************
*   by Jason Saragih, 5th Dec 2012
*   http://jsaragih.org/
******************************************************************************
*   Ch6 of the book "Mastering OpenCV with Practical Computer Vision Projects"
*   Copyright Packt Publishing 2012.
*   http://www.packtpub.com/cool-projects-with-opencv/book
*****************************************************************************/
/*
  visualize_face_tracker: perform face tracking from a video/camera stream
  Jason Saragih (2012)
*/
#include "ft.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#define fl at<float>
//==============================================================================
void
draw_string(Mat img,                       //image to draw on
        const string text)             //text to draw
{
  Size size = getTextSize(text,FONT_HERSHEY_COMPLEX,0.6f,1,NULL);
  putText(img,text,Point(0,size.height),FONT_HERSHEY_COMPLEX,0.6f,
      Scalar::all(0),1,CV_AA);
  putText(img,text,Point(1,size.height+1),FONT_HERSHEY_COMPLEX,0.6f,
      Scalar::all(255),1,CV_AA);
}
//==============================================================================
int main()
{
  //load detector model
  face_tracker tracker = load_ft<face_tracker>("E:\\C++\\opencv\\project\\muct-landmarks\\tracker.yaml");

  //create tracker parameters
  face_tracker_params p; p.robust = false;
  p.ssize.resize(3);
  p.ssize[0] = Size(21,21);
  p.ssize[1] = Size(11,11);
  p.ssize[2] = Size(5,5);

  //open video stream
  VideoCapture cam("face2.mkv");//"Megamind.avi"
  if (!cam.isOpened())
  {
	  cout << "Fail to open this file!" << endl;
	  return 0;
  }
  int frame_count = cam.get(CV_CAP_PROP_FRAME_COUNT);
  //cout << "frame_count "<<frame_count << endl;

  //detect until user quits
  namedWindow("face tracker");
  while(cam.get(CV_CAP_PROP_POS_AVI_RATIO) < 0.999999){
    Mat im; cam >> im; 

  int frame_num = cam.get(CV_CAP_PROP_POS_FRAMES);
  if (frame_num == frame_count) {
	  cam.set(CV_CAP_PROP_POS_FRAMES, 1);
  }
  cout << frame_num << endl;

    if(tracker.track(im,p))tracker.draw(im);
    draw_string(im,"d - redetection");
    tracker.timer.display_fps(im,Point(1,im.rows-1));
    imshow("face tracker",im);
    int c = waitKey(100);
    if(c == 'q')break;
    else if(c == 'd')tracker.reset();
  }
  destroyWindow("face tracker"); cam.release(); return 0;
}
//==============================================================================

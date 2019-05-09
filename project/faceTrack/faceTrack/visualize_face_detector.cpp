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
  visualize_face_detector: Visualize the placement of points on the face
  Jason Saragih (2012)
*/
#include "ft.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<opencv2/opencv.hpp>
#define fl at<float>
using namespace std;
//==============================================================================
int main()
{
  //parse command line arguments
  
  //load detector model
  face_detector detector = load_ft<face_detector>("E:\\C++\\opencv\\project\\muct-landmarks\\detector.yaml");

  //open video stream
  VideoCapture cam(0);
  
  if(!cam.isOpened()){
    cout << "Failed opening video file." << endl; 
	return 0;
  }
  //detect until user quits
  namedWindow("face detector");
  while(cam.get(CV_CAP_PROP_POS_AVI_RATIO) < 0.999999){
    Mat im; cam >> im;     
    vector<Point2f> p = detector.detect(im);
    if(p.size() > 0){
      for(int i = 0; i < int(p.size()); i++)
    circle(im,p[i],1,CV_RGB(0,255,0),2,CV_AA);
    }
    imshow("face detector",im);
    if(waitKey(10) == 'q')break;
  }
  destroyWindow("face detector"); cam.release(); return 0;
}
//==============================================================================

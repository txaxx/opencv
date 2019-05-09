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
  train_face_detector: learn a face_detector object from training data
  Jason Saragih (2012)
*/
#include "ft.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#define fl at<float>
//==============================================================================
int main()
{
  //parse cmdline input
  float frac = 0.8;
  bool mirror = false;

  //load data
  ft_data data = load_ft<ft_data>("E:\\C++\\opencv\\project\\muct-landmarks\\annotations.yaml");
  shape_model smodel = load_ft<shape_model>("E:\\C++\\opencv\\project\\muct-landmarks\\shape.yaml");
  smodel.set_identity_params();
  vector<Point2f> r = smodel.calc_shape();
  Mat ref = Mat(r).reshape(1,2*r.size());

  //train face detecto
  face_detector detector; 
  detector.train(data, "E:\\C++\\opencv\\project\\muct-landmarks\\haarcascade_frontalface_alt.xml",ref,mirror,true,frac);

  //save detector
  save_ft<face_detector>("E:\\C++\\opencv\\project\\muct-landmarks\\detector.yaml",detector);
  return 0;
}
//==============================================================================

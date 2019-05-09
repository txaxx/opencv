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
  train_patch_model: learn a patch_model object from training data
  Jason Saragih (2012)
*/
#include "ft.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#define fl at<float>
//==============================================================================
float                                      //scaling factor
calc_scale(const Mat &X,                   //scaling basis vector
       const float width)              //width of desired shape
{
  int n = X.rows/2; float xmin = X.at<float>(0),xmax = X.at<float>(0);
  for(int i = 0; i < n; i++){
    xmin = min(xmin,X.at<float>(2*i));
    xmax = max(xmax,X.at<float>(2*i));
  }return width/(xmax-xmin);
}
//==============================================================================
int main()
{
  int width  = 100;
  int psize  = 11;
  int ssize  = 11;
  bool mirror = false;
  Size wsize(psize+ssize,psize+ssize);

  //load data
  ft_data data = load_ft<ft_data>("E:\\C++\\opencv\\project\\muct-landmarks\\annotations.yaml");
  data.rm_incomplete_samples();
  if(data.imnames.size() == 0){
    cerr << "Data file does not contain any annotations."<< endl; return 0;
  }
  //load shape model
  shape_model smodel = load_ft<shape_model>("E:\\C++\\opencv\\project\\muct-landmarks\\shape.yaml");

  //generate reference shape 
  smodel.p = Scalar::all(0.0); 
  smodel.p.fl(0) = calc_scale(smodel.V.col(0),width); 
  vector<Point2f> r = smodel.calc_shape();

  //train patch models
  patch_models pmodel;
  pmodel.train(data,r,Size(psize,psize),Size(ssize,ssize),mirror);
  save_ft<patch_models>("E:\\C++\\opencv\\project\\muct-landmarks\\patch.yaml",pmodel);
  return 0;
}
//==============================================================================

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
  train_face_tracker: build a face_tracker object from its constituents
  Jason Saragih (2012)
*/
#include "ft.hpp"
#include <iostream>
#define fl at<float>

using namespace std;
const char* usage = 
"usage: ./train_face_tracker shape_model_file patch_models_file"
" face_detector_file face_tracker_file";
//==============================================================================
bool
parse_help(int argc,char** argv)
{
  for(int i = 1; i < argc; i++){
    string str = argv[i];
    if(str.length() == 2){if(strcmp(str.c_str(),"-h") == 0)return true;}
    if(str.length() == 6){if(strcmp(str.c_str(),"--help") == 0)return true;}
  }return false;
}
//==============================================================================
int main()
{
  
  //create face tracker model
  face_tracker tracker;
  tracker.smodel = load_ft<shape_model>("E:\\C++\\opencv\\project\\muct-landmarks\\shape.yaml");
  tracker.pmodel = load_ft<patch_models>("E:\\C++\\opencv\\project\\muct-landmarks\\patch.yaml");
  tracker.detector = load_ft<face_detector>("E:\\C++\\opencv\\project\\muct-landmarks\\detector.yaml");
  
  //save face tracker
  save_ft<face_tracker>("E:\\C++\\opencv\\project\\muct-landmarks\\tracker.yaml",tracker); return 0;
}
//==============================================================================

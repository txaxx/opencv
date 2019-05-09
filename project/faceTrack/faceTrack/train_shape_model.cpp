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
  train_shape_model: Learn a shape_model object from training data
  Jason Saragih (2012)
*/
#include "ft.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

//==============================================================================
int main()
{
	//load data
	float frac = 0.95;
	int kmax = 20;
	bool mirror = false;
	ft_data data = load_ft<ft_data>("E:\\C++\\opencv\\project\\muct-landmarks\\annotations.yaml");
	if (data.imnames.size() == 0) {
		cerr << "Data file does not contain any annotations." << endl; return 0;
	}
	//remove unlabeled samples and get reflections as well
	data.rm_incomplete_samples();
	vector<vector<Point2f> > points;
	for (int i = 0; i < int(data.points.size()); i++) {
		points.push_back(data.get_points(i, false));
		if (mirror)points.push_back(data.get_points(i, true));
	}
	//train model and save to file
	cout << "shape model training samples: " << points.size() << endl;
	shape_model smodel; smodel.train(points, data.connections, frac, kmax);
	cout << "retained: " << smodel.V.cols - 4 << " modes" << endl;
	save_ft("E:\\C++\\opencv\\project\\muct-landmarks\\shape.yaml", smodel); return 0;
}
//==============================================================================

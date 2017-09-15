/* ColorBlind.cpp              */
/* CSI494 Computer Vision      */
/* Parker Hornstein            */
/* image display code          */
/* taken from opencv tutorial  */
/////////////////////////////////

#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/matx.hpp"

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	/// Read image given by user

	setBreakOnError(true);  //catches exceptions

	String imageName("test.jpg"); // by default
	if (argc > 1)
	{
		imageName = argv[1];
	}
	Mat image = imread(imageName);


	Mat new_image = imread(imageName);/*Mat::zeros(image.size(), image.type());*/


									  // Initialize values	
									  //Transposed matrix

	double m[3][3] = { 0.430749076295, 0.717402505462, -0.148151581757,  0.336582831043,  0.574447762213,  0.0889694067435, -0.0236572929497,0.0275635332006,0.996093759749 };
	double pixelR;
	double pixelG;
	double pixelB;

	double alpha = .5; //Variable 0-3
					   //Transformation code via matrix multiplication

	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {

			pixelR = new_image.at<Vec3b>(y, x)[0];
			pixelG = new_image.at<Vec3b>(y, x)[1];
			pixelB = new_image.at<Vec3b>(y, x)[2];

			new_image.at<Vec3b>(y, x)[0] = saturate_cast<uchar>(m[0][0] * pixelR + m[0][1] * pixelR + m[0][2] * pixelR);
			new_image.at<Vec3b>(y, x)[1] = saturate_cast<uchar>(m[1][0] * pixelG + m[1][1] * pixelG + m[1][2] * pixelG);
			new_image.at<Vec3b>(y, x)[2] = saturate_cast<uchar>(m[2][0] * pixelB + m[2][1] * pixelB + m[2][2] * pixelB);
		}
	}


	// Create Windows
	namedWindow("Original Image", WINDOW_AUTOSIZE);
	namedWindow("New Image", WINDOW_AUTOSIZE);

	// Show stuff
	imshow("Original Image", image);
	imshow("New Image", new_image);

	// Wait until user press some key
	waitKey();

	return 0;
}
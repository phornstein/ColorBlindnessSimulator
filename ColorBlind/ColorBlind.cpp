/* Convolution.cpp              */
/* CSI494 Computer Vision      */
/* Parker Hornstein            */
/* image display code          */
/* taken from opencv tutorial  */
/////////////////////////////////

#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <new>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/matx.hpp"
#include <cmath>


using namespace std;
using namespace cv;


/*int ary(int x, int y, int z) { //x = x value, y = y value, z = k
int temp;
temp = y* + x;
return temp;
}*/

int main(int argc, char** argv)
{
	/// Read image given by user

	setBreakOnError(true);  //catches exceptions

	String imageName("test.jpg"); // by default
	if (argc > 1)
	{
		imageName = argv[1];
	}

	int flag = 1;
	Mat image = imread(imageName, flag);

	Mat new_image = imread(imageName, flag); //image to convolute
	Mat con_image = imread(imageName, flag); //convoluted image
											 //IplImage* con_image = cvCreateImage(cvSize(image.rows-1, image.cols-1), 8, 3);

											 //Prompt for kernel size
	int k_size = 3;
	cout << "Enter Kernel Size" << endl;
	cin >> k_size;
	if (k_size % 2 == 0) {
		cout << "Invalid Kernel Size, must be an odd number." << endl;
		system("Pause");
		exit(0);
	}

	int k = k_size * k_size;

	//create and fill dynamic array for convolution
	//int sizeX = k;
	//int sizeY = k;

	double *kernel = new double[k];

	cout << "Enter the kernel values by row from left to right and top to bottom" <<
		endl << "Example:" <<
		endl << "1 2 3" <<
		endl << "4 5 6" <<
		endl << "7 8 9" <<
		endl;

	for (int a = 0; a < k; a++) {
		cout << "Enter Kernel Value " << a << ": " << endl;
		cin >> kernel[a];
	}

	for (int y = 0; y < k; y++) {
		if (y%k_size == 0)
			cout << endl;
		cout << kernel[y];
	}


	//double kernel[9] = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };

	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < image.rows; b++) {
			for (int c = 0; c < image.cols; c++) {
				con_image.at<Vec3b>(b, c)[a] = 0;
			}
		}
	}

	//Convolution
	for (int h = 0; h < 3; h++) { //repeat 3 times for each layer
		for (int x = 0; x < image.cols - 1; x++) { //original image rows
			for (int y = 0; y < image.rows - 1; y++) {//original images cols
													  //for (int i = 0; i < k_size; i++) { //new image rows
													  //for (int j = 0; j < k_size; j++) { //new image cols
				int knum = k - 1 - x;
				con_image.at<Vec3b>(y + 1, x + 1)[h] = /*con_image.at<Vec3b>(y + 1, x + 1)[h] +*/ saturate_cast<uchar>(
					(image.at<Vec3b>(0, 0)[h] * kernel[knum]) +
					(image.at<Vec3b>(0, 1)[0] * kernel[knum]) +
					(image.at<Vec3b>(0, 2)[0] * kernel[knum]) +
					(image.at<Vec3b>(1, 0)[0] * kernel[knum]) +
					(image.at<Vec3b>(1, 1)[0] * kernel[knum]) +
					(image.at<Vec3b>(1, 2)[0] * kernel[knum]) +
					(image.at<Vec3b>(2, 0)[0] * kernel[knum]) +
					(image.at<Vec3b>(2, 1)[0] * kernel[knum]) +
					(image.at<Vec3b>(2, 2)[0] * kernel[knum]));
				//}
				//}
			}
		}
	}

	delete[]kernel;

	// Create Windows
	namedWindow("Original Image", WINDOW_AUTOSIZE);
	namedWindow("Convoluted Image", WINDOW_AUTOSIZE);

	// Show stuff
	imshow("Original Image", image);
	imshow("Convoluted Image", con_image);

	// Wait until user press some key
	waitKey();

	return 0;
}

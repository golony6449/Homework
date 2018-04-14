#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#pragma once

void hello();
void chap3_17();
void chap3_19();
void chap4_9();
void chap4_11();
void chap4_13();

// callBack Function
void Mouse(int, int, int, int, void *);	//chap4_11.cpp
void changedThickness(int, void*);		//chap4_13.cpp
void changedRadius(int, void*);			//chap4_13.cpp

// parameter for callBack Function 
typedef struct {
	int thickness;
	int radius;
	Mat img;
}Params;
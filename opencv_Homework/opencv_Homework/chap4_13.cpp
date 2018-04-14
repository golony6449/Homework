#include "custom.h"

void chap4_13() {
	Mat image(500, 500, CV_8UC3, Scalar(255, 255, 255));
	string title = "eventCtrl";
	
	Params params;
	params.img = image;
	params.thickness = 1;
	params.radius = 20;

	namedWindow(title);
	createTrackbar("±½±â", title, &(params.thickness), 10);
	createTrackbar("¹ÝÁö¸§", title, &(params.radius), 50);

	imshow("eventCtrl", image);

	setMouseCallback("eventCtrl", Mouse, (void *)&params);
	waitKey();
}

void changedThickness(int value, void* userdata) {
	Params* data = (Params*)userdata;
	data->thickness = value;
}

void changedRadius(int value, void* userdata) {
	Params* data = (Params*)userdata;
	data->radius = value;
}
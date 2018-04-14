#include "custom.h"

void chap4_11() {
	Mat image(500, 500, CV_8UC3, Scalar(255, 255, 255));
	Params params;
	params.img = image;
	params.thickness = 1;
	params.radius = 20;
	
	imshow("eventCtrl", image);

	setMouseCallback("eventCtrl", Mouse, (void *)&params);
	waitKey();
}

void Mouse(int event, int x, int y, int flags, void* userdata) {
	Params* userParams = (Params*)userdata;
	
	if (event == EVENT_RBUTTONDOWN) {
		Point center(x, y);
		circle(userParams->img, center, userParams->radius, Scalar(255, 0, 0));
		imshow("eventCtrl", userParams->img);
		waitKey();
	}
	else if (event == EVENT_LBUTTONDOWN) {
		rectangle(userParams->img, Rect(x - 15, y - 15, 30, 30), Scalar(0, 0, 255), userParams->thickness);
		imshow("eventCtrl", userParams->img);
	}
}
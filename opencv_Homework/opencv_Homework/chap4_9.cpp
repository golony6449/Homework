#include "custom.h"

void chap4_9() {
	Mat image(600, 400, CV_8UC3);
	Rect rect(100, 100, 200, 300);

	rectangle(image, rect, Scalar(0, 0, 255));

	imshow("window", image);
	waitKey(0);
}
#include <opencv2/highgui.hpp>
using namespace cv;

void hello() {
	Mat srcImage = Mat(300, 300, CV_8UC1, Scalar(200));
	imshow("Å×½ºÆ®", srcImage);
	waitKey();
}
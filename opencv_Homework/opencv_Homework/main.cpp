#include <opencv2/opencv.hpp>
using namespace cv;

void first(Mat img);
void main_Hough_OpenCV();

int main() {
	Mat src = imread("img.jpg", IMREAD_GRAYSCALE);
	main_Hough_OpenCV();
}
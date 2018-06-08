#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void Display_Lines(Mat &src_img, vector<Vec2f> lines, const char* str);

void main_Hough_OpenCV() {
	Mat src_img = imread("./test_car/07.jpg");
	//Mat src_img = imread("board1.jpg");
	//imshow("before", src_img);

	Mat gray_img, edge_img;
	cvtColor(src_img, gray_img, CV_BGR2GRAY); 

	GaussianBlur(gray_img, gray_img, Size(5, 5), 4, 4);

	Canny(gray_img, edge_img, 30, 30);
	imshow("Canny process", edge_img);

	vector<Vec2f> lines;

	////2-1
	//int angle = 10;
	// double rho = 2, theta = (CV_PI / 180) * angle, threshold = 200;

	//HoughLines(edge_img, lines, rho, theta, threshold);

	//Display_Lines(src_img, lines, "1");

	//2-2
	int angle = 14;
	double rho = 2.5, theta = (CV_PI / 180) * angle, threshold = 250;

	HoughLines(edge_img, lines, rho, theta, threshold);

	Display_Lines(src_img, lines, "2");

	waitKey();
}

void Display_Lines(Mat &src_img, vector<Vec2f> lines, const char * str) {
	for (int i = 0; i < lines.size(); i++) {
		float rho = lines[i][0];
		float theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(src_img, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);

	}
	//imshow("Hough 직선 검출 영상", src_img);
	imshow(str, src_img);
}
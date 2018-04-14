//#include <opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//
//void firstSolution();
//void secondSolution();
//
//void second() {
//	firstSolution();
//	//secondSolution();
//}
//
//void firstSolution() {
//	Mat image = imread("logo.jpg");
//	Mat bgr[3], zero(image.size(), CV_8U, Scalar(0));
//	Mat output[3] = { Mat::zeros(image.size(), CV_8UC1), Mat::zeros(image.size(), CV_8UC1), Mat::zeros(image.size(), CV_8UC1) };
//	Mat result[3];
//
//	split(image, bgr);
//
//	for (int i = 0; i < 3; i++) {
//		output[i] = bgr[i];
//		merge(output, 3, result[i]);
//		output[i] = Mat::zeros(image.size(), CV_8UC1);
//	}
//
//	imshow("image", image);
//	imshow("b", result[0]);
//	imshow("g", result[1]);
//	imshow("r", result[2]);
//	waitKey();
//}
//
//void secondSolution() {
//	Mat image = imread("logo.jpg");
//	Mat bgr[3], zero(image.size(), CV_8U, Scalar(0));
//	Mat blue_img(image.size(), CV_8UC3), green_img(image.size(), CV_8UC3), red_img(image.size(), CV_8UC3);
//
//	split(image, bgr);
//
//	//Mat src[] = { bgr[0], bgr[1], bgr[2], zero };
//	Mat src[] = { image, zero };
//	Mat dst[] = { blue_img, green_img, red_img };
//
//	int from_to[] = { 0, 0, 3, 1, 3, 2, 3, 3, 1, 4, 3, 5, 3, 6, 3, 7, 2, 8 };
//	mixChannels(src, 2, dst, 3, from_to, 9);
//
//	imshow("image", image);
//	imshow("blue_img", blue_img);
//	imshow("green_img", green_img);
//	imshow("red_img", red_img);
//	waitKey();
//}
//#include <opencv2/opencv.hpp>
//#include <iostream>
//using namespace cv;
//using namespace std;
//
//void calc_Histo(const Mat& img, Mat& hist, int bins, int range_max = 256) {
//	int histSize[] = { bins };
//	float range[] = { 0, (float)range_max };
//	int channels[] = { 0 };
//	const float* ranges[] = { range };
//
//	//cout << hist.dims << endl;
//	calcHist(&img, 1, channels, Mat(), hist, 1, histSize, ranges);
//}
//
//void draw_histo(Mat hist, Mat &hist_img, Size size = Size(256, 200)) {
//	hist_img = Mat(size, CV_8U, Scalar(255));
//	float bin = (float)hist_img.cols / hist.rows; //계급 너비 계산
//	normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX);
//
//	//cout << hist << endl;
//
//	for (int i = 0; i < hist.rows; i++) {
//		float start_x = i * bin;
//		float end_x = (i + 1) * bin;
//		Point2f pt1(start_x, 0);
//		Point2f pt2(end_x, hist.at<float>(i));
//
//		if (pt2.y > 0)
//			rectangle(hist_img, pt1, pt2, Scalar(0), -1);
//
//	}
//	flip(hist_img, hist_img, 0);
//}
//
//void first() {
//	Mat image = imread("img.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//	CV_Assert(!image.empty());
//
//	Mat hist, hist_image;
//
//	calc_Histo(image, hist, 256);
//	//cout << hist.rows << "  " << hist.cols << endl;
//	draw_histo(hist, hist_image);
//
//	imshow("histo", hist_image);
//	imshow("결과", image);
//	waitKey();
//}
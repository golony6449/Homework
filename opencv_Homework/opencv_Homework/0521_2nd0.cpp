//#include <opencv2/opencv.hpp>
//using namespace cv;
//
//void myDCT_filtering(Mat img, Mat filter, Mat &dst, int N, int M) {
//
//	for (int bi = 0; bi < img.rows; bi += N) {
//		for (int bj = 0; bj < img.cols; bj += M) {
//			Rect rect(Point(bj, bi), Size(M, N));
//			multiply(img(rect), filter, dst(rect));
//		}
//	}
//}
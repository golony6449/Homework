//#include <opencv2\opencv.hpp>
//using namespace cv;
//
//// 내부 외부 엣지 계산
//void third() {
//	Mat img = imread("img2.jpg", IMREAD_GRAYSCALE);
//	Mat bin_img, after_processing;
//	threshold(img, bin_img, 128, 255, THRESH_BINARY);
//	
//	Mat mask = (Mat_<uchar>(3, 3) << 
//		0, 255, 0,
//		255, 255, 255,
//		0, 255, 0);
//
//	erode(bin_img, after_processing, mask);
//	//imshow("원본 ", bin_img);
//	//imshow("결과", after_processing);
//	imshow("Edge", bin_img - after_processing);
//	waitKey();
//}
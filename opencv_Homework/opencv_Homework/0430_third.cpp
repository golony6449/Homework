//#include <opencv2\opencv.hpp>
//using namespace cv;
//
//// ���� �ܺ� ���� ���
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
//	//imshow("���� ", bin_img);
//	//imshow("���", after_processing);
//	imshow("Edge", bin_img - after_processing);
//	waitKey();
//}
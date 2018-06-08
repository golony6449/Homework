//// 이진영상에서의 형태학 처리
//#include <opencv2/opencv.hpp>
//using namespace cv;
//
//void ex_Morphology_Binary()
//{
//	Mat gray_img = imread("img2.jpg", IMREAD_GRAYSCALE);
//	Mat bin_img(gray_img.rows, gray_img.cols, CV_8UC1);
//	bin_img = gray_img;
//	threshold(gray_img, bin_img, 128, 255, THRESH_BINARY);
//	namedWindow( "이진영상", CV_WINDOW_AUTOSIZE );  
//    imshow( "이진영상", bin_img);  
//
//	Mat dst_img(bin_img.rows, bin_img.cols, CV_8UC1);
//
//	//// custom 1
//	//Mat mask = (Mat_<uchar>(10, 5) <<		// mask
//	//			0,   255,   0, 0, 0, 0, 0, 0, 255, 0,
//	//			0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//	//			255, 255, 255, 255, 255, 255, 255, 255, 255, 0,
//	// 	        0,   255,   0, 0, 0, 0, 0, 0, 255, 0,
//	//			0, 255, 0, 0, 0, 0, 0, 0, 255, 0);
//
//	//// custom 2
//	//Mat mask = (Mat_<uchar>(10, 10) <<		// mask
//	//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//	//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//	//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//	//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//	//	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//	//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//	//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//	//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//	//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//	//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0);
//
//	// example
//	Mat mask = (Mat_<uchar>(5, 5) <<
//		0, 0, 255, 0, 0,
//		0, 0, 255, 0, 0,
//		255, 255, 255, 255, 255,
//		0, 0, 255, 0, 0,
//		0, 0, 255, 0, 0);
//
//	erode(bin_img, dst_img, mask);
//    imshow( "침식영상", dst_img);
//
//	dilate(bin_img, dst_img, mask);
//    imshow( "팽창영상", dst_img);
//
//	morphologyEx(bin_img, dst_img, MORPH_OPEN, mask);
//	imshow("열림영상", dst_img);
//
//	morphologyEx(bin_img, dst_img, MORPH_CLOSE, mask);
//	imshow("닫힘영상", dst_img);
//	
//	waitKey(0);
//	destroyAllWindows();
//}
//

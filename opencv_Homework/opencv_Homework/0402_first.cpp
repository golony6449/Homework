//#include <opencv2/opencv.hpp>
//using namespace cv;
//
//void first() {
//	Mat img = imread("img.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//	Mat output(img.rows, img.cols, CV_8UC1);
//	
//
//	for (int i = 0; i < img.rows; i++) 
//		for (int j = 0; j < img.cols; j++)
//			output.at<unsigned char>(i, j) = (unsigned char) (255 - img.at<unsigned char>(i, j));
//
//	imshow("source", img);
//	imshow("°á°ú", output);
//	waitKey();
//}
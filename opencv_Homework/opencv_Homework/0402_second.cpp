//#include <opencv2/opencv.hpp>
//#include <iostream>
//using namespace cv;
//using namespace std;
//
//void second() {
//	int value;
//	cout << "��� �� �Է�: ";
//	cin >> value;
//
//	Mat img = imread("img.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//	
//	for (int i = 0; i < img.rows; i++) {
//		uchar *row = img.ptr(i);
//		for (int j = 0; j < img.cols; j++) {
//			row[j] = (uchar) min(max(0, (row[j] + value)), 255); 
//		}
//	}
//
//	imshow("���", img);
//	waitKey();
//	
//}
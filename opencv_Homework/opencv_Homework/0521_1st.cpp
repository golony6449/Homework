//#include <opencv2/opencv.hpp>
//#include <iostream>
//using namespace cv;
//using namespace std;
//
//void first(Mat img) {
//	imshow("before", img);
//
//	Mat transformed, tempOutput;
//	img.convertTo(img, CV_32FC1);
//
//	dct(img, transformed, 0); // ¡§πÊ«‚ DCT
//	transformed.convertTo(tempOutput, CV_8UC1);
//	
//	imshow("dct", transformed);
//	imshow("dct CV8UC1", tempOutput);
//
//	//cout << transformed << endl;
//
//	Mat inversed, finalOutput;
//	idct(transformed, inversed);
//
//	inversed.convertTo(finalOutput, CV_8UC1);
//
//	imshow("idct", finalOutput);
//	waitKey();
//}
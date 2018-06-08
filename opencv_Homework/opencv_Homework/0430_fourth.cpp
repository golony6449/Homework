//#include <opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//
//void fourth() {
//	while (1) {
//		int no;
//		cout << "차량 영상 번호(0:종료) : ";
//		cin >> no;
//		if (no == 0) break;
//
//		string fname = format("./test_car/%02d.jpg", no);
//		Mat image = imread(fname, 1);
//		if (image.empty()) {
//			cout << to_string(no) + "번 영상 파일이 없습니다." << endl;
//			continue;
//		}
//
//		Mat gray, sobel, th_img, morph;
//		Mat kernel(20, 50, CV_8UC1, Scalar(1));
//
//		//// custom 2
//		//Mat kernel = (Mat_<uchar>(10, 10) <<		// mask
//		//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//		//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//		//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//		//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//		//	255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
//		//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//		//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//		//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//		//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//		//	0, 255, 0, 0, 0, 0, 0, 0, 255, 0);
//
//		//// custom 1
//		//kernel = (Mat_<uchar>(10, 5) <<		// mask
//		//			0,   255,   0, 0, 0, 0, 0, 0, 255, 0,
//		//			0, 255, 0, 0, 0, 0, 0, 0, 255, 0,
//		//			255, 255, 255, 255, 255, 255, 255, 255, 255, 0,
//		// 	        0,   255,   0, 0, 0, 0, 0, 0, 255, 0,
//		//			0, 255, 0, 0, 0, 0, 0, 0, 255, 0);
//
//		cvtColor(image, gray, CV_BGR2GRAY);
//		blur(gray, gray, Size(5, 5));
//		Sobel(gray, gray, CV_8U, 1, 0, 3);
//		
//		threshold(gray, th_img, 120, 255, THRESH_BINARY);
//		morphologyEx(th_img, morph, MORPH_CLOSE, kernel);
//
//		imshow("image", image);
//		imshow("이진 영상", th_img), imshow("열림 연산", morph);
//		waitKey(0);
//	}
//	return;
//}
//#include <opencv2/opencv.hpp>
//using namespace cv;
//
//void third() {
//	Mat img = imread("plate.JPG", CV_LOAD_IMAGE_GRAYSCALE);
//	Mat forAt(img.size(), CV_8UC1);
//	Mat forPtr(img.size(), CV_8UC1);
//	uchar threadhold = 100;
//	uchar *src, *target;
//
//	// at 시간 체크
//	double t1, t2, time;
//	t1 = static_cast<double>(getTickCount());
//
//	// 여기에서 영상처리
//	for(int i = 0; i < img.cols; i++)
//		for (int j = 0; j < img.rows; j++)
//			if (img.at<uchar>(j, i) < threadhold)
//				forAt.at<uchar>(j, i) = 0;
//			else
//				forAt.at<uchar>(j, i) = 255;
//
//	t2 = static_cast<double>(getTickCount());
//	time = (t2 - t1) / getTickFrequency();
//	printf("time(at) = %f \n", time);
//
//	// ptr시간 체크
//	t1 = static_cast<double>(getTickCount());
//
//	// 여기에서 영상처리
//	for (int i = 0; i < img.rows; i++) {
//		src = img.ptr(i);
//		target = forPtr.ptr(i);
//		for (int j = 0; j < img.cols; j++)
//			if (src[j] < threadhold)
//				target[j] = 0;
//			else
//				target[j] = 255;
//	}
//
//	t2 = static_cast<double>(getTickCount());
//	time = (t2 - t1) / getTickFrequency();
//	printf("time(ptr) = %f \n", time);
//
//	imshow("At method", forAt);
//	imshow("Ptr method", forPtr);
//	waitKey();
//}
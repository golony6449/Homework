//#include <opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//
//void first() {
//	VideoCapture captureRight(1);
//	VideoCapture captureLeft(2);
//	//capture.open("video_file_in_text.avi");
//	CV_Assert(captureRight.isOpened());
//	CV_Assert(captureLeft.isOpened());
//
//	//capture.set(CV_CAP_PROP_CONVERT_RGB)
//	captureRight.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
//	captureRight.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
//	captureLeft.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
//	captureLeft.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
//
//	double frame_rate = captureRight.get(CV_CAP_PROP_FPS);
//	int delay = 1000 / frame_rate;
//	Mat frameRight, frameLeft;
//	//Mat mask(capture.get(CV_CAP_PROP_FRAME_HEIGHT), capture.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC1, Scalar(0));
//	//Mat green(mask.size(), CV_8UC3, Scalar(0, 50, 0));
//
//	Rect roi(200, 100, 100, 200);
//	//mask(roi).setTo(1);
//
//
//	while (captureRight.read(frameRight) && captureLeft.read(frameLeft)) {
//		//if (waitKey(delay) >= 0) break;
//
//		//add(frame, green, frame, mask);
//
//		//rectangle(frame, roi, Scalar(0, 0, 255), 3);
//
//		imshow("비디오 처리", (frameRight * 0.5) + (frameLeft * 0.5));
//		waitKey(1);
//	}
//}
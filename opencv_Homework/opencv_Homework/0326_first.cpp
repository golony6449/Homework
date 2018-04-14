//#include <opencv2/opencv.hpp>
//using namespace cv;
//using namespace std;
//
//void first() {
//	VideoCapture capture;
//	capture.open("video_file_in_text.avi");
//	CV_Assert(capture.isOpened());
//
//	double frame_rate = capture.get(CV_CAP_PROP_FPS);
//	int delay = 1000 / frame_rate;
//	Mat frame;
//	Mat mask(capture.get(CV_CAP_PROP_FRAME_HEIGHT), capture.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC1, Scalar(0));
//	Mat green(mask.size(), CV_8UC3, Scalar(0, 50, 0));
//
//	Rect roi(200, 100, 100, 200);
//	mask(roi).setTo(1);
//
//
//	while (capture.read(frame)) {
//		if (waitKey(delay) >= 0) break;
//
//		add(frame, green, frame, mask);
//
//		rectangle(frame, roi, Scalar(0, 0, 255), 3);
//
//		imshow("비디오 처리", frame);
//	}
//}
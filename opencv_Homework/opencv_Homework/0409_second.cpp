#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void Hist_Equalize(Mat &gray_img);

//void main()
void second() {
	Mat gray_img = imread("img2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("srcImage", gray_img);
	Hist_Equalize(gray_img);
	imshow("dstImage", gray_img);
	waitKey();
	destroyAllWindows();
}

void Hist_Equalize(Mat &gray_img) {
	double sum[256], norm[256];
	int lut[256];

	int histSize = 256;

	float range[] = { 0, 256 };
	const float  *ranges[] = { range };

	Mat hist;
	calcHist(&gray_img, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
	//cout << hist << endl;
	sum[0] = (double)hist.at<float>(0);
	for (int k = 1; k < 256; k++) {
		sum[k] = sum[k - 1] + hist.at<float>(k);	//추가
		//cout << sum[k] << endl;
	}
	for (int k = 0; k < 256; k++) {
		norm[k] = sum[k] / sum[255];				// 추가
		//cout << norm[k] << endl;
	}
	for (int k = 0; k < 256; k++)
		lut[k] = norm[k] * 255;						//추가

	int index, value;
	for (int r = 0; r < gray_img.rows; r++) {
		for (int c = 0; c < gray_img.cols; c++) {
			index = gray_img.at<uchar>(r, c);
			value = lut[index];						// 추가
			gray_img.at<uchar>(r, c) = value;
		}
	}
}
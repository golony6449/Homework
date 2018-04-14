#include <opencv2/opencv.hpp>
using namespace cv;

void calc_Histo(const Mat& img, Mat& hist, int bins, int range_max = 256);
void draw_histo(Mat hist, Mat &hist_img, Size size = Size(256, 200));

void applyThreadhold(Mat &mat, uchar threadhold) {
	for (int i = 0; i < mat.rows; i++) {
		uchar* row = mat.ptr<uchar>(i);
		for (int j = 0; j < mat.cols; j++)
			if (row[j] > threadhold)
				row[j] = 255;
			else
				row[j] = 0;
	}
}

void third() {
	Mat image = imread("plate.JPG", CV_LOAD_IMAGE_GRAYSCALE);
	Mat hist, hist_img;
	Mat result;

	calc_Histo(image, hist, 256);
	draw_histo(hist, hist_img, image.size());

	imshow("histogram", hist_img);
	imshow("source", image);

	applyThreadhold(image, 215);
	imshow("result", image);

	waitKey();
}
#include <opencv2/opencv.hpp>
using namespace cv;

Mat getDCT_filter_dc(int N, int M)
{
	Mat filter(N, M, CV_32F, Scalar(0));
	filter.at<float>(0, 0) = 1;

	return filter;
}

Mat getDCT_filter_hori(int N, int M)
{
	Mat filter(N, M, CV_32F, Scalar(0));
	for (int i = 0; i < N; i++)
		filter.at<float>(0, i) = 1;

	return filter;
}

Mat getDCT_filter_verti(int N, int M)
{
	Mat filter(N, M, CV_32F, Scalar(0));
	for (int i = 0; i < M; i++)
		filter.at<float>(i, 0) = 1;

	return filter;
}

Mat getDCT_filter_low(int N, int M)
{
	Mat filter(N, M, CV_32F, Scalar(0));
	for (int i = 0; i < N / 2; i++)
		for (int j = 0; j < M / 2; j++)
			filter.at<float>(j, i) = 1;

	return filter;
}

Mat getDCT_filter_high(int N, int M) {
	Mat filter(N, M, CV_32F, Scalar(1));
	filter.at<float>(0, 0) = 0;  filter.at<float>(0, 1) = 0;
	filter.at<float>(0, 2) = 0;	filter.at<float>(1, 0) = 0;
	filter.at<float>(1, 1) = 0;	filter.at<float>(2, 1) = 0;

	return filter;
}

Mat Ideal_Lowpass_Filtering(int N, int M, int D0)
{
	Mat filter(N, M, CV_32F, Scalar(1));
	int u, v;
	double D; // distance
	double H;
	double centerU = M / 2;
	double centerV = N / 2;
	CvScalar cmplxValue;

	// ideal filter H
	for (v = 0; v < N; v++) {
		for (u = 0; u < M; u++) {
			D = sqrt((u - centerU)*(u - centerU) + (v - centerV)*(v - centerV));
			if (D <= D0)
				filter.at<Vec2f>(v, u) = 1.0;
			else
				filter.at<Vec2f>(v, u) = 0.0;
		}
	}
	return filter;
}

Mat get_Ideal_Lowpass_Filtering(int N, int M, int D0)
{
	Mat filter(N, M, CV_32F, Scalar(1));
	int u, v;
	double D;
	double centerU = filter.cols / 2;
	double centerV = filter.rows / 2;

	// ideal filter H
	for (v = 0; v < filter.rows; v++) {
		for (u = 0; u < filter.cols; u++) {
			D = sqrt((u - centerU)*(u - centerU) + (v - centerV)*(v - centerV));
			if (D <= D0)
				filter.at<float>(v, u) = 1.0;
			else
				filter.at<float>(v, u) = 0.0;
		}
	}

	return filter;
}

Mat get_Ideal_Highpass_Filtering(int N, int M, int D0)
{
	Mat filter(N, M, CV_32F, Scalar(1));
	int u, v; 
	double D;
	double centerU = filter.cols / 2;
	double centerV = filter.rows / 2;

	for (v = 0; v < filter.rows; v++) {
		for (u = 0; u < filter.cols; u++) {
			D = sqrt((u - centerU)*(u - centerU) + (v - centerV)*(v - centerV));
			if (D <= D0)
				filter.at<float>(v, u) = 0;
			else
				filter.at<float>(v, u) = 1;
		}
	}

	return filter;
}
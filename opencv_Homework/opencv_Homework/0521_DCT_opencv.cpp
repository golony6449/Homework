//#include <opencv2/opencv.hpp>
//#include <iostream>
//using namespace cv;
//
//void myDCT(Mat srcImg, Mat& dstImg, int M, int N, int dir = 0);
//Mat getDCT_filter_low(int N, int M);
//Mat getDCT_filter_high(int N, int M);
//
//// Ideal Filter
//
////filter
//Mat getDCT_filter_dc(int N, int M);
//Mat getDCT_filter_hori(int N, int M);
//Mat getDCT_filter_verti(int N, int M);
//Mat get_Ideal_Lowpass_Filtering(int N, int M, int D0);
//Mat get_Ideal_Highpass_Filtering(int N, int M, int D0);
//
//
//void myDCT_filtering(Mat img, Mat filter, Mat &dst, int N, int M);
//
//void main_DCT_opencv() {
//	Mat image = imread("88.jpg", IMREAD_GRAYSCALE);
//	CV_Assert(image.data);
//	Mat filter;
//	int M, N; // M: 행, N: 열
//	M = N = 8;
//
//	//filter = getDCT_filter_high(N, M);
//	//filter = getDCT_filter_low(N, M);
//	//filter = getDCT_filter_dc(N, M);
//	filter = getDCT_filter_hori(N, M);
//	//filter = getDCT_filter_verti(N, M);
//	//filter = get_Ideal_Lowpass_Filtering(N, M, 4); // D0: 0 ~ 5
//	//filter = get_Ideal_Highpass_Filtering(N, M, 2); // D0: 0 ~ 5
//
//	std::cout << filter << std::endl;
//
//	Mat floatImg;
//	image.convertTo(floatImg, CV_32F);
//	Mat m_dct(floatImg.size(), CV_32FC1);
//	Mat m_idct(floatImg.size(), CV_32FC1);
//	myDCT(floatImg, m_dct, M, N); // forward
//
//	myDCT_filtering(m_dct, filter, m_dct, 8, 8); 
//
//	myDCT(m_dct, m_idct, M, N, DCT_INVERSE); // backward
//	m_idct.convertTo(m_idct, CV_8U);
//
//	imshow("imageSrc", image);
//	imshow("idct", m_idct);
//	waitKey();
//}
//
//void myDCT(Mat srcImg, Mat& dstImg, int M, int N, int dir) {
//	if (M == 1 && N == 1) {
//		dct(srcImg, dstImg, dir); // 모든 화소를 대상으로 연산
//	}
//	
//	else {
//		for (int bi = 0; bi < srcImg.rows; bi += M) {
//			for (int bj = 0; bj < srcImg.cols; bj += N) {
//				Rect rect(Point(bj, bi), Size(N, M));
//				Mat block = srcImg(rect), new_block;
//				dct(block, new_block, dir);
//				new_block.copyTo(dstImg(rect));
//			}
//		}
//	}
//}
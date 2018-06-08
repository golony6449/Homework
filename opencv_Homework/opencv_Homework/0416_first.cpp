//#include <opencv2/opencv.hpp>
//using namespace std;
//using namespace cv;
//
//void example(Mat image) {
//	short data1[] = {
//		-1, -1, -1,
//		0, 0, 0,
//		1, 1, 1,
//	};
//
//	short data2[] = {
//		-1, 0, 1,
//		-1, 0, 1,
//		-1, 0, 1,
//	};
//
//	Mat dst1, dst2, dst;
//	Mat mask1(3, 3, CV_16S, data1);
//	Mat mask2(3, 3, CV_16S, data2);
//
//	filter2D(image, dst1, CV_32F, mask1);
//	filter2D(image, dst2, CV_32F, mask2);
//	magnitude(dst1, dst2, dst);
//	dst.convertTo(dst, CV_8U);
//
//	imshow("data1 filtering", dst1);
//	imshow("data2 filtering", dst2);
//	imshow("After filtering", dst);
//	waitKey();
//}
//
//void blur(Mat image) {
//	float blurVal[] = {
//		1 / 9., 1 / 9., 1 / 9.,
//		1 / 9., 1 / 9., 1 / 9.,
//		1 / 9., 1 / 9., 1 / 9.,
//	};
//
//	float blurVal2[] = {
//		1 / 25., 1 / 25., 1 / 25., 1 / 25., 1 / 25.,
//		1 / 25., 1 / 25., 1 / 25., 1 / 25., 1 / 25.,
//		1 / 25., 1 / 25., 1 / 25., 1 / 25., 1 / 25.,
//		1 / 25., 1 / 25., 1 / 25., 1 / 25., 1 / 25.,
//		1 / 25., 1 / 25., 1 / 25., 1 / 25., 1 / 25.,
//	};
//
//	Mat blurDst, blurDst2;
//	Mat blurMask(3, 3, CV_32F, blurVal);
//	Mat blurMask2(5, 5, CV_32F, blurVal2);
//
//	filter2D(image, blurDst, CV_32F, blurMask);
//	filter2D(image, blurDst2, CV_32F, blurMask2);
//
//	blurDst.convertTo(blurDst, CV_8U);
//	blurDst2.convertTo(blurDst2, CV_8U);
//
//	imshow("3x3 blur", blurDst);
//	imshow("5x5 blur", blurDst2);
//	waitKey();
//}
//
//void sharpen(Mat image) {
//	short sharpenVal[] = {
//		0, -1, 0,
//		-1, 5, -1,
//		0, -1, 0,
//	};
//
//	short sharpenVal2[] = {
//		1, -2, 1,
//		-2, 5, -2,
//		1, -2, 1
//	};
//
//	Mat sharpenDst, sharpenDst2;
//
//	Mat sharpenMask(3, 3, CV_16S, sharpenVal);
//	Mat sharpenMask2(3, 3, CV_16S, sharpenVal2);
//
//	filter2D(image, sharpenDst, CV_32F, sharpenMask);
//	filter2D(image, sharpenDst2, CV_32F, sharpenMask2);
//
//	sharpenDst.convertTo(sharpenDst, CV_8U);
//	sharpenDst2.convertTo(sharpenDst2, CV_8U);
//
//	imshow("4way sharpen", sharpenDst);
//	imshow("8way sharpen", sharpenDst2);
//	waitKey();
//}
//
//Mat prewitt(Mat image) {
//	short hPrewitt[] = {
//		-1, -1, -1,
//		0, 0, 0,
//		1, 1, 1,
//	};
//
//	short vPrewitt[] = {
//		-1, 0, 1,
//		-1, 0, 1,
//		-1, 0, 1,
//	};
//
//	Mat hPrewittMask(3, 3, CV_16S, hPrewitt);
//	Mat vPrewittMask(3, 3, CV_16S, vPrewitt);
//	Mat vdst, hdst, dst;
//
//	filter2D(image, vdst, CV_32F, hPrewittMask);
//	filter2D(image, hdst, CV_32F, vPrewittMask);
//	magnitude(vdst, hdst, dst);
//	dst.convertTo(dst, CV_8U);
//	
//	cout << hPrewittMask << endl;
//	//imshow("수평", hdst);
//	//imshow("수직", vdst);
//	imshow("prewitt dst", dst);
//	return dst;
//}
//
//Mat sobel(Mat image) {
//	short hSobel[] = {
//		-1, -2, -1,
//		0, 0, 0,
//		1, 2, 1,
//	};
//
//	short vSobel[] = {
//		-1, 0, 1,
//		-4, 0, 4,
//		-1, 0, 1,
//	};
//
//	Mat vSobelMask(3, 3, CV_16S, vSobel);
//	Mat hSobelMask(3, 3, CV_16S, hSobel);
//	Mat vdst, hdst, dst;
//
//	filter2D(image, vdst, CV_32F, vSobelMask);
//	filter2D(image, hdst, CV_32F, hSobelMask);
//	magnitude(vdst, hdst, dst);
//	dst.convertTo(dst, CV_8U);
//
//	//imshow("수평", hdst);
//	//imshow("수직", vdst);
//	imshow("sobel dst", dst);
//	return dst;
//}
//
//void rap(Mat image) {
//	short rapVal1[] = {
//		0, -1, 0,
//		-1, 4, -1,
//		0, -1, 0,
//	};
//
//	short rapVal2[] = {
//		-1, -1, -1,
//		-1, 8, -1,
//		-1, -1, -1
//	};
//
//	Mat rap1dst, rap2dst;
//	Mat rap1Mask(3, 3, CV_16S, rapVal1);
//	Mat rap2Mask(3, 3, CV_16S, rapVal2);
//
//	filter2D(image, rap1dst, CV_16S, rap1Mask);
//	filter2D(image, rap2dst, CV_16S, rap2Mask);
//	rap1dst.convertTo(rap1dst, CV_8U);
//	rap2dst.convertTo(rap2dst, CV_8U);
//
//	imshow("Val1", rap1dst);
//	imshow("Val2", rap2dst);
//}
//
//void first() {
//	Mat image = imread("img2.jpg", IMREAD_GRAYSCALE);
//	CV_Assert(image.data);
//
//	imshow("src", image);
//
//	//example(image);
//	//blur(image);
//	sharpen(image);
//
//	//prewitt(image);
//	//sobel(image);
//	//imshow("diff", (prewitt(image) - sobel(image)) + (sobel(image) - prewitt(image)));
//	
//	//rap(image);
//	waitKey();
//}
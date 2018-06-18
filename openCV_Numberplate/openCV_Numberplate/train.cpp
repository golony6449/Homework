#include <opencv2/opencv.hpp>
#include "commons.h"
using namespace cv;
using namespace std;

void collect_trainImage(Mat& trainingData, Mat& labels, int Nimages = 146)
{
	for (int i = 0; i< Nimages; i++)
	{
		cout << "start: " << i << endl;
		string fname = format("../image/train/%03d.png", i);		// 학습영상 파일
		Mat img = imread(fname, 0);
		CV_Assert(img.data);

		Mat tmp = img.reshape(1, 1);
		int label = (i < 77) ? 1 : 0;								// 데이터셋 추가

		trainingData.push_back(tmp);
		labels.push_back(label);
	}
	trainingData.convertTo(trainingData, CV_32FC1);
}

void collect_trainNumber(Mat& trainingData, Mat& labels, int Nimages = 100)
{
	for (int i = 0; i< Nimages; i++)
	{
		cout << "start: " << i << endl;
		string fname = format("../image/trainNumber/%02d.png", i);		// 학습영상 파일
		Mat img = imread(fname, 0);
		resize(img, img, Size(40, 40));
		CV_Assert(img.data);

		Mat tmp = img.reshape(1, 1);
		int label = i / 10;

		trainingData.push_back(tmp);
		labels.push_back(label);
	}
	trainingData.convertTo(trainingData, CV_32FC1);
}

void write_traindata(string fn, Mat trainingData, Mat classes)
{
	FileStorage fs(fn, FileStorage::WRITE);
	fs << "TrainingData" << trainingData;
	fs << "classes" << classes;
	fs.release();
}

// xml 데이터 읽기
void  read_trainData(string fn, Mat & trainingData, Mat & lables)
{
	trainingData = Mat();
	lables = Mat();
	FileStorage fs(fn, FileStorage::READ);
	CV_Assert(fs.isOpened());

	fs["TrainingData"] >> trainingData;
	fs["classes"] >> lables;
	fs.release();

	trainingData.convertTo(trainingData, CV_32FC1);
}

Ptr<ml::SVM>  SVM_create(int type, int max_iter, double epsilon)
{
	Ptr<ml::SVM> svm = ml::SVM::create();		// SVM 객체 선언
												// SVM 파라미터 지정
	svm->setType(ml::SVM::C_SVC);				// C-Support Vector Classification				
	svm->setKernel(ml::SVM::LINEAR);			// 선형 SVM 
	svm->setGamma(1);							// 커널함수의 감마값
	svm->setC(1);								// 최적화를 위한 C 파리미터

	TermCriteria criteria(type, max_iter, epsilon);
	svm->setTermCriteria(criteria);				// 반복 알고리즘의 조건
	return svm;
}

void train(int flag)
{
	Mat trainingData, labels;

	if (flag == NUMBER) {
		//read_trainData("../NUMBER.xml", trainingData, labels);
		collect_trainNumber(trainingData, labels);
		write_traindata("../NUMBER.xml", trainingData, labels);
	}
	else if(flag == PLATE) {
		//read_trainData("../SVMDATA.xml", trainingData, labels);
		collect_trainImage(trainingData, labels);
		write_traindata("../SVMDATA.xml", trainingData, labels);
	}


	//Mat  trainingData, labels;
	//read_trainData("../SVMDATA.xml", trainingData, labels);

	// SVM 객체 선언 
	Ptr<ml::SVM> svm = SVM_create(CV_TERMCRIT_ITER, 1000, 0);
	svm->train(trainingData, ml::ROW_SAMPLE, labels);	// 학습수행
	if (flag == NUMBER) {
		svm->save("../SVMtrainNumber.xml");
	}
	else if (flag == PLATE) {
		svm->save("../SVMtrain.xml");
	}
	
}


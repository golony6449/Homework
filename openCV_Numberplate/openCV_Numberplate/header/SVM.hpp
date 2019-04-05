#pragma once

void write_traindata(string fn, Mat trainingData, Mat classes);


int classify_plates(Ptr<ml::SVM> svm, vector<Mat> candi_img)
{
	for (int i = 0; i < (int)candi_img.size(); i++)
	{
		Mat onerow = candi_img[i].reshape(1, 1);  // 1행 데이터 변환
		onerow.convertTo(onerow, CV_32F);

		Mat results;						// 분류 결과 저장 행렬
		svm->predict(onerow, results);		// SVM 분류 수행

		if (results.at<float>(0) == 1) 		// 분류결과가 번호판이면
			return i;						// 영상번호 반환
	}
	return -1;
}

int classify_number(Ptr<ml::SVM> svm, Mat candi_img)
{
	Mat onerow = candi_img.reshape(1);  // 1행 데이터 변환
	onerow.convertTo(onerow, CV_32F);

	Mat results;						// 분류 결과 저장 행렬
	svm->predict(onerow, results);		// SVM 분류 수행

	return results.at<float>(0);
}

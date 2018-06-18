#pragma once

void write_traindata(string fn, Mat trainingData, Mat classes);


int classify_plates(Ptr<ml::SVM> svm, vector<Mat> candi_img)
{
	for (int i = 0; i < (int)candi_img.size(); i++)
	{
		Mat onerow = candi_img[i].reshape(1, 1);  // 1�� ������ ��ȯ
		onerow.convertTo(onerow, CV_32F);

		Mat results;						// �з� ��� ���� ���
		svm->predict(onerow, results);		// SVM �з� ����

		if (results.at<float>(0) == 1) 		// �з������ ��ȣ���̸�
			return i;						// �����ȣ ��ȯ
	}
	return -1;
}

int classify_number(Ptr<ml::SVM> svm, Mat candi_img)
{
	Mat onerow = candi_img.reshape(1);  // 1�� ������ ��ȯ
	onerow.convertTo(onerow, CV_32F);

	Mat results;						// �з� ��� ���� ���
	svm->predict(onerow, results);		// SVM �з� ����

	return results.at<float>(0);
}

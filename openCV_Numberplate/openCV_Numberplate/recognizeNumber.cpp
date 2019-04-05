#include "./header/preprocess.hpp"
#include "./header/candiate.hpp"				// 후보영역 개선 및 후보영상 생성 함수
#include "./header/SVM.hpp"						// 학습데이터 로드 및 SVM 수행
#include "./header/kNN.hpp"						// kNN 학습 함수 – 10장 3절
#include "./header/classify_objects.hpp"		// kNN 분류 함수

void recognition()
{
	bool blurFlag = 1;

	int K1 = 15, K2 = 15;
	Ptr<ml::KNearest> knn[2];
	knn[0] = kNN_train("../image/trainimage/train_numbers_custom.png", K1, 10, 20);		// 데이터셋 교체
	knn[1] = kNN_train("../image/trainimage/train_texts.png", K2, 25, 20);

	// 	학습된 데이터 로드
	Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("../SVMtrain.xml");
	Ptr<ml::SVM> svmNumber = ml::StatModel::load<ml::SVM>("../SVMtrainNumber.xml");
	
	while(1) {
		int car_no;
		cout << "차량 영상 번호 (0-20) : ";
		cin >> car_no;
		string fn = format("../image/test_car/%02d.jpg", car_no);
		Mat image = imread(fn, 1);
		CV_Assert(image.data);

		blurFlag = 1;

		recursive:
		Mat morph = preprocessing(image, blurFlag);					// 검출에 실패한 경우 blurFlag를 0으로 변경, 전처리 단계에서 블러링 제외하고 다시 수행 (흐린 사진 대응)
		vector<RotatedRect> candidates;
		find_candidates(morph, candidates);									
		vector<Mat> candidate_img = make_candidates(image, candidates);

		int plate_no = classify_plates(svm, candidate_img);			// 번호판 검출

		if (plate_no >= 0)
		{
			vector <Rect> obejct_rects, sorted_rects;
			vector <Mat> numbers;							 
			Mat  plate_img, color_plate;								

			preprocessing_plate(candidate_img[plate_no], plate_img);	
			cvtColor(plate_img, color_plate, CV_GRAY2BGR);

			find_objects(~plate_img, obejct_rects);		


			sort_rects(obejct_rects, sorted_rects);			

			for (size_t i = 0; i < sorted_rects.size(); i++)
			{
				numbers.push_back(plate_img(sorted_rects[i]));	
				rectangle(color_plate, sorted_rects[i], Scalar(0, 0, 255), 1); 

				////svm을 이용한 숫자 추출
				//Mat temp;
				//resize(plate_img(sorted_rects[i]), temp, Size(40, 40));
				//cout << classify_number(svmNumber, temp);		
				//imshow("number", plate_img(sorted_rects[i]));
				//waitKey();
			}

			if (numbers.size() == 7) {
				classify_numbers(numbers, knn, K1, K2);		// kNN 분류 수행	// 데이터셋을 수정했지만, 4개 중 1글자가 올바르게 나오지 않는 현상 발생.
			}
			else  cout << "숫자(문자) 객체를 정확히 검출하지 못했습니다. " << numbers.size() << " 개의 문자가 검출되었습니다." << endl;

			imshow("번호판 영상", color_plate);					
			draw_rotatedRect(image, candidates[plate_no], Scalar(0, 0, 255), 2);
		}
		else {
			cout << "번호판을 검출하지 못하였습니다. ";
			if (blurFlag == 0) {
				
			}
			else {
				blurFlag = 0;
				goto recursive;
			}
		}
		imshow("image", image);
		waitKey();
		destroyAllWindows();
		cout << endl;
	}
}


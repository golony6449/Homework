#include "custom.h"

void chap3_19() {
	Mat data(10, 15, CV_32SC1, Scalar(100));

	// ROI 3개 설정, 200(1,3 ~ 4,7), 300(5,8 ~ 8,13), 555(3,5 ~ 6,9) 순서로 값 설정
	Range num200x(1, 5), num200y(3, 8), num300x(5, 9), num300y(8, 14), num555x(3, 7), num555y(5, 10);
	
	data(num200x, num200y) = 200;
	data(num300x, num300y) = 300;
	data(num555x, num555y) = 555;

	cout << data << endl;
}
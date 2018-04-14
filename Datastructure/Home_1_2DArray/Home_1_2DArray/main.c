#include <stdio.h>
#include <stdlib.h>

#define None -1
#define Plus 1
#define Minus -1

int check(char[]);
int convertC2I(char);
void extractor(char*, int **);
void print(int**);

int main(void)
{
	char fomula1[100], fomula2[100];
	int f1Len, f2Len, resultLen;
	int *f1Val[2];	//0: 계수, 1: 지수
	int *f2Val[2];	//0: 계수, 1: 지수
	int *result[2];	//0: 계수, 1: 지수
	int pointer = 0;	

	// 입력 받은 이후 항 갯수 계산
	printf("식을 입력해주세요. (ex: 1x3+2x2+3x0 or 1x^3+2x^2+3x^0) \n");
	printf("첫번째 식: ");
	scanf_s("%s" , &fomula1,100);
	f1Len = check(fomula1);	// 식 1의 항의 수 파악

	printf("두번째 식: ");
	scanf_s("%s", &fomula2, 100);
	f2Len = check(fomula2);	// 식 2의 항의 수 파악

	// 항 갯수에 맞게 공간할당
	for (int i = 0; i < 2; i++){
		f1Val[i] = (int *)malloc(f1Len * sizeof(int));
		f2Val[i] = (int *)malloc(f2Len * sizeof(int));
	}

	// fomula 1의 지수 및 계수 추출
	extractor(fomula1, f1Val);
	extractor(fomula2, f2Val);

	// 결과 항 갯수 파악
	resultLen = f1Len + f2Len;
	for (int i = 0; i < f1Len; i++){
		for (int j = 0; j < f2Len; j++){
			if (f1Val[1][i] == f2Val[1][j])	resultLen--;
		}
	}
	//결과 배열 공간 할당
	result[0] = (int*)malloc(resultLen * sizeof(int));
	result[1] = (int*)malloc(resultLen * sizeof(int));
	
	int f1Pnt = 0;	//다항식 1의 포인터
	int f2Pnt = 0;	//다항식 2의 포인터

	//덧셈 수행 (결과항 수 만큼 반복)
	for (int i = 0; i < resultLen; i++) {
		if (f1Val[1][f1Pnt] > f2Val[1][f2Pnt])	//각 항의 지수를 비교해 연산 여부 결정
		{
			result[0][pointer] = f1Val[0][f1Pnt];
			result[1][pointer] = f1Val[1][f1Pnt];
			f1Pnt++; pointer++;
		}
		else if (f1Val[1][f1Pnt] == f2Val[1][f2Pnt])
		{
			result[0][pointer] = f1Val[0][f1Pnt] + f2Val[0][f2Pnt];
			result[1][pointer] = f1Val[1][f1Pnt];
			f1Pnt++; f2Pnt++; pointer++;
		}
		else
		{
			result[0][pointer] = f2Val[0][f2Pnt];
			result[1][pointer] = f2Val[1][f2Pnt];
			f2Pnt++; pointer++;
		}
	}


	////test code
	//for (int i = 0; i < f1Len; i++) {
	//	printf("계수: %d 지수:%d ", f1Val[0][i], f1Val[1][i]);
	//}
	//printf("\n");

	//for (int i = 0; i < f2Len; i++) {
	//	printf("계수: %d 지수:%d ", f2Val[0][i], f2Val[1][i]);
	//}

	//printf("\n결과 \n");
	//for (int i = 0; i < resultLen; i++){
	//	printf("계수: %d 지수:%d ", result[0][i], result[1][i]);
	//}
	//printf("\n");
	
	print(result, resultLen);	//결과 출력
	printf("\n");
}

// 항의 수 파악
int check(char value[])
{
	int para = 0;
	int result = 0;
	while (1){
		if (*(value + para) == '\0')	break;	//문자열의 끝
		else if ((*(value + para) == '+' || *(value + para) == '-')&&para) result++;	//para번째 원소가 +,-이고 para가 0이 아닌(첫번째 문자) 경우
		para++;	//다음 글자로 이동
	}

	return result+1;
}

// 문자를 숫자로 변환 (숫자가 아닌경우 -1(None)을 반환)
int convertC2I(char input)
{
	if (input >= '0' && input <= '9')	return input - '0';
	else{
		return None;
	}
}

// 문자열에서 계수, 지수를 추출해 target 배열에 저장
void extractor(char* origin ,int * fomula[])	// origin: 식(string), fomula: 추출값을 저장할 위치
{
	int flagPnt[2] = { 0,0 };	//동적 배열에 저장을위한 포인터 역할 변수
	int flag = 0;		//지수 계수 구분 flag (계수:0, 지수:1)
	int data = None;
	int sign = Plus;

	if (origin[0]=='-') sign = Minus;	//첫 항이 음수인 경우 sign 값 변경
	
	for (int i = 0; i < 100; i++){
		if (convertC2I(origin[i]) != None){	//숫자여부 확인
			if (data == None)	data = 0;
			data *= 10;
			data += convertC2I(origin[i]);
		}
		else { //Operator, '\0', 변수(x)를 만난 경우
			if (data == None)	continue;

			*(fomula[flag] + flagPnt[flag]) = data*sign;	//값을 부호처리한 뒤, 배열에 저장
			sign = Plus;	//부호 초기화(지수부에서는 +를 별도로 표기하지 않기 때문)
			flagPnt[flag] += 1;
			data = None;

			//부호 뒤는 항상 계수 -> flag를 0(계수)로 설정 (지수가 음수일때는 고려하지 않았음)
			if (origin[i] == '-') {
				flag = 0;	
				sign = Minus;
			}
			else if (origin[i] == '+') {
				flag = 0;
				sign = Plus;
			}
			else if (origin[i] == 'x')	flag = 1;	//x 뒤는 항상 지수 -> flag를 1(지수)로 설정
			else if (origin[i - 1] == '\0')	break;
		}
	}
}

//result 배열을 식의 형태로 출력
void print(int *array[], int length)
{
	for (int i = 0; i < length; i++){
		printf("%dx^%d ", array[0][i], array[1][i]);
		if (i < length - 1 && array[0][i+1] >= 0)	printf("+ ");
	}
}
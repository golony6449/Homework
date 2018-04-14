#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define None -1
#define Pop -2
#define True 1
#define False 0
#define MAX_LENGTH 100

typedef struct {
	int *stack;
	int Pnt;
	int length;
}_Stack;

void initStack(char *, _Stack *);	// Stack 초기화
void mkpostFix(char *data, int *);	// 후위연산식으로 변환
void push(int, _Stack *,int);	//Push 수행
int pop(_Stack *);	//Pop 수행
int checkTop(_Stack *);	// 포인터 이동 없이, Top의 값 출력
int convertC2I(char);	// 문자를 숫자로 변환 (숫자가 아닌경우 -1(None)을 반환)
int calc(int *);	//실제 계산 수행
int checkPriority(char data, _Stack *value, int);	//우선순위 판별

int main()
{
	char input[MAX_LENGTH];
	int preFix[MAX_LENGTH];	//후위연산식 배열
	printf("계산기 입니다. \n");
	printf("식을 입력해주세요.: ");
	scanf_s("%s", input, 100);

	mkpostFix(input,preFix);	//후위연산식 생성

	//후위연산식 출력
	for (int i = 0; preFix[i] != None; i++) {
		if (preFix[i] > 9) {
			if (preFix[i] != '(' && preFix[i] != ')') printf("%c", preFix[i]);	//괄호를 제외한 연산자의 경우
		}
		else printf("%d", preFix[i]);	//숫자의 경우
	}
	printf("\n결과: %d \n", calc(preFix));
}

// Stack 초기화
void initStack(char *data, _Stack *value)
{
	int length = 0;
	int index = 0;
	int extra = 0;

	while (1) {
		if (data[index] != '\0') {
			length++;
			if (data[index] == '+' || data[index] == '-' || data[index] == '*' || data[index] == '/') extra++;	//글자 구분용 공백 추가
		}
		else break;
		index++;
	}

	value->length = length + (extra * 2);	//추후 삽입된 공백 고려한
	value->Pnt = -1;	//Empty 상태의 포인터
	value->stack = (int*)malloc(length * sizeof(int));
}

// 후위연산식으로 변환
void mkpostFix(char *data, int *target)
{
	int val[100];
	int valPnt = 0;
	int bracketChecker;
	_Stack operator;

	initStack(data, &operator);

	for (int i = 0; data[i]!='\0' ; i++) {
		if (convertC2I(data[i]) != None) val[valPnt++]=convertC2I(data[i]);	//data[i]가 숫자인 경우
		else {
			val[valPnt++] = ' ';	//구분용 공백 삽입
			while (1) {
				if (checkPriority(data[i], &operator,None) == None) {	//push여부 결정
					push(data[i], &operator, False);
					break;
				}
				else if (checkPriority(data[i], &operator,Pop) == Pop) {	//pop여부 결정
					val[valPnt++] = pop(&operator);
				}
				else {
					push(data[i], &operator, False);
					break;
				}
			}}}

	int temp = operator.Pnt;
	while (checkTop(&operator) != None)
		val[valPnt++] = pop(&operator);	//남은 연산자 처리

	val[valPnt++] = None;	//문자열의 끝임을 알림
	memcpy(target, val, valPnt*sizeof(int));	//매개변수에 배열을 복사
}

// Push 수행 (단, data가 문자형인 경우 ASCII 값 그대로 저장 (추후 10 이상의 정수이면 연산자로 간주)
void push(int data, _Stack *value,int intFlag)
{
	if (value->Pnt == value->length - 1)	return;
	else {
		value->Pnt = value->Pnt + 1;

		// calc 함수에서의 Stack은 10 자릿수 이상의 값을 입력받고, 연산자는 push하지 않기 때문에 intFlags에 True(1)을 줌으로서, data를 변환하지 않고 저장
		if (intFlag == True)	value->stack[value->Pnt] = data;
		else if (convertC2I(data) == None) value->stack[value->Pnt] = data;
		else value->stack[value->Pnt] = convertC2I(data);
	}
}

//Pop 수행
int pop(_Stack *value)
{
	if (value->Pnt == -1)	return None;
	else	return value->stack[value->Pnt--];
}

// 포인터 이동 없이, Top의 값 출력
int checkTop(_Stack *value)
{
	if (value->Pnt == None) return None;
	else return value->stack[value->Pnt];
}

// 문자를 숫자로 변환 (숫자가 아닌경우 -1(None)을 반환)
int convertC2I(char input)
{
	if (input >= '0' && input <= '9')	return input - '0';
	else {
		return None;
	}
}

//실제 연산 수행
int calc(int *value)
{
	int temp = 0, firstValue, secondValue, total = 0;
	int Index = 0;
	_Stack calcStack;
	initStack("                   ", &calcStack);	//20개의 문자를 가지는 스택으로 초기화

	while (1) {
		if (value[Index] == None) break;
		//피연산자 (숫자)의 경우
		else if(value[Index] < 10) {
			while (value[Index] < 10) {
				temp = temp * 10 + value[Index];
				Index++;
			}
			push(temp, &calcStack, True);
			temp = 0;
		}
		//연산자인 경우
		else if (value[Index] == ' ' || value[Index] == '(' || value[Index] == ')') Index++;
		else if(value[Index] > 9) {
			secondValue = pop(&calcStack);
			firstValue = pop(&calcStack);

			switch (value[Index]) {
			case '*': total = firstValue * secondValue; break;
			case '/': total = firstValue / secondValue; break;
			case '+': total = firstValue + secondValue; break;
			case '-': total = firstValue - secondValue; break;
			}
			push(total, &calcStack, True);
			Index++;
		}
		else Index++; 
	}
	return total;
}

//우선순위 판별
int checkPriority(char data,_Stack *value, int isPop)
{
	int topPriority, dataPriority;
	char temp = checkTop(value);

	if (temp == None) return None;	//Stack이 비어있는 경우

	//Pop 수행 여부 결정
	if (isPop == Pop) {
		switch (temp) {
		case '(': case ')': topPriority = 0; break;
		case '-': case '+': topPriority = 1; break;
		case '/': case '*': topPriority = 2; break;
		}

		switch (data) {
		case '(': case ')': dataPriority = 0; break;
		case '-': case '+': dataPriority = 1; break;
		case '/': case '*': dataPriority = 2; break;
		}
	}
	//Push 여부 결정
	else {
		switch (temp) {
		case ')': topPriority = 0;	break;
		case '-': case '+': topPriority = 1; break;
		case '/': case '*': topPriority = 2; break;
		case '(': topPriority = 2; break;
		}

		switch (data) {
		case ')': dataPriority = 0; break;
		case '-': case '+': dataPriority = 1; break;
		case '/': case '*': dataPriority = 2; break;
		case '(': dataPriority = 3; break;
		}
	}
	if (dataPriority>topPriority)	return None;
	else return Pop;
}
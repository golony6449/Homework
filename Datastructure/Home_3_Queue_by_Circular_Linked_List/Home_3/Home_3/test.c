//#include <stdio.h> 
//#include <stdlib.h> 
//#include<string.h>
//typedef struct {   /* 연결 큐의 struct 원소 타입 */
//	int  id;
//}element;
//
//typedef struct queueNode {   /* 연결 큐의 노드 타입 */
//	element   data;
//	struct queueNode* link;
//} queueNode;
//
//typedef struct {   /* 연결 큐 데이타 타입 */
//	queueNode*  front;   /* 삭제연산 포인터 */
//	queueNode*  rear;    /* 삽입연산 포인터 */
//	int  length;   /* 큐(리스트)의 원소 수를 표현 */
//}linkedQueue;
//
//linkedQueue* createQ() {
//	/* 연결 큐(q)를 생성하고 초기화  */
//	linkedQueue* q;
//	q = (linkedQueue*)malloc(sizeof(linkedQueue));
//	q->front = NULL;
//	q->rear = NULL;
//	q->length = 0;
//	return q;
//}
//
//int isEmpty(linkedQueue* q) {
//	/* 연결 큐가 공백인가를 검사 */
//	return (q->length == 0);
//}
//
//void enqueue(linkedQueue* q, element item) {
//	/* 연결 큐에 원소를 삽입 */
//	queueNode* newNode;
//	newNode = (queueNode*)malloc(sizeof(queueNode));
//	newNode->data = item;
//
//	if (q->length == 0) {   /* 연결 큐가 공백인 경우 */
//		newNode->link = newNode;
//		q->front = q->rear = newNode;
//	}
//	else {
//		newNode->link = q->front;//sakljfa;lksdjf;laksjdf;lkasjd;flkajs;dlkfja;lskdfja;lksdjf;lkasjdf;lkasjf;lkasjd;fkasdjf
//		q->rear->link = newNode;
//		q->rear = newNode;
//	}
//	printf("enqueue한값 %d\n", item);
//	q->length++;
//}
//
//void dequeue(linkedQueue* q) {
//	/* 연결 큐에서 원소를 삭제하고 반환 */
//	queueNode* temp;
//	element item;
//	if (q->length == 0) {    /* 연결 큐가 공백인 경우 */
//		printf("Queue is empty\n");
//		exit(1);
//	}
//	else {
//		item = q->front->data;
//		temp = q->front;
//		q->front = q->front->link;
//		//if (q->front->link == q->front) { /*q->front = NULL; q->rear = NULL;*/ }
//		//else q->front->link = temp->link;//if (q->front == NULL) q->rear = NULL;//
//		q->length--;
//		free(temp);    /* 삭제된 노드를 반환 */
//		printf("dequeue한 값 : %d\n", item);
//		//return item;
//		if (q->length==0) { q->front = NULL; q->rear = NULL; }
//	}
//}
//
//
//void main() {
//	element item;
//	linkedQueue* q;
//	q = createQ();
//	item.id = 3;
//	enqueue(q, item);
//	item.id = 5;
//	enqueue(q, item);
//	item.id = 7;
//	enqueue(q, item);
//	item.id = 9;
//	enqueue(q, item);
//	dequeue(q);
//	dequeue(q);
//	dequeue(q);
//
//
//	system("pause");
//}
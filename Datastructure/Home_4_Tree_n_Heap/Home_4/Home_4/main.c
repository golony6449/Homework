// Array의 0번 Index부터 값 저장	=> Tree 구조체의 tree에 접근하는 모든 경우에 해당 Value-1 처리
// 전제조건: 키값은 0

#include <stdio.h>
#include <stdlib.h>

#define LEN 31
#define INIT 1
#define TREE -1
#define HEAP -2

typedef struct _Tree {
	int level;
	int nodeCnt;
	int Structure;
	int lastPnt;	//Heap 구조에서 마지막에 삽입된 Index값 저장
	int *tree;		//Array 기반 구조
}Tree;

int countNode(int);				//레벨 수가 주어졌을때, 노드수 계산 후 반환
void insert(Tree*, int);		//object, target
void change(Tree*, int, int);	//트리에서 해당 인덱스 끼리 값 변경
void init(Tree *, int, int);	//트리 구조체 초기화 (매개변수: 해당 구조체, 레벨수, 형태(TREE, HEAP))
void inOrder(Tree, int);		//중위순회
void preOrder(Tree, int);		//전위순회
void postOrder(Tree, int);		//후위순회
void delete(Tree*);				//HEAP에서 루트 노드 출력 후 삭제하고 재정렬 수행

int main() {
	Tree tree;
	Tree heap;
	int level = 4;	// 1부터 카운트

	init(&tree, level, TREE);	//트리로 초기화
	init(&heap, level, HEAP);	//Heap으로 초기화

	int List[] = { 29,16,45,19,6,25,47,2,8,43,39,44,37,5,48};	//python으로 생성한 난수 값
	for (int i = 0; i < 15; i++) {
		insert(&tree, List[i]);
		insert(&heap, List[i]);
	}
	printf("Tree구조\n");

	inOrder(tree,INIT);
	preOrder(tree,INIT);
	postOrder(tree,INIT);

	printf("\n\nHeap구조\n");

	inOrder(heap, INIT);
	preOrder(heap, INIT);
	postOrder(heap, INIT);

	printf("\n\n(번외) 힙을 이용한 정렬\n");
	for (int i = 0; i < heap.nodeCnt; i++) {
		delete(&heap);
	}
	system("pause");
}

int countNode(int level) {
	int Cnt = 1;
	for (int i = 0; i < level; i++) {
		Cnt = Cnt * 2;
	}
	return Cnt - 1;	// (2^n -1)
}

void insert(Tree* obj, int number) {
	int currentPnt;
	int parentPnt;

	if (obj->Structure == TREE) {
		parentPnt = 1;

		while (1) {
			if (parentPnt > obj->nodeCnt) {
				printf("TreeInsertError: Overflow occured during insert %d\n",number);
				return;
			}

			if (obj->tree[parentPnt - 1] == 0) { //해당 노드가 존재 하지 않는 Case
				obj->tree[parentPnt - 1] = number;
				return;
			}
			else if (number < obj->tree[parentPnt - 1]) parentPnt = parentPnt * 2;			//현재 노드의 키 보다 추가하려는 키가 작은 경우
			else if (obj->tree[parentPnt - 1] < number) parentPnt = (parentPnt * 2) + 1;	//현재 노드의 키 보다 추가하려는 키가 큰 경우
		}
	}

	if (obj->Structure == HEAP) {
		if (obj->lastPnt-1 == obj->nodeCnt) {
			printf("HeapInsertError: Overflow occured during insert %d\n",number);
			return;
		}

		currentPnt = obj->lastPnt;
		obj->lastPnt++;
		
		// lastPnt(=currentPnt)는 1부터 카운트하기 때문에 currentPnt-1을 index로 사용. 
		// 또한, heap은 완전 이진트리 => lastPnt 순으로 저장
		obj->tree[currentPnt - 1] = number;

		if (currentPnt == 1) return;	//첫 노드의 경우

		while (currentPnt != 1) {
			if (obj->tree[currentPnt-1] > obj->tree[(currentPnt / 2)-1]){
				change(obj, currentPnt - 1, (currentPnt / 2) - 1);	//부모 노드와, 왼쪽 자식 노드 간 자리변경
				currentPnt = currentPnt / 2;						//상위 레벨로 이동
			}
			else 
				return;
		}
	}
}

void change(Tree* obj, int targetIndex, int tobeIndex) {
	int temp = obj->tree[tobeIndex];
	int temp2 = obj->tree[targetIndex];
	obj->tree[tobeIndex] = obj->tree[targetIndex];
	obj->tree[targetIndex] = temp;
}

void init(Tree *obj, int level, int structure) {
	obj->level = level;					//레벨 수 저장
	obj->nodeCnt = countNode(level);	//노드 수 저장
	obj->tree = (int*)malloc(sizeof(int)*obj->nodeCnt);
	obj->Structure = structure;		//구조 저장
	obj->lastPnt = 1;				//1부터 시작 -> 배열의 index는 0 부터 이므로 tree에 대한 인덱스로 사용시에는 -1 한 뒤 사용

	for (int i = 1; i < obj->nodeCnt + 1; i++) {
		obj->tree[i - 1] = 0; // 모든 키가 양수라고 가정함 => 0이면 비어있는 노드라고 간주
	}

}

void inOrder(Tree obj,int current) {
	if (current == INIT) printf("\n중위순회\n");
	if (current <= obj.nodeCnt) {
		inOrder(obj, current * 2);			//왼쪽 자식 노드
		if (obj.tree[current - 1] != 0) printf("%d  ", obj.tree[current - 1]);	//배열은 0번부터 시작
		inOrder(obj, (current * 2) + 1);	//오른쪽 자식 노드
	}
	else {
		// 해당 노드가 존재하지 않음
		return;
	}
}

void preOrder(Tree obj, int current) {
	if (current == INIT) printf("\n전위순회\n");
	if (current <= obj.nodeCnt) {
		if (obj.tree[current - 1] != 0) printf("%d  ", obj.tree[current - 1]);	//배열은 0번부터 시작
		preOrder(obj, current * 2);			//왼쪽 자식 노드
		preOrder(obj, (current * 2) + 1);	//오른쪽 자식 노드
	}
	else {
		// 해당 current 번호를 가지는 노드가 없음
		return;
	}
}

void postOrder(Tree obj, int current) {
	if (current == INIT) printf("\n후위순회\n");
	if (current <= obj.nodeCnt) {
		postOrder(obj, current * 2);		//왼쪽 자식 노드
		postOrder(obj, (current * 2) + 1);	//오른쪽 자식 노드
		if (obj.tree[current - 1] != 0) printf("%d  ", obj.tree[current - 1]);
	}
	else {
		return;
	}
}

void delete(Tree* obj) {
	int Pnt = 1;
	printf("%d ", obj->tree[0]);

	obj->tree[0] = 0;	// 루트 노드 값 삭제

	// 재정렬
	while (Pnt * 2 < obj->nodeCnt) {					//다음 레벨이 존재하는 동안 반복 (= 존재하지 않으면 중단)
		if (obj->tree[Pnt * 2 -1] < obj->tree[(Pnt * 2 + 1) -1]) {
			change(obj, Pnt - 1, (Pnt * 2 + 1) - 1);	// 부모와 오른쪽 자식노드간 자리 변경 //-1 연산 이유: 배열의 index는 0부터 but Pnt는 1부터 시작되기 때문
			Pnt = Pnt * 2 + 1;							// 위치이동
		}
		else if (obj->tree[Pnt * 2 - 1] > obj->tree[(Pnt * 2 + 1) - 1]) {
			change(obj, Pnt - 1, (Pnt * 2) - 1);	// 부모와 왼쪽 자식노드간 자리 변경 //-1 연산 이유: 배열의 index는 0부터 but Pnt는 1부터 시작되기 때문
			Pnt = Pnt * 2;							// 위치이동
		}
		else {	//하위 자식이 존재하지 않는(0인) 경우
			break;
		}
	}
}
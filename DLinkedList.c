#define _CRT_SECURE_NO_WARNINGS
#include "DLinkedList.h"

//DLinkedList에 있는 head는 각 자료의 끝과 처음을 잡아준다. (마지막 -> head -> 처음 -> ... -> 마지막 -> head) 반복

//추가할 때에는 추가할 자료(ptr)의 next,prev를 먼저 연결시킨다.
//이후 양 옆(왼쪽 자료일 경우 (이전 자료)->next, 오른쪽 자료일 경우 (다음 자료)->prev의 값(주소)를 추가할 자료(ptr의 주소)로 넣는다 

DLinkedList* createDLinkedList() {
	DLinkedList* temp;
	temp = (DLinkedList*)malloc(sizeof(DLinkedList));

	temp->head.prev = &(temp->head);
	temp->head.next = &(temp->head);
	temp->size = 0;

	return temp;
}
void deleteFirstDLinkedList(DLinkedList* dl) {
	PointType* temp = dl->head.next;

	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;

	dl->size--;

	free(temp);
}

void destroyDLinkedList(DLinkedList* dl) {
	PointType* temp = dl->head.next;
	PointType* fPtr;

	for (int i = 0; i < dl->size; i++) {
		fPtr = temp;
		temp = temp->next;
		free(fPtr);
	}

	free(dl);
}

int sizeDLinkedList(DLinkedList* dl) {
	return dl->size;
}


int insertFirstDLinkedList(DLinkedList* dl, int x, int y) {
	PointType* nPtr = (PointType*)malloc(sizeof(PointType));
	nPtr->x = x;
	nPtr->y = y;

	nPtr->prev = &(dl->head);
	nPtr->next = dl->head.next;

	nPtr->next->prev = nPtr;
	dl->head.next = nPtr;
	
	dl->size++;

	return 1;
}
int insertLastDLinkedList(DLinkedList* dl, int x, int y) {
	PointType* nPtr = (PointType*)malloc(sizeof(PointType));
	nPtr->x = x;
	nPtr->y = y;

	nPtr->prev = dl->head.prev;
	nPtr->next = &(dl->head);

	dl->head.prev->next = nPtr;
	dl->head.prev = nPtr;

	dl->size++;

	return 1;
}
void printDLinkedList(DLinkedList* dl) {

	PointType* start = dl->head.next;

	for (int i = 0; i < dl->size; i++) {
		printf("[%d] x: %d y: %d\n",i ,start->x, start->y);
		start = start->next;
	}
}

DLinkedList* insertAtDLinkedList(DLinkedList* dl, int at, int x, int y) {
	if (at >= 0 && at <= dl->size) {

		if (at == 0) {
			insertFirstDLinkedList(dl, x, y);
			return dl;
		}
		else if (at == dl->size) {
			insertLastDLinkedList(dl, x, y);
			return dl;
		}

		PointType* nPtr = (PointType*)malloc(sizeof(PointType));
		nPtr->x = x;
		nPtr->y = y;

		PointType* temp = dl->head.next;
		for (int i = 0; i < at - 1; i++) {
			temp = temp->next;
		}

		nPtr->prev = temp;
		nPtr->next = temp->next;

		nPtr->next->prev = nPtr;
		temp->next = nPtr;

		dl->size++;

		return dl;
	}
}
extern PointType deleteAtDLinkedList(DLinkedList* dl, int at) {
	if (at >= 0 && at < dl->size) {
		PointType delete;

		if (at == 0) {
			delete = *(dl->head.next);
			printf("삭제된 값 = x: %d, y: %d\n", dl->head.next->x, dl->head.next->y);
			deleteFirstDLinkedList(dl);
			return delete;
		}

		PointType* fPtr;

		PointType* temp = dl->head.next;
		for (int i = 0; i < at - 1; i++) {
			temp = temp->next;
		}

		fPtr = temp->next;
		delete = *fPtr;

		fPtr->next->prev = fPtr->prev;
		fPtr->prev->next = fPtr->next;
		printf("삭제된 값 = x: %d, y: %d\n", delete.x, delete.y);


		free(fPtr);
		dl->size--;

		return delete;
	}
}

void StartDLinkedList() {
	struct DLinkedList* List = createDLinkedList();
	int finish = -1;
	int menu;

	while (finish != 0) {

		int index, x, y = 0;

		printf("\n");
		printf("1. 맨 앞에 추가: 정수를 입력받아 리스트의 가장 앞에 삽입\n");
		printf("2. 맨 뒤에 추가: 정수를 입력받아 리스트의 가장 뒤에 삽입\n");
		printf("3. 특정 위치에 추가: 위치(index)와 정수를 입력받아 해당 위치에 삽입\n");
		printf("4. 특정 위치 삭제: 위치(index)를 입력받아 해당 노드를 삭제하고 값 출력\n");
		printf("5. 전체 목록 출력: 현재 리스트에 저장된 모든 정수를 순서대로 출력\n");
		printf("6. 리스트 크기 확인: 현재 저장된 노드의 총 개수를 출력\n");
		printf("0. 종료: 모든 메모리를 해제(destroy)하고 프로그램을 종료\n\n");

		printf("메뉴를 선택하세요 : ");

		scanf("%d", &menu);

		switch (menu) {

		case 1:
			printf("x, y값을 입력하세요 : ");
			scanf("%d,%d", &x, &y);
			insertFirstDLinkedList(List, x, y);
			break;
		case 2:
			printf("x, y값을 입력하세요 : ");
			scanf("%d,%d", &x, &y);
			insertLastDLinkedList(List, x, y);
			break;
		case 3:
			printf("추가할 위치(index)를 입력하세요 : ");
			scanf("%d", &index);
			printf("x, y값을 입력하세요 : ");
			scanf("%d,%d", &x, &y);
			insertAtDLinkedList(List, index, x, y);
			break;
		case 4:
			printf("삭제할 위치(index)를 입력하세요 : ");
			scanf("%d", &index);
			deleteAtDLinkedList(List, index);
			break;
		case 5:
			printDLinkedList(List);
			break;
		case 6:
			printf("현재 저장된 노드의 수 : %d", sizeDLinkedList(List));
			break;
		case 0:
			printf("프로그램을 종료합니다.");
			destroyDLinkedList(List);
			finish = 0;
			break;
		}
	}
}


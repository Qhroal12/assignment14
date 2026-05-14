#include <stdio.h>
#include <stdlib.h>

typedef struct PointType {
	int x;
	int y;
	struct PointType* prev;
	struct PointType* next;

}PointType;

typedef struct DLinkedList {
	PointType head;
	int size;

}DLinkedList;

extern DLinkedList* createDLinkedList();
extern void deleteFirstDLinkedList(DLinkedList* dl);

extern int sizeDLinkedList();
extern void printDLinkedList(DLinkedList* dl);
extern void destroyDLinkedList(DLinkedList* dl);


extern int insertFirstDLinkedList(DLinkedList* dl, int x, int y);
extern int insertLastDLinkedList(DLinkedList* dl, int x, int y);
extern DLinkedList* insertAtDLinkedList(DLinkedList* dl, int at, int x, int y);
extern PointType deleteAtDLinkedList(DLinkedList* dl, int at);
extern void StartDLinkedList();
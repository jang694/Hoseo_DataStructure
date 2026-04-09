#include <stdio.h>
#include <stdbool.h>
#define SIZE 30
typedef struct {
	int data[SIZE];
	int front;
	int rear;
}LinearQueue;

//초기화 함수
void initQueue(LinearQueue* q) {
	q->front = 0;
	q->rear = -1;
}

//큐가 비어있는지 확인
bool isEmpty(LinearQueue* q) {
	return q->rear < q->front; // rear가 front보다 작으면 비어 있음
}

//큐가 가득 찼는지 확인
bool isFull(LinearQueue* q) {
	return q->rear == SIZE - 1; // rear가 배열 끝에 도달하면 가득 참
}

//삽입 함수
bool enqueue(LinearQueue* q, int value) {
	if (isFull(q)) {
		printf("큐가 가득 찼습니다.");
		return false;
	}
	q->rear++;
	q->data[q->rear] = value; // rear 위치에 데이터 추가
}

//삭제 함수
int dequeue(LinearQueue* q) {
	if (isEmpty(q)) {
		printf("큐가 비어있습니다");
		return -1;
	}
	int value = q->data[q->front];
	q->front++;
	return value;
}

int main() {
	LinearQueue q;
	initQueue(&q);
	int c = 1;
	int i = 0;



	while (1) {
		printf("1.삽입, 2.삭제, 3.데이터 출력, 4.종료\n");
		scanf("%d", &c);
		switch (c)
		{
		case 1:
		{
			printf("삽입할 데이터를 입력하시오\n");
			scanf("%d", &i);
			enqueue(&q, i);
			break;
		}
		case 2:
		{
			printf("데이터를 삭제합니다\n");
			dequeue(&q);
			break;
		}
		case 3:
		{
			if (isEmpty(&q)) {
				printf("큐가 비어있어 출력할 데이터가 없습니다.\n");
			}
			else {
				printf("현재 큐 데이터: ");
				// front부터 rear까지 순서대로 출력합니다.
				for (int k = q.front; k <= q.rear; k++) {
					printf("%d ", q.data[k]);
				}
				printf("\n");
			}
			break;
		}
		case 4:
		{
			printf("프로그램을 종료합니다. 안녕히 가세요!\n");
			break; 
		}

		default:
			printf("번호를 잘 못 입력하셨습니다");
			break;
		}
	}
	return 0;
}

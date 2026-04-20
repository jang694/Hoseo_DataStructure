#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10  

typedef struct {
    char documentName[50];
    int numPages;
} PrintJob;

typedef struct {
    PrintJob queue[SIZE];
    int front;
    int rear;
} PrintQueue;

void initQueue(PrintQueue* q) {
    q->front = 0;
    q->rear = 0;
}

bool isEmpty(PrintQueue* q) {
    return q->front == q->rear;
}

bool isFull(PrintQueue* q) {
    return (q->rear + 1) % SIZE == q->front;
}

// [조건 1] enqueue 함수 수정: 50장 초과 제한
bool enqueue(PrintQueue* q, char* documentName, int numPages) {
    if (numPages > 50) { // 1-a, 1-b 조건 반영
        printf("거부: '%s'은(는) 50장을 초과하여 등록할 수 없습니다.\n", documentName);
        return false;
    }
    if (isFull(q)) {
        printf("대기열이 가득 찼습니다.\n");
        return false;
    }
    strcpy(q->queue[q->rear].documentName, documentName);
    q->queue[q->rear].numPages = numPages;
    q->rear = (q->rear + 1) % SIZE;
    printf("작업 '%s' (%d 페이지) 추가 완료.\n", documentName, numPages);
    return true;
}

// [조건 2] cancelJob 함수 추가: 특정 문서 삭제 및 당기기
void cancelJob(PrintQueue* q, char* targetName) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있어 취소할 수 없습니다.\n");
        return;
    }

    int i = q->front;
    int foundIdx = -1;

    // 문서 찾기
    while (i != q->rear) {
        if (strcmp(q->queue[i].documentName, targetName) == 0) {
            foundIdx = i;
            break;
        }
        i = (i + 1) % SIZE;
    }

    if (foundIdx == -1) {
        printf("해당 문서가 없습니다.\n"); // 2-b 조건
        return;
    }

    // [조건 2-c] 데이터 한 칸씩 당기기
    int current = foundIdx;
    int next = (current + 1) % SIZE;

    while (next != q->rear) {
        q->queue[current] = q->queue[next];
        current = next;
        next = (next + 1) % SIZE;
    }

    q->rear = current; // 마지막 rear 위치 수정
    printf("작업 '%s'이(가) 취소되었습니다. 대기열을 재정렬합니다.\n", targetName);
}

// [조건 3] clearQueue 함수 추가: 전체 비우기
void clearQueue(PrintQueue* q) {
    initQueue(q); // 초기 상태로 되돌림
    printf("대기열 초기화\n"); // 3-c 조건
}

PrintJob dequeue(PrintQueue* q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        PrintJob emptyJob = { "", 0 };
        return emptyJob;
    }
    PrintJob job = q->queue[q->front];
    q->front = (q->front + 1) % SIZE;
    return job;
}

void printQueue(PrintQueue* q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }
    printf("\n--- 현재 대기열 상태 ---\n");
    int i = q->front;
    while (i != q->rear) {
        printf("- %s (%d 페이지)\n", q->queue[i].documentName, q->queue[i].numPages);
        i = (i + 1) % SIZE;
    }
}

int main() {
    PrintQueue q;
    initQueue(&q);

    int choice, numPages;
    char docName[50];

    while (true) {
        printf("\n1.작업추가 2.작업처리 3.대기열출력 4.인쇄취소 5.전체비우기 6.종료\n선택: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("문서 이름: "); scanf("%s", docName);
            printf("페이지 수: "); scanf("%d", &numPages);
            enqueue(&q, docName, numPages);
            break;
        case 2:
        {
            PrintJob job = dequeue(&q);
            if (strlen(job.documentName) > 0)
                printf("'%s' 처리 중...\n", job.documentName);
        }
        break;
        case 3: printQueue(&q); break;
        case 4:
            printf("취소할 문서 이름: "); scanf("%s", docName);
            cancelJob(&q, docName);
            break;
        case 5: clearQueue(&q); break;
        case 6: return 0;
        default: printf("잘못된 입력입니다.\n"); break;
        }
    }
}

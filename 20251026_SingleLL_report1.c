#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 새로운 노드 생성 함수 (테스트용 도우미 함수)
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 1. searchValue1: 특정 값의 위치(인덱스)를 반환
// 위치는 1부터 시작한다고 가정합니다. 찾지 못하면 -1 반환.
int searchValue1(Node* head, int val) {
    Node* curr = head;
    int index = 1;
    
    while (curr != NULL) {
        if (curr->data == val) {
            return index;
        }
        curr = curr->next;
        index++;
    }
    return -1;
}

// 2. searchValue2: 특정 값의 앞과 뒤 노드 값을 출력
void searchValue2(Node* head, int val) {
    Node* prev = NULL;
    Node* curr = head;
    
    while (curr != NULL) {
        if (curr->data == val) {
            printf("%d를 찾았습니다.\n", val);
            
            // 이전 노드 확인
            if (prev != NULL) printf("이전 노드의 값: %d\n", prev->data);
            else printf("이전 노드가 없습니다 (첫 번째 노드).\n");
            
            // 다음 노드 확인
            if (curr->next != NULL) printf("다음 노드의 값: %d\n", curr->next->next ? curr->next->data : curr->next->data); 
            // 위 문장은 단순하게 curr->next가 존재하면 curr->next->data 출력
            if (curr->next != NULL) printf("다음 노드의 값: %d\n", curr->next->data);
            else printf("다음 노드가 없습니다 (마지막 노드).\n");
            
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("%d 값을 리스트에서 찾을 수 없습니다.\n", val);
}

// 3. freeList: 모든 리스트 메모리 해제
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        printf("메모리 해제 중: %d\n", temp->data);
        free(temp);
    }
    printf("모든 메모리가 해제되었습니다.\n");
}

int main() {
    // 테스트용 연결 리스트 생성: 10 -> 20 -> 30 -> 40
    Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);

    // [함수 1 테스트]
    int val = 30;
    int pos = searchValue1(head, val);
    if (pos != -1) {
        printf("%d의 위치는 %d번째입니다.\n", val, pos);
    } else {
        printf("%d을(를) 찾지 못했습니다.\n", val);
    }

    printf("\n");

    // [함수 2 테스트]
    searchValue2(head, 30);

    printf("\n");

    // [함수 3 테스트] 리스트 전체 메모리 해제
    freeList(head);
    head = NULL;

    return 0;
}

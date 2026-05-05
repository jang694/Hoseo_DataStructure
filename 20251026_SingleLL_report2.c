#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 연락처 구조체 정의
typedef struct Node {
    char name[20];
    char phone[20];
    struct Node* next;
} Node;

Node* head = NULL;

// 1. 새로운 연락처 추가 (리스트 끝에 추가)
void addContact(char* name, char* phone) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("연락처가 추가되었습니다: %s\n", name);
}

// 2. 특정 이름의 연락처 검색
void searchContact(char* name) {
    Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("검색 결과 - 이름: %s, 전화번호: %s\n", temp->name, temp->phone);
            return;
        }
        temp = temp->next;
    }
    printf("%s 님을 찾을 수 없습니다.\n", name);
}

// 3. 특정 이름의 연락처 삭제
void deleteContact(char* name) {
    Node* temp = head;
    Node* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (prev == NULL) { // 첫 번째 노드를 삭제하는 경우
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("%s 님의 연락처가 삭제되었습니다.\n", name);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("삭제할 이름(%s)이 존재하지 않습니다.\n", name);
}

// 4. 현재 전화번호부 전체 출력
void printAll() {
    if (head == NULL) {
        printf("전화번호부가 비어있습니다.\n");
        return;
    }
    printf("\n--- 전화번호부 목록 ---\n");
    Node* temp = head;
    while (temp != NULL) {
        printf("이름: %s | 번호: %s\n", temp->name, temp->phone);
        temp = temp->next;
    }
    printf("----------------------\n");
}

int main() {
    // 테스트용 데이터
    addContact("홍길동", "010-1234-5678");
    addContact("김철수", "010-9876-5432");
    addContact("이영희", "010-1111-2222");

    printAll();

    searchContact("김철수");

    deleteContact("홍길동");
    
    printAll();

    return 0;
}

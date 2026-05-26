#include <stdio.h>
#include <stdlib.h>

// 1. 트리 노드 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 노드 생성 함수
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ---------------------------------------------------------
// 기존 작성 내용: 순회 및 트리 속성 함수들
// ---------------------------------------------------------
void preorder(TreeNode* node) {
    if (node != NULL) {
        printf("%d ", node->data);
        preorder(node->left);
        preorder(node->right);
    }
}

void inorder(TreeNode* node) {
    if (node != NULL) {
        inorder(node->left);
        printf("%d ", node->data);
        inorder(node->right);
    }
}

void postorder(TreeNode* node) {
    if (node != NULL) {
        postorder(node->left);
        postorder(node->right);
        printf("%d ", node->data);
    }
}

int getHeight(TreeNode* node) {
    if (node == NULL) return -1; // 간선 개수 기준 트리 높이 (루트만 있으면 0)
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countNodes(TreeNode* node) {
    if (node == NULL) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int countLeaves(TreeNode* node) {
    if (node == NULL) return 0;
    if (node->left == NULL && node->right == NULL) return 1;
    return countLeaves(node->left) + countLeaves(node->right);
}

void freeTree(TreeNode* node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

// ---------------------------------------------------------
// [새롭게 추가할 3개의 함수 구현부]
// ---------------------------------------------------------

// 1. 각 노드가 가진 값의 총합을 계산하는 함수
int getSum(TreeNode* node) {
    if (node == NULL) return 0;
    // 현재 노드 값 + 왼쪽 서브트리 총합 + 오른쪽 서브트리 총합
    return node->data + getSum(node->left) + getSum(node->right);
}

// 2. 전체 트리 노드 중 최댓값을 가진 노드의 값 출력 함수
int getMax(TreeNode* node) {
    if (node == NULL) return -1; // 노드가 없을 경우 예외 처리 값
    
    int max = node->data;
    int leftMax = getMax(node->left);
    int rightMax = getMax(node->right);
    
    if (leftMax > max) max = leftMax;
    if (rightMax > max) max = rightMax;
    
    return max;
}

// 3. 두 값 사이의 값을 가진 노드 출력 함수 (전위 순회 방식 적용)
// (출력 예시 기준 '이상/이하'이므로 >=, <= 조건 사용)
void searchRange(TreeNode* node, int min, int max) {
    if (node == NULL) return;
    
    if (node->data >= min && node->data <= max) {
        printf("%d ", node->data);
    }
    
    searchRange(node->left, min, max);
    searchRange(node->right, min, max);
}


// ---------------------------------------------------------
// 메인 함수 (과제 이미지와 동일하게 구성)
// ---------------------------------------------------------
int main() {
    // 트리 구성
    TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(15);
    root->right->right = createNode(25);

    // 순회 출력
    printf("전위 순회: ");
    preorder(root);
    printf("\n");

    printf("중위 순회: ");
    inorder(root);
    printf("\n");

    printf("후위 순회: ");
    postorder(root);
    printf("\n\n");

    // 트리 속성 출력
    printf("트리 높이: %d\n", getHeight(root));
    printf("전체 노드 수: %d\n", countNodes(root));
    printf("리프 노드 수: %d\n\n", countLeaves(root));

    // [함수 추가 부분]
    printf("노드 값 총합: %d\n", getSum(root)); // 함수 호출
    printf("최댓값: %d\n\n", getMax(root));     // 함수 호출

    // 범위 검색
    printf("값이 6 이상 20 이하의 노드: ");
    searchRange(root, 6, 20);                  // 함수 호출
    printf("\n");

    freeTree(root);
    return 0;
}

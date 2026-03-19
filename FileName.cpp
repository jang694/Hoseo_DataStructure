#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 함수 선언
double calculateAverage(int scores[], int size);
int getStudentScore(int scores[], int size, int studentNumber);
void printScore(int scores[], int size, double avr, int option);
void deleteStudent(int* scores, int size, int studentNumber);

int main() {
    int* scores;
    int size = 30;
    int capacity = 30;
    int choice, studentNumber;
    int option;
    int score;
    double average;

    scores = (int*)malloc(capacity * sizeof(int));
    if (!scores) {
        printf("allocation error\n");
        return 1;
    }

    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        scores[i] = rand() % 101;
    }
    printf("입력 완료\n");

    while (1) {
        printf("---학생 성적 관리 프로그램---\n");
        printf("1. 학생정보 추가\n");
        printf("2. 학생정보 삭제\n");
        printf("3. 학생정보 검색\n");
        printf("4. 학생정보 출력(옵션 : 0,1,2)\n");
        printf("5. 프로그램 종료\n");
        scanf("%d", &choice);
        system("cls");

        switch (choice)
        {
        case 1: { //add
            if (capacity - size <= 5) {
                capacity += 10;
                int* newScores = (int*)realloc(scores, capacity * sizeof(int)); //int* newScores = realloc(scores, capacity * sizeof(int));
                if (!newScores) {                                                 //왜 안되나요?
                    printf("allocation error\n");
                    return 1;
                }
                scores = newScores;
            }
            int newScore = rand() % 101;
            scores[size] = newScore;
            size++;
            printf("새로운 학생 추가 : 번호 - %d, 점수 - %d\n", size, newScore);

            break;
        }
        case 2: //delete
            printf("삭제할 학생 번호 입력(1~%d):", size);
            scanf("%d", &studentNumber);
            deleteStudent(scores, size, studentNumber);
            break;
        case 3:
            printf("검색할 학생 번호 입력(1~%d):", size);
            scanf("%d", &studentNumber);
            score = getStudentScore(scores, size, studentNumber);
            if (score != -1) {
                printf("%d번 학생 점수: %d\n", studentNumber, score);
            }
            else {
                printf("해당 학생은 없는 학생입니다.\n");
            }
            break;
        case 4:
            scanf("%d", &option);
            average = calculateAverage(scores, size);
            printScore(scores, size, average, option);
            break;
        case 5:
            free(scores);
            break;
        default:
            printf("잘못된 입력\n");
            break;
        }
    }

    return 0;
}

// 평균 계산 함수
double calculateAverage(int scores[], int size) {
    int sum = 0;
    int count = 0; // 실제 점수가 있는 학생 수
    for (int i = 0; i < size; i++) {
        if (scores[i] != -1) { // [추가] 삭제된 학생은 계산 안 함
            sum += scores[i];
            count++;
        }
    }
    if (count == 0) return 0;
    return sum / (double)count;
}

// 특정 학생 점수 검색 함수
int getStudentScore(int scores[], int size, int studentNumber) {
    if (studentNumber >= 1 && studentNumber <= size) {
        if (scores[studentNumber - 1] == -1) return -1; // [추가] 삭제된 학생이면 -1 반환
        return scores[studentNumber - 1];
    }
    return -1;
}

//옵션은 정수이며, 0, 1, 2 세 개의 값 중 하나임. 0은 모든 학생, 1은 평균 이상 학생, 2는 평균 미만 학생
void printScore(int scores[], int size, double avr, int option) {
    if (option == 0) {
        for (int i = 0; i < size; i++) {
            printf("%d번 학생의 성적:%d\n", i + 1, scores[i]);
        }
    }
    else if (option == 1) {
        printf("평균 이상의 성적을 가진 학생들\n");
        for (int i = 0; i < size; i++) {
            if (scores[i] == -1) continue;
            if (scores[i] >= avr) {
                printf("%d번 학생의 성적:%d\n", i + 1, scores[i]);
            }
            
        }
    }
    else if (option == 2) {
        printf("평균 미만의 성적을 가진 학생들\n");
        for (int i = 0; i < size; i++) {
            if (scores[i] < avr) {
                printf("%d번 학생의 성적:%d\n", i + 1, scores[i]);
            }
        }
    }
}

void deleteStudent(int* scores, int size, int studentNumber) {
    if (studentNumber < 1 || studentNumber > size) {
        printf("학생 번호 오류\n");
    }
    if (scores[studentNumber - 1] == -1) {
        printf("삭제된 학생입니다.\n");
    }
    else {
        scores[studentNumber - 1] = -1;
        printf("%d 학생 삭제 완료\n",studentNumber);
    }
}
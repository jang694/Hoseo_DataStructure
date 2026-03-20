#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
    int korean;
    int english;
    int math;
    double average;
} Student;
// 함수 선언
void allAverage(Student* avr, int size, double allAvr);



int main() {
    Student students[30];
    int num = 0; //case 문 숫자
    int studentNumber;//학생번호
    int size = 30; //배열 크기
    double all = 0; //평균값 다 더한 값


    // 초기화: 점수 임의 설정
    for (int i = 0; i < 30; i++) {
        students[i].korean = rand() % 101;
        students[i].english = rand() % 101;
        students[i].math = rand() % 101;
        students[i].average = (students[i].korean + students[i].english + students[i].math) / 3.0;
    }
    while (1) {
        printf("---학생 성적 관리 프로그램---\n");
        printf("1.학생 정보 검색\n");
        printf("2.학생들 평균 검색\n");
        printf("3.흔적 지우기\n");
        printf("4.전체 학생 성적 출력\n");
        printf("5.종료\n");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            printf("검색할 학생의 번호를 입력하시오(1~30)>>");
            scanf("%d", &studentNumber);
            if (studentNumber >= 1 && studentNumber <= 30) {
                printf("%d번 학생:국어(%d), 영어(%d), 수학(%d), 평균(%f)\n", studentNumber, students[studentNumber-1].korean, students[studentNumber-1].english, students[studentNumber-1].math, students[studentNumber-1].average);
                break;
            }
            else {
                printf("존재하지 않는 번호입니다.\n");
                break;
            }
        case 2:
            allAverage(students, size, all);
            break;
        case 3:
            system("cls");
            break;
        case 4:
            for (int i = 0; i < size; i++) {
                printf("%d번 학생:국어(%d), 영어(%d), 수학(%d), 평균(%f)\n", i+1, students[i].korean, students[i].english, students[i].math, students[i].average);
            }
            break;
        case 5:
            return 0;

        default:
            printf("다시 번호를 입력해주세요.\n");
            break;
        }
    }
    return 0;
}

//전체 학생들 평균 계산함수
void allAverage(Student* avr, int size, double allAvr) {
    for (int i = 0; i < size; i++) {
        allAvr += avr[i].average;
    }
    printf("학생들의 전체 평균:%f\n",allAvr/size);

}

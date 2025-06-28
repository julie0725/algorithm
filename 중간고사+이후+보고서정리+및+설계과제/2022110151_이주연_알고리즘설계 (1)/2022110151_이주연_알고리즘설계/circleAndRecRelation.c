#include <stdio.h>
#include <math.h> // 수학 함수 사용 (sqrt제곱근, fabs절댓값)

// 직사각형 구조체 ------------------------------------------
// -> 왼쪽 아래 x, y좌표와 오른쪽 위 x, y좌표
typedef struct {
    double x1, y1;
    double x2, y2;
} Rectangle;

// 원 구조체 (중심 (x, y), 반지름 r)
typedef struct {
    double x, y;
    double r;
} Circle;

// 두 점 ((x1, y1)과 (x2, y2)) 사이의 거리 제곱 -------------
// 거리의 제곱 = (x2 - x1)^2 + (y2 - y1)^2
double disSquare(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1; //dx : x좌표 차이
    double dy = y2 - y1; //dy : y좌표 차이 

    double disSquare = dx*dx + dy*dy;  //거리의 제곱

    return disSquare;
}

//-----------------------------------------------------------
// 원이 직사각형 안에 완전히 포함되거나 접하는 경우 -1 반환
int isCircleIn(Rectangle r, Circle c) {
    // 1. 원이 직사각형 내에 완전히 포함되는지 체크
    // 만약 원의 왼쪽, 오른쪽, 아래, 위 경계가 모두 직사각형의 경계 안에 포함될 경우
    if (c.x - c.r >= r.x1 && c.x + c.r <= r.x2 &&
        c.y - c.r >= r.y1 && c.y + c.r <= r.y2) {
        return -1; // -1 반환
    }

    // 2. 원이 직사각형 바깥쪽에서 접하거나 꼭짓점에 접하는지 체크
    // 원의 중심으로부터 직사각형의 가장 가까운 점 closestX, closestY찾기
    double closestX = c.x;  //초기화
    // 만약 원의 중심이 직사각형 왼쪽 경계보다 작으면 
    if (c.x < r.x1) {
        closestX = r.x1; // 직사각형의 왼쪽 경계를 가장 가까운 x좌표로 설정하기
    } else if (c.x > r.x2) { // 만약 원이 중심이 직사각형 오른쪽 경계보다 크면 
        closestX = r.x2; // 직사각형의 오른쪽 경계를 가장 가까운 x좌표로 설정하기
    }

    double closestY = c.y; //초기화
    // 만약 원의 중심이 직사각형 아래쪽 경계보다 작으면
    if (c.y < r.y1) {   
        closestY = r.y1; //직사각형의 아래쪽 경계를 가장 가까운 y좌표로 설정하기 
    } else if (c.y > r.y2) { // 원의 중심이 직사각형 위쪽 경계보다 큰경우
        closestY = r.y2; //직사각형의 위쪽 경계를 가장 가까운 y좌표로 설정
    }

    // 원의 중심과 직사각형의 가장 가까운 점 사이의 거리 제곱
    double distCenterToRectSq = disSquare(c.x, c.y, closestX, closestY);
    double radiusSquare = c.r * c.r; //원 반지름 제곱 

    const double EPSILON = 1e-9;
    // 오차 범위 내에서 
    // 만약 거리가 반지름과 같으면 -> 원이 직사각형에 접하는 것으로 보고
    // () -> 부동소수점 오차 1e-9 고려한 것)
    if (fabs(distCenterToRectSq - radiusSquare) < EPSILON) {
        return -1; // -1 반환하기
    }
    
    // 보완) 1 2번 조건에서 해당되지 않는 내부 접촉 상황 고려
    // 3. 원의 중심이 직사각형 내부에 있으면서 완전히 포함되진 않고
    // 접하는 경우 체크하기 

    // 만약 원의 x중심좌표가 직사각형의 x 범위 안에 있을 경우에 
    // 입실론까지 고려하여 
    if (c.x + EPSILON >= r.x1 && c.x - EPSILON <= r.x2 ) {
        // 원의 아래쪽 경계 (c.y - c.r)가 직사각형 아래 변(r.y1)에 닿는지 체크
        // : c.y 와 r.y1 + c.r이 거의 일치하는지 체크 
        if (fabs(c.y - (r.y1 + c.r)) < EPSILON) return -1;
        // 원의 위쪽 경계 (c.y + c.r)과 직사각형 위 변(r.y2)에 닿는지 체크하기
        if (fabs(c.y - (r.y2 - c.r)) < EPSILON) return -1;
    }
    // 만약 원의 y중심좌표가 직사각형의 y 범위 안에 있을 경우에
    if (c.y + EPSILON >= r.y1 && c.y - EPSILON <= r.y2 ) {
        //원의 왼쪽 경계(c.x - c.r)가 직사각형에 왼쪽 변(r.x1)에 닿는지 체크
        if (fabs(c.x - (r.x1 + c.r)) < EPSILON) return -1;
        // 원의 오른쪽 경계(c.x + c.r)가 직사각형의 오른쪽 변(r.x2)에 닿는지 체크
        if (fabs(c.x - (r.x2 - c.r)) < EPSILON) return -1;
    }
    return 0; // 포함되지도, 접하지도 않을 경우에는 0 반환
}

// 직사각형이 원 안에 완전히 포함되거나 접하는 경우 1 반환
// 모든 직사각형의 꼭짓점이 원 안에 있거나 원의 경계에 있는 경우
int isRectIn(Rectangle r, Circle c) {
    double radiusSquare = c.r * c.r; // 원 반지름 제곱
    const double EPSILON = 1e-9; //발생하는 부동 소수점 오차를 고려하기 위해 epsilon 정의

    // 직사각형의 네 꼭짓점 정의하기
    double vertices[4][2] = {
        {r.x1, r.y1}, // 왼쪽 아래
        {r.x1, r.y2}, // 왼쪽 위
        {r.x2, r.y1}, // 오른쪽 아래
        {r.x2, r.y2}  // 오른쪽 위
    };

    int i;
    // 직사각형의 각 꼭짓점에 대해서 
    for (i = 0; i < 4; i++) {
        // 각 꼭짓점에서 원의 중심까지의 거리 제곱하기 
        double distToCenterSq = disSquare(vertices[i][0], vertices[i][1], c.x, c.y);

        // 만약 어떤 꼭짓점이든 원의 반지름 제곱보다 크다면 (오차 epsilon 고려해서)
        if (distToCenterSq > radiusSquare + EPSILON) {
            return 0; // 
        }
    }
    return 1; //모든 꼭짓점이 원 안에 있거나, 접하면 1 반환
}

// 최종 관계를 확인하는 함수
int checkRelation(Rectangle r, Circle c) {
    // 1. 원이 직사각형에 포함/접하면 -1 반환 (우선순위)
    if (isCircleIn(r, c) == -1) {
        return -1;
    }

    // 2. 직사각형이 원에 포함/접하면 1 반환
    if (isRectIn(r, c) == 1) {
        return 1;
    }

    // 3. 그 외의 경우 0 반환
    return 0;
}

int main() {
    Rectangle r;
    Circle c;

    // 직사각형 정보 입력
    printf("직사각형 입력 (x1 y1 x2 y2): ");
    scanf("%lf %lf %lf %lf", &r.x1, &r.y1, &r.x2, &r.y2);

    // x, y 좌표 정규화 (x1 <= x2, y1 <= y2)
    if (r.x1 > r.x2) { 
        double temp = r.x1; r.x1 = r.x2; r.x2 = temp; 
    }
    if (r.y1 > r.y2) { 
        double temp = r.y1; r.y1 = r.y2; r.y2 = temp; 
    }

    // 원 정보 입력
    printf("원 입력 (x y r): ");
    scanf("%lf %lf %lf", &c.x, &c.y, &c.r);

    // 관계 체크 및 결과 출력
    int result = checkRelation(r, c);

    if (result == 1) {
        printf("결과: 1\n");
        printf("직사각형이 원에 완전히 포함되거나 접한다\n");
    } else if (result == -1) {
        printf("결과: -1\n");
        printf("원이 직사각형에 완전히 포함되거나 접한다\n");
    } else {
        printf("결과: 0\n");
        printf("그렇지 않은 경우\n");
    }

    return 0;
}

#include <stdio.h>
#include <math.h> // ���� �Լ� ��� (sqrt������, fabs����)

// ���簢�� ����ü ------------------------------------------
// -> ���� �Ʒ� x, y��ǥ�� ������ �� x, y��ǥ
typedef struct {
    double x1, y1;
    double x2, y2;
} Rectangle;

// �� ����ü (�߽� (x, y), ������ r)
typedef struct {
    double x, y;
    double r;
} Circle;

// �� �� ((x1, y1)�� (x2, y2)) ������ �Ÿ� ���� -------------
// �Ÿ��� ���� = (x2 - x1)^2 + (y2 - y1)^2
double disSquare(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1; //dx : x��ǥ ����
    double dy = y2 - y1; //dy : y��ǥ ���� 

    double disSquare = dx*dx + dy*dy;  //�Ÿ��� ����

    return disSquare;
}

//-----------------------------------------------------------
// ���� ���簢�� �ȿ� ������ ���Եǰų� ���ϴ� ��� -1 ��ȯ
int isCircleIn(Rectangle r, Circle c) {
    // 1. ���� ���簢�� ���� ������ ���ԵǴ��� üũ
    // ���� ���� ����, ������, �Ʒ�, �� ��谡 ��� ���簢���� ��� �ȿ� ���Ե� ���
    if (c.x - c.r >= r.x1 && c.x + c.r <= r.x2 &&
        c.y - c.r >= r.y1 && c.y + c.r <= r.y2) {
        return -1; // -1 ��ȯ
    }

    // 2. ���� ���簢�� �ٱ��ʿ��� ���ϰų� �������� ���ϴ��� üũ
    // ���� �߽����κ��� ���簢���� ���� ����� �� closestX, closestYã��
    double closestX = c.x;  //�ʱ�ȭ
    // ���� ���� �߽��� ���簢�� ���� ��躸�� ������ 
    if (c.x < r.x1) {
        closestX = r.x1; // ���簢���� ���� ��踦 ���� ����� x��ǥ�� �����ϱ�
    } else if (c.x > r.x2) { // ���� ���� �߽��� ���簢�� ������ ��躸�� ũ�� 
        closestX = r.x2; // ���簢���� ������ ��踦 ���� ����� x��ǥ�� �����ϱ�
    }

    double closestY = c.y; //�ʱ�ȭ
    // ���� ���� �߽��� ���簢�� �Ʒ��� ��躸�� ������
    if (c.y < r.y1) {   
        closestY = r.y1; //���簢���� �Ʒ��� ��踦 ���� ����� y��ǥ�� �����ϱ� 
    } else if (c.y > r.y2) { // ���� �߽��� ���簢�� ���� ��躸�� ū���
        closestY = r.y2; //���簢���� ���� ��踦 ���� ����� y��ǥ�� ����
    }

    // ���� �߽ɰ� ���簢���� ���� ����� �� ������ �Ÿ� ����
    double distCenterToRectSq = disSquare(c.x, c.y, closestX, closestY);
    double radiusSquare = c.r * c.r; //�� ������ ���� 

    const double EPSILON = 1e-9;
    // ���� ���� ������ 
    // ���� �Ÿ��� �������� ������ -> ���� ���簢���� ���ϴ� ������ ����
    // () -> �ε��Ҽ��� ���� 1e-9 ����� ��)
    if (fabs(distCenterToRectSq - radiusSquare) < EPSILON) {
        return -1; // -1 ��ȯ�ϱ�
    }
    
    // ����) 1 2�� ���ǿ��� �ش���� �ʴ� ���� ���� ��Ȳ ���
    // 3. ���� �߽��� ���簢�� ���ο� �����鼭 ������ ���Ե��� �ʰ�
    // ���ϴ� ��� üũ�ϱ� 

    // ���� ���� x�߽���ǥ�� ���簢���� x ���� �ȿ� ���� ��쿡 
    // �ԽǷб��� ����Ͽ� 
    if (c.x + EPSILON >= r.x1 && c.x - EPSILON <= r.x2 ) {
        // ���� �Ʒ��� ��� (c.y - c.r)�� ���簢�� �Ʒ� ��(r.y1)�� ����� üũ
        // : c.y �� r.y1 + c.r�� ���� ��ġ�ϴ��� üũ 
        if (fabs(c.y - (r.y1 + c.r)) < EPSILON) return -1;
        // ���� ���� ��� (c.y + c.r)�� ���簢�� �� ��(r.y2)�� ����� üũ�ϱ�
        if (fabs(c.y - (r.y2 - c.r)) < EPSILON) return -1;
    }
    // ���� ���� y�߽���ǥ�� ���簢���� y ���� �ȿ� ���� ��쿡
    if (c.y + EPSILON >= r.y1 && c.y - EPSILON <= r.y2 ) {
        //���� ���� ���(c.x - c.r)�� ���簢���� ���� ��(r.x1)�� ����� üũ
        if (fabs(c.x - (r.x1 + c.r)) < EPSILON) return -1;
        // ���� ������ ���(c.x + c.r)�� ���簢���� ������ ��(r.x2)�� ����� üũ
        if (fabs(c.x - (r.x2 - c.r)) < EPSILON) return -1;
    }
    return 0; // ���Ե�����, �������� ���� ��쿡�� 0 ��ȯ
}

// ���簢���� �� �ȿ� ������ ���Եǰų� ���ϴ� ��� 1 ��ȯ
// ��� ���簢���� �������� �� �ȿ� �ְų� ���� ��迡 �ִ� ���
int isRectIn(Rectangle r, Circle c) {
    double radiusSquare = c.r * c.r; // �� ������ ����
    const double EPSILON = 1e-9; //�߻��ϴ� �ε� �Ҽ��� ������ ����ϱ� ���� epsilon ����

    // ���簢���� �� ������ �����ϱ�
    double vertices[4][2] = {
        {r.x1, r.y1}, // ���� �Ʒ�
        {r.x1, r.y2}, // ���� ��
        {r.x2, r.y1}, // ������ �Ʒ�
        {r.x2, r.y2}  // ������ ��
    };

    int i;
    // ���簢���� �� �������� ���ؼ� 
    for (i = 0; i < 4; i++) {
        // �� ���������� ���� �߽ɱ����� �Ÿ� �����ϱ� 
        double distToCenterSq = disSquare(vertices[i][0], vertices[i][1], c.x, c.y);

        // ���� � �������̵� ���� ������ �������� ũ�ٸ� (���� epsilon ����ؼ�)
        if (distToCenterSq > radiusSquare + EPSILON) {
            return 0; // 
        }
    }
    return 1; //��� �������� �� �ȿ� �ְų�, ���ϸ� 1 ��ȯ
}

// ���� ���踦 Ȯ���ϴ� �Լ�
int checkRelation(Rectangle r, Circle c) {
    // 1. ���� ���簢���� ����/���ϸ� -1 ��ȯ (�켱����)
    if (isCircleIn(r, c) == -1) {
        return -1;
    }

    // 2. ���簢���� ���� ����/���ϸ� 1 ��ȯ
    if (isRectIn(r, c) == 1) {
        return 1;
    }

    // 3. �� ���� ��� 0 ��ȯ
    return 0;
}

int main() {
    Rectangle r;
    Circle c;

    // ���簢�� ���� �Է�
    printf("���簢�� �Է� (x1 y1 x2 y2): ");
    scanf("%lf %lf %lf %lf", &r.x1, &r.y1, &r.x2, &r.y2);

    // x, y ��ǥ ����ȭ (x1 <= x2, y1 <= y2)
    if (r.x1 > r.x2) { 
        double temp = r.x1; r.x1 = r.x2; r.x2 = temp; 
    }
    if (r.y1 > r.y2) { 
        double temp = r.y1; r.y1 = r.y2; r.y2 = temp; 
    }

    // �� ���� �Է�
    printf("�� �Է� (x y r): ");
    scanf("%lf %lf %lf", &c.x, &c.y, &c.r);

    // ���� üũ �� ��� ���
    int result = checkRelation(r, c);

    if (result == 1) {
        printf("���: 1\n");
        printf("���簢���� ���� ������ ���Եǰų� ���Ѵ�\n");
    } else if (result == -1) {
        printf("���: -1\n");
        printf("���� ���簢���� ������ ���Եǰų� ���Ѵ�\n");
    } else {
        printf("���: 0\n");
        printf("�׷��� ���� ���\n");
    }

    return 0;
}

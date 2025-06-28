// 2022110151 이주연 
// 3. 레드블랙 트리 구현  
//  [ 함수 구성 ] 
//1. 데이터 구조 정의 (1)노드 2)레드블랙 트리 구조체 정의) 
//2. 노드 & 트리 생성 함수
//3. 트리 그림으로 출력하는  함수 
//4. 회전 함수 ( left rotate, right rotate) 
//5. 레드 블랙 특성 복구 함수 (fix-up)
//6. 노드 삽입 (Insertion)
//7. 메모리 헤제 (Free Memory)
//8. 메인 함수 (Main) 
#include <stdio.h>
#include <stdlib.h> // malloc, free exit (메모리 할당 및 해제를 위해 사용했습니다!) 

// 색상 열거형 정의 : RED = 0, BLACK = 1
typedef enum { RED, BLACK } Color;

// 1. 데이터 구조 정의 : 1) 노드 구조체 정의-------------------------------------------------------
// 각 노드는 key값,color색과 parent,left,right를 가리키는 포인터를 가지도록 설정했습니다.  
typedef struct Node {
    int key;             //  key : 노드 값                 e.g. 5  
    Color color;         //  color : 색상 (RED / BLACK)    e.g. RED
    struct Node *parent; //  부모 노드를 가리키는 포인터    
    struct Node *left;   //  왼쪽(l) 가리키는 포인터  
    struct Node *right;  //  오른쪽(r)을 가리키는 포인터  
} Node;

//  1. 데이터 구조 정의 : 2) 레드블랙 트리 구조체 정의
typedef struct RedBlackTree {
    Node *root; // root :트리의 루트 노드를 가리킵니다.  
    Node *NIL; //  nil 모든 리프 노드는 NIL을 가리킵니다.  
} RedBlackTree;

//  2. 노드 & 트리 생성 함수 : 1) 새 node 생성 및 초기화-------------------------------------------
Node* createNode(RedBlackTree *tree, int key) {
// 입력 : 레드블랙 트리와 key값 을 입력받아, 
//        노드를 생성하고  기본 속성을 설정한 후(초기화),  
// 출력(반환) : 초기화된 새 노드를 반환합니다.  
	// 1) newNode 동적 메모리 할당  
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("실패) 새로운 노드 메모리 할당 실패");
        exit(EXIT_FAILURE);
    }
    // 2) newNode 속성 초기화 (기본 설정)  
    newNode->key = key;     // 입력받은 key값을 새 노드의 key 값으로 넣고, 
    newNode->color = RED;   // 새로운 노드는 RED로 색을 설정해준 후, (black-height를 맞추기 위함) 
    newNode->parent = tree->NIL; // 부모, 왼쪽 자식, 오른쪽 자식 모두 NIL 노드로 초기화  
    newNode->left = tree->NIL;   
    newNode->right = tree->NIL;
    return newNode; // 생성되고 초기화된 newNode 반환  
}

//  2. 노드 & 트리 생성 함수 : 2) 레드블랙 tree 생성 및 초기화 
RedBlackTree* createRedBlackTree() {
// 출력(반환) : 트리  
	// 1) 레드블랙트리(tree) 동적 메모리 할당 
    RedBlackTree *tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    if (tree == NULL) {
        perror("실패) 트리 메모리 할당 실패");
        exit(EXIT_FAILURE);
    }
    // 2) (트리 내)NIL 노드 동적 메모리 할당 및 초기화 (초기 설정해주기)  
    tree->NIL = (Node*)malloc(sizeof(Node));
    if (tree->NIL == NULL) {
        perror("실패) NIL 노드 메모리 할당 실패");
        exit(EXIT_FAILURE);
    }
    tree->NIL->key = 0;            // NIL노드 key값을 0(임의의 값)으로 초기화하고,  
    tree->NIL->color = BLACK;      // BLACK 색상으로 색도 초기화한 후, 
    tree->NIL->parent = tree->NIL; // 자기 자신을 부모, 왼쪽 자식, 오른쪽 자식으로 가리키도록 설정 
    tree->NIL->left = tree->NIL;
    tree->NIL->right = tree->NIL;

    tree->root = tree->NIL; // 처음엔 트리가 비어 있으므로, 루트는 초기에 NIL로 설정 
    return tree; //트리 반환  
}

// 3. 트리 그림으로 출력하는 함수 ------------------------------------------------------------- 
// 위-> 아래 형태로 트리 구조를 표현하기 어려워
// 전위 순회 방식으로 형태로 트리 구조를 표현했습니다 ! 
void drawTree(RedBlackTree *tree, Node *node, int space, int isRight) {
	char colorRB;
	
	// NIL이면 반환  
    if (node == tree->NIL) {
        return;
    }

    // 간격은 5로 두기 
    space += 5;

    // 오른쪽 자식부터 출력하기 (트리의 위쪽에 위치하도록) 
    drawTree(tree, node->right, space, 1);

    // 현재 노드를 출력하기  
    printf("\n");
    int i;
    for (i = 5; i < space; i++) {  //트리 모양을 위한 공백  
        printf(" ");
    }

    // 부모 노드와의 관계를 반영해 출력 
	// / 과 \ 로 표현하려 했지만 출력시에는 구조가 한눈에 들어오지 않아  
	// ┌──와  └──로 대체해 표현했습니다
	// e.g.       ┌──C                           A 
	//           A                same as         /   \
	//            └──B                        B     C
    if (isRight) {
        printf("┌── ");   //  A기준 C가 오른쪽 자식임을 표현  
    } else {
        printf("└── ");   //  A기준 B가 왼쪽 자식임을 표현  
    }
	
	// 노드 컬러도  함께 출력 
	// 노드 컬러가  
	// Red 면     -> R
	// Black 이면 -> B  로 표시  
	if (node->color == RED){
		colorRB = 'R';
	} else {
		colorRB = 'B';
	}
    printf("%d(%c)\n", node->key, colorRB);  // e.g. 15(B)  :Black 노드임을 의미 

    // 재귀 호출을 통해 왼쪽 자식도 출력
    drawTree(tree, node->left, space, 0);
}

// 메시지와 함꼐 트리그리는 함수 호출해 출력  
void displayTree(RedBlackTree *tree, const char *message) {
    if (message) {
        printf("\n------------------ %s -----------------\n", message);
    }
    if (tree->root == tree->NIL) {
        printf("트리가 비어있습니다\n");
    } else {
//        drawTree(tree, tree->root, 0, "Root: ");
		drawTree(tree, tree->root, 0, 0);
    }
    printf("---------------------------------------------------\n");
}


// 4. 회전 함수 : 1) 왼쪽(left)으로 회전
// e.g. B노드 기준 왼쪽으로 회전 (left Rotate)    leftRotate(T,x)       
//          x                             y
//        /  \                          /  \
//       a    y            =>          x    r
//          /  \                      /  \
//         b    r                    a    b     
void leftRotate(RedBlackTree *tree, Node *x) {
	// : 노드x를 기준으로 트리 T 를 왼쪽으로 회전 
	// Left Rotating 중이라는 메시지 출력  
	char colorRB; 
	if (x->color == RED){
		colorRB = 'R';
	} else {
		colorRB = 'B';
	}
    printf("-> 노드 %d(%c)에 대해 Left Rotate 진행합니다. \n", x->key, colorRB);
    
    // 1) 회전할 노드 X의 오른쪽 자식을 y로 설정  
    Node *y = x->right;
    
    // 2) y의 왼쪽 서브트리(b)를 -> x의 오른쪽 서브트리(b)로 옮겨주기  
    x->right = y->left;
    
    // 3) y의 왼쪽 자식이 NIL이 아니면 부모를 x로 설정하기  
    if (y->left != tree->NIL) {
        y->left->parent = x;
    }
    // 4) y의 부모를  x의 부모로 설정하기  
    y->parent = x->parent;
    //   a) 만약 x가 루트였으면 -> y가 새로운 루트가 되고,  
    if (x->parent == tree->NIL) {
        tree->root = y;
    }
	//   b) x가 부모의 왼쪽 자식이었으면 -> y를 부모의 왼쪽 자식으로 설정하고,  
	else if (x == x->parent->left) {
        x->parent->left = y;
    } 
    //   c) x가 부모의 오른쪽 자식이었으면 -> y를 부모의 오른쪽 자식으로 설정하기  
	else {
        x->parent->right = y;
    }
    // 5) y의 왼쪽 자식으로 x를 이동시키고, 
    y->left = x;
    //    x의 부모를 y로 설정해주기  
    x->parent = y;
    // left rotate 완료 후 트리 모습 출력  
    displayTree(tree, "Left Rotate 후");
}

// 4. 회전 함수 : 2) 오른쪽(Right)으로  회전  rightRotate(T,y)
// e.g.       y                           x
//          /  \                        /  \
//         x    r         =>           a    y
//       /  \                             /  \
//      a    b                           b    r
void rightRotate(RedBlackTree *tree, Node *y) {
	// 트리랑 노드를 입력받아 이를 기준으로 오른쪽 회전
	// Right Rotate 중이라는 메시지 출력  
	char colorRB; 
	if (y->color == RED){
		colorRB = 'R';
	} else {
		colorRB = 'B';
	}
    printf("-> 노드 %d(%c)에 대해 Right Rotate 진행합니다.\n", y->key, colorRB);
    
    // 1) 회전할 노드 y의 왼쪽 자식을 x로 설정  
    Node *x = y->left;
    
    // 2) x의 오른쪽 서브트리(b)를 -> y의 왼쪽 서브트리(b)로 먼저 옮기기 
    y->left = x->right;
    
    // 3) x의 오른쪽 자식이 NIL이 아니면, -> 부모를 y로 설정  
    if (x->right != tree->NIL) {
        x->right->parent = y;
    }
    // 4) x의 부모를 y로 설정해주기  
    x->parent = y->parent;
    //   a) 만약 y가 루트였으면 -> x를 새로운 루트로 설정하고, 
    if (y->parent == tree->NIL) {
        tree->root = x;
    }
	//   b) 만약 y가 부모의 오른쪽 자식이었으면-> x를 부모의 오른쪽 자식으로 설정하고, 
	else if (y == y->parent->right) {
        y->parent->right = x;
    }
	//   c) 만약 y가 부모의 왼쪽 자식이었으면 -> x를 부모의 왼쪽 자식으로 설정하기  
	else {
        y->parent->left = x;
    }
    // 5) y를 x의 오른쪽 자식으로 이동시키고,  
    x->right = y;
    //    y의 부모를 x로 설정해주기  
    y->parent = x;
    
    // right-rotate후 트리 모습 출력하기  
    displayTree(tree, "Right Rotate 후");
}

// 5. 레드 블랙 특성을 복구하는 함수 (fix-up)  : 위배된 특성을 -> 다시 복구하는 역할  
void rbFixup(RedBlackTree *tree, Node *z) {
// tree : 수정할 레드블랙 트리
// z: 새롭게 삽입된 노드
// y: 삼촌 노드를 가리키는 포인터  
    Node *y; 
    // rbFixup (특성 복구)를 하는 노드 알려주는 메시지  
	char colorRB; 
	if (z->color == RED){
		colorRB = 'R';
	} else {
		colorRB = 'B';
	}
    printf("RB 특성 복구(fixup) 시작! - 노드 %d(%c) \n\n", z->key, colorRB);
	
	// 부모가 red일 때 반복  (4번 특성을 위배했을 때 진행)  
	// (삽입된 노드도 red, 노드의 부모도 red로 레드블랙 트리 규칙이 위반되었을 때 처리 과정) 
    while (z->parent->color == RED) {
    	// 만약 부모(z.p)가 조부모(z.p.p)의 왼쪽(l) 자식일 떄 
		//             z.p.p (G)
		//             /    \ 
		//        z.p(여기)  y 
		//          / \
		//         ?   ?
        if (z->parent == z->parent->parent->left) { 
            y = z->parent->parent->right; // 삼촌 노드를 설정해준다.  
            // Case 1 : 삼촌(y)이 Red인 경우  
	        //               z.p.p (black)       ->          z.p.p(Red)
			//              /    \           p&u:black        /    \ 
			//           z.p(red) y(RED)    G(p.p):red      z.p(B) y(B)
			//           /                                  /
			//          z                                  z 
            if (y->color == RED) {                         
            	char colorRB;
            	if (y->color == RED){
            		colorRB = 'R';
				} else {
					colorRB = 'B';
				}
                printf("-> Case 1: 삼촌 노드 %d(%c)가 RED.\n", y->key, colorRB);
                z->parent->color = BLACK; // 부모를 Black으로 바꾸고  
                y->color = BLACK;         // 삼촌도 Black으로 바꾸고  
                z->parent->parent->color = RED; // 조부모는 Red로 바꾼다. 
				 
				 //문구 및 트리 형태 출력  
                displayTree(tree, "부모, 삼촌, 조부모 색 변경완료. 조부모가 새로운 z가 됩니다.");   
                // 조부모 (Grandp즉, z.p.p) 를 새로운 z로 설정  
                z = z->parent->parent;
            } else { 
			    // 삼촌이 Black인 경우 및  
				// Case 2 :  z가 오른쪽(r)자식일 때 ->  (Left rotate) 진행 (해서 case3로 변환) 
		        //          z.p.p (black)       ->            z.p.p(black)
		        //         /    \            왼쪽 회전         /  \
				//     z.p(red) y(BLACK)       (LR)       z.p(red) y(BLACK)
				//         \                                /
				//          z(red) <-이경우                z (왼쪽으로 회전)  
                if (z == z->parent->right) { 
                    printf("-> Case 2 (LR): 노드 %d 는 오른쪽 자식입니다. Case 3로 변환하겠습니다!.\n", z->key);
                    z = z->parent;
                    leftRotate(tree, z); // 왼쪽 회전 진행  
                }
                // Case 3: z가 부모의 왼쪽 자식 (LL Case, 또는 Case 2에서 변환됨)
                //          z.p.p (black)     ->               z.p.p (red)     ->         z.p (black) 
				//         /    \            z.p: black          /  \     오른쪽으로 회전 /  \
				//     z.p(red) y(BLACK)     z.p.p: red     z.p(black) y(BLACK)       z(red)  z.p.p(red)
				//      /                  로 색 바꾼 후      /                               \
			    //     z(red) <-이경우                      z(red)                             y (black) 
                 printf("-> Case 3 : 부모와 조부의 색을 바꾼 후, rightRotate를 진행하겠습니다.\n");
                z->parent->color = BLACK;              // 부모&조부모 색 바꾼 후  
                z->parent->parent->color = RED;   
                displayTree(tree, "부모와 조부모 색 변경 완료");
                rightRotate(tree, z->parent->parent); // right rotate 진행 
            }
        } else { 
		    // z의 부모(z.p)가 조부모(z.p.p)의 오른쪽 자식인 경우
			// - 이경우엔 부모가 왼쪽에 있을 떄랑 대칭으로 동작!
			//             z.p.p (G)
			//             /    \ 
			//           y   z.p(여기) 
			//                  / \
			//                 ?   ? 
            y = z->parent->parent->left; // 삼촌노드(y) 설정  
            if (y->color == RED) { 
			    // Case 1: 삼촌이 RED일때 :
				//  -> 부모와 삼촌 Black으로 변경,  
				//  -> 조부모 Red로 변경 (균형 맞춰주기)
				//   z.p.p(조부모)를 z로 설정해 다시 while 진행  
			    char colorRB;
				if (y->color == RED){
            		colorRB = 'R';
				} else {
					colorRB = 'B';
				}
                printf("-> Case 1 (대칭): 삼촌 노드 %d(%c)가 RED입니다.\n", y->key, colorRB);
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                displayTree(tree, "부모, 삼촌, 조부모 색 변경완료. 조부모가 새로운 Z가 됩니다.");
                z = z->parent->parent;
            } else { // 삼촌이 BLACK이고  
            	// Case 2: z가 부모의 왼쪽(l) 자식인 경우 (RL 경우)
            	//  -> 부모를 기준으로 오른쪽 회전  (z = z->parent;)
            	//  -> 오른쪽 회전(rightRotate)해서 Case3으로 넘어가기  
                if (z == z->parent->left) { 
                     printf("-> Case 2 (RL 대칭): 노드 %d 는 왼쪽 자식입니다. Case 3로 변환하겠습니다.\n", z->key);
                    z = z->parent;
                    rightRotate(tree, z);
                }
                // Case 3: z가 부모의 오른쪽(r) 자식 (RR 경우거나 또는 Case 2에서 변환된 경우 의미)
                //  -> 색 변경 : 부모는 black으로, 조부모는 red로 색 변경 (코드 구현상 편의를 위해 먼저) 
                //  -> 조부모 기준으로 왼쪽 회전 (leftrotate)
				//     그러면 회전 후 부모가 균형 있게 위치하게 됩니다! 
				//     black
				//     /   \ 
				//   red   red (이렇게 트리가 균형 있는 형태가 됩니다!)  
				printf("-> Case 3 (RR or 변환된 RL 대칭): 부모와 조부모의 색을 바꾼 후 rotate를 진행하겠습니다. \n");
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                displayTree(tree, "부모와 조부모의 색상 변경 완료.");
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    // 루트의 색은 black이 될 수 있게 설정해주기 (2번 특성)  
    printf("-> 규칙 2: 루트 노드의 색상을 BLACK으로 바꿔주겠습니다.\n");
    tree->root->color = BLACK;
}

// 레드-블랙 트리에 노드 삽입
void rbInsert(RedBlackTree *tree, int key) {
// 입력 : 레드블랙 트리와 삽입할 키값을 받아, 
    printf("\n>>>>>>>>>>>>>>>>>[ 삽입할 노드: %d ]<<<<<<<<<<<<<<<<<\n", key);
    // 1. 새로운 노드 생성  
    Node *z = createNode(tree, key); // 새로운 노드z 생성(Red색상으로, left,right는 NIL로 초기화) 
    Node *y = tree->NIL;             // y: 탐색 중인 노드의 부모 가리킵니다. 
    Node *x = tree->root;            // x: 실제 탐색 중인 현재 노드를 가리킵니다.  
	
	// 2. 트리 탐색 
	// x가 NIL(리프 노드)일 때까지 탐색 
    while (x != tree->NIL) {
        y = x; // X를 부모로 설정해주고  
        if (z->key < x->key) { // x값을 기준으로 값이 작으면  
            x = x->left;       // 왼쪽 서브트리로,
        } else {               // x값을 기준으로 값이 크면 
            x = x->right;      // 오른쪽 서브트리로 이동하도록 설정해주기 
        }
    } //최종적으로 y가 z가 삽입될 부모노드가 됨!! 
	
	// 3. 새로운 노드 삽입  
    z->parent = y;
    if (y == tree->NIL) { // y가 NIL이면 트리가 비어있는 상태므로 
        tree->root = z;   // z가 루트가 됩니다.  
    } else if (z->key < y->key) { // 비어있지 않은 상태로 부모 y보다 작으면 
        y->left = z;                // z는 y의 왼쪽 자식으로 
    } else {                     // 비어있지 않은 상태로 부모 y보다 크면
        y->right = z;               // z는 y의 오른쪽 자식으로 연결됩니다.  
    }

	//4. 트리 출력하기  
    char msg[100];
    // printf로 하면 버퍼 채로 저장이 안돼 깨지다 보니 
	// sprintf (버퍼로 저장하는 방식)을 이용해서 메시지와 트리 모습이 출력되도록 설정
    sprintf(msg, "%d(R) 삽입 후", key); 
    displayTree(tree, msg); //트리 모습 출력 
	
	//5. 레드블랙(rb) 속성 복구 (rbFixup) 
	// 레드블랙 트리의 규칙이 깨지면 복구되도록 설정 
    rbFixup(tree, z);
    
    // 6. 최종 트리 출력하기  
    printf("\n>>>>>>>>>>[ %d 삽입이 완료되었습니다! ]<<<<<<<<<<<\n", key);
    sprintf(msg, "%d 삽입 후 최종 트리", key);
    displayTree(tree, msg);
}

// 트리 메모리 해제 
// 재귀 호출을 사용해 후위 순회 방식으로 트리를 탐색하며 노드를 메모리 해제하도록 설정했습니다.
// 노드 해제   
void freeTreeNodes(RedBlackTree *tree, Node *node) {
    if (node != tree->NIL) {  // 현재 노드가 NIL이 아니면 순회하며 해제할 것 
        freeTreeNodes(tree, node->left); // 왼쪽 자식노드부터 재귀적으로 해제 
        freeTreeNodes(tree, node->right); //오른쪽 자식 노드도 재귀적으로 해제 
        free(node); // 마지막으로 현재 노드도 해제하기  
    }
}

// 트리 해제  
void freeRedBlackTree(RedBlackTree *tree) {
    if (tree) { // 트리가 있으면  
        freeTreeNodes(tree, tree->root); // 트리의 모든 노드를 후위 순회 방식으로 해제하고 
        free(tree->NIL); // NIL 노드도 해제하고  
        free(tree); // 트리 구조체 자체를 해제하기  
    }
}


int main() {
    RedBlackTree *rbt = createRedBlackTree(); //트리 생성 
    int keysToInsert[] = {20, 15, 14, 12, 13, 1}; // 삽입할 키 값들 배열로 정의 
    int numKeys = sizeof(keysToInsert) / sizeof(keysToInsert[0]); // 배열 크기 계산 (6) 
	int i;
	
    for (i = 0; i < numKeys; i++) {
        rbInsert(rbt, keysToInsert[i]); //반복문을 통해 노드 삽입하기  
    }

    printf("\n\n============= <최종 레드-블랙 트리 구조> =============\n"); //최종 트리 출력하기  
    displayTree(rbt, "레드블랙 트리 최종 구조");

    freeRedBlackTree(rbt); // 메모리 해제하기  

    return 0;
}

// 2022110151 ���ֿ� 
// 3. ����� Ʈ�� ����  
//  [ �Լ� ���� ] 
//1. ������ ���� ���� (1)��� 2)����� Ʈ�� ����ü ����) 
//2. ��� & Ʈ�� ���� �Լ�
//3. Ʈ�� �׸����� ����ϴ�  �Լ� 
//4. ȸ�� �Լ� ( left rotate, right rotate) 
//5. ���� �� Ư�� ���� �Լ� (fix-up)
//6. ��� ���� (Insertion)
//7. �޸� ���� (Free Memory)
//8. ���� �Լ� (Main) 
#include <stdio.h>
#include <stdlib.h> // malloc, free exit (�޸� �Ҵ� �� ������ ���� ����߽��ϴ�!) 

// ���� ������ ���� : RED = 0, BLACK = 1
typedef enum { RED, BLACK } Color;

// 1. ������ ���� ���� : 1) ��� ����ü ����-------------------------------------------------------
// �� ���� key��,color���� parent,left,right�� ����Ű�� �����͸� �������� �����߽��ϴ�.  
typedef struct Node {
    int key;             //  key : ��� ��                 e.g. 5  
    Color color;         //  color : ���� (RED / BLACK)    e.g. RED
    struct Node *parent; //  �θ� ��带 ����Ű�� ������    
    struct Node *left;   //  ����(l) ����Ű�� ������  
    struct Node *right;  //  ������(r)�� ����Ű�� ������  
} Node;

//  1. ������ ���� ���� : 2) ����� Ʈ�� ����ü ����
typedef struct RedBlackTree {
    Node *root; // root :Ʈ���� ��Ʈ ��带 ����ŵ�ϴ�.  
    Node *NIL; //  nil ��� ���� ���� NIL�� ����ŵ�ϴ�.  
} RedBlackTree;

//  2. ��� & Ʈ�� ���� �Լ� : 1) �� node ���� �� �ʱ�ȭ-------------------------------------------
Node* createNode(RedBlackTree *tree, int key) {
// �Է� : ����� Ʈ���� key�� �� �Է¹޾�, 
//        ��带 �����ϰ�  �⺻ �Ӽ��� ������ ��(�ʱ�ȭ),  
// ���(��ȯ) : �ʱ�ȭ�� �� ��带 ��ȯ�մϴ�.  
	// 1) newNode ���� �޸� �Ҵ�  
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("����) ���ο� ��� �޸� �Ҵ� ����");
        exit(EXIT_FAILURE);
    }
    // 2) newNode �Ӽ� �ʱ�ȭ (�⺻ ����)  
    newNode->key = key;     // �Է¹��� key���� �� ����� key ������ �ְ�, 
    newNode->color = RED;   // ���ο� ���� RED�� ���� �������� ��, (black-height�� ���߱� ����) 
    newNode->parent = tree->NIL; // �θ�, ���� �ڽ�, ������ �ڽ� ��� NIL ���� �ʱ�ȭ  
    newNode->left = tree->NIL;   
    newNode->right = tree->NIL;
    return newNode; // �����ǰ� �ʱ�ȭ�� newNode ��ȯ  
}

//  2. ��� & Ʈ�� ���� �Լ� : 2) ����� tree ���� �� �ʱ�ȭ 
RedBlackTree* createRedBlackTree() {
// ���(��ȯ) : Ʈ��  
	// 1) �����Ʈ��(tree) ���� �޸� �Ҵ� 
    RedBlackTree *tree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    if (tree == NULL) {
        perror("����) Ʈ�� �޸� �Ҵ� ����");
        exit(EXIT_FAILURE);
    }
    // 2) (Ʈ�� ��)NIL ��� ���� �޸� �Ҵ� �� �ʱ�ȭ (�ʱ� �������ֱ�)  
    tree->NIL = (Node*)malloc(sizeof(Node));
    if (tree->NIL == NULL) {
        perror("����) NIL ��� �޸� �Ҵ� ����");
        exit(EXIT_FAILURE);
    }
    tree->NIL->key = 0;            // NIL��� key���� 0(������ ��)���� �ʱ�ȭ�ϰ�,  
    tree->NIL->color = BLACK;      // BLACK �������� ���� �ʱ�ȭ�� ��, 
    tree->NIL->parent = tree->NIL; // �ڱ� �ڽ��� �θ�, ���� �ڽ�, ������ �ڽ����� ����Ű���� ���� 
    tree->NIL->left = tree->NIL;
    tree->NIL->right = tree->NIL;

    tree->root = tree->NIL; // ó���� Ʈ���� ��� �����Ƿ�, ��Ʈ�� �ʱ⿡ NIL�� ���� 
    return tree; //Ʈ�� ��ȯ  
}

// 3. Ʈ�� �׸����� ����ϴ� �Լ� ------------------------------------------------------------- 
// ��-> �Ʒ� ���·� Ʈ�� ������ ǥ���ϱ� �����
// ���� ��ȸ ������� ���·� Ʈ�� ������ ǥ���߽��ϴ� ! 
void drawTree(RedBlackTree *tree, Node *node, int space, int isRight) {
	char colorRB;
	
	// NIL�̸� ��ȯ  
    if (node == tree->NIL) {
        return;
    }

    // ������ 5�� �α� 
    space += 5;

    // ������ �ڽĺ��� ����ϱ� (Ʈ���� ���ʿ� ��ġ�ϵ���) 
    drawTree(tree, node->right, space, 1);

    // ���� ��带 ����ϱ�  
    printf("\n");
    int i;
    for (i = 5; i < space; i++) {  //Ʈ�� ����� ���� ����  
        printf(" ");
    }

    // �θ� ������ ���踦 �ݿ��� ��� 
	// / �� \ �� ǥ���Ϸ� ������ ��½ÿ��� ������ �Ѵ��� ������ �ʾ�  
	// ��������  �������� ��ü�� ǥ���߽��ϴ�
	// e.g.       ������C                           A 
	//           A                same as         /   \
	//            ������B                        B     C
    if (isRight) {
        printf("������ ");   //  A���� C�� ������ �ڽ����� ǥ��  
    } else {
        printf("������ ");   //  A���� B�� ���� �ڽ����� ǥ��  
    }
	
	// ��� �÷���  �Բ� ��� 
	// ��� �÷���  
	// Red ��     -> R
	// Black �̸� -> B  �� ǥ��  
	if (node->color == RED){
		colorRB = 'R';
	} else {
		colorRB = 'B';
	}
    printf("%d(%c)\n", node->key, colorRB);  // e.g. 15(B)  :Black ������� �ǹ� 

    // ��� ȣ���� ���� ���� �ڽĵ� ���
    drawTree(tree, node->left, space, 0);
}

// �޽����� �Բ� Ʈ���׸��� �Լ� ȣ���� ���  
void displayTree(RedBlackTree *tree, const char *message) {
    if (message) {
        printf("\n------------------ %s -----------------\n", message);
    }
    if (tree->root == tree->NIL) {
        printf("Ʈ���� ����ֽ��ϴ�\n");
    } else {
//        drawTree(tree, tree->root, 0, "Root: ");
		drawTree(tree, tree->root, 0, 0);
    }
    printf("---------------------------------------------------\n");
}


// 4. ȸ�� �Լ� : 1) ����(left)���� ȸ��
// e.g. B��� ���� �������� ȸ�� (left Rotate)    leftRotate(T,x)       
//          x                             y
//        /  \                          /  \
//       a    y            =>          x    r
//          /  \                      /  \
//         b    r                    a    b     
void leftRotate(RedBlackTree *tree, Node *x) {
	// : ���x�� �������� Ʈ�� T �� �������� ȸ�� 
	// Left Rotating ���̶�� �޽��� ���  
	char colorRB; 
	if (x->color == RED){
		colorRB = 'R';
	} else {
		colorRB = 'B';
	}
    printf("-> ��� %d(%c)�� ���� Left Rotate �����մϴ�. \n", x->key, colorRB);
    
    // 1) ȸ���� ��� X�� ������ �ڽ��� y�� ����  
    Node *y = x->right;
    
    // 2) y�� ���� ����Ʈ��(b)�� -> x�� ������ ����Ʈ��(b)�� �Ű��ֱ�  
    x->right = y->left;
    
    // 3) y�� ���� �ڽ��� NIL�� �ƴϸ� �θ� x�� �����ϱ�  
    if (y->left != tree->NIL) {
        y->left->parent = x;
    }
    // 4) y�� �θ�  x�� �θ�� �����ϱ�  
    y->parent = x->parent;
    //   a) ���� x�� ��Ʈ������ -> y�� ���ο� ��Ʈ�� �ǰ�,  
    if (x->parent == tree->NIL) {
        tree->root = y;
    }
	//   b) x�� �θ��� ���� �ڽ��̾����� -> y�� �θ��� ���� �ڽ����� �����ϰ�,  
	else if (x == x->parent->left) {
        x->parent->left = y;
    } 
    //   c) x�� �θ��� ������ �ڽ��̾����� -> y�� �θ��� ������ �ڽ����� �����ϱ�  
	else {
        x->parent->right = y;
    }
    // 5) y�� ���� �ڽ����� x�� �̵���Ű��, 
    y->left = x;
    //    x�� �θ� y�� �������ֱ�  
    x->parent = y;
    // left rotate �Ϸ� �� Ʈ�� ��� ���  
    displayTree(tree, "Left Rotate ��");
}

// 4. ȸ�� �Լ� : 2) ������(Right)����  ȸ��  rightRotate(T,y)
// e.g.       y                           x
//          /  \                        /  \
//         x    r         =>           a    y
//       /  \                             /  \
//      a    b                           b    r
void rightRotate(RedBlackTree *tree, Node *y) {
	// Ʈ���� ��带 �Է¹޾� �̸� �������� ������ ȸ��
	// Right Rotate ���̶�� �޽��� ���  
	char colorRB; 
	if (y->color == RED){
		colorRB = 'R';
	} else {
		colorRB = 'B';
	}
    printf("-> ��� %d(%c)�� ���� Right Rotate �����մϴ�.\n", y->key, colorRB);
    
    // 1) ȸ���� ��� y�� ���� �ڽ��� x�� ����  
    Node *x = y->left;
    
    // 2) x�� ������ ����Ʈ��(b)�� -> y�� ���� ����Ʈ��(b)�� ���� �ű�� 
    y->left = x->right;
    
    // 3) x�� ������ �ڽ��� NIL�� �ƴϸ�, -> �θ� y�� ����  
    if (x->right != tree->NIL) {
        x->right->parent = y;
    }
    // 4) x�� �θ� y�� �������ֱ�  
    x->parent = y->parent;
    //   a) ���� y�� ��Ʈ������ -> x�� ���ο� ��Ʈ�� �����ϰ�, 
    if (y->parent == tree->NIL) {
        tree->root = x;
    }
	//   b) ���� y�� �θ��� ������ �ڽ��̾�����-> x�� �θ��� ������ �ڽ����� �����ϰ�, 
	else if (y == y->parent->right) {
        y->parent->right = x;
    }
	//   c) ���� y�� �θ��� ���� �ڽ��̾����� -> x�� �θ��� ���� �ڽ����� �����ϱ�  
	else {
        y->parent->left = x;
    }
    // 5) y�� x�� ������ �ڽ����� �̵���Ű��,  
    x->right = y;
    //    y�� �θ� x�� �������ֱ�  
    y->parent = x;
    
    // right-rotate�� Ʈ�� ��� ����ϱ�  
    displayTree(tree, "Right Rotate ��");
}

// 5. ���� �� Ư���� �����ϴ� �Լ� (fix-up)  : ����� Ư���� -> �ٽ� �����ϴ� ����  
void rbFixup(RedBlackTree *tree, Node *z) {
// tree : ������ ����� Ʈ��
// z: ���Ӱ� ���Ե� ���
// y: ���� ��带 ����Ű�� ������  
    Node *y; 
    // rbFixup (Ư�� ����)�� �ϴ� ��� �˷��ִ� �޽���  
	char colorRB; 
	if (z->color == RED){
		colorRB = 'R';
	} else {
		colorRB = 'B';
	}
    printf("RB Ư�� ����(fixup) ����! - ��� %d(%c) \n\n", z->key, colorRB);
	
	// �θ� red�� �� �ݺ�  (4�� Ư���� �������� �� ����)  
	// (���Ե� ��嵵 red, ����� �θ� red�� ����� Ʈ�� ��Ģ�� ���ݵǾ��� �� ó�� ����) 
    while (z->parent->color == RED) {
    	// ���� �θ�(z.p)�� ���θ�(z.p.p)�� ����(l) �ڽ��� �� 
		//             z.p.p (G)
		//             /    \ 
		//        z.p(����)  y 
		//          / \
		//         ?   ?
        if (z->parent == z->parent->parent->left) { 
            y = z->parent->parent->right; // ���� ��带 �������ش�.  
            // Case 1 : ����(y)�� Red�� ���  
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
                printf("-> Case 1: ���� ��� %d(%c)�� RED.\n", y->key, colorRB);
                z->parent->color = BLACK; // �θ� Black���� �ٲٰ�  
                y->color = BLACK;         // ���̵� Black���� �ٲٰ�  
                z->parent->parent->color = RED; // ���θ�� Red�� �ٲ۴�. 
				 
				 //���� �� Ʈ�� ���� ���  
                displayTree(tree, "�θ�, ����, ���θ� �� ����Ϸ�. ���θ� ���ο� z�� �˴ϴ�.");   
                // ���θ� (Grandp��, z.p.p) �� ���ο� z�� ����  
                z = z->parent->parent;
            } else { 
			    // ������ Black�� ��� ��  
				// Case 2 :  z�� ������(r)�ڽ��� �� ->  (Left rotate) ���� (�ؼ� case3�� ��ȯ) 
		        //          z.p.p (black)       ->            z.p.p(black)
		        //         /    \            ���� ȸ��         /  \
				//     z.p(red) y(BLACK)       (LR)       z.p(red) y(BLACK)
				//         \                                /
				//          z(red) <-�̰��                z (�������� ȸ��)  
                if (z == z->parent->right) { 
                    printf("-> Case 2 (LR): ��� %d �� ������ �ڽ��Դϴ�. Case 3�� ��ȯ�ϰڽ��ϴ�!.\n", z->key);
                    z = z->parent;
                    leftRotate(tree, z); // ���� ȸ�� ����  
                }
                // Case 3: z�� �θ��� ���� �ڽ� (LL Case, �Ǵ� Case 2���� ��ȯ��)
                //          z.p.p (black)     ->               z.p.p (red)     ->         z.p (black) 
				//         /    \            z.p: black          /  \     ���������� ȸ�� /  \
				//     z.p(red) y(BLACK)     z.p.p: red     z.p(black) y(BLACK)       z(red)  z.p.p(red)
				//      /                  �� �� �ٲ� ��      /                               \
			    //     z(red) <-�̰��                      z(red)                             y (black) 
                 printf("-> Case 3 : �θ�� ������ ���� �ٲ� ��, rightRotate�� �����ϰڽ��ϴ�.\n");
                z->parent->color = BLACK;              // �θ�&���θ� �� �ٲ� ��  
                z->parent->parent->color = RED;   
                displayTree(tree, "�θ�� ���θ� �� ���� �Ϸ�");
                rightRotate(tree, z->parent->parent); // right rotate ���� 
            }
        } else { 
		    // z�� �θ�(z.p)�� ���θ�(z.p.p)�� ������ �ڽ��� ���
			// - �̰�쿣 �θ� ���ʿ� ���� ���� ��Ī���� ����!
			//             z.p.p (G)
			//             /    \ 
			//           y   z.p(����) 
			//                  / \
			//                 ?   ? 
            y = z->parent->parent->left; // ���̳��(y) ����  
            if (y->color == RED) { 
			    // Case 1: ������ RED�϶� :
				//  -> �θ�� ���� Black���� ����,  
				//  -> ���θ� Red�� ���� (���� �����ֱ�)
				//   z.p.p(���θ�)�� z�� ������ �ٽ� while ����  
			    char colorRB;
				if (y->color == RED){
            		colorRB = 'R';
				} else {
					colorRB = 'B';
				}
                printf("-> Case 1 (��Ī): ���� ��� %d(%c)�� RED�Դϴ�.\n", y->key, colorRB);
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                displayTree(tree, "�θ�, ����, ���θ� �� ����Ϸ�. ���θ� ���ο� Z�� �˴ϴ�.");
                z = z->parent->parent;
            } else { // ������ BLACK�̰�  
            	// Case 2: z�� �θ��� ����(l) �ڽ��� ��� (RL ���)
            	//  -> �θ� �������� ������ ȸ��  (z = z->parent;)
            	//  -> ������ ȸ��(rightRotate)�ؼ� Case3���� �Ѿ��  
                if (z == z->parent->left) { 
                     printf("-> Case 2 (RL ��Ī): ��� %d �� ���� �ڽ��Դϴ�. Case 3�� ��ȯ�ϰڽ��ϴ�.\n", z->key);
                    z = z->parent;
                    rightRotate(tree, z);
                }
                // Case 3: z�� �θ��� ������(r) �ڽ� (RR ���ų� �Ǵ� Case 2���� ��ȯ�� ��� �ǹ�)
                //  -> �� ���� : �θ�� black����, ���θ�� red�� �� ���� (�ڵ� ������ ���Ǹ� ���� ����) 
                //  -> ���θ� �������� ���� ȸ�� (leftrotate)
				//     �׷��� ȸ�� �� �θ� ���� �ְ� ��ġ�ϰ� �˴ϴ�! 
				//     black
				//     /   \ 
				//   red   red (�̷��� Ʈ���� ���� �ִ� ���°� �˴ϴ�!)  
				printf("-> Case 3 (RR or ��ȯ�� RL ��Ī): �θ�� ���θ��� ���� �ٲ� �� rotate�� �����ϰڽ��ϴ�. \n");
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                displayTree(tree, "�θ�� ���θ��� ���� ���� �Ϸ�.");
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    // ��Ʈ�� ���� black�� �� �� �ְ� �������ֱ� (2�� Ư��)  
    printf("-> ��Ģ 2: ��Ʈ ����� ������ BLACK���� �ٲ��ְڽ��ϴ�.\n");
    tree->root->color = BLACK;
}

// ����-�� Ʈ���� ��� ����
void rbInsert(RedBlackTree *tree, int key) {
// �Է� : ����� Ʈ���� ������ Ű���� �޾�, 
    printf("\n>>>>>>>>>>>>>>>>>[ ������ ���: %d ]<<<<<<<<<<<<<<<<<\n", key);
    // 1. ���ο� ��� ����  
    Node *z = createNode(tree, key); // ���ο� ���z ����(Red��������, left,right�� NIL�� �ʱ�ȭ) 
    Node *y = tree->NIL;             // y: Ž�� ���� ����� �θ� ����ŵ�ϴ�. 
    Node *x = tree->root;            // x: ���� Ž�� ���� ���� ��带 ����ŵ�ϴ�.  
	
	// 2. Ʈ�� Ž�� 
	// x�� NIL(���� ���)�� ������ Ž�� 
    while (x != tree->NIL) {
        y = x; // X�� �θ�� �������ְ�  
        if (z->key < x->key) { // x���� �������� ���� ������  
            x = x->left;       // ���� ����Ʈ����,
        } else {               // x���� �������� ���� ũ�� 
            x = x->right;      // ������ ����Ʈ���� �̵��ϵ��� �������ֱ� 
        }
    } //���������� y�� z�� ���Ե� �θ��尡 ��!! 
	
	// 3. ���ο� ��� ����  
    z->parent = y;
    if (y == tree->NIL) { // y�� NIL�̸� Ʈ���� ����ִ� ���¹Ƿ� 
        tree->root = z;   // z�� ��Ʈ�� �˴ϴ�.  
    } else if (z->key < y->key) { // ������� ���� ���·� �θ� y���� ������ 
        y->left = z;                // z�� y�� ���� �ڽ����� 
    } else {                     // ������� ���� ���·� �θ� y���� ũ��
        y->right = z;               // z�� y�� ������ �ڽ����� ����˴ϴ�.  
    }

	//4. Ʈ�� ����ϱ�  
    char msg[100];
    // printf�� �ϸ� ���� ä�� ������ �ȵ� ������ ���� 
	// sprintf (���۷� �����ϴ� ���)�� �̿��ؼ� �޽����� Ʈ�� ����� ��µǵ��� ����
    sprintf(msg, "%d(R) ���� ��", key); 
    displayTree(tree, msg); //Ʈ�� ��� ��� 
	
	//5. �����(rb) �Ӽ� ���� (rbFixup) 
	// ����� Ʈ���� ��Ģ�� ������ �����ǵ��� ���� 
    rbFixup(tree, z);
    
    // 6. ���� Ʈ�� ����ϱ�  
    printf("\n>>>>>>>>>>[ %d ������ �Ϸ�Ǿ����ϴ�! ]<<<<<<<<<<<\n", key);
    sprintf(msg, "%d ���� �� ���� Ʈ��", key);
    displayTree(tree, msg);
}

// Ʈ�� �޸� ���� 
// ��� ȣ���� ����� ���� ��ȸ ������� Ʈ���� Ž���ϸ� ��带 �޸� �����ϵ��� �����߽��ϴ�.
// ��� ����   
void freeTreeNodes(RedBlackTree *tree, Node *node) {
    if (node != tree->NIL) {  // ���� ��尡 NIL�� �ƴϸ� ��ȸ�ϸ� ������ �� 
        freeTreeNodes(tree, node->left); // ���� �ڽĳ����� ��������� ���� 
        freeTreeNodes(tree, node->right); //������ �ڽ� ��嵵 ��������� ���� 
        free(node); // ���������� ���� ��嵵 �����ϱ�  
    }
}

// Ʈ�� ����  
void freeRedBlackTree(RedBlackTree *tree) {
    if (tree) { // Ʈ���� ������  
        freeTreeNodes(tree, tree->root); // Ʈ���� ��� ��带 ���� ��ȸ ������� �����ϰ� 
        free(tree->NIL); // NIL ��嵵 �����ϰ�  
        free(tree); // Ʈ�� ����ü ��ü�� �����ϱ�  
    }
}


int main() {
    RedBlackTree *rbt = createRedBlackTree(); //Ʈ�� ���� 
    int keysToInsert[] = {20, 15, 14, 12, 13, 1}; // ������ Ű ���� �迭�� ���� 
    int numKeys = sizeof(keysToInsert) / sizeof(keysToInsert[0]); // �迭 ũ�� ��� (6) 
	int i;
	
    for (i = 0; i < numKeys; i++) {
        rbInsert(rbt, keysToInsert[i]); //�ݺ����� ���� ��� �����ϱ�  
    }

    printf("\n\n============= <���� ����-�� Ʈ�� ����> =============\n"); //���� Ʈ�� ����ϱ�  
    displayTree(rbt, "����� Ʈ�� ���� ����");

    freeRedBlackTree(rbt); // �޸� �����ϱ�  

    return 0;
}

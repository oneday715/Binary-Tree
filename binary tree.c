#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
}Node;

Node *insertNode(Node *root, int key){
    if(root == NULL){
        Node *newnode = (Node *)malloc(sizeof(Node));
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->data = key;
        root = newnode;
    }
        if(root->data > key){
            root->left = insertNode(root->left, key);
        }
        else if(root->data < key){
            root->right = insertNode(root->right, key);
        }
    return root;
}

int findNode(Node *root, int key){
    if(root->data == key){
        return 1;
    }
    else if(root->data > key){
        if(root->left != NULL)
            return findNode(root->left, key);
        else return 0;
    }
    else{
        if(root->right != NULL)
            return findNode(root->right, key);
        else return 0;
    }
}

Node* findL(Node *root){
    Node *current = root->left;
    while(current->right != NULL){
        current = current->right;
    }
    return current;
}
Node* findTmp(Node *root, Node* tmp){
    Node *finder = root->left;
    while(finder->right != tmp){
        finder = finder->right;
    }
    return finder;
}

Node* deleteNode(Node *root, int key){
    Node *tmpF = root;
    if(root == NULL){
        printf("삭제할 키 값[%d]는 트리에 없습니다.\n", key);
        return root;
    }

    if(root->data > key){
        root->left = deleteNode(root->left, key);
    }
    else if(root->data < key){
        root->right = deleteNode(root->right, key);
    }
    else if(root->data == key){
        if(root->left == NULL && root->right == NULL){
            root = NULL;
        }
        else if(root->left == NULL){
            root = root->right;
        }
        else if(root->right == NULL){
            root = root->left;
        }
        else{
            Node *tmp = findL(root);
            tmpF = findTmp(root, tmp);
            root->data = tmp->data;
            tmpF->right = NULL;
        free(tmp);
        }
    }
    return root;
}

void preOrder(Node *root){
    if(root){
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
    }
}

int main(void){
    int n;
    int key;
    Node *root = (Node *)malloc(sizeof(Node));
    root = NULL;
    while(1){
        printf("0: 종료\n");
        printf("1: 검색\n");
        printf("2: 삽입\n");
        printf("3: 삭제\n");
        printf("4: 출력\n");
        printf("메뉴를 선택하세요: ");
        scanf("%d", &n);
        if(n == 0) break;
        else if(n == 1){
            printf("검색할 키 값을 입력하세요: ");
            scanf("%d", &key);
            if(findNode(root, key) == 1){
                printf("찾는 키 값 [%d]는 트리에 있습니다\n", key);
            }
            else if(findNode(root, key) == 0){
                printf("찾는 키 값 [%d]는 트리에 없습니다\n", key);
            }
            printf("\n");
        }
        else if(n == 2){
            printf("삽입할 키 값을 입력하세요: ");
            scanf("%d", &key);
            root = insertNode(root, key);
            printf("\n");
        }
        else if(n == 3){
            printf("삭제할 키 값을 입력하세요: ");
            scanf("%d", &key);
            root = deleteNode(root, key);
            printf("\n");
        }
        else if(n == 4){
            printf("출력 결과>> ");
            preOrder(root);
            printf("\n\n");
        }
    }
    return 0;
}

//
//  Binary_Search_2.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/04/23.
//  Copyright © 2020 이주원. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

typedef struct node {
    int data;
    node* left;
    node* right;
    node* p;
}node;
node* insert(node** root, int data);
void del(node** root, int data);
node* search(node** root, int data);
void print(node* root);
node* max_min(node** root);


int main()
{
    node* root = NULL;
    
    printf("Commands : \n +key : Insert (or Update) element\n ?key : Retrieved element\n -key : Remove element\n Q    : Quit the test program\n");
    
    printf("Empty Tree\n");
    int flag=1;
    
    while(flag){
        printf("Command : ");
        string temp="";
        cin >> temp;
        if(temp.at(0)=='+'){
            //사용자로부터 스트링으로 입력받고, 이를 수로 데이터화시키기 위해 cstring library의 stoi함수 이용
            int num=stoi(temp.substr(1));
            insert(&root, num);
            print(root);
        } else if(temp.at(0)=='-') {
            int num=stoi(temp.substr(1));
            del(&root, num);
            print(root);
        } else if(temp.at(0)=='?'){
            int num=stoi(temp.substr(1));
            node* result=search(&root, num);
            printf("Retrieved : key = %d\n",num);
            if(result->left==NULL){
                cout << "left child is none" <<endl;
            } else {
                cout << "left child is " << result->left->data << endl;
            }
            if(result->right==NULL){
                cout << "right child is none" <<endl;
            } else{
                cout << "right child is " << result->right->data << endl;
            }
            
            //print(root);
        } else{
            flag=0;
        }
    }
    return 0;
}

node* search(node** root, int data)
{
    node* ret = (node*)malloc(sizeof(node));
    
    if (root == NULL) {
        printf("찾으려는 값이 트리에 존재하지 않습니다\n");
        return ret=NULL;
    }
    
    if ( (*root)->data== data){
        return ret=*root;
    }
    if ((*root)->data > data) {
        ret = search(&((*root)->left), data);
    } else {
        ret = search(&((*root)->right), data);
    }
    return ret;
}

// 내 오른쪽에서 가장 왼쪽 구하기
node* max_min(node** root)
{
    node* ret;
    if ((*root)->left == NULL) {
        ret = *root;
        return ret;
    }
    ret = max_min(&(*root)->left);
    return ret;
}

// 노드 삽입하는 함수
node* insert(node** root, int data)
{
    node* ret = (node*)malloc(sizeof(node));
    
    
    //트리가 비어있으면 그곳에 삽입
    if (*root == NULL){
        ret->data = data;
        ret->left = NULL;
        ret->right = NULL;
        *root = ret;
        return ret;
    }
    //값이 작을때 왼쪽으로, 리턴하면서 부모정해주기.
    if ((*root)->data > data) {
        ret= insert(&(*root)->left, data);
        ret->p = *root;
    }
    //값이 클때 오른쪽으로, 리턴하면서 부모정해주기.
    else if ((*root)->data < data) {
        ret =insert(&(*root)->right, data);
        ret->p = *root;
    }
    
    return *root;
}

// 노드 삭제하는 함수
void del(node** root, int data) {
    node* del_node = search(root, data);
    
    if (del_node == NULL)
        return;
    
    //자식이 하나도 없을 때
    if (del_node->left == NULL && del_node->right == NULL) {
        
        //지우는 노드가 루트노드일때
        if (del_node->p == NULL){
            *root = NULL;
            return;
        }
        //자식 노드가 하나도 없을때 부모를 구해서, 해당하는 자식 노드를 삭제해주고 지울노드 해제.
        node* parent = (node*)malloc(sizeof(node));
        parent = del_node->p;
        
        if (parent->left == del_node) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
        free(del_node);
        del_node = NULL;
    }
    //자식이 둘다 있을 때
    else if (del_node->left != NULL && del_node->right != NULL) {
        node* tmp = (node*)malloc(sizeof(node));
        
        //나보다 큰 것중에서 가장 작은 것이랑 값을 바꿔줌
        tmp = max_min(&(*root)->right);
        del_node->data = tmp->data;
        
        //그리고 그 값을 삭제
        del(&del_node->right, tmp->data);
    }
    //자식이 하나 있을 때
    else {
        node* tmp = (node*)malloc(sizeof(node));
        tmp = del_node->p;
        //값을 바꿔주고, 자식노드 삭제
        if (del_node->left != NULL) {
            del_node->data = del_node->left->data;
            del(&del_node->left, del_node->data);
        }
        else{
            del_node->data = del_node->right->data;
            del(&del_node->right, del_node->data);
        }
    }
}

// 전체 트리를 출력해주는 함수
void print(node *t) {
    if (t == NULL) {
        return;
    }
    printf("NODE [%d] > ", t->data);
    
    if (t->left != NULL) {
        printf("LEFT [%d] ", (t->left)->data);
    }
    if (t->right != NULL) {
        printf("RIGHT [%d]", (t->right)->data);
    }
    printf("\n");
    
    if (t->left) {
        print(t->left);
    }
    if (t->right) {
        print(t->right);
    }
}

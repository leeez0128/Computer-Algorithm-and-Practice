//
//  Binary_Search_1.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/04/23.
//  Copyright © 2020 이주원. All rights reserved.
//

#include <iostream>
using namespace std;
struct node
{
    struct node *l;
    int key;
    struct node *r;
};

struct node* TreeInit();
struct node *TreeSearch(struct node *head, int xkey);
struct node *TreeSearchParent(struct node *head, int xkey);
void TreeInsert(struct node *head, int xkey);
void TreeDel(struct node *head, int xkey);
void print(struct node *head);

int main()
{
    struct node *T1 = NULL;
    struct node *result = NULL;
    T1 = TreeInit();

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
            TreeInsert(T1, num);
            print(T1);
        } else if(temp.at(0)=='-') {
            int num=stoi(temp.substr(1));
            TreeDel(T1, num);
            print(T1);
        } else if(temp.at(0)=='?'){
            int num=stoi(temp.substr(1));
            result=TreeSearch(T1, num);
            printf("Retrieved : key = %d\n",num);
            if(result->l==NULL){
                cout << "left child is none" <<endl;
            } else {
                cout << "left child is " << result->l->key << endl;
            }
            if(result->r==NULL){
                cout << "right child is none" <<endl;
            } else{
                cout << "right child is " << result->r->key << endl;
            }
            print(T1);
        } else{
            flag=0;
        }
    }
    
    return 0;
}

struct node* TreeInit()//head 노드를 반환해준다.
{
    struct node *head;
    head = (struct node*)malloc(sizeof*head);
    head->l = NULL;
    head->r = NULL;
    head->key = 0;
    return head;//head의 오른쪽 자식 노드가 트리의 루트 노드
}

struct node *TreeSearch(struct node *head, int xkey)
{
    struct node *t;
    t = head->r;//head의 오른쪽 자식 노드가 트리의 루트 노드

    while (t != NULL)//자식 노드가 없을 경우 빠져나온다.
    {
        if (xkey == t->key) return t;//원하는 노드를 찾았을 경우 반환
        if (xkey < t->key) t = t->l;//현재 노드의 키 값이 찾고자 하는 노드의 키 값보다 클 경우 왼쪽 자식 노드로 이동
        if (xkey > t->key) t = t->r;//반대일 경우
    }
    return NULL;//찾지 못했을 경우
}
struct node *TreeSearchParent(struct node *head, int xkey)
{
    struct node *t;
    t = head->r;//head의 오른쪽 자식 노드가 루트 노드

    while (t != NULL)//자식 노드가 없을 경우 빠져나온다.
    {
        if (xkey < t->key) {
            if (t->l == NULL) return NULL;
            else if (t->l->key == xkey) return t;
            else t = t->l;
        }
        if (xkey > t->key) {
            if (t->r == NULL) return NULL;
            else if (t->r->key == xkey) return t;
            else t = t->r;
        }
    }
    return NULL;//찾지 못했을 경우
}

void TreeInsert(struct node *head, int xkey)
{
    struct node *p, *t;
    t = head->r;
    p = head;
    while (t != NULL)
    {
        p = t;//삽입 될 노드의 부모 노드로 사용된다.
        if (xkey == t->key) return;//같은 키 값을 가진 노드가 있을 경우 돌아간다.
        else if (xkey < t->key) t = t->l;//삽입할 노드의 키 값이 현재 노드보다 작으면 왼쪽 자식 노드로 이동
        else t = t->r;//반대일 경우
    }
    t = (struct node*)malloc(sizeof*t);//메모리 할당
    t->key = xkey; t->l = NULL; t->r = NULL;//삽입 노드 설정
    if (xkey < p->key) p->l = t;//부모 노드의 키 값이 삽입된 노드의 키 값보다 크면 왼쪽 자식으로 설정
    else p->r = t;//반대일 경우
}

void TreeDel(struct node *head, int xkey)
{
    struct node *c, *t, *x, *p;
    x = TreeSearch(head, xkey);//TreeSearch 함수가 head의 오른쪽 자식노드(루트 노드)부터 시작하므로 head
    if (x == NULL) return;//삭제할 노드를 찾지 못했을 경우
    else {//찾았을 경우
        p = TreeSearchParent(head, xkey);//부모 노드도 찾아 놓는다.
        t = x;
    }
    if (t->r == NULL) x = t->l;//삭제할 노드의 오른쪽 자식이 없을 경우 왼쪽 자식 노드를 선택
    else if (t->r->l == NULL)//삭제할 노드의 오른쪽 자식의 왼쪽 자식이 없을 경우
    {
        x = t->r;
        x->l = t->l;
    }
    else//삭제할 노드의 오른쪽 자식의 왼쪽 자식이 있는 경우
    {
        c = x->r;
        while (c->l->l != NULL) c = c->l;
        x = c->l;
        c->l = x->r;
        x->l = t->l;
        x->r = t->r;
    }
    if (xkey < p->key) p->l = x;//삭제될 노드의 부모 노드가 새로운 자식보다 크면 왼쪽에 둔다
    else p->r = x;//반대의 경우
    free(t);//메모리 해제 
}
// 전체 트리를 출력해주는 함수
void print(struct node *head) {
    if (head == NULL) {
        return;
    }
    printf("NODE [%d] > ", head->key);
    
    if (head->l != NULL) {
        printf("LEFT [%d] ", (head->l)->key);
    }
    if (head->r != NULL) {
        printf("RIGHT [%d]", (head->r)->key);
    }
    printf("\n");
    
    if (head->l) {
        print(head->l);
    }
    if (head->r) {
        print(head->r);
    }
}

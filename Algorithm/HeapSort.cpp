//
//  HeapSort.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/04/01.
//  Copyright © 2020 이주원. All rights reserved.
//

#include <iostream>
using namespace std;

void HeapSort(int A[], int n);
void MakeHeap(int A[], int Root, int LastNode);
void swap(int* num, int* minIndex);

int main()
{
    int A[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
    int n = sizeof(A) / sizeof(int);

    for (int i = n / 2 - 1; i >= 0; i--){
        MakeHeap(A, i, n - 1);
    }
    cout << ">> Creating Heap" << endl;
    for (int i = 0; i < n; i++) {
        cout << A[i] << ' ';
    }
    cout << endl;
    
    //힙 정렬
    HeapSort(A, n);
    cout << "\n>> HeapSort " << endl;
    for (int i=0; i<n; i++){
        cout << A[i] << ' ';
    }
    cout << endl;
    return 0;
}

void HeapSort(int A[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        MakeHeap(A, i, n - 1);
    }
    for (int i = n - 1; i > 0; i--) {//루트 값과 마지막 값을 바꾸고 그것을 제외한 후 힙정렬
        swap(&A[0], &A[i]);
        MakeHeap(A, 0, i - 1);
    }
}

void MakeHeap(int A[], int Root, int LastNode)
{
    int Parent, LeftSon, RightSon, Son, RootValue;
    Parent = Root;
    RootValue = A[Root];
    LeftSon = 2 * Parent + 1;
    RightSon = LeftSon + 1;

    while (LeftSon <= LastNode) {//루트를 돌면서 Leftson이 LastNode보다 커지면 빠져나온다(부모 노드의 자식이 없을 경우)
        if (RightSon <= LastNode&&A[LeftSon] < A[RightSon]) {//오른쪽 자식이 크면 son에 index 저장
            Son = RightSon;
        }
        else {
            Son = LeftSon;//왼쪽 자식이 크면 son에 index 저장
        }
        if (RootValue < A[Son]) {
            A[Parent] = A[Son];//루트 값이 자식보다 작으면 자식 값을 올린다.
            Parent = Son;//루트 값이 자식 위치로 이동한 것처럼 설정
            LeftSon = 2 * Parent + 1;//자식 index 재설정
            RightSon = LeftSon + 1;
        }
        else break;
    }
    A[Parent] = RootValue;//맨 위에 있던 루트 값을 마지막에 설정된 위치에 저장
}

void swap(int* num, int* minIndex)
{
    int temp;
    temp = *num;
    *num = *minIndex;
    *minIndex = temp;
}

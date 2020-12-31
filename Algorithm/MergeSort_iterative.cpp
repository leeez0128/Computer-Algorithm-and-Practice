//
//  MergeSort_iterative.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/04/01.
//  Copyright © 2020 이주원. All rights reserved.
//

#include <iostream>
using namespace std;

int length;
void Merge(int* A, int Left, int Mid, int Right)
{
    int *B = new int[length];
    int i, LeftPtr, RightPtr, BufPtr;
    LeftPtr = Left, RightPtr = Mid + 1, BufPtr = Left;

    while (LeftPtr <= Mid && RightPtr <= Right)
    {
        if (A[LeftPtr] < A[RightPtr]) {//둘 중 작은 값을 버퍼에 저장
            B[BufPtr++] = A[LeftPtr++];
        }
        else {
            B[BufPtr++] = A[RightPtr++];
        }
    }//저장 후 각 배열들의 포인터 증가
    if (LeftPtr > Mid)//왼쪽 배열이 끝난 경우 남은 오른쪽 배열을 버퍼에 저장
    {
        for (i = RightPtr; i <= Right; i++) {
            B[BufPtr++] = A[i];
        }
    }
    else//오른쪽 배열이 끝난 경우 남은 왼쪽 배열을 버퍼에 저장
    {
        for (i = LeftPtr; i <= Mid; i++) {
            B[BufPtr++] = A[i];
        }
    }
    for (i = Left; i <= Right; i++) {//원본 배열에 정렬된 버퍼를 저장
        A[i] = B[i];
    }

    for (int i = 0; i < length; i++) {
        cout<<A[i]<<' ';
    }
    cout << endl;
}

void iterMergeSort(int A[], int n)
{
    int Left, Right, Mid;

    for (int i = 1; i < n; i = 2 * i)//배열을 둘로 나눌 수 없는 상태부터 시작하여 간격을 넓히면서 Left, Mid, Right 범위를 바꿔준다.
    {
        Left = 1;                     //ex) i=1일 경우, (Left = 1, Mid = 1, Right = 2)에서 시작하면서 합병
        while (Left <= n)                 //i=2일 경우, (Left = 1, Mid = 2, Right = 4)에서 시작
        {
            Right = Left + 2 * i - 1;
            if (Right > n) {
                Right = n;
            }
            Mid = Left + i - 1;
            if (Mid <= n){
                Merge(A, Left, Mid, Right);
            }
            Left = Right + 1;
        }
    }
}

int main()
{
    int *A;

    cout << "배열의 길이를 입력하세요 : ";
    cin >> length;
    A = new int[length];
    cout << "배열의 값을 입력하세요 : ";
    for (int i = 0; i < length; i++) {
        cin >> A[i];
    }
    cout << ">> 합병정렬이 되는 과정 " << endl;
    iterMergeSort(A, length);

    cout << endl << ">> 합병정렬의 결과" << endl;
    for (int i = 1; i <= length; i++) {
        cout << A[i] << ' ';
    }
    cout << endl;

    return 0;
}

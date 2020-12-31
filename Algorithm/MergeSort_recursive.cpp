//
//  MergeSort_recursive.cpp
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
        if (A[LeftPtr] < A[RightPtr])//둘 중 작은 값을 버퍼에 저장
            B[BufPtr++] = A[LeftPtr++];
        else B[BufPtr++] = A[RightPtr++];
    }//저장 후 각 배열들의 포인터 증가
    if (LeftPtr > Mid)//왼쪽 배열이 끝난 경우 남은 오른쪽 배열을 버퍼에 저장
    {
        for (i = RightPtr; i <= Right; i++)
            B[BufPtr++] = A[i];
    }
    else//오른쪽 배열이 끝난 경우 남은 왼쪽 배열을 버퍼에 저장
    {
        for (i = LeftPtr; i <= Mid; i++)
            B[BufPtr++] = A[i];
    }
    for (i = Left; i <= Right; i++)//원본 배열에 정렬된 버퍼를 저장
        A[i] = B[i];

    for (int i = 0; i < length; i++)
        cout<<A[i]<<' ';
    cout << endl;
}

void MergeSort(int *A, int Left, int Right)
{
    int Mid;
    if (Left < Right)//더 이상 둘로 나눌 수 없을 때 까지 수행
    {
        Mid = (Left + Right) / 2;
        MergeSort(A, Left, Mid);//왼쪽 배열 정렬
        MergeSort(A, Mid + 1, Right);//오른쪽 배열 정렬
        Merge(A, Left, Mid, Right);//합병
    }
}

int main()
{
    int n;
    int *A;

    cout << "배열의 길이를 입력하세요 : ";
    cin >> n;
    A = new int[n];
    length = n;
    cout << "배열의 값을 입력하세요 : ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    cout << ">> 합병정렬이 되는 과정 " << endl;
    MergeSort(A, 0, n - 1);

    cout << endl << ">> 합병정렬의 결과" << endl;
    for (int i = 0; i < n; i++)
        cout << A[i] << ' ';
    cout << endl;

    return 0;
}

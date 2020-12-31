//
//  Find_min_max.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/04/08.
//  Copyright © 2020 이주원. All rights reserved.
//

#include <iostream>
#include <time.h>
using namespace std;

int Minimum(int A[], int n);
int Maximum(int A[], int n);
void FindMinMax(int A[], int n, int *Minimum, int *Maximum);

int main()
{
    int A[1000];
    int Max, Min;

    srand((unsigned)time(NULL));

    for (int i = 0; i < 1000; i++)
    {
        A[i] = rand()%100000+1;//1부터 100000까지 난수 생성
    }
    cout << ">> Minimum()함수를 통한 최소값 : " << Minimum(A, 1000) << endl;
    cout << ">> Maximum()함수를 통한 최대값 : " << Maximum(A, 1000) << endl;

    FindMinMax(A, 1000, &Min, &Max);
    cout << "\n>> FindMinMax() 함수 이용 " << endl;
    cout << "최소값 : " << Min << endl;
    cout << "최대값 : " << Max << endl;

    return 0;
}

int Minimum(int A[], int n)
{
    int i, temp;
    temp = A[0];

    for (i = 1; i < n; i++)//A[i]가 더 작으면 temp에 저장
        if (temp > A[i]) temp = A[i];

    return temp;
}

int Maximum(int A[], int n)
{
    int i, temp;
    temp = A[0];

    for (i = 1; i < n; i++)//A[i]가 더 크면 temp에 저장
        if (temp < A[i]) temp = A[i];

    return temp;
}

void FindMinMax(int A[], int n, int *Minimum, int *Maximum)
{
    int i;
    int Small, Large;
    *Minimum = A[0], *Maximum = A[0];

    for (i = 1; i < n - 1; i += 2)
    {
        /*
        비교하여 작은 값을 Small에 저장
        큰 값은 Large에 저장
        */
        if (A[i] < A[i + 1])
        {
            Small = A[i];
            Large = A[i + 1];
        }
        else
        {
            Small = A[i + 1];
            Large = A[i];
        }
        if (Small < *Minimum) *Minimum = Small;//Minimum이 더 크면 갱신
        if (Large > *Maximum) *Maximum = Large;//Maximum이 더 작으면 갱신
    }
    return;
}

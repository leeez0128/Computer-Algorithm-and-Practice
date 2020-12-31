//
//  DynamicChange.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/04/17.
//  Copyright © 2020 이주원. All rights reserved.
//

#include <iostream>
using namespace std;
static int CoinChange(int m, int* c, int n)
{
    int *M = new int[m+1];//dynamic programming을 통해 1~m원 각각 필요한 동전의 최소 개수를 저장하는 배열
    int *subM = new int[m+1];//1~m원 각각의 단계에서 어떤 동전이 저장되는 지 알 수 있다.
    //이 때 subM[]에 저장되는 값 (0,1,...n-1)이 가리키는 값은 갖고 있는 동전을 내림차순으로 입력한 순서대로 그 동전의 index를 나타낸다.
    
    M[0]=0;  //0원에 대한 필요한 동전의 최소 개수는 0이다.
    for (int i = 1; i <= m; i++) {
        M[i]=INT_MAX-1; //1~m까지 M[] 초기화
        subM[i]=-1; //초기화
    }
    
    //dynamic programming 결과 도출하는 부분
    for(int i=1; i<=m; i++) { //각 1~m까지의 금액별로
        for(int j=0; j<n; j++) { //각 동전종류index에 대해 for문을 돌린다.
            if(i >= c[j]) { //1..m의 값이 동전 금액 보다 크거나 같을 때
                if(M[i-c[j]]+1<M[i]) { //M[i에서 c[j]값을 뺀 값(c[j]만큼 back tracking)]+1이 현재 M[i]값보다 작으면
                    M[i] = M[i-c[j]]+1; //M[i에서 c[j]값을 뺀 값(c[j]만큼 back tracking)]+1으로 M[i]를 갱신한다.
                    subM[i]=j; //어떤 동전(index)이 쓰였는지 알기 위해 저장한다.
                }
            }
        }
    }
    return M[m]; //M[m]을 반환하면서 필요한 최소 동전 개수가 출력되도록 한다.
}

int main()
{
    int m = 0;
    int n = 0;
    cout << "M값을 입력하세요 : " ;
    cin >> m;
    cout << "갖고 있는 동전의 종류의 수를 입력하세요 : ";
    cin >> n;
    int* c  = new int[n];
    cout << "갖고 있는 동전의 종류를 입력해주세요 : ";
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    cout << ">> M값에 따른 최소 동전의 개수" << endl;
    for(int i=1;i<=m;i++){
        printf("M = %2d => %d개\n",i,CoinChange(i, c, n));
    }
    return 0;
}

//
//  GreedyBetterChange.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/03/24.
//  Copyright © 2020 이주원. All rights reserved.
//

#include <iostream>

void GreedyBetterChange(int M, int *c, int d){
    int *k = new int[d]; //각각의 동전이 얼마나 필요할 지 세어줄 배열 생성
    // for문을 통해 사용가능한 가장 큰 동전을 먼저 사용하고
    // 그 다음단계에서는 전 단계 이후 남은 금액에서 사용가능한 가장 큰 동전을 사용한다.
    // 남은 금액이 없을 때까지 계속 수행한다.
    int cnt=0; //총 동전의 개수의 합
    printf("필요한 동전 조합 : ( ");
    for(int i=0; i<d; i++){ // 동전의 종류 수만큼 greedy algorithm 실행
        // 이 때, greedy algorithm은 가장 큰 값을 가지는 coin을 먼저 사용하기 때문에
        // 동전 사용은 k[0]부터 k[4]과 같이 내림차순으로 진행한다.
        k[i]=M/c[i];
        M = M - c[i]*k[i]; // 각 해당하는 동전에 대해 필요한 개수와 곱을 하고 총액에서 뺀다.
        cnt+=k[i];
        printf("%d ",k[i]);
    }
    printf(")\n필요한 동전의 총 개수 : %d\n",cnt);
}

int main(int argc, const char * argv[]) {
    // 사용자로부터 M, d, c 입력받는다.
    // M : 바꾸고 싶은 돈의 액수,
    // d : 갖고 있는 동전 종류의 수(배열 c의 크기)
    // c : 갖고 있는 동전 종류(배열로 저장),
    
    printf("M값을 입력하세요 : ");
    int M=0;
    std::cin>>M;
    printf("갖고 있는 동전 종류의 개수를 입력하세요 : ");
    int d=0;
    std::cin>>d;
    printf("갖고 있는 동전 종류를 내림차순으로 입력하세요 : ");
    int *c=new int[d];
    for(int i=0;i<d;i++){
        std::cin>>c[i];
    }
    GreedyBetterChange(M, c, d);
    return 0;
}

//
//  Compare_greedy_bruteforce.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/03/24.
//  Copyright © 2020 이주원. All rights reserved.
//

#include <iostream>

int GreedyBetterChange(int M, int *c, int d){
    int *k = new int[d]; //각각의 동전이 얼마나 필요할 지 세어줄 배열 생성
    // for문을 통해 사용가능한 가장 큰 동전을 먼저 사용하고
    // 그 다음단계에서는 전 단계 이후 남은 금액에서 사용가능한 가장 큰 동전을 사용한다.
    // 남은 금액이 없을 때까지 계속 수행한다.
    int cnt=0; //총 동전의 개수의 합
    for(int i=0; i<d; i++){ // 동전의 종류 수만큼 greedy algorithm 실행
        // 이 때, greedy algorithm은 가장 큰 값을 가지는 coin을 먼저 사용하기 때문에
        // 동전 사용은 k[0]부터 k[4]과 같이 내림차순으로 진행한다.
        k[i]=M/c[i];
        M = M - c[i]*k[i]; // 각 해당하는 동전에 대해 필요한 개수와 곱을 하고 총액에서 뺀다.
        cnt+=k[i];
    }
    return cnt;
}

int BruteForceChange(int M, int*c, int d){
    int smallestNumberOfCoins = INT_MAX;
    int *k=new int[d];
    memset(k,0,sizeof(k));
    int valueOfCoins=0;
    int numberOfCoins=0;
    
    for(k[0]=0; M-k[1]*c[1]-k[2]*c[2]-k[3]*c[3]-k[4]*c[4]-k[5]*c[5]>=k[0]*c[0]; k[0]++) {
        for(k[1]=0; M-k[0]*c[0]-k[2]*c[2]-k[3]*c[3]-k[4]*c[4]-k[5]*c[5]>=k[1]*c[1]; k[1]++) {
            for(k[2]=0; M-k[0]*c[0]-k[1]*c[1]-k[3]*c[3]-k[4]*c[4]-k[5]*c[5]>=k[2]*c[2]; k[2]++) {
                for(k[3]=0; M-k[0]*c[0]-k[1]*c[1]-k[2]*c[2]-k[4]*c[4]-k[5]*c[5]>=k[3]*c[3]; k[3]++) {
                    for(k[4]=0; M-k[0]*c[0]-k[1]*c[1]-k[2]*c[2]-k[3]*c[3]-k[5]*c[5]>=k[4]*c[4]; k[4]++) {
                        for(k[5]=0; M-k[0]*c[0]-k[1]*c[1]-k[2]*c[2]-k[3]*c[3]-k[4]*c[4]>=k[5]*c[5]; k[5]++) {
                            for(int i=0; i<d; i++) {
                                valueOfCoins+=c[i]*k[i]; //동전의 종류(c)가 몇개(k)있는지에 따라 해당 동전으로 만드는 돈의 액수
                            }
                            if(valueOfCoins==M) {
                                for(int i=0; i<d; i++) {
                                    numberOfCoins+=k[i];
                                }
                                if(numberOfCoins < smallestNumberOfCoins) {
                                    smallestNumberOfCoins=numberOfCoins;
                                }
                            }
                            valueOfCoins=0;
                        }
                        numberOfCoins=0;
                        k[5]=0;
                    }
                    k[4]=0;
                }
                k[3]=0;
            }
            k[2]=0;
        }
        k[1]=0;
    }
    return smallestNumberOfCoins;
}

int main(int argc, const char * argv[]) {
    // 사용자로부터 M, d, c 입력받는다.
    // M : 바꾸고 싶은 돈의 액수,
    // d : 갖고 있는 동전 종류의 수(배열 c의 크기)
    // c : 갖고 있는 동전 종류(배열로 저장),
    
    printf("M의 값 : 1~100, c = {55,22,15,10,7,1}\n");
    int d=6;
    int c[]={55,22,15,10,7,1};
    int BFCResult=0, BGCResult=0;
    for(int i=1; i<=100; i++) {
        
        BGCResult= GreedyBetterChange(i, c, d);
        BFCResult= BruteForceChange(i, c, d);
        
        if(BGCResult != BFCResult) {
            std::cout<<"M의 값 : "<<i<<' ';
            std::cout<<"BetterGreedyChange의 결과 : "<<BGCResult<<' ';
            std::cout<<"BruteForceChange의 결과 : "<<BFCResult<<std::endl;
        }
    }
    return 0;
}

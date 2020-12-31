//
//  BruteForceChange.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/03/24.
//  Copyright © 2020 이주원. All rights reserved.
//

#include <iostream>

void BruteForceChange(int M, int*c, int d){
    int smallestNumberOfCoins = INT_MAX;
    int *k=new int[d];
    memset(k,0,sizeof(k));
    int valueOfCoins=0;
    int numberOfCoins=0;
    int bestChange[d];
    
    for(k[0]=0;M-k[1]*c[1]-k[2]*c[2]-k[3]*c[3]-k[4]*c[4]>=k[0]*c[0];k[0]++){
        for(k[1]=0;M-k[0]*c[0]-k[2]*c[2]-k[3]*c[3]-k[4]*c[4]>=k[1]*c[1];k[1]++){
            for(k[2]=0;M-k[0]*c[0]-k[1]*c[1]-k[3]*c[3]-k[4]*c[4]>=k[2]*c[2];k[2]++){
                for(k[3]=0;M-k[0]*c[0]-k[1]*c[1]-k[2]*c[2]-k[4]*c[4]>=k[3]*c[3];k[3]++){
                    for(k[4]=0;M-k[0]*c[0]-k[1]*c[1]-k[2]*c[2]-k[3]*c[3]>=k[4]*c[4];k[4]++){
                        for(int i=0; i<d; i++){
                            valueOfCoins += c[i]*k[i];
                        }
                        if(valueOfCoins==M){
                            for(int i=0; i<d; i++){
                                numberOfCoins += k[i];
                            }
                            if(numberOfCoins < smallestNumberOfCoins || smallestNumberOfCoins==-1){
                                smallestNumberOfCoins=numberOfCoins;
                                for(int i=0;i<d;i++){
                                    bestChange[i]=k[i];
                                }
                            }
                        }
                        valueOfCoins=0;
                    }
                    numberOfCoins=0;
                    k[4]=0;
                }
                k[3]=0;
            }
            k[2]=0;
        }
        k[1]=0;
    }
    std::cout<<"필요한 동전 조합 : ("<<' ';
    for(int best:bestChange){
        std::cout<<best<<' ';
    }
    std::cout<<")"<<std::endl;
    std::cout<<"필요한 동전 수의 합 : "<<' ';
    std::cout<<smallestNumberOfCoins<<std::endl;
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
    BruteForceChange(M, c, d);
    return 0;
}

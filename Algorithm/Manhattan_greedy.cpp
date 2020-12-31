//
//  Manhattan_greedy.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/04/08.
//  Copyright © 2020 이주원. All rights reserved.
//

#include <iostream>
#define M_size 3 //manhattan distance problem을 풀어나가기 위해 제시되는 map size
using namespace std;

struct map{ //struct를 이용하여 map의 right, bottom을 정의
    int right;
    int bottom;
}map[M_size][M_size];

void greedy(int i, int j){ //greedy algorithm을 이용하여 manhattan distance problem을 해결한다.
    if(map[i][j].right>map[i][j].bottom){ //map의 오른쪽 값이 더 클 경우, 오른쪽으로 이동
        printf("map[%d][%d] ",i,j+1); //이동하는 포인트를 출력
        greedy(i, j+1); //다음 포인트에서 똑같이 greedy를 진행
    }
    if(map[i][j].right<map[i][j].bottom){ //map의 아래 값이 더 클 경우, 아래쪽으로 이동
        printf("map[%d][%d] ",i+1,j); //이동하는 포인트를 출력
        greedy(i+1, j); //다음 포인트에서 똑같이 greedy를 진행
    }
}

int main(void){
    
    //사용자로부터 map의 각 포인트로 가는 가중치를 입력받는다.
    for(int i=0;i<M_size;i++){
        for(int j=0;j<M_size;j++){
            printf("Enter the weight of map[%d][%d].right, map[%d][%d].bottom(input example : 3 1) : ",i,j,i,j);
            scanf("%d %d",&map[i][j].right, &map[i][j].bottom);
        }
    }
    
    printf(">> RESULT\nmap[0][0] "); //처음 시작포인트 출력
    greedy(0,0); //map[0][0]부터 greedy algorithm을 진행
    printf("\n");
    
    return 0;
}

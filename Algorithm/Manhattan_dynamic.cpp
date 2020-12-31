//
//  Manhattan_dynamic.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/04/17.
//  Copyright © 2020 이주원. All rights reserved.
//

#include <iostream>
#define M_size 5 //manhattan distance problem을 풀어나가기 위해 제시되는 map size
using namespace std;

struct weight{ //struct를 이용하여 weight의 right, bottom을 정의
    int right;
    int bottom;
}weight[M_size][M_size];
int map[M_size][M_size]={0,};

void ManhattanTourist(int right, int bottom, int row, int column){
    for(int i=1; i<column; i++){ //맨 왼쪽 한 열 채우는 방법 -> 전의 vertex에 남측 가중치를 더한다.
        map[i][0]=map[i-1][0]+weight[i-1][0].bottom;
    }
    for(int j=1; j<row; j++){ //맨 윗줄 한 행 채우는 방법 -> 전의 vertex에 우측 가중치를 더한다.
        map[0][j]=map[0][j-1]+weight[0][j-1].right;
    }
    for(int i=1; i<column; i++){
        for(int j=1; j<row; j++){
            if(weight[i][j-1].right+map[i][j-1]>weight[i-1][j].bottom+map[i-1][j]){ //옆의 vertex에 right를 더한 값이 위의 vertex에 bottom를 더한 값보다 크면
                map[i][j]=weight[i][j-1].right+map[i][j-1]; // 현재 vertex는 옆의 vertex에 right를 더한 값
            } else{ // 옆의 vertex에 edge를 더한 값이 위의 vertex에 edge를 더한 값보다 작으면
                map[i][j]=weight[i-1][j].bottom+map[i-1][j]; // 현재 vertex는 위의 vertex에 bottom를 더한 값
            }
        }
    }
}

int main(void){
    //사용자로부터 map의 각 포인트로 가는 가중치를 입력받는다.
    for(int i=0;i<M_size;i++){
        for(int j=0;j<M_size;j++){
            printf("Enter the weight[%d][%d].right, weight[%d][%d].bottom(input example : 3 1) : ",i,j,i,j);
            scanf("%d %d",&weight[i][j].right, &weight[i][j].bottom);
            
        }
    }
    for(int i=0;i<M_size;i++){
        for(int j=0;j<M_size;j++){
            ManhattanTourist(weight[i][j].right, weight[i][j].bottom, M_size, M_size); //ManhattanTourist problem을 dynamic program으로 실행
            printf("map[%d][%d]=%2d ",i,j,map[i][j]);
        }
        printf("\n");
    }
    return 0;
}

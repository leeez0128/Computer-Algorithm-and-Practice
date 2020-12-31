//
//  TrivialMapping.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/05/19.
//  Copyright © 2020 이주원. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
#define N 500000 //Reference와 MyDNA의 길이(500000)
#define n 15000 //shortread의 개수
#define k 60 //shortread 길이
#define miss 2
using namespace std;
//reference 만들고 snp줘서 내 dna만든다음에 shortread만들어.shortread를 복원할 때 ref랑 이용해서 mydna 복원. 일치율 얼만지

char* DNA_rand(){
    char DNA[4]={'A','C','G','T'}; //A=T, G 삼중 C
    srand((unsigned)time(NULL));
    char* ref = new char[N];
    for(int i=0; i<N; i++){
        int R = rand()%4;//0부터 100000까지 난수 생성
        ref[i]=DNA[R];
    }
    return ref;
}

int bruteSearch(char *p, char *a) {
    int i, j, mismatch=0;
    int index=-1;
   
    for (i = 0; i <= N - k; i++) {//텍스트와 패턴을 처음부터 전부 비교
        for (j = 0; j < k; j++) {
            if (a[i + j] != p[j]) {
                mismatch++;
            }
            if(a[i + j] != p[j] && mismatch>miss) {
                break;
            }
        }
        if (j == k){
//            printf("%d mismatch : %d\n",i, mismatch);
            index=i;
            break;
        }
        mismatch=0; //shortread당 miss match 수 2개 이하로 잡았으므로 하나의 shortread 검사가 끝나면 miss match를 0으로 초기화
    }
    return index;
}


int main(void) {
    //ref 생성
    char* ref= DNA_rand();
    //WRITE FILE
    ofstream writeFile;
    writeFile.open("Reference.txt");
    writeFile.write(ref,N);
    writeFile.close();
    
    
    char* myDNA=ref;
    //shortread당 평균적으로 2개이상의 snip이 있으므로
    //총 dna길이에서 n*2개의 snp을 발생시킨다.
    //snp가 발생하는 위치 또한 랜덤으로 발생
    for(int i=0; i<n*2; i++){
        char temp[4]={'A','C','G','T'};
        int R=rand()%4;
        myDNA[rand()%N]=temp[R];
    }
    ofstream writeFile2;
    writeFile2.open("myDNA.txt");
    writeFile2.write(myDNA,N);
    writeFile2.close();
    
    
    char buffer[k + 1];
    char shortread[n][k];
    fpos_t pos = 0;
    int i = 0;
    
    
    srand((unsigned)time(NULL));
    
    
    //myDNA에서 임의의 위치를 선정하여(랜덤함수 이용) k 길이의 shortread를 n개만큼 생성
    ofstream writeFile3;
    writeFile3.open("shortread.txt");
    for(int i=0; i<n; i++){
        int temp=rand()%N;
        if(N-temp>=k){ //임의로 선정된 위치는 k길이만큼 자를 수 있는 위치여야 함.
            for(int j=0; j<k;j++){
                shortread[i][j]=myDNA[temp+j];
            }
//            printf("%d shortread : %s\n", i,shortread[i]);
            writeFile3.write(shortread[i],k);
        }
        
    }
   
   
    writeFile3.close();
    
    
    char recover[N]={0,};//shortread를 기반으로 복원하는 myDNA, 추후에 앞서 만들어놓았던 myDNA와 비교하여 일치율을 확인할 것임
    
    time_t start, end;
    double result;
    start = clock(); // 수행 시간 측정 시작
    
    for(int i=0; i<n; i++){
        int tmp=bruteSearch(shortread[i], ref); //shortread 한개씩 bruteforce로 비교.
        if(tmp!=-1){ //설정된 miss 개수보다 missmatch의 수가 많은 경우 -1를 반환, 그 외의 경우는 shortread가 매치되는 reference에서의 첫 인덱스가 반환됨
            for(int j=0; j<k; j++){
                recover[tmp+j]=shortread[i][j]; //반환된 인덱스를 시작으로 해당 shortread의 길이인 k만큼을 recover에 저장
            }
        } else{
//            printf("all results return -1\n");
        }
    }
    
    end = clock(); //시간 측정 끝
    result = (double)(end - start);
    cout << "It takes " << ((result) / CLOCKS_PER_SEC) << "seconds" << endl;

    
    ofstream writeFile4;
    writeFile4.open("recover.txt");
    writeFile4.write(recover,N);
    writeFile4.close();
    
    
    //myDNA와 recover(복원된 DNA) 사이의 일치율을 확인하기 위해 서로 다른 값을 가진 경우 cnt를 증가시킨다.
    int cnt=0;
    for(int i=0; i<N; i++){
        if(myDNA[i]!=recover[i]){
            cnt++;
        }
    }
    printf("not matched : %d\n",cnt);
    
    //길이가 N인 DNA에서 N-cnt만큼 일치하였으므로 일치율은 N-cnt/N * 100이다.
    float matchrate=(float)(N-cnt)/N*100;
//    printf("matchrate %f",matchrate);
    cout << "matchrate : " << matchrate << "%" << endl;
    
}

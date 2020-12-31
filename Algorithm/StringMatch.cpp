//
//  StringMatch.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/05/10.
//  Copyright © 2020 이주원. All rights reserved.
//
#include <iostream>
#include <time.h>
using namespace std;
int *SP;
const int q = 33554393; //mod계산을 위한 소수
const int d = 26; //알파벳 총 개수
void bruteSearch(char *p, char *a);
void kmpSearch(char *p, char *a);
void initSP(char *p);
void rkSearch(char *p, char *a);
int index(char c);

int main()
{
    char textString[100000];
    char patternString[100000];
    cout << "TEXT STRING: ";
    fgets(textString, sizeof(textString), stdin);
    textString[strlen(textString) - 1] = 0;
    cout << "PATTERN STRING: ";
    fgets(patternString, sizeof(patternString), stdin);
    patternString[strlen(patternString) - 1] = 0;
    cout << "==================================================" << endl;
    
    cout << "Brute-Force Result▼" << endl;
    bruteSearch(patternString, textString);
    cout << "==================================================" << endl;
    cout << "KMPSearch Result▼" << endl;
    kmpSearch(patternString, textString);
    cout << "==================================================" << endl;
    cout << "Rabin-Karp Result▼" << endl;
    rkSearch(patternString, textString);
    cout << endl;
    
    return 0;
}

void bruteSearch(char *p, char *a) {
    time_t start, end;
    double result;
    int i, j, m = strlen(p), n = strlen(a);
    start = clock(); // 수행 시간 측정 시작
    for (i = 0; i <= n - m; i++) {//텍스트와 패턴을 처음부터 전부 비교
        for (j = 0; j < m; j++)
            if (a[i + j] != p[j])break;
        if (j == m)
            printf("The pattern matches at text[%d]\n", i);
    }
    end = clock(); //시간 측정 끝
    result = (double)(end - start);
    cout << "It takes " << ((result) / CLOCKS_PER_SEC) << "seconds" << endl;
}

void kmpSearch(char *p, char*a) {
    time_t start, end;
    double result;
    int i, j, m = strlen(p), n = strlen(a);
    SP = new int[strlen(p)];
    initSP(p);
    start = clock(); // 수행 시간 측정 시작
    for (i = 0, j = -1; i <= n - 1; i++) {
        while ((j >= 0) && (p[j + 1] != a[i]))j = SP[j];//다르면 k를 SP값으로 수정
        if (p[j + 1] == a[i])j++;//같으면 j값을 증가
        if (j == m - 1) {
            printf("The pattern matches at text[%d]\n", i-j);
            j = SP[j];
        }
    }
    delete SP;
    end = clock(); //시간 측정 끝
    result = (double)(end - start);
    cout << "It takes " << ((result) / CLOCKS_PER_SEC) << "seconds" << endl;
}

void initSP(char *p) {
    int i, j, m = strlen(p);
    SP[0] = -1;
    for (i = 1, j = -1; i <= m - 1; i++) {
        while ((j >= 0) && (p[j + 1] != p[i]))j = SP[j];//다르면 k를 SP값으로 수정
        if (p[j + 1] == p[i])j++;//같으면 j값을 증가
        SP[i] = j;
    }
}

void rkSearch(char *p, char *a)
{
    time_t start, end;
    double result;
    int i, j, h1 = 0, h2 = 0, dM = 1, flag;
    int n = strlen(a), m = strlen(p);
    start = clock(); // 수행 시간 측정 시작
    for (i = 1; i < m; i++) dM = (d*dM) % q;
    
    for (i = 0; i < m; i++) {
        h1 = (d*h1 + index(p[i])) % q;//해시 값 계산
        h2 = (d*h2 + index(a[i])) % q;//해시 값 계산
    }
    
    for (i = 0; i <= n - m; i++) {
        if (h1 == h2) { //해시 값이 동일한 경우에 한해 자세한 패턴 매칭을 진행
            flag = 1;
            for (j = 0; j < m; j++)
                if (p[j] != a[i + j]) {
                    flag = 0;
                    break;
                }
            
            if (flag) printf("The pattern matches at text[%d]\n", i);
        }
        //해시 값이 다를 경우 이전에 사용했던 해시 값 이용-->mod연산을 통한 hash값 계산으로 h2의 빠른 계산 가능
        else h2 = (d*(h2 - ((index(a[i])*dM) % q)) + index(a[i + m])) % q;
    }
    end = clock(); //시간 측정 끝
    result = (double)(end - start);
    cout << "It takes " << ((result) / CLOCKS_PER_SEC) << "seconds" << endl;
}

int index(char c) { //알파벳의 각 문자에 대한 정수값을 반환.
    if (c >= 'A' && c <= 'Z') //index로 넘어온 문자가 대문자 A-Z일 경우, 해당 문자에서 대문자 A를 뺀 값을 반환한다.
        return c - 'A'; //즉, 'index로 넘어온 문자의 아스키'-65가 반환된다.
    else return c - 'a' + 26; //index로 넘어온 문자가 소문자 a-z일 경우, 해당 문자에서 'a'의 아스키값 97을 뺀 후 26을 더한값을 반환한다.
    //즉, 알파벳이 패턴이라고 가정할 때
    //대문자들은 각각 0부터 25로, 소문자들은 각각 26부터 41로 반환된다.
}

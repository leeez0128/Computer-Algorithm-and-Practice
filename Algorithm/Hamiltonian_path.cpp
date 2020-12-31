//
//  Hamiltonian_path.cpp
//  Algorithm
//
//  Created by 이주원 on 2020/05/25.
//  Copyright © 2020 이주원. All rights reserved.
//

/* C++ program for solution of Hamiltonian
Cycle problem using backtracking */
#include <iostream>
using namespace std;


#define n 10
#define l 3
// Number of vertices in the graph
#define V n-l+1

void printSolution(int path[]);

/* A utility function to check if
the vertex v can be added at index 'pos'
in the Hamiltonian Cycle constructed
so far (stored in 'path[]') */
bool isSafe(int v, bool graph[V][V],
   int path[], int pos)
{
   /* Check if this vertex is an adjacent
   vertex of the previously added vertex. */
   if (graph[path[pos - 1]][v] == 0)
      return false;

   /* Check if the vertex has already been included.
   This step can be optimized by creating
   an array of size V */
   for (int i = 0; i < pos; i++)
      if (path[i] == v)
         return false;

   return true;
}

/* A recursive utility function
to solve hamiltonian cycle problem */
bool hamCycleUtil(bool graph[V][V],
   int path[], int pos)
{
   /* base case: If all vertices are
   included in Hamiltonian Cycle */
   if (pos == V)
   {
      // And if there is an edge from the
      // last included vertex to the first vertex
      if (graph[path[pos - 1]][path[0]] == 1)
         return true;
      else
         return false;
   }

   // Try different vertices as a next candidate
   // in Hamiltonian Cycle. We don't try for 0 as
   // we included 0 as starting point in hamCycle()
   for (int v = 1; v < V; v++)
   {
      /* Check if this vertex can be added
      // to Hamiltonian Cycle */
      if (isSafe(v, graph, path, pos))
      {
         path[pos] = v;

         /* recur to construct rest of the path */
         if (hamCycleUtil(graph, path, pos + 1) == true)
            return true;

         /* If adding vertex v doesn't lead to a solution,
         then remove it */
         path[pos] = -1;
      }
   }

   /* If no vertex can be added to
   Hamiltonian Cycle constructed so far,
   then return false */
   return false;
}

/* This function solves the Hamiltonian Cycle problem
using Backtracking. It mainly uses hamCycleUtil() to
solve the problem. It returns false if there is no
Hamiltonian Cycle possible, otherwise return true
and prints the path. Please note that there may be
more than one solutions, this function prints one
of the feasible solutions. */
bool hamCycle(bool graph[V][V])
{
   int *path = new int[V];
   for (int i = 0; i < V; i++)
      path[i] = -1;

   /* Let us put vertex 0 as the first vertex in the path.
   If there is a Hamiltonian Cycle, then the path can be
   started from any point of the cycle as the graph is undirected */
   path[0] = 0;
   if (hamCycleUtil(graph, path, 1) == false)
   {
      cout << "\nSolution does not exist";
      return false;
   }

   printSolution(path);
   return true;
}

/* A utility function to print solution */
void printSolution(int path[])
{
   cout << "Solution Exists:"
      " Following is one Hamiltonian Cycle \n";
   for (int i = 0; i < V; i++)
      cout << path[i] << " ";

   // Let us print the first vertex again
   // to show the complete cycle
   cout << path[0] << " ";
   cout << endl;
}

// Driver Code
int main()
{
   /* Let us create the following graph
   (0)--(1)--(2)
   | / \ |
   | / \ |
   | / \ |
   (3)-------(4) */
    //k mers
    //Spectrum(s1, 3) = {AGT, AAA, ACT, AAC, CTT, GTA, TTT, TAA}
   bool graph1[V][V] = { { 0, 1, 0, 0, 0, 0, 0, 0 },
   { 1, 0, 1, 0, 0, 0, 0, 0 },{ 0, 1, 0, 1, 0, 0, 0, 0 },{ 0, 0, 1, 0, 1, 0, 0, 0 },
       { 0, 0, 0, 1, 0, 1, 0, 0 },{ 0, 0, 0, 0, 1, 0, 1, 0 },{ 0, 0, 0, 0, 0, 1, 0, 1 },
       { 0, 1, 0, 0, 0, 0, 1, 0 },
   };

   // Print the solution
   hamCycle(graph1);

//   /* Let us create the following graph
//   (0)--(1)--(2)
//   | / \ |
//   | / \ |
//   | / \ |
//   (3) (4) */
//   bool graph2[V][V] = { { 0, 1, 0, 1, 0 },
//   { 1, 0, 1, 1, 1 },
//   { 0, 1, 0, 0, 1 },
//   { 1, 1, 0, 0, 0 },
//   { 0, 1, 1, 0, 0 } };
//
//   // Print the solution
//   hamCycle(graph2);

   return 0;
}


//#include <iostream>
//#include <stdlib.h>
//#include <string>
//using namespace std;
//
//
//void printarray(char** arr, int m, int n) {
//    for (int i = 0; i < m; i++) {
//        for (int j = 0; j < n; j++) {
//            printf("%c", arr[i][j]);
//        }
//        printf(", ");
//    }
//    printf("}\n");
//}
//
//
//void hamil(char** arr, int m, int n) {
//   bool* visit=new bool[m];
//   for (int i = 0; i < m; i++) {
//      arr[i]
//   }
//}
//
//
//int main(void) {
//    int n=0;
//    printf("**Spectrum(s, l)**\nEnter the s's length : ");
//    scanf("%d", &n);
//    printf("Enter the s : ");
//    char *s=new char[n];
//    cin >> s;
//
//
//    int l;//spectrum(s,l) "l"
//    printf("Enter the l : ");
//    scanf("%d", &l);
//
//
//    char **spec;
//    spec = new char*[n - l + 1];
//    for (int i = 0; i < n - l +1; i++) {
//        spec[i] = new char[l];
//    }
//
//
//    for (int i = 0; i < n - l + 1; i++) {
//        for (int j = 0; j < l; j++) {
//            spec[i][j] = s[i+j];
//        }
//    }
//
//    printf("spectrum is made = { ");
//    printarray(spec, n - l + 1, l);
//
//    hamil(spec, n - l + 1, l);
//
//
//
//    for (int i = 0; i < n-l+1; i++)
//        delete[] spec[i];
//    delete[] spec;
//
//    return 0;
//}

//// 2014112052 배재현
//#include <iostream>
//#define n 10
//#define l 3
//#define k n-l+1
//using namespace std;
//
//string hamil(char* spec[]){
//    //spec[i]     => 'agt' 이거 덩어리 하나
//    //spec[i][j]  => 'agt' 덩어리에서 'a' 하나
//    bool visit[k];
//    string spectrum="";
//    for(int i=0; i<k; i++){
//        for(int j=0; j<l;j++){
//
//        }
//
//    }
//    return spectrum;
//}
//
////k mers
////Spectrum(s1, 3) = {AGT, AAA, ACT, AAC, CTT, GTA, TTT, TAA}
//int main(void){
//
//    char *spec[k]={"AGT", "AAA", "ACT", "AAC", "CTT", "GTA", "TTT", "TAA"};
//    //printf("spec[0][1] : %c",spec[0][1]);
//    string spectrum=hamil(spec);
//    cout << spectrum << endl;
//}

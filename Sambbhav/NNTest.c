#include<stdio.h>
#define IGNORE 65535

// int findMax(int i){
// }

int main(){
  int i=0, j, n, count, next_i, min = IGNORE;
  printf("Enter no. of Nodes: ");
  scanf("%d", &n);
  unsigned int graph[n][n];

  for(i=0; i<n; i++){
    for(j=i; j<n; j++){
      if(i==j){
        graph[i][j] = IGNORE;
        continue;
      }
      scanf("%d", &graph[i][j]);
      graph[j][i] = graph[i][j];
    }
  }

  for(i=0; i<n; ){
    for(j=0; j<n; j++){
      if (graph[i][j] < min){
        min = graph[i][j];
      }
      i = j;
      printf("%d->", i)
    }
    // min in 0th row->go to that index as row->min in that row
  }

  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      printf("%d ", graph[i][j]);
    }
    printf("\n");
  }
}

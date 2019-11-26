#include<stdio.h>
#define IGNORE 65535
int main(){
  int i,j,n;
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

  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      printf("%d ", graph[i][j]);
    }
    printf("\n");
  }
}

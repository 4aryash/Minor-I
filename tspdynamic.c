//This Program will calculate minimum weight hamiltonian cycle using Dynnamic programming approach when matrix is symmetric

#include<stdio.h>
#include<time.h>

int node_table[10][10];
int traversed[10];
int n,cost=0;

void get(){
	int i,j;
	printf("Enter No. of Cities: ");
	scanf("%d",&n);
	
	printf("\nEnter Cost Matrix\n");
	
	for(i=0;i < n;i++){
		printf("\nEnter Elements of Row # : %d\n",i+1);
		for( j=0;j < n;j++)
			scanf("%d",&node_table[i][j]);
		traversed[i]=0;
	}
	
	printf("\n\nThe cost list is:\n\n");
	for( i=0;i < n;i++){
		printf("\n\n");
		for(j=0;j < n;j++)
			printf("\t%d",node_table[i][j]);
	}
}

int lowest(int c){
	int i,nc=1000;
	int min=1000,kmin;
	
	for(i=0; i<n; i++){
		if((node_table[c][i]!=0)&&(traversed[i]==0))
			if(node_table[i][c] + node_table[c][i] < min){
				min=node_table[i][0]+node_table[c][i];
				kmin=node_table[c][i];
				nc=i;
			}
	}
	
	if(min!=1000)
		cost+=kmin;
	return nc;
}

float mincost(int city){
	
		double time_spent = 0.0;
	clock_t begin = clock();
	
	int i,ncity;
	traversed[city]=1;	
	
	printf("%d -->",city+1);
	
	ncity=lowest(city);
	if(ncity==1000){
		ncity=0;
		printf("%d",ncity+1);
		cost+=node_table[city][ncity];
		return;
	}
	mincost(ncity);

	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    return time_spent;
}


void put(){
	printf("\n\nMinimum cost:");
	printf("%d",cost);
}

int main(){
	float time_spent;
	get();
	printf("\n\nThe Path is:\n\n");
	time_spent=mincost(0);
	put();
     
    printf("\n\ntotal time spent is %f", time_spent);
	return 0;
}

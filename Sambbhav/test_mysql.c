#include<stdio.h>
#include<mysql.h>
#include<stdlib.h>
#include<time.h>


MYSQL_ROW row;
MYSQL *con;
MYSQL_RES *res;
int n, num_rows, num_fields, n, cost=0, fprice=0, grossValue=0;
float MULT[num_rows][num_fields];
int node_table[num_rows][num_fields];
char *server = "localhost";
char *user = "Minor";
char *password = "minor1";
char *database = "RTable";
int traversed[num_rows];

void finish_with_error(MYSQL *con){
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

// ENTER DB NAME TO BE ENTERED
void createDatabase(char * DBName){
  if(mysql_real_connect(con, server, user, password, NULL, 0, NULL, 0) == NULL){
    finish_with_error(con);
  }
  if (mysql_query(con, "CREATE DATABASE RTable")){
    finish_with_error(con);
  }
}

// RECEIVE TABLE NAME & AND FIELDS TO BE ENTERED
void createTable(char * TableName){
  printf("If this table exists, it will be dropped. Do you accept? (y/n)\n");

  char choice;
  scanf("%c", &choice);

  if(choice == 'y' || choice == 'Y'){
    if(mysql_query(con, "DROP TABLE IF EXISTS DISTANCES")){
        finish_with_error(con);
    }

    if (mysql_query(con, "CREATE TABLE DISTANCES(A FLOAT, B FLOAT, C FLOAT, D FLOAT)")){
      finish_with_error(con);
    }
  }
  else{
    printf("You chose not to drop existing databases.\n");
  }
}

// RECEIVE VALUES TO BE ENTERED
void insertValues(){
  if(mysql_query(con, "INSERT INTO DISTANCES VALUES(4.70, 5.75, 3.99, 4.12)")){
    finish_with_error(con);
  }
}
// ----------------------------------------------------------------------------------
void get(){
	int i,j;
	printf("Enter No. of Cities: ");
	scanf("%d",&n);

	printf("\nEnter Cost Matrix\n");

	for(i=0;i < n;i++){
		printf("\nEnter Elements of Row # : %d\n",i+1);
		for( j=0;j < n;j++)
			node_table[i][j] = MULT[i][j];
		traversed[i]=0;
	}

	printf("\n\nThe cost list is:\n\n");
	for( i=0; i<n; i++){
		printf("\n\n");
		for(j=0; j<n; j++)
			printf("\t%d", node_table[i][j]);
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

	printf("%d --> ",city+1);

	ncity=lowest(city);
	if(ncity==1000){
		ncity=0;
		printf("%d",ncity+1);
		cost+=node_table[city][ncity];
		return 0;
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

int calculateQuantity(int price)
{
  int quantity;
  //int fprice;
  printf("Enter the quantity: \n");  scanf("%d",&quantity);

  fprice = price * quantity;
  printf("Order Value for this item is - %d", fprice );

  return fprice;
}

int chooseMenu()
{
  char choice;
  int flag, again;
  flag = 1;
  while(flag==1){
    printf("\n---------- Welcome to Node A Restaurant -----------\n");
    printf(" A. Item 0 -> Rs. 90\n");
    printf(" B. Item 1 -> Rs. 20\n");
    printf(" C. Item 2 -> Rs. 100\n");
    printf(" D. Item 3 -> Rs. 60\n");
    printf(" E. Item 4 -> Rs. 10\n");

    printf("Enter the option you want to order\n" );

    scanf("%ch\n",&choice );

    switch (choice) {
      case 'A':   {calculateQuantity(90); grossValue=grossValue+fprice; break;}
      case 'B':   {calculateQuantity(20); grossValue=grossValue+fprice; break;}
      case 'C':   {calculateQuantity(100);grossValue=grossValue+fprice; break;}
      case 'D':   {calculateQuantity(60); grossValue=grossValue+fprice; break;}
      case 'E':   {calculateQuantity(10); grossValue=grossValue+fprice; break;}
    }

    flag=0;
  }
  printf("\nDo you want to continue your order [1] Yes [2] No\n");
  scanf("%d",&again);
  if(again==2){
    printf("THANK YOU\nGross Value is=%d \n",grossValue);
    return grossValue;
  }
  else{
    chooseMenu();
  }
}

int main(int argc, char** argv){
  float DISTANCES[num_rows][num_fields];
  float TIMES[num_rows][num_fields];
  con = mysql_init(NULL);
  if(con == NULL){
    fprintf(stderr, "mysql_init() failed\n");
    exit(1);
  }

  //CREATE DATABASE BEFORE next line.

  if(mysql_real_connect(con, server, user, password, database, 0, NULL, 0)==NULL){
    finish_with_error(con);
  }

  printf("DISTANCE(S) TABLE: \n");
  if(mysql_query(con, "SELECT * FROM DISTANCES")){
    finish_with_error(con);
  }
  res = mysql_store_result(con); //  retrieves all data from the DISTANCES table.
  //MYSQL_RES is a structure for holding a result set
  if(res == NULL){
    finish_with_error(con);
  }

  num_rows = mysql_num_rows(res);
  num_fields = mysql_num_fields(res); //num_fields = no. of columns

  int DISTANCES_i = 0;

  while(row = mysql_fetch_row(res)){
    for(int j=0; j<num_fields; j++){
      DISTANCES[DISTANCES_i][j] = atof(row[j]);
      // printf("%s ", row[j] ? row[j] : "NULL");
    }
    DISTANCES_i++;
    // printf("\n");
  }
  printf("\n");

  for(int i=0; i<num_rows; i++){
    for(int j=0; j<num_fields; j++){
      printf("%.2f ", DISTANCES[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  printf("TIME(S) TABLE: \n");
  if(mysql_query(con, "SELECT * FROM TIMES")){ // returns 0, hence doesnt enter block
    finish_with_error(con);
  }

  res = mysql_store_result(con);

  if(res == NULL){
    finish_with_error(con);
  }

  num_rows = mysql_num_rows(res);
  num_fields = mysql_num_fields(res); //num_fields = no. of columns

  int TIMES_i = 0;

  while(row = mysql_fetch_row(res)){
    for(int j=0; j<num_fields; j++){
      TIMES[TIMES_i][j] = atof(row[j]);
      // printf("%s ", row[j] ? row[j] : "NULL");
    }
    TIMES_i++;
    // printf("\n");
  }

  for(int i=0; i<num_rows; i++){
    for(int j=0; j<num_fields; j++){
      printf("%.2f ", TIMES[i][j]);
    }
    printf("\n");
  }
  printf("\n");


  for(int i=0; i<num_rows; i++){
    for(int j=0; j<num_fields; j++){
      MULT[i][j] = DISTANCES[i][j] * TIMES[i][j];
      // printf("%.2f ", MULT[i][j]);
    }
    printf("\n");
  }

  int customers = num_rows-1;
  // printf("Enter number of customers: "); scanf("%d", &customers);
  int GrossValues[customers];
  for(int i=0; i<customers; i++){
    GrossValues[i] = chooseMenu();
  }

  for(int i=0; i<num_rows; i++){
    for(int j=0; j<num_fields; j++){
      MULT[i][j] = GrossValues[i] / MULT[i][j];
    }
  }

  mysql_free_result(res);
  mysql_close(con);
  chooseMenu();
  float time_spent;
	get();
	printf("\n\nThe Path is:\n\n");
	time_spent=mincost(0);
	put();
  printf("\n\ntotal time spent is %f", time_spent);

  exit(0);
}

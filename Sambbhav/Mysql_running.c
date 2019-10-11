#include<stdio.h>
#include<mysql.h>
#include<stdlib.h>
MYSQL_ROW row;
MYSQL *con;
MYSQL_RES *res;
int num_fields;
int num_rows;
char *server = "localhost";
char *user = "Minor";
char *password = "minor1";
char *database = "RTable";

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

int main(int argv, char** argc){
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

  float DISTANCES[num_rows][num_fields];
  int DISTANCES_i = 0;

  while(row = mysql_fetch_row(res)){
    for(int j=0; j<num_fields; j++){
      DISTANCES[DISTANCES_i][j] = atof(row[j]);
      // printf("%s ", row[j] ? row[j] : "NULL");
    }
    DISTANCES_i++;
    // printf("\n");
  }
  // printf("\n");

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

  float TIMES[num_rows][num_fields];
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

  printf("\nFINAL TABLE\n");
  // int GrossValues[num_rows] = {45,67,200,45};
  float MULT[num_rows][num_fields];

  for(int i=0; i<num_rows; i++){
    for(int j=0; j<num_fields; j++){
      MULT[i][j] = DISTANCES[i][j] * TIMES[i][j];
      printf("%.2f ", MULT[i][j]);
    }
    printf("\n");
  }

  mysql_free_result(res);
  mysql_close(con);
  exit(0);
}

#include<stdio.h>
#include<stdlib.h>

void chooseMenu();
int calculateQuantity(int price);
int storeGV(int gv);

//Global variable declaration
int fprice=0;
int grossValue = 0;

//MAIN METHOD
int main()
{
  chooseMenu();
}

void chooseMenu()
{
 char choice;
 int flag,again ;
 flag = 1;
 //int grossValue = 0;

while(flag==1){
  printf("\n---------- Welcome to Node A Restaurant -----------\n");
  printf(" A. Paneer -> Rs. 90\n");
  printf(" B. ADVANCE-> Rs. 20\n");
  printf(" C. FISH-> Rs. 100\n");
  printf(" D. DAL-> Rs. 60\n");
  printf(" E. ROTI-> Rs. 10\n");

  printf("Enter the option you want to order\n" );

  scanf("%ch\n",&choice );

  switch (choice) {
    case 'A':   {calculateQuantity(90); grossValue=grossValue+fprice; break;}
    case 'B':   {calculateQuantity(20);grossValue=grossValue+fprice;break;}
    case 'C':   {calculateQuantity(100);grossValue=grossValue+fprice;break;}
    case 'D':   {calculateQuantity(60);grossValue=grossValue+fprice;break;}
    case 'E':   {calculateQuantity(10);grossValue=grossValue+fprice;break;}
  }

  flag=0;
}

//end while
printf("\nDo you want to continue your order [1] Yes [2] No\n");
scanf("%d",&again);
if(again==2)
{
  printf("THANK YOU\nGross Value is=%d \n",grossValue);
  storeGV(grossValue);
}
else
{
  chooseMenu();
}
//{flag=0;break;}
}


//QUANTITTIES CALCULATION
int calculateQuantity(int price)
{
  int quantity;
  //int fprice;
  printf("Enter the quantity\n");
  scanf("%d",&quantity);

  fprice = price* quantity;
  printf("Order Value for this item is - %d", fprice );

  return fprice;
}


//FILE HANDLING
int storeGV(int gv)
{
  char nd;
  printf("Which node:");
  scanf("%ch",&nd);
  printf("%ch",nd);
  FILE *p1;


}

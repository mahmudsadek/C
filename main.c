#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "category.c"

// #include <windows.h>


COORD coord= {0,0};                  // this is global variable

//center of axis is set to the top left corner of the screen
void gotoxy(int x,int y) {
   coord.X=x;
   coord.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


void SetColor(int ForgC) {
   WORD wColor;

   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   if(GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
   }
   return;
}



int chooseCategory(ListOfCategory *c) {
   int X_Axies = 10;
   int Y_Axies = 0;
   int flag = 1;
   do {
      system("cls");
      SetColor(15);
      gotoxy(X_Axies,9);
      printf("\tChoose Category :\n" );
      gotoxy(X_Axies,10);
      printf("================================================");
      for (int i = 0; i < C_COUNTER; i++) {
         if(Y_Axies == i) {
            SetColor(1);
            gotoxy(X_Axies,i+11);
            printf("\tName : %19s\n",c->arr[Y_Axies].cat_name);
         }
         else {
            SetColor(15);
            gotoxy(X_Axies,i+11);
            printf("\tName : %19s\n",c->arr[i].cat_name);
         }
      }
      SetColor(15);
      gotoxy(X_Axies,C_COUNTER+11);
      printf("===============================================\n");
      gotoxy(X_Axies,C_COUNTER+11);
      char ch;
      ch = getch();
      switch (ch) {
      case -32:
         ch = getch();
         switch(ch) {
         case 80:
            Y_Axies++;
            if(Y_Axies >= C_COUNTER) {
               Y_Axies = 0;
            }
            break;
         case 72:
            Y_Axies--;
            if(Y_Axies < 0) {
               Y_Axies = C_COUNTER-1;
            }
            break;
         default:
            break;
         }
         break;
      case 13:
         return Y_Axies;
      }
   }while(flag);
}

void moveProdact(ListOfCategory *c, ListOfProdacts *p) {
   int X_Axies = 10;
   int Y_Axies = 0;
   int flag = 1;
   do {
      system("cls");
      SetColor(15);
      gotoxy(X_Axies,9);
      printf("\t Choose Prodact to Move\n");
      printf("\t================================================\n");
      for (int i = 0; i < P_COUNTER; i++) {
         if(Y_Axies == i) {
            SetColor(1);
            gotoxy(X_Axies,i+11);
            printf("\tName : %19s\t ID: %d\t Cate ID: %d",p->arr[Y_Axies].name, p->arr[Y_Axies].id,  p->arr[Y_Axies].cat_id);
         }
         else {
            SetColor(15);
            gotoxy(X_Axies,i+11);
            printf("\tName : %19s\t ID: %d\t Cate ID: %d",p->arr[i].name, p->arr[i].id, p->arr[i].cat_id);
         }
      }
      SetColor(15);
      gotoxy(X_Axies,P_COUNTER+11);
      printf("===============================================\n");
      char ch;
      ch = getch();
      switch (ch) {
      case -32:
         ch = getch();
         switch(ch) {
         case 80:
            Y_Axies++;
            if(Y_Axies >= P_COUNTER) {
               Y_Axies = 0;
            }
            break;
         case 72:
            Y_Axies--;
            if(Y_Axies < 0) {
               Y_Axies = P_COUNTER-1;
            }
            break;
         default:
            break;
         }
         break;
      case 13:
         int id = chooseCategory(c);
         p->arr[Y_Axies].cat_id = id;
         break;
      // case 27:
      //    flag = 0;
      //    break;
      // default:
      //    flag = 0;
      //    break;
      }
      if(ch == 27) {
         flag = 0;
      }
   }while(flag);
}

void ProdactMenu(ListOfCategory *c, ListOfProdacts *p) {
   char ProdMenu[3][20] = {
      "1- Add Prodact",
      "2- Show Prodact",
      "3- Move Prodact"
   };
   int X_Axies = 10;
   int Y_Axies = 0;
   int flag = 1;
   do {
      system("cls");
      SetColor(15);
      gotoxy(X_Axies,9);
      printf("===========================");
      for (int i = 0; i < 3; i++) {
         if(Y_Axies == i) {
            SetColor(3);
            gotoxy(X_Axies,i+10);
            printf("\t%s\n",ProdMenu[i]);
         }
         else {
            SetColor(15);
            gotoxy(X_Axies,i+10);
            printf("\t%s\n", ProdMenu[i]);
         }
         SetColor(15);
         gotoxy(X_Axies,13);
         printf("===========================");
      }
      char ch;
      ch = getch();
      switch (ch)
      {
      case -32:
         ch = getch();
         switch(ch) {
         case 80:
            Y_Axies++;
            if(Y_Axies > 2) {
               Y_Axies = 0;
            }
            break;
         case 72:
            Y_Axies--;
            if(Y_Axies < 0) {
               Y_Axies = 2;
            }
            break;
         }
         break;
      case 13:
         switch (Y_Axies)
         {
         case 0:
            system("cls");
            push_back_p(p, addProdact());
            p->arr[P_COUNTER-1].cat_id = chooseCategory(c);
            break;
         case 1:
            system("cls");
            DisplayProdacts(c, p);
            getch();
            break;
         case 2:
            system("cls");
            moveProdact(c, p);
            break;
         default:
            break;
         }
         break;
      default:
         break;
   case 27:
      flag = 0;
      }
   } while(flag);
}

void chooseProduct(ListOfProdacts *order, ListOfProdacts *p) {
   int X_Axies = 10;
   int Y_Axies = 0;
   int flag = 1;
   do {
      system("cls");
      SetColor(15);
      gotoxy(X_Axies,9);
      printf("\tChoose Prodact :\n" );
      gotoxy(X_Axies,10);
      printf("================================================");
      for (int i = 0; i < P_COUNTER; i++) {
         if(Y_Axies == i) {
            SetColor(1);
            gotoxy(X_Axies,i+11);
            printf("\tName : %19s \t Price : %f\n", p->arr[Y_Axies].name, p->arr[Y_Axies].price);
         }
         else {
            SetColor(15);
            gotoxy(X_Axies,i+11);
            printf("\tName : %19s \t Price : %f\n", p->arr[i].name, p->arr[i].price);
         }
      }
      SetColor(15);
      gotoxy(X_Axies,P_COUNTER+11);
      printf("===============================================\n");
      gotoxy(X_Axies,P_COUNTER+12);
      char ch;
      ch = getch();
      switch (ch) {
      case -32:
         ch = getch();
         switch(ch) {
         case 80:
            Y_Axies++;
            if(Y_Axies >= P_COUNTER) {
               Y_Axies = 0;
            }
            break;
         case 72:
            Y_Axies--;
            if(Y_Axies < 0) {
               Y_Axies = P_COUNTER-1;
            }
            break;
         default:
            break;
         }
         break;
      case 13:
         system("cls");
         int q;
         gotoxy(X_Axies,10);
         printf("Enter Quantity :");
         scanf("%d", &q);
         if(q > p->arr[Y_Axies].quntity) {
            gotoxy(X_Axies,11);
            printf("Sorry There is no enough quantity !");
            getch();
         }
         else if(q == p->arr[Y_Axies].quntity) {
            push_back_p(order, p->arr[Y_Axies]);
            pop_at_p(p, Y_Axies);
         }
         else {
            push_back_p(order, p->arr[Y_Axies]);
            order->arr[Y_Axies].quntity = q;
            p->arr[Y_Axies].quntity -= q;
         }
         break;
      case 27:
         flag = 0;
         break;
      }
   }while(flag);
}

void showBill(ListOfProdacts *order) {
   SetColor(23);
   float total = 0;
   float price = 0;
   printf("\n\n");
   printf("\t---------------------------------------------------------------------------------------\n");
   for (int i = 0; i < order->len; i++) {
      price = (order->arr[i].quntity) * (order->arr[i].price);
      printf("\t\tName: %19s \tQuantity: %d\t price: %f\n", order->arr[i].name, order->arr[i].quntity, price);
      printf("\t---------------------------------------------------------------------------------------\n");
      total += price;
   }
      printf("\t=======================================================================================\n");
      printf("\t\t Totol Price: %f\n",total);
      printf("\t=======================================================================================\n");
}

void BuyMenu(ListOfProdacts *order,ListOfProdacts *p) {
   
   char Menu[2][20] = {
      "1- Buy Product",
      "2- Show Bill"
   };
   int X_Axies = 10;
   int Y_Axies = 0;
   int flag = 1;
   do {
      system("cls");
      SetColor(15);
      gotoxy(X_Axies,9);
      printf("===========================");
      for (int i = 0; i < 2; i++) {
      if(Y_Axies == i) {
         SetColor(3);
         gotoxy(X_Axies,i+10);
         printf("\t%s\n",Menu[i]);
      }
      else {
         SetColor(15);
         gotoxy(X_Axies,i+10);
         printf("\t%s\n", Menu[i]);
      }
      SetColor(15);
      gotoxy(X_Axies,12);
      printf("===========================");
      }
      char ch;
      ch = getch();
      switch (ch)
      {
      case -32:
         ch = getch();
         switch(ch) {
         case 80:
            Y_Axies++;
            if(Y_Axies > 2) {
               Y_Axies = 0;
            }
            break;
         case 72:
            Y_Axies--;
            if(Y_Axies < 0) {
               Y_Axies = 2;
            }
            break;
         }
         break;
      case 13:
         switch (Y_Axies)
         {
         case 0:
            system("cls");
            chooseProduct(order, p);
            break;
         case 1:
            system("cls");
            showBill(order);
            getch();
            break;
         default:
            break;
         }
         break;
      default:
         break;
      case 27:
      flag = 0;
      }
   }while(flag);

}


void CategoryMenu(ListOfCategory *c) {
   char cateMenu[2][20] = {
      "1- Add Category",
      "2- Show Category"
   };
   int X_Axies = 10;
   int Y_Axies = 0;
   int flag = 1;
   do {
      system("cls");
      SetColor(15);
      gotoxy(X_Axies,9);
      printf("===========================");
      for (int i = 0; i < 2; i++) {
      if(Y_Axies == i) {
         SetColor(3);
         gotoxy(X_Axies,i+10);
         printf("\t%s\n",cateMenu[i]);
      }
      else {
         SetColor(15);
         gotoxy(X_Axies,i+10);
         printf("\t%s\n", cateMenu[i]);
      }
      SetColor(15);
      gotoxy(X_Axies,12);
      printf("===========================");
      }
      char ch;
      ch = getch();
      switch (ch)
      {
      case -32:
         ch = getch();
         switch(ch) {
         case 80:
            Y_Axies++;
            if(Y_Axies > 2) {
               Y_Axies = 0;
            }
            break;
         case 72:
            Y_Axies--;
            if(Y_Axies < 0) {
               Y_Axies = 2;
            }
            break;
         }
         break;
      case 13:
         switch (Y_Axies)
         {
         case 0:
            system("cls");
            push_back(c, addCategory());
            break;
         case 1:
            system("cls");
            ShowCategorys(c);
            getch();
            break;
         default:
            break;
         }
         break;
      default:
         break;
   case 27:
      flag = 0;
      }
   }while(flag);
   
}

void MainMenu(ListOfCategory *c, ListOfProdacts *p, ListOfProdacts *order) {

   char menu[3][20] = {
      "1- Category",
      "2- Prodact",
      "3- Buy Now !"
   };
   int X_Axies = 10;
   int Y_Axies = 0;

   while(1) {
      system("cls");
      SetColor(15);
      gotoxy(X_Axies,9);
      printf("===========================\n");
      for (int i = 0; i < 3; i++) {
         if(Y_Axies == i) {
            SetColor(20);
            gotoxy(X_Axies,i+10);
            printf("\t%s\n", menu[i]);
         }
         else {
            SetColor(15);
            gotoxy(X_Axies,i+10);
            printf("\t%s\n", menu[i]);
         }
      }
      SetColor(15);
      gotoxy(X_Axies,13);
      printf("===========================");

      char ch;
      ch = getch();
      switch (ch)
      {
      case -32:
         ch = getch();
         switch(ch) {
         case 80:
            Y_Axies++;
            if(Y_Axies > 2) {
               Y_Axies = 0;
            }
            break;
         case 72:
            Y_Axies--;
            if(Y_Axies < 0) {
               Y_Axies = 2;
            }
            break;
         }
         break;
      case 13:
         switch (Y_Axies)
         {
         case 0:
            system("cls");
            CategoryMenu(c);
            break;
         case 1:
            system("cls");
            ProdactMenu(c, p);
            break;
         case 2:
            system("cls");
            BuyMenu(order,p);
            break;
         default:
            break;
         }
         break;
      default:
         break;
      }
   }
}

int main () {
   ListOfCategory category;
   makeListOfCategory(&category, 5);
   
   ListOfProdacts prodact;
   makeListOfProdacts(&prodact,5);

   ListOfProdacts order;
   makeListOfProdacts(&order, 5);

   MainMenu(&category, &prodact, &order);

}
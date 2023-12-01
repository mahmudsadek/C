#ifndef CATE_H_INCLUDED
#define CATE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
// #include <windows.h>
#include "prodact.c"
// #include "tools.c"

struct Category {
   int cat_id;
   char cat_name[20];
};
typedef struct Category Category;

struct ListOfCategory {
   int len;
   Category * arr;
   int size;
};
typedef struct ListOfCategory ListOfCategory;


int C_COUNTER = 0;

void makeListOfCategory(ListOfCategory * l, int size) {
   l->size = size;
   l->len = 0;
   l->arr = (Category*) malloc(size * sizeof(Category));
}

void expandSize(ListOfCategory *l) {
      l->size *= 2;
      Category * arr2 = (Category*) malloc(l->size * sizeof(Category));
      for (int i = 0; i < l->len; i++) {
         arr2[i].cat_id = l->arr[i].cat_id;
         strcpy(arr2[i].cat_name , l->arr[i].cat_name);
      }
      free(l->arr);
      l->arr = arr2;
}

int l_length(ListOfCategory *l) {
   return l->len;
}

int Empty(ListOfCategory *l) {
   return l->len == 0 ? 1 : 0;
}

int Full(ListOfCategory* l) {
   return l->len == l->size ? 1 : 0;
}

void push_back(ListOfCategory * l, Category item) {
   if(Full(l)) {
      expandSize(l);
   }
   l->arr[l->len] = item;
   l->len++;
}

Category pop_back(ListOfCategory * l) {
   if(Empty(l)) {
      printf("You Can Not pop, List is Empty ");
   }
   else {
      l->len--;
      return l->arr[l->len];
   }
}

void push_at(ListOfCategory* l, int index, Category item) {
   if(Full(l)) {
      expandSize(l);
   }
   for (int i = (l->len); i > index; i--) {
      l->arr[i] = l->arr[i-1] ;
   }
   l->arr[index] = item;
   l->len++;
}

Category pop_at(ListOfCategory* l, int index) {
   if(Empty(l)) {
      printf("Can't pop,  List is Empty!");
   }

   else if(index >= l->len) {
      printf("Can't pop, Wrong index!!");
   }
   else {
      Category ele = l->arr[index];
      int count = l->len - 1;
      for (int i = index; i < count; i++) {
         l->arr[i] = l->arr[i+1];
      }
      l->len--;
      return ele;
   }
}

void ShowCategorys(ListOfCategory * l) {
   for (int i = 0; i < l->len; i++) {
      printf("\tCategory ID   :%d\n",l->arr[i].cat_id);
      printf("\tCategory Name : %s\n",l->arr[i].cat_name);
   }
   printf("\n");
}

Category addCategory() {
   Category  cate;
   printf("\t\tEnter Category Name : ", cate.cat_name);
   scanf("%s",&cate.cat_name);
   cate.cat_id = C_COUNTER;
   C_COUNTER++;
   return cate;
}

void DisplayProdacts(ListOfCategory* c,ListOfProdacts *p) {
   for(int i = 0; i < c->len; i++) {
      printf("\n================= { %s } ====================\n",c->arr[i].cat_name);
      for(int k = 0; k < p->len; k++) {
            if(c->arr[i].cat_id == p->arr[k].cat_id) {
               printf("\t\tProdact ID       : %d\n", p->arr[k].id);
               printf("\t\tProdact Name     : %s\n", p->arr[k].name);
               printf("\t\tProdact Price    : %f\n", p->arr[k].price);
               printf("\t\tProdact Quantity : %d\n", p->arr[k].quntity);
               printf("------------------------------------------------\n");
            }
      }
      printf("\n");
   }
}





#endif // CATE_H_INCLUDED

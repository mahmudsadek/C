#ifndef PROD_H_INCLUDED
#define PROD_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int P_COUNTER = 0;


struct Prodact {
   int id;
   char name[20];
   int quntity;
   float price;
   int cat_id;
};
typedef struct Prodact Prodact;

struct ListOfProdacts {
   int len;
   Prodact * arr;
   int size;
};
typedef struct ListOfProdacts ListOfProdacts;


void makeListOfProdacts(ListOfProdacts * l, int size) {
   l->size = size;
   l->len = 0;
   l->arr = (Prodact*) malloc(size * sizeof(Prodact));
}

void expandSize_p(ListOfProdacts *l) {
      l->size *= 2;
      Prodact * arr2 = (Prodact*)malloc(l->size * sizeof(Prodact));
      for (int i = 0; i < l->len; i++) {
         arr2[i].id = l->arr[i].id;
         strcpy(arr2[i].name , l->arr[i].name);
         arr2->quntity = l->arr[i].quntity;
         arr2->price = l->arr[i].price;
         arr2->cat_id = l->arr[i].cat_id;
      }
      free(l->arr);
      l->arr = arr2;
}

int l_length_p(ListOfProdacts *l) {
   return l->len;
}

int Empty_p(ListOfProdacts *l) {
   return l->len == 0 ? 1 : 0;
}

int Full_p(ListOfProdacts* l) {
   return l->len == l->size ? 1 : 0;
}

void push_back_p(ListOfProdacts * l, Prodact item) {
   if(Full_p(l)) {
      expandSize_p(l);
   }
   l->arr[l->len] = item;
   l->len++;
}

Prodact pop_back_p(ListOfProdacts * l) {
   if(Empty_p(l)) {
      printf("You Can Not pop, List is Empty ");
   }
   else {
      P_COUNTER--;
      l->len--;
      return l->arr[l->len];
   }
}

void push_at_p(ListOfProdacts* l, int index, Prodact item) {
   if(Full_p(l)) {
      expandSize_p(l);
   }
   for (int i = (l->len); i > index; i--) {
      l->arr[i] = l->arr[i-1] ;
   }
   l->arr[index] = item;
   l->len++;
}

Prodact pop_at_p(ListOfProdacts* l, int index) {
   if(Empty_p(l)) {
      printf("Can't pop,  List is Empty!");
   }
   else if(index >= l->len) {
      printf("Can't pop, Wrong index!!");
   }
   else {
      Prodact ele = l->arr[index];
      int count = l->len - 1;
      for (int i = index; i < count; i++) {
         l->arr[i] = l->arr[i+1];
      }
      l->len--;
      P_COUNTER--;
      return ele;
   }
}


Prodact addProdact() {
   Prodact p;
   p.id = P_COUNTER;
   printf("\n\n\n\tProdact Name    : ");
   scanf("%s", p.name);
   printf("\tProdact Price   : ");
   scanf("%f", &p.price);
   printf("\tProdact Quntity : ");
   scanf("%d", &p.quntity);
   printf("\tProdact Category: ");
   P_COUNTER++;
   return p;
}





/*void print_p(ListOfProdacts * l,ListCate *c) {
   for (int i = 0; i < l->len; i++) {
      printf("Prodact id : %d\n",l->arr[i].id);
      printf("Prodact Name : %s\n",l->arr[i].name);
      printf("Prodact Price : %f\n",l->arr[i].price);
      printf("Prodact Quntity : %d\n",l->arr[i].quntity);
      for(int j = 0; j < c->len; j++) {
         if(c->arr[j].cat_id == l->arr[i].cat_id) {
            printf("Category : %s\n",c->arr[j].cat_name);
         }
      }
   }
   printf("\n");
}

*/

#endif // PROD_H_INCLUDED

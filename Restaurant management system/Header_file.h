#ifndef  Header_file
#define Header_file
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define N 15
 
typedef struct item {

	char* ProductName;
	int Price;
	int Quantity;
	char Premium;
	struct item *next;

}Item;

typedef struct manot {

	Item *head;
	Item *tail;
	int size;
}Manot;

typedef struct order {

	char *ProductName;
	int Quantity;
	int price;
	char Premium;

	struct order *next, *prev;
	
}Order;

typedef struct table {

	Order *mana;
	float pay;
}Table;

void CreateProducts(Manot *menu, FILE *f);
void AddItems(Manot *mana, char *ProductName, int Quantity);
void OrderItem(Table table, char* ProductName, int Quantity, Manot *mana, int num);
void RemoveItem(Table table, char* ProductName, int Quantity, Manot *mana, int num);
void RemoveTable(Table table, int num);
void ErrorMessage(char *string);
void freeAllmanot(Manot *mana);
void freeAllTables(Table *table);

#endif

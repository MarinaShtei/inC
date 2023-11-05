#include "Header_file.h"

void ErrorMessage(char *string)
{
	printf("%s\n", string);
	exit(0);
}

void CreateProducts(Manot *menu, FILE *f)
{
	char str[256], ch1, ch2;
	Item *temp = NULL;
	int i = 0, price, Quantity;

	while ((fscanf(f,"%s%d%d%c%c", &str, &Quantity, &price, &ch1, &ch2)) == 4)
	{
		temp = (struct item*)malloc(sizeof(struct item));
		if (temp->ProductName == NULL)
		{
			ErrorMessage("allocation failed\n");
		}
		temp->ProductName = (char*)malloc((strlen(str + 1)) * sizeof(char));
		if (temp->ProductName == NULL)
		{
			freeAllmanot(&menu);
			ErrorMessage("allocation failed\n");
		}

		temp->Price = price;
		temp->Quantity = Quantity;
		temp->Premium = ch2;

		if (temp->Quantity < 0 && temp->Price < 0)
		{
			i++;
		}
		if (temp->Premium != 'Y' && temp->Premium != 'N')
		{
			i++;
		}
		

		strcpy(temp->ProductName, str);
		
		if (menu->size == 0)
		{
			temp->next = NULL;
			menu->head = temp;
			menu->tail = temp;
		}
		else
		{
			temp->next = menu->head;
			menu->head = temp;
		}
		menu->size++;

		temp = menu->tail;

		while (temp != NULL)
		{
			if (strcmp(str, temp->ProductName) == 0) i++;
		}
	}

	if (i != 0)
	{
		printf("Creation of the menu failed\n");

	}
	else
	{
		printf("Creation of the menu succeded\n");
	}
}

void AddItems(Manot *mana, char *ProductName, int Quantity)

{
	Item *temp = mana->head;
	int i = 0; 
	while (temp != NULL)
	{
		if (strcmp(temp->ProductName, ProductName) == 0)
		{
			temp->Quantity = temp->Quantity + Quantity;
			i++;
			break;
		}
		else
		{
			temp = temp->next;
		}
	}
	if (i == 0 && Quantity < 0)
	{
		printf("The poduct does not exist or the Quantity is lower then 0\n");
	}
	else
	{
		printf("The product has been added to kichen\n");
	}
}


void OrderItem(Table table, char* ProductName, int Quantity, Manot *mana, int table_num)
{
	Item *temp = mana->head;
	Order *order; 
	int i;
	

	if (table_num > 15 && table_num < 1)
	{
		printf("table number is not exist\n");
		return 0;
	}
	while (temp != NULL)
	{
		if (strcmp(temp->ProductName,ProductName) == 0) break;
		 temp = temp->next;
	}

	if (temp == NULL) 
	{
		printf("The product does not exist\n");
		return 0;
	}

	if (Quantity > temp->Quantity)
	{
		printf("The order is higher then stock\n");
		return 0;
	}
	if (Quantity < 0)
	{
		printf("The quantity is not vailed\n");
		return 0;
	}
	temp->Quantity = temp->Quantity - Quantity;
	(&table + table_num - 1)->pay += (temp->Price*Quantity);
	order = (struct order*)malloc(sizeof(struct order));
	if (order == NULL)
	{
		ErrorMessage("Allocation failed\n");
	}
	order->Quantity = Quantity;
	order->ProductName = (char*)malloc((strlen(temp->ProductName) + 1) * sizeof(char));
	if (order->ProductName == NULL)
	{
		freeAllmanot(mana->head);
		freeAllTables(&table);
	}
	strcpy(order->ProductName, ProductName);
	order->price = temp->Price;
	order->Premium = temp->Premium;
	if ((&table + table_num - 1)->mana == NULL)
	{
		order->next = NULL;
		(&table + table_num - 1)->mana = order;
	}
	else
	{
		order->next = (&table + table_num - 1)->mana;
		(&table + table_num - 1)->mana->prev = order;
		(&table + table_num - 1)->mana = order;
	}
	printf("The order was take care off\n");
}


void RemoveItem(Table table, char* ProductName, int Quantity, Manot *mana, int num)
{
	Order *order;

	if (num > 15 && num < 1)
	{
		printf("table number is not exist\n");
		return 0;
	}

	if ((&table + num - 1)->mana == NULL)
	{
		printf("the table is empty");
		return 0;
	}

	order = (&table + num - 1)->mana;

	while (order != NULL)
	{
		if (strcmp(order->ProductName, ProductName) == 0) break;
		else order = order->next;
	}

	if (order == NULL)
	{
		printf("The product does not exist\n");
		return 0;
	}

	if (Quantity > order->Quantity)
	{
		printf("The order is higher then what is ordered\n");
		return 0;
	}
	if (Quantity < 0)
	{
		printf("The quantity is not vailed\n");
		return 0;
	}

	order->Quantity = order->Quantity - Quantity;
	(&table + num - 1)->pay = (&table + num - 1)->pay - (order->price*Quantity);
	if (order->Quantity == 0)
	{
		if (order->next == NULL && order->prev == NULL)
		{
			free(order);
			(&table + num - 1)->mana = NULL;
		}
		if(order->prev == NULL)
		{
			order->prev->next = NULL;
			(&table + num - 1)->mana = order->next;
			free(order);
		}
		if (order->next == NULL)
		{
			order->prev->next = NULL;
			free(order);
		}
		else
		{
			order->prev->next = order->next;
			order->next->prev = order->prev;
			free(order);
		}
	}

	printf("Item removed\n");

}

void RemoveTable(Table table, int num)
{
	Order *temp;

	if (num > 15 && num < 1)
	{
		printf("table number is not exist\n");
		return 0;
	}
	if ((&table + num - 1)->mana == NULL)
	{
		printf("table is empty\n");
		return 0;
	}

	temp = (&table + num - 1)->mana;
	while (temp != NULL)
	{
		if (temp->Premium == 'Y')
		{
			(&table + num - 1)->pay = (&table + num - 1)->pay + (((&table + num - 1)->pay * 10) / 100);
			printf("This is a premium table you need to pay %f NIS\n" , (&table + num - 1)->pay);
		}
		else
		{
			temp = temp->next;
		}
	}
	if (temp == NULL)
	{
		printf("This is not a premium table you need to pay %f NIS\n", (&table + num - 1)->pay);
	}

	while ((&table + num - 1)->mana != NULL)
	{
		temp = (&table + num - 1)->mana;
		(&table + num - 1)->mana = (&table + num - 1)->mana->next;
		free(temp);
	}
}

void freeAllmanot(Manot *mana)
{
	Item *temp;

	while (mana->head != NULL)
	{
		free(mana->head->ProductName);
		temp = mana->head;
		mana->head = mana->head->next;
		free(temp);
	}
}

void freeAllTables(Table *table)
{
	Order *temp;
	int i;
	for (i = 0; i < 15; i++)
	{
	
			while (table[i].mana->next != NULL)
			{
				temp = table[i].mana;
				table[i].mana = table[i].mana->next;
				free(temp->ProductName);
				free(temp);
			}
		
	}
}

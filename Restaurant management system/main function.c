#include "Header_file.h"
int main()
{
	FILE* input;
	FILE* instractions;
	int counter1 = 0, counter2 = 0,j,num1, num2;
	char  item[256];
	int i;
	Manot mana;
	Table table[N];
	mana.head = NULL;
	mana.tail = NULL;
	mana.size = 0;
	

	input = fopen("Manot.txt", "rt");
	if (input == NULL) ErrorMessage("Could not open file");
	instractions = fopen("Instructions.txt", "rt");
	if (instractions == NULL) ErrorMessage("Could not open file");
	while (counter1 < 10)
	{
		printf("This resturant order system. Please choose your option:\n");
		printf("1. Create menu\n");
		printf("2. Add item to kichen\n");
		printf("3. Order for table\n");
		printf("4. Cancel order\n");
		printf("5. Close table\n");
		scanf("%d", &j);
		if (j != 0)
		{
			while (j != 0)
			{
				printf("wrong option need to press 0\n");
				scanf("%d", &j);
			}

		}
		counter1++;

		fscanf(instractions,"%d", &i);

		switch (i)
		{
		case 1:
		{
			counter2++;
			CreateProducts(&mana,input);
			break;
		}
		case 2:
		{
			if (counter2 == 0)
			{
				printf("you need create the kichen first");
				break;
			}

			fscanf(instractions, "%s%d", &item, &num1);
			AddItems(&mana, item, num1);
			break;
		}

		case 3:
		{
			if (counter2 == 0)
			{
				printf("you need create the kichen first");
				break;
			}
			fscanf(instractions, "%d%s%d", &num2, &item, &num1);

			OrderItem(*table, item, num1, &mana, num2);
			break;
		}

		case 4:
		{
			if (counter2 == 0)
			{
				printf("you need create the kichen first");
				break;
			}
			fscanf(instractions, "%d%s%d", &num2, &item, &num1);

			RemoveItem(*table, item, num1, &mana, num2);
			break;
		}
		case 5:
		{
			if (counter2 == 0)
			{
				printf("you need create the kichen first");
				break;
			}
			fscanf(instractions, "%d", &num2);
			RemoveTable(*table, num2);


		}

		default:
			{
				printf("\nInstructions are not right.");
				break;
			}
		}

	}
	
	fclose(input);
	fclose(instractions);
	freeAllTables(&table);
	freeAllmanot(&mana);


}



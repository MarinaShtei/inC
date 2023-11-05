#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int* radix(int[], int, int);
int* countSort(int[], int[], int, int);

void main()
{
	int* aArr;
	int* finArr;
	int maxNum = 0, i=0, num;

	printf("Enter how many numbers in the array:"); // asks the user for an array size
	scanf("%d", &num);
	aArr = (int*)malloc(num * sizeof(int)); // give to an array the memory
	if (aArr == NULL) // if allocarion failed
	{
		printf("allocation failed\n");
		exit(1);
		getchar();
	}
	for (i = 0; i < num; i++) // asks input from the user
	{
		printf("Please entrer number from 1 to 9999\n");
		scanf("%d", &aArr[i]);
		if (aArr[i] >= maxNum)
		{
			maxNum = aArr[i];
		}
	}

	finArr = (int*)malloc(num * sizeof(int)); // create an final array for sorted array
	if (finArr == NULL) // if allocation failed
	{
		printf("allocation failed\n");
		exit(1);
		getchar();
	}

	finArr = radix(aArr, num, maxNum); // calls to a radix sort

	for (i = 0; i < num; i++) // prints finished sorted array
	{
		printf("%d ", finArr[i]);
	}
	printf("\n");
	getchar();
	free(aArr);
	free(finArr);
}

int* radix(int aArr[], int counter, int max) // func gets an array, size of array and max num and sorts the array number by their digits
{
	int i,j;
	int* bArr; // output arr

	bArr = (int*)malloc(counter * sizeof(int)); // allocatin memory
	if (bArr == NULL) // if allocation failed
	{
		printf("allocation failed\n");
		exit(1);
		getchar();
	}

	for (i = 1; max / i > 0; i *= 10) // a for loop to sort the array numbers by each digit. the num of digits is determined by the num of digits in max num
	{
		bArr = countSort(aArr, bArr, counter, i); // calls for a stable sorting func

		for (j = 0; j < counter; j++)// for loop to update the original array
		{
			aArr[j] = bArr[j];
		}

	}

	return bArr; // return sorted arr to main func
}

int* countSort(int aArr[], int bArr[], int counter, int k) // the func gets 2 arrays, size of arrays and k that will help to sort every number by different type of digit
{ // the sorting will be done by counting array with size of 10 for 10 digits and sort the number by different type of digits
	int tempArr[10] = {0}; // helping counting array, it will count the num of appearance of each digit
	int i;


	for (i = 0; i < counter; i++) // counts the num of appearance of each digit
	{
		tempArr[(aArr[i]/k) % 10 ]++;
	}
	for (i = 1; i < 10; i++)
	{
		tempArr[i] = tempArr[i] + tempArr[i - 1]; // accumulates the number of appearance so each num can be put in the right place in the output array
	}
	for (i = counter - 1; i >= 0; i--) // puts the numbers in a sorted way in the output array
	{
		bArr[tempArr[(aArr[i] / k) % 10]-1] = aArr[i];
		tempArr[(aArr[i]/k)%10]--;
	}
	return bArr;

}
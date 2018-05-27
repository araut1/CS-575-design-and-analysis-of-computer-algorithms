#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#define DEBUG

//global variables for backtracking solution
int num = 0;			 //number of items considered for the best case
int max_profit = 0;		 // maximum profit
int *include;			 //current tree solution
int *bestset;			 // best solution item include
int preorder_node_order; // node arrangement

// knapsack structure
struct knapsack
{
	int size;					  // number of items for the problem
	int *weight, *profit, *items; // arrays to hold size and capacity
	int capacity;				  // total capacity of the knapsack
};

// knapsack generation
struct knapsack *create_knapsack(int no_of_items)
{
	struct knapsack *k = malloc(sizeof(struct knapsack));
	k->size = no_of_items;
	k->items = malloc(sizeof(int) * no_of_items);
	k->weight = malloc(sizeof(int) * no_of_items);
	k->profit = malloc(sizeof(int) * no_of_items);
	memset(k->items, 0, sizeof(int) * no_of_items);
	memset(k->weight, 0, sizeof(int) * no_of_items);
	memset(k->profit, 0, sizeof(int) * no_of_items);
	k->capacity = -1;
	return k;
}

// swap functionality
void swap(int *arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

// prints knapsack functionality
void print_knapsack(struct knapsack *k)
{
	int i;
	printf("\nNumber of Items: %d\n", k->size);
	printf("Item:\t");
	for (i = 0; i < k->size; i++)
		printf(" %2d ", k->items[i]);
	printf("\n");
	printf("Weight:\t");
	for (i = 0; i < k->size; i++)
		printf(" %2d ", k->weight[i]);
	printf("\n");
	printf("Profit:\t");
	for (i = 0; i < k->size; i++)
		printf(" %2d ", k->profit[i]);
	printf("\nCapacity: %d\n", k->capacity);
}

// remove knapsack
int delete_knapsack(struct knapsack *k)
{
	free(k->weight);
	free(k->profit);
	free(k->items);
	free(k);
	return 0;
}

// knapsack initialization
void init_knapsack(struct knapsack *k)
{
	double total_weight = 0;
	double rate = 0.6;
	for (int i = 0; i < k->size; i++)
	{
		k->items[i] = i;
		k->profit[i] = rand() % 20 + 10;
		k->weight[i] = rand() % 15 + 5;
		total_weight += k->weight[i];
	}
	k->capacity = (int)(rate * total_weight);
}

// knapsack initialization other
void init_knapsack2(struct knapsack *k)
{
	for (int i = 0; i < k->size; i++)
	{
		k->items[i] = i;
	}
	k->profit[0] = 40;
	k->weight[0] = 2;
	k->profit[1] = 30;
	k->weight[1] = 5;
	k->profit[2] = 50;
	k->weight[2] = 10;
	k->profit[3] = 10;
	k->weight[3] = 5;
	k->capacity = 16;
}

// knapsack sorting
void sort_knapsack_nondecreasing(struct knapsack *k)
{
	int i, j;
	double pw1, pw2;
	for (i = 0; i < k->size; i++)
	{
		pw1 = (double)k->profit[i] / (double)k->weight[i];
		for (j = i + 1; j < k->size; j++)
		{
			pw2 = (double)k->profit[j] / (double)k->weight[j];

			if (pw2 > pw1)
			{
				swap(k->items, i, j);
				swap(k->weight, i, j);
				swap(k->profit, i, j);
				pw1 = pw2;
			}
		}
	}
}

// take input from user with validation
int getAlgorithmId()
{
	int x = -1;
	char ch;
	if (scanf("%d", &x) != 1)
	{
		while ((ch = getchar()) != '\n' && ch != EOF);
		printf("Please Enter a number\n");
		return getAlgorithmId();
	}
	return x;
}

// check range of AlgorithmId
int validateChoice(int algorithmId)
{
	if (algorithmId <= 0 || algorithmId >= 6)
	{
		return 1;
	}
	return 0;
}

// check if user wants to exit
void checkForExit(int algorithmId)
{
	if (algorithmId == 5)
	{
		printf("\nExiting...\n");
		exit(0);
	}
}

// developes power set
int **get_power_set(int set_size)
{
	int power_set_size = pow(2, set_size);
	int i, j;
	int **sets = (int **)malloc(power_set_size * sizeof(int *));
	for (i = 0; i < power_set_size; i++)
		sets[i] = (int *)malloc(set_size * sizeof(int));

	for (i = 0; i < power_set_size; i++)
	{
		for (j = 0; j < set_size; j++)
		{
			if (i & (1 << j))
				sets[i][j] = 1;
			else
				sets[i][j] = 0;
		}
	}
	return sets;
}








// main driver code
int main(void)
{
	//Algorithm selection by taking input from user
	int algorithmId = -1;
	struct knapsack *k;
	srand(time(NULL));

	// GUI to user
	while (1)
	{
		printf("\nAlgorithms:\n");
		printf("1. Brute Force Knapsack\n");
		printf("2. Dynamic programming Knapsack\n");
		printf("3. Backtracking Knapsack\n");
		printf("4. Run all Knapsack algorithms on SAME input\n");
		printf("5. Exit\n");
		printf("Enter  your choice\n");

		algorithmId = getAlgorithmId();
		if (validateChoice(algorithmId))
		{
			printf("\nInvalid choice.\nLet's start over!\n");
			continue;
		}
		// check if user want to exit
		checkForExit(algorithmId);
		//number of items selected between (exclusive) 4 to 8 and knapsack initialised
		k = create_knapsack(rand() % 3 + 5);
		init_knapsack(k);
		print_knapsack(k);

		// selection of algorithm
		switch (algorithmId)
		{
		case 1:
			brute_force_knapsack(k);
			delete_knapsack(k);
			break;
		case 2:
			dynamic_programming_knapsack(k);
			delete_knapsack(k);
			break;
		case 3:
			backtracking_knapsack(k);
			delete_knapsack(k);
			break;
		case 4:
			brute_force_knapsack(k);
			dynamic_programming_knapsack(k);
			backtracking_knapsack(k);
			delete_knapsack(k);
			break;
		default:
			printf("Improper!\n");
			break;
		}
	}
	return 0;
}

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

// first requirement of program
void brute_force_knapsack(struct knapsack *k)
{
	int **subsets = get_power_set(k->size);
	int current_total_weight, current_total_profit, best_weight = INT_MIN, best_profit = INT_MIN, best_subset = -1;
	int i, j;
	for (i = 0; i < pow(2, k->size); i++)
	{
		current_total_weight = 0;
		current_total_profit = 0;
		for (j = 0; j < k->size; j++)
		{
			//sum up items included
			if (subsets[i][j])
			{
				current_total_profit += k->profit[j];
				current_total_weight += k->weight[j];
			}
		}
		if (current_total_profit > best_profit && current_total_weight <= k->capacity)
		{
			best_profit = current_total_profit;
			best_subset = i;
			best_weight = current_total_weight;
		}
	}
	printf("\n-----------------------------");
	printf("\nBrute Force Solution");
	printf("\nTotal Profit:%d", best_profit);
	printf("\nItem\tWeight\tProfit\n");
	for (i = 0; i < k->size; i++)
	{
		if (subsets[best_subset][i])
		{
			printf("Item%d\t%d\t$%d\n", k->items[i], k->weight[i], k->profit[i]);
		}
	}
	printf("\nTotal Weight:%d", best_weight);
	printf("\n-----------------------------");
	for (i = 0; i < pow(2, k->size); i++)
		free(subsets[i]);
	free(subsets);
}

//sets the data structure which gives the items to be included in the solution
void set_include(int **include, int i, int w, int include_current, struct knapsack *k)
{
	if (include_current == 0)
	{
		include[i][w] = include[i - 1][w];
	}
	else
	{
		include[i][w] = include[i - 1][w - k->weight[i - 1]];
		include[i][w] = include[i][w] | (1 << i);
	}
}

void recursive_dp_knapsack(int **B, int i, int w, struct knapsack *k, int **include)
{
	int use_current, term1, term2;

	//first rule
	if (w <= 0 || i == 0)
	{

		B[i][0] = 0;
		return;
	}
	//check if solution already generated i.e. check redundancy
	if (B[i][w] != -1)
	{
		printf("............check2 encountered\n");
		return;
	}

	//second rule
	if (k->weight[i - 1] > w)
	{
		if (B[i - 1][w] == -1)
			recursive_dp_knapsack(B, i - 1, w, k, include);
		B[i][w] = B[i - 1][w];
		set_include(include, i, w, 0, k);
		return;
	}

	//check wether value already set or not
	if (B[i - 1][w] == -1)
	{
		recursive_dp_knapsack(B, i - 1, w, k, include);
	}
	term1 = B[i - 1][w];

	if (B[i - 1][w - k->weight[i - 1]] == -1)
	{
		recursive_dp_knapsack(B, i - 1, w - k->weight[i - 1], k, include);
	}
	term2 = B[i - 1][w - k->weight[i - 1]];

	if ((B[i - 1][w]) > (B[i - 1][w - k->weight[i - 1]] + k->profit[i - 1]))
	{
		B[i][w] = B[i - 1][w];
		set_include(include, i, w, 0, k);
	}
	else
	{
		B[i][w] = (B[i - 1][w - k->weight[i - 1]] + k->profit[i - 1]);
		set_include(include, i, w, 1, k);
	}
	return;
}

// print matrix functionality
void print_matrix(int **B, struct knapsack *k)
{
	int i, j;
	printf("B matrix after init:\n");
	for (i = 0; i <= k->size; i++)
	{
		for (j = 0; j <= k->capacity; j++)
		{
			printf(" %2d ", B[i][j]); //= -1;
		}
		printf("\n");
	}
}

// second program requirement: Implement the refinement algorithm of dynamic programming approach
void dynamic_programming_knapsack(struct knapsack *k)
{
	int **B;
	// to save item,encoded into bits. max no_of_items limited to 32
	int **include;
	int i, j;
	int total_weight = 0;
	B = malloc(sizeof(int *) * (k->size + 1));
	include = malloc(sizeof(int *) * (k->size + 1));

	for (i = 0; i < k->size + 1; i++)
	{
		B[i] = malloc(sizeof(int) * (k->capacity + 1));
		include[i] = malloc(sizeof(int) * (k->capacity + 1));
		memset(include[i], 0, sizeof(int) * (k->capacity + 1));
	}

	for (i = 0; i <= k->size; i++)
	{
		for (j = 0; j <= k->capacity; j++)
		{
			if (i == 0 || j == 0)
			{
				B[i][j] = 0;
			}
			else
			{
				B[i][j] = -1;
			}
		}
	}

	recursive_dp_knapsack(B, k->size, k->capacity, k, include);

	printf("\n-----------------------------");
	printf("\nDynamic programming Solution");
	printf("\nTotal Profit:%d", B[k->size][k->capacity]);
	printf("\nItem\tWeight\tProfit\n");
	int solution = include[k->size][k->capacity];
	for (i = 1; i < k->size + 1; i++)
	{
		if (solution & (1 << i))
		{
			printf("Item%d\t%d\t$%d\n", k->items[i - 1], k->weight[i - 1], k->profit[i - 1]);
			total_weight += k->weight[i - 1];
		}
	}
	printf("\nTotal Weight:%d", total_weight);
	printf("\n-----------------------------");
	for (i = 0; i < k->size + 1; i++)
	{
		free(include[i]);
		free(B[i]);
	}
	free(B);
	free(include);
}

int kwf2(int i, int weight, int profit, struct knapsack *k)
{
	int bound = profit;
	int j;
	double fraction;
	while (weight < k->capacity && i < k->size)
	{
		if ((weight + k->weight[i]) <= k->capacity)
		{
			weight += k->weight[i];
			bound += k->profit[i];
		}
		else
		{
			fraction = (double)(k->capacity - weight) / (double)k->weight[i];
			weight = k->capacity;
			bound += (fraction * (double)k->profit[i]);
		}
		i++;
	}
	return bound;
}

// implemting to find promising routes
int promising(struct knapsack *k, int i, int weight, int profit)
{
	int bound;
	if (weight > k->capacity)
	{
		return 0;
	}
	bound = kwf2(i, weight, profit, k);
	printf("UpperBound:%d\n", bound);
	return (bound > max_profit);
}

void knapsack(struct knapsack *k, int i, int profit, int weight)
{
	if (weight <= k->capacity && profit > max_profit)
	{
		max_profit = profit;
		num = i;
		memcpy(bestset, include, sizeof(int) * k->size);
	}
	printf("\nNode:%d\n", preorder_node_order++);
	printf("Total Profit:%d\n", profit);
	printf("Total Weight:%d\n", weight);
	if (promising(k, i, weight, profit))
	{
		printf("Promising\n");
		include[i] = 1;
		knapsack(k, i + 1, profit + k->profit[i], weight + k->weight[i]);
		include[i] = 0;
		knapsack(k, i + 1, profit, weight);
	}
	else
	{
		printf("Not promising\n");
	}
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

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

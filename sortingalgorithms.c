
int main()
{
	int algorithmId, n;

	printf("\n Select a sorting algorithm: \n");
	printf("Input 1  for Exchange Sort \n");
	printf("Input 2  for Insertion Sort \n");
	printf("Input 3  for Merge Sort \n");
	printf("Input 4  for Randomized Quick Sort \n\n");
	scanf("%d", &algorithmId);

	printf("\n\nYou have selected:  ");
	switch (algorithmId)
	{
	case 1:
		printf("Exchange Sort");
		break;

	case 2:
		printf("Insertion Sort");
		break;

	case 3:
		printf("Merge Sort");
		break;

	case 4:
		printf("Randomized Quick Sort");
		break;
	default:
		printf("Improper Input");
		return 0;
	}

	printf("\n\nFor sorting, provide Array size: n \n");
	scanf("%d", &n);

	if (n < 1 || n> 1000)
	{
		printf("Improper Input. \n");
		return 0;
	}
	else if (n > 20)
	{
		// array generation

		int arr[n];

		srand(time(NULL));
		for (int i = 0; i < n; i++)
		{
			arr[i] = (rand() % 1000 + 1);
		}

		printf("\n Array for sorting: \n");
		printArray(arr,n);
		
		// Algorith function call selection

		switch (algorithmId)
		{
		case 1:
			exchangeSort(arr,n);
			break;

		case 2:
			insertionSort(arr, n);
			break;

		case 3:
			mergeSort(arr, 0, n - 1);
			break;

		case 4:
			randomizedQuickSort(arr, 0, n-1);
			break;
		default:
			printf("\n Improper Input \n");
			return 0;
		}			

		printf("\n Sorted array \n");
		printArray(arr, n);
	}
	else
	{
		// array generation
		int arr[n];

		srand(time(NULL));
		for (int i = 0; i < n; i++)
		{
			arr[i] = (rand() % 14 + 1);
		}

		printf("\n Array for sorting: \n");
		printArray(arr, n);
		printf("\n");
		printStar(arr, n);
		
		// Algorithm Selection
		switch (algorithmId)
		{
		case 1:
			exchangeSort(arr, n);
			break;

		case 2:
			insertionSort(arr, n);
			break;

		case 3:
			mergeSortStar(arr, 0, n - 1);
			break;

		case 4:
			randomizedQuickSortStar(arr, 0, n - 1);
			break;
		default:
			printf("\n Improper Input \n");
			return 0;
		}
		
		printf("\n Sorted array: \n");
		printArray(arr, n);
		printf("\n");
		printStar(arr, n);
	}
		
	printf("\n");
	return 0;
}

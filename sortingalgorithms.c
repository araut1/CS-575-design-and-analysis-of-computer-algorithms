

//Exchange sort
void exchangeSort(int arr[], int n)
{
	int i, j,temp;
	for (i = 0; i < (n - 1); i++)
	{
		for (j = (i + 1); j < n; j++)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
		if (n<=20)
		{
			printStar(arr, n);
		}
	}
}

// Insertion sort
void insertionSort(int arr[], int n)
{
	int i, j, key;
	
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		if (n <= 20)
		{
			printStar(arr, n);
		}
	}
}


// Merge sort
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	
	int L[n1], R[n2];

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0; 
	k = l; 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r)
{
	printf("%d", r);
	if (l < r)
	{
		int m = l + (r - l) / 2;		
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);		
	}	
	
}

// Merge sort for  special case (n less than or equal to 20)
void mergeSortStar(int arr[], int l, int r)
{
	printf("%d", r);
	if (l < r)
	{
		int m = l + (r - l) / 2;
		mergeSortStar(arr, l, m);
		mergeSortStar(arr, m + 1, r);
		merge(arr, l, m, r);
		if ((r + 1) <= 20)
		{
			printStar(arr, (r + 1));
		}
	}

}

// Randomized Quick sort Algorithm
int partition(int arr[], int p, int r)
{
	srand(time(0));
	int pivot = rand() % (r - p);
	pivot += p;
	
	int swapTemp;
	
	swapTemp = arr[pivot];
	arr[pivot] = arr[r];
	arr[r] = swapTemp;

	pivot = r;
	int temp = arr[r];
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (arr[j] <  temp) {
			i++;
			swapTemp = arr[j];
			arr[j] = arr[i];
			arr[i] = swapTemp;
		}
	}
	i++;
	swapTemp = arr[i];
	arr[i] = arr[r];
	arr[r] = swapTemp;
	return i;
}

void randomizedQuickSort(int arr[], int p, int r)
{
	if (p < r)
	{
		int q = partition(arr, p, r);
		randomizedQuickSort(arr, p, q);
		randomizedQuickSort(arr, q + 1, r);	
	}
}

// Randomized Quick sort function for special case (n less than or equal to 20)
void randomizedQuickSortStar(int arr[], int p, int r)
{
	if (p < r)
	{
		int q = partition(arr, p, r);
		randomizedQuickSortStar(arr, p, q);
		randomizedQuickSortStar(arr, q + 1, r);

		if ((r + 1) <= 20)
		{
			printStar(arr, (r + 1));
		}
	}
}

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

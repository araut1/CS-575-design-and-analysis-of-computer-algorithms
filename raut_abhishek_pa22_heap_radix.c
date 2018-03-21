#include<stdio.h>
#include<stdlib.h>  
#include<time.h>

// Function to print an array
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d  ", arr[i]);
	}
	printf("\n");
}

// Function to print stars relative to value of integer in an array
void printStar(int arr[], int n)
{
	printf("\n Visualization:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < arr[i]; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	printf("\n");
}

// Heap Sort

// Function to heapify a subtree rooted with node i which is an index in arr[]. n : heap size
void heapify(int arr[], int n, int i)
{
	int largest = i;  // Initialize largest as root
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	// If left child is larger than root , make it as largest
	if (left < n && arr[left] > arr[largest])
		largest = left;

	// If right child is larger than largest so far
	if (right < n && arr[right] > arr[largest])
		largest = right;

	// If largest is not root
	if (largest != i)
	{
		// Swap implementaion
		int swapTemp;
		swapTemp = arr[largest];
		arr[largest] = arr[i];
		arr[i] = swapTemp;

		// Recursively heapify affected sub-tree
		heapify(arr, n, largest);
	}
}

// main function to do heap sort
void heapSort(int arr[], int n)
{
	// Building heap by rearranging array
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// extracting an element from heap one after the other
	for (int i = n - 1; i >= 0; i--)
	{
		// swap implementation to move current root to end
		int swapTemp;
		swapTemp = arr[i];
		arr[i] = arr[0];
		arr[0] = swapTemp;


		// max heapify on the reduced heap
		heapify(arr, i, 0);
		
		// code to print stars
		if (n <= 20)
		{
			printStar(arr, n);
		}

	}
}


// Radix Sort

// A utility function to get maximum value in an array
int getMax(int arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}

// A function to do counting sort which is used to implement radix sort, pow represents power 10 at a digit place (Ex. 1:10th power or 3:1000th power)
void countSort(int arr[], int n, int pow)
{
	// output array
	int output[n]; 
	int i, count[10] = { 0 };

	// Store count of occurrence of a digit in array count[]
	for (i = 0; i < n; i++)
		count[(arr[i] / pow) % 10]++;

	// count[] array containing actual position of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// output array
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / pow) % 10] - 1] = arr[i];
		count[(arr[i] / pow) % 10]--;
	}

	//output[] -> arr[] : putting sorted numbers
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

// The main function to that sorts array of size n using Radix Sort
void radixSort(int arr[], int n)
{
	// Find the maximum number to identify number of digits
	int max = getMax(arr, n);

	// Do counting sort for every digit, pow represents power 10 at a digit place (Ex. 1:10th power or 3:1000th power)
	for (int pow = 1; max / pow > 0; pow *= 10)
	{
		countSort(arr, n, pow);
		
		// code to print star
		if (n <= 20)
		{
			printStar(arr, n);
		}

	}
}

// main function
int main()
{
	int algorithmId, n;

	printf("\nSelect a sorting algorithm: \n");
	printf("Input 1  for Heap Sort \n");
	printf("Input 2  for Radix Sort \n");
	scanf("%d", &algorithmId);

	printf("\n\nYou have selected:  \n");
	switch (algorithmId)
	{
	case 1:
		printf("Heap Sort");
		break;

	case 2:
		printf("Radix Sort");
		break;

	default:
		printf("Improper Input!\n");
		return 0;
	}

	printf("\n\nFor sorting, provide the Array size: n \n");
	scanf("%d", &n);

	// Validation of value of n
	if (n < 1 || n> 1000)
	{
		printf("Improper Input! \n");
		return 0;
	}
	else if (n > 20)
	{
		
		int arr[n];
		
		// Array generation and Algorithm selection
		switch (algorithmId)
		{
		
			// Heap sort
			case 1:
			
			// array generation
			srand(time(NULL));
			for (int i = 0; i < n; i++)
			{
				arr[i] = rand();
			}

			printf("\n Array for sorting: \n");
			printArray(arr, n);
			heapSort(arr, n);
			break;


			// Radix Sort
			case 2:
			
			// array generation
			srand(time(NULL));
			for (int i = 0; i < n; i++)
			{
				arr[i] = (rand() % 1000);
			}

			printf("\n Array for sorting: \n");
			printArray(arr, n);
			radixSort(arr, n);
			break;

			default:
			printf("\nImproper Input! \n");
			return 0;
		}	
		
		printf("\nSorted array: \n");
		printArray(arr, n);
	}
	else
	{
		// array generation with range between 0 and 15
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
			heapSort(arr, n);
			break;

		case 2:
			radixSort(arr, n);
			break;

		default:
			printf("\nImproper Input! \n");
			return 0;
		}

		printf("\n Sorted array: \n");
		printArray(arr, n);
		printf("\n");
		printStar(arr, n);
	}
	return 0;
}
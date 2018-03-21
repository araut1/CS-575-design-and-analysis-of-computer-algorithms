#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

/*  Code implementation to raise an integer to the power of another integer, we are validating parameter 'exp' to be non-negative by validating
	n in main() function as: positive & multiple of k and use of floor function while calculating m in function calculateProd()
*/
unsigned long long calculatePower(unsigned long long base, unsigned long long exp)
{
	unsigned long long result = 1;
	while (exp)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		base *= base;
	}

	return result;
}

// function to calculate floor of a number
unsigned long long calculateFloor(double x)
{
	if (x>0)return (unsigned long long)x;
	return (unsigned long long)(x - 0.9999999999999999);
}

// generate number A of size n
unsigned long long generateA(unsigned long long n)
{
	int a[n];

	srand(time(0));
	a[0] = rand() % 9 + 1;
	for (int i = 1; i<n; i++)
		a[i] = rand() % 10;

	unsigned long long num = 0;
	for (int i = 0; i < n; i++)
		num = 10 * num + a[i];

	return num;
}

// generate number B of size n
unsigned long long generateB(unsigned long long n)
{
	int a[n];

	//	srand(time(0));
	a[0] = rand() % 9 + 1;
	for (int i = 1; i<n; i++)
		a[i] = rand() % 10;

	unsigned long long num = 0;
	for (int i = 0; i < n; i++)
		num = 10 * num + a[i];

	return num;
}

/* This function is used to calculate maximumm digits for a numbe rin a list, it can be redundant code as both input numbers are of same size
we included this code to show logic of algorithm
*/
unsigned long long noOfDigit(unsigned long long m, unsigned long long n)
{
	unsigned long long max;
	int b = 0;
	if (m >= n)
		max = m;
	else
		max = n;
	while (max>0)
	{
		max = max / 10;
		b++;
	}
	return b;
}

// class algorithm implementation
unsigned long long calculateProd(unsigned long long u, unsigned long long v)
{
	unsigned long long x, y, w, z;
	unsigned long long n, m, p, q, r;

	// Redundant function call, as both the number generated are of size n we can pass value of n to function
	n = noOfDigit(u, v);

	if (u == 0 || v == 0)
	{
		return 0;
	}

	else if (n <= 2)
	{
		return (u*v);
	}
	else
	{
		m = calculateFloor(n / 2);

		x = u / calculatePower(10, m);
		y = u % (unsigned long long)calculatePower(10, m);
		w = v / calculatePower(10, m);
		z = v % (unsigned long long)calculatePower(10, m);

		p = calculateProd(x, w);
		q = calculateProd(y, z);
		r = calculateProd( x + y, w + z);

		return p * calculatePower(10, 2 * m) + (r - p - q) * calculatePower(10, m) + q;
	}
}

// custom algorithm
unsigned long long calculateCustomProd(unsigned long long u, unsigned long long v)
{
	unsigned long long n, m, x, y, z, p, q, r;

	// Redundant function call, as both the number generated are of size n we can pass value of n to function
	n = noOfDigit(u, v);

	if (u == 0 || v == 0)
	{
		return 0;
	}

	else if (n <= 2)
	{
		return (u*v);
	}
	else
	{
		m = calculateFloor(n / 3);

		x = u / calculatePower(10, 2*(m));
		y = (u % (unsigned long long)calculatePower(10, 2 * (m))) / calculatePower(10, m);
		z = u % calculatePower(10, m);

		p = v / calculatePower(10, 2 * (m));
		q = (v % (unsigned long long)calculatePower(10, 2 * (m))) / calculatePower(10, m);
		r = v % calculatePower(10, m);

		return calculateCustomProd(x,p) * calculatePower(10, 4 * m) +
			(calculateCustomProd(x,q)+ calculateCustomProd(y,p))* calculatePower(10, 3*m) +
			(calculateCustomProd(x, r) + calculateCustomProd(y, q) + calculateCustomProd(p,z) ) * calculatePower(10, 2 * m) +
			(calculateCustomProd(y,r) + calculateCustomProd(z, q) )* calculatePower(10, m) +
			calculateCustomProd(z,r);
	}
}

// main function
int main()
{
	// input variable n
	unsigned long long n;
	unsigned long long prod, customProd;
	unsigned long long A, B;
	printf("Enter the size of numbers to be multiplied (should be multiple of 6 and greater than 0): \n");
	scanf("%d", &n);
	printf("\n");

	// validate value of n as 6k k is positive
	if (n <= 0 || (n % 6 != 0))
	{
		printf("Improper Input!\n\n");
		return 0;
	}

	// generate and print A and B following the condition 1-9
	A = generateA(n);

	B = generateB(n);

	printf("Numbers generated for mutiplication: %llu & %llu \n",A,B);


	// A*B using the class algortihm
	prod = calculateProd(A, B);

	// A*B using the custom algorithm
	customProd = calculateCustomProd(A, B);

	// verifying result
	if (prod == customProd)
	{
		printf("\nSAME RESULT! For multiplication of %llu and %llu :\nClass Algorithm product: %llu\nCustom Algorithm Product: %llu\n", A, B, prod,customProd);
	}
	else
	{
		printf("\nDIFFERENT RESULT! For multiplication of %llu and %llu :\nClass Algorithm product: %llu\nCustom Algorithm Product: %llu\n", A, B, prod, customProd);
	}
	
	printf("\n");
	return 0;
}
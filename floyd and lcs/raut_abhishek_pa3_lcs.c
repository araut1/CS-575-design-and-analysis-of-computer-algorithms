#include<stdio.h>
#include<string.h>

// finds maximum out of two integers
int max(int a, int b);

// function finds LCS and and length of LCS
void findLCS(char *X, char *Y, int XLen, int YLen);

int max(int a, int b)
{
	return (a > b)? a : b;
}

void findLCS(char *X, char *Y, int XLen, int YLen) 
{
	int L[XLen + 1][YLen + 1];
	int r, c, i;

	// to find the length of the LCS
	
	for(r = 0; r <= XLen; r++) 
        {
		for(c = 0; c <= YLen; c++) 
                {
			if(r == 0 || c == 0)
                        {
				L[r][c] = 0;
			} 
                        else if(X[r - 1] == Y[c - 1]) 
                        {
				L[r][c] = L[r - 1][c - 1] + 1;
			} 
                        else 
                        {
				L[r][c] = max(L[r - 1][c], L[r][c - 1]);
			}
		}
 	}

	// finds LCS

	r = XLen;
	c = YLen;
	i = L[r][c];

	char LCS[i+1];
        LCS[i] = '\0';

 	while(r > 0 && c > 0)
        {
		if(X[r - 1] == Y[c - 1]) 
                {
			LCS[i - 1] = X[r - 1];
			i--;
			r--;
			c--;
		} 
                else if(L[r - 1][c] > L[r][c - 1])
                {
			r--;
		} 
                else
                {
			c--;
		}
	}

	//print result
	printf("\nLength of the LCS: %d\n", L[XLen][YLen]);
	printf("And LCS: %s\n\n", LCS);
}

// main function with argument as two strings
int main(int argc, char** argv)
{
	//the two sequences
	char* X = argv[1];
   	char* Y = argv[2];
	printf("\nString 1: %s\nString 2: %s\n", X,Y);

	//length of the sequences
	int XLen = strlen(X);
	int YLen = strlen(Y);

	findLCS(X, Y, XLen, YLen);

	return 0;
}

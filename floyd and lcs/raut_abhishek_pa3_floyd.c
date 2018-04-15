#include<stdio.h>
#include<stdlib.h>  
#include<math.h>
#include<time.h>

int path[10][10];
int A[10][10];

void route(int i,int j)
{
    if (path[i][j]==-1)
    {
        return;
    }
    route(i,path[i][j]);
    printf("v%d ",path[i][j]+1);
    route(path[i][j],j);
}

void dispath(int n)
{
    int i,j;
    printf("\nAll pairs shortest paths using Floyds algorithm: \n\n");
    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            if (i != j && i < j) 
            {
                printf("From %d to %d shortest path length = %d | shortest path => v%d ",i+1,j+1,A[i][j],i+1);
                route(i,j);
                printf("v%d \n",j+1);
            }
        }
    }
}

void floyd(int **matrixA, int n)
{
    int i,j,k;
    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            A[i][j]=matrixA[i][j];
            path[i][j]=-1;
        }
    }
    for (k=0;k<n;k++)
    {
        for (i=0;i<n;i++)
        {
            for (j=0;j<n;j++)
            {
                if (A[i][j]>A[i][k]+A[k][j])
                {
                    A[i][j]=A[i][k]+A[k][j];
                    path[i][j]=k;
                }
            }
        }
    }
    dispath(n);
}

int main(void)
{
    srand(time(NULL));
    int n;
    n = (rand() % (10-5+1)+5);
    printf("Randomly selected %d(n) vertices.\n",n);

    //    int matrixA [n+1][n+1]; 
   /*  
    int **matrixA;

    // error
    matrixA = int *[n+1];
    
    for (int i = 0; i<n; i++) {
    
        // error
        matrixA[i] = int[n+1];
    }
    */

    int r=n+1;
    int c=r;
    int *matrixA[r];
    for (int i=0; i<r; i++)
        matrixA[i] = (int *)malloc(c * sizeof(int));

    for (int i = 0; i<n; i++)
    {
        matrixA[i][i] = 0;
    }
    for (int i = 0; i<n; i++)
     {
        for (int j = 1; j<n ; j++) 
        {
            if (i != j && i < j)
            {
                matrixA[i][j] = rand() % n + 1;
                matrixA[j][i] = matrixA[i][j];
            }
        }
    }
    // 	Display	the	generated	adjacency	matrix
    printf("\nGenerated Adjacency matrix: \n\n");

    for (int i = 0; i<n; i++) 
    {
        for (int j = 0; j<n; j++) 
        {
            printf("%d ",matrixA[i][j]);
        }
        printf("\n");
    }
    floyd(matrixA, n);
    printf("\n");
  
    return 0;
}

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#define DEBUG


// driver program to test MST algo
// *** didn’t pass any parameter to main() function
int main(void)
{
    int algorithmId = -1; //Algorithm selection 
    srand(time(NULL));
    
    while (1)
    {
        printDialog();
        algorithmId = getInput();
        
        if (validateChoice(algorithmId))
        {
            printf("\nImproper Input! Enter the choice again!\n\n");
            continue;
        }

        checkForExit(algorithmId);
        
        // if everything is validated
        initialiseGraph();
        printGraph();
        switch (algorithmId)
        {
        case 1:
            printf("\nPrim’s minimum spanning tree algorithm selected!\n");
            primsMSTheap(); //  Prim’s minimum spanning tree algorithm by programing priority queue either as heap data structure
            //primsMSTarray(); //  Prim’s minimum spanning tree algorithm by programing priority queue either as array data structure
            break;
        case 2:
            printf("\nKruskal’s minimum spanning tree algorithm selected!\n");
            kruskalsMST();
            break;

        default:
            printf("Improper Input!\n");
            break;
        }
    }
    return 0;
}
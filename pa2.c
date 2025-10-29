#include <stdio.h>
#include "pa2structs.h"
#include "memory.h"
#include "fileman.h"
#include "DPfunc.h"

void DebugPrintHead(treeNode* root)
{
    if (!root) return;

    printf("\n\n");

    printf("All possible configurations:\n");
    printf("%d\n", root -> size);

    int n = root -> size;
    int i;
    int area = root -> x[0] * root -> y[0];
    int areaIndex = 0;
    int tempArea;

    for (i = 0; i < n; i++)
    {
        printf("(%d,%d) ", root -> x[i], root -> y[i]);
    }
    printf("\n\n");

    for (i = 1; i< n; i++)
    {
        tempArea = root -> x[i] * root -> y[i];
        if (tempArea < area)
        {
            area = tempArea;
            areaIndex = i;
        }
    }
    printf("(%d,%d)\n", root -> x[areaIndex], root -> y[areaIndex]);
}

int main (int argc, char *argv[])
{
    treeNode* root = readInputFile(argc, argv);
    
    makeOutFile1(root, argv);

    makeOutFile2(root, argv);

    DP(root);

    DebugPrintHead(root);

    deleteTree(root);
    return 0;
}
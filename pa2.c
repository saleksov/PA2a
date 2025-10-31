#include <stdio.h>
#include "pa2structs.h"
#include "memory.h"
#include "fileman.h"
#include "DPfunc.h"

int main (int argc, char *argv[])
{
    treeNode* root = readInputFile(argc, argv);
    
    if (root)
    {
        root -> xCord = 0;
        root -> yCord = 0;
    }

    makeOutFile1(root, argv, 2);

    makeOutFile2(root, argv, 3);

    DP(root);

    FindOptimalComb(root);

    makeOutFile1(root, argv, 4);

    makeOutFile2(root, argv, 5);

    deleteTree(root);
    return 0;
}
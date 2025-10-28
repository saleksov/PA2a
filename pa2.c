#include <stdio.h>
#include "pa2structs.h"
#include "memory.h"
#include "fileman.h"

void debugPrint(treeNode* node)
{
    if(!node) return;
    debugPrint(node->left);
    debugPrint(node->right);

    printf("%d(%d,%d)\n", node->label, node->x[0], node->y[0]);
}

int main (int argc, char *argv[])
{
    treeNode* root = readInputFile(argc, argv);
    
    makeOutFile1(root, argv);

    makeOutFile2(root, argv);

    deleteTree(root);
    return 0;
}
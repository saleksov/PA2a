#include <stdio.h>
#include "pa2structs.h"
#include "memory.c"
#include "fileman.c"

int main (int argc, char *argv[])
{
    treeNode* root = readInputFile(argc, argv);
    
    deleteTree(root);
    return 0;
}
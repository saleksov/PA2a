#include <stdio.h>
#include "pa2structs.h"
#include "memory.h"
#include "fileman.h"

int main (int argc, char *argv[])
{
    treeNode* root = readInputFile(argc, argv);
    
    deleteTree(root);
    return 0;
}
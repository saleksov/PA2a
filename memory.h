#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdlib.h>
#include "pa2structs.h"
#include <stdio.h>

treeNode* popStack(StackNode** stack);
StackNode* pushStack(StackNode* stack, treeNode* Node);

treeNode * makeLeafNode(int label, int * x, int * y, int size);
treeNode * makeInternalNode(int label, treeNode * right, treeNode * left);

void deleteTree(treeNode * node);

#endif


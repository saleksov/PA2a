#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdlib.h>
#include "pa2structs.h"
#include <stdio.h>

listNode * makeTree(FILE * Input);

listNode * makeListNode();

void deleteList(listNode * node);
void deleteTree(treeNode * node);

#endif


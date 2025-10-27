#ifndef __PA2STRUCTS_H__
#define __PA2STRUCTS_H__

#include <stdio.h>

#define H -6
#define V -7

// main node for my boxes

typedef struct treeNode {
    int label; // if > 0 real box, if < 0 cut
    
    int * x;
    int * y;
    int size;

    struct treeNode * left;
    struct treeNode * right;
} treeNode;

typedef struct StackNode {
    treeNode * node;
    struct StackNode * next;
} StackNode;

#endif
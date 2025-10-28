#include "memory.h"

treeNode * makeInternalNode()
{
    treeNode * node = (treeNode*)malloc(sizeof(treeNode));
    if (!node) exit(EXIT_FAILURE);

    node -> size = 1;

    node -> xCord = 0;
    node -> yCord = 0;

    node -> x = (int*)malloc(sizeof(int));
    node -> y = (int*)malloc(sizeof(int));

    return node;
}

treeNode * makeLeafNode(int label, int * x, int * y, int size)
{
    treeNode * node = (treeNode*)malloc(sizeof(treeNode));
    if (!node) exit(EXIT_FAILURE);

    node -> label = label;
    node -> size = size;

    node -> left = NULL;
    node -> right = NULL;

    node -> xCord = 0;
    node -> yCord = 0;

    node -> x = (int*)malloc(size * sizeof(int));
    node -> y = (int*)malloc(size * sizeof(int));

    if (!node -> x || !node -> y) exit(EXIT_FAILURE);

    for (int i = 0; i < size; i++)
    {
        node -> x[i] = x[i];
        node -> y[i] = y[i];
    }

    return node;
}

StackNode* pushStack(StackNode* stack, treeNode* Node)
{
    StackNode* stackNode = (StackNode*)malloc(sizeof(StackNode));
    if(!stackNode) exit(EXIT_FAILURE);

    stackNode -> node = Node;
    stackNode -> next = stack;

    return stackNode;
}

treeNode* popStack(StackNode** stack)
{
    if (!stack || !(*stack)) return NULL;

    StackNode* temp = *stack;

    treeNode* Node = temp -> node;

    *stack = temp -> next;
    free(temp);

    return Node;
}


void deleteTree(treeNode * node)
{
    if (node)
    {
        if(node -> x)
            free(node -> x);
        if(node -> y)
            free(node -> y);

        deleteTree(node -> left);
        deleteTree(node -> right);
        free(node);
    }
}
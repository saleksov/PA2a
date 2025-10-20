#include "memory.h"

static treeNode* popStack(StackNode** stack);
static StackNode* pushStack(StackNode* stack, treeNode* Node);

listNode * makeTree(FILE * Input)
{
    StackNode * stack = NULL;
    treeNode * node = NULL;
    char line;
    int label;
    int x;
    int y;

    while(fgets(line, sizeof(line), Input)){
        if (leaf)
        {
            node = (treeNode *)malloc(sizeof(treeNode));
            node -> left = NULL;
            node -> right = NULL;
            node -> label = label;

            node -> xy = makeListNode(x,y,NULL);
            // WHAT IF THERE ARE MULTIPLE x and Ys?
        }
        else if (internal)
        {
            node = (treeNode *)malloc(sizeof(treeNode));
            node -> right = popStack(&stack);
            node -> left  = popStack(&stack);

            if (!node->left || !node->right) 
                exit(EXIT_FAILURE);

            if (V???) node -> label = V;
            if (H???) node -> label = H;

            node -> xy = NULL;

            stack = pushStack(stack, node);
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }

    node = popStack(&stack);

    if (stack != NULL)
    {
        exit(EXIT_FAILURE);  
    }

    return node;
}

static StackNode* pushStack(StackNode* stack, treeNode* Node)
{
    StackNode* stackNode = (StackNode*)malloc(sizeof(StackNode));
    if(!stackNode) exit(EXIT_FAILURE);

    stackNode -> node = Node;
    stackNode -> next = stack;

    return stackNode;
}

static treeNode* popStack(StackNode** stack)
{
    if (!stack || !(*stack)) return NULL;

    StackNode* temp = *stack;

    treeNode* Node = temp -> node;

    *stack = temp -> next;
    free(temp);

    return Node;
}

listNode * makeListNode(int x, int y, listNode * next)
{
    listNode * node = (listNode*)malloc(sizeof(listNode));
    node -> next = next;
    node -> x = x;
    node -> y = y;
    return node;
}

void deleteList(listNode * node)
{
    if (node)
    {
        deleteList(node -> next);
        free(node);
    }
}

void deleteTree(treeNode * node)
{
    if (node)
    {
        deleteList(node -> xy);
        deleteTree(node -> left);
        deleteTree(node -> right);
        free(node);
    }
}
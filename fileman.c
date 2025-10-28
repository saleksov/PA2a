#include "fileman.h"

treeNode * readInputFile(int argc, char *argv[])
{
    if (argc != 5)
        exit(EXIT_FAILURE); // Invalid input
    
    FILE *inputFile1 = fopen(argv[1], "r");

    if (inputFile1 == NULL)
    {
        exit(EXIT_FAILURE); // FAILED TO OPEN FIRST INPUT FILE
    }

    StackNode *stack = NULL;
    treeNode* temp = NULL;

    int x[1000];
    int y[1000];
    int maxSize = 0;

    char c;
    int label;
    while (((c = fgetc(inputFile1)) != EOF))
    {
        if (c > 65) // is a character
        {
            if (c == 'H')
                label = H;
            else
                label = V;

            temp = makeInternalNode(label);
            temp -> right = popStack(&stack);
            temp -> left = popStack(&stack);

            stack = pushStack(stack, temp);

            while ((c = fgetc(inputFile1)) != '\n' && c != EOF);
        }
        else
        {
            ungetc(c, inputFile1);
            fscanf(inputFile1, "%d", &label);
            fgetc(inputFile1); // Get rid of leading '('

            while(fscanf(inputFile1, "(%d,%d)", &x[maxSize], &y[maxSize]) == 2)
            {
                maxSize++;
            }
            
            temp = makeLeafNode(label, x, y, maxSize);
            stack = pushStack(stack, temp);
            maxSize = 0;

            while ((c = fgetc(inputFile1)) != '\n' && c != EOF);
        }     
    }

    temp = popStack(&stack);
    
    if (stack != NULL)
    {
        exit(EXIT_FAILURE);
    }

    fclose(inputFile1);

    return temp;
}
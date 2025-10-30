#include "fileman.h"

static void outFile2Coords(treeNode* node);
static void writeOutFile2(treeNode* node, FILE* outputFile2);

treeNode * readInputFile(int argc, char *argv[])
{
    if (argc != 6)
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
            
            temp = makeInternalNode();
            temp -> right = popStack(&stack);
            temp -> left = popStack(&stack);

            if (c == 'H')
            {  
                temp -> label = H;
                temp->x[0] = (temp->left->x[0] > temp->right->x[0]) ? temp->left->x[0] : temp->right->x[0];
                temp->y[0] = temp->left->y[0] + temp->right->y[0];
            }
            else if (c == 'V')
            {
                temp -> label = V;
                temp->x[0] = temp->left->x[0] + temp->right->x[0];
                temp->y[0] = (temp->left->y[0] > temp->right->y[0]) ? temp->left->y[0] : temp->right->y[0];
            }
            else
            {
                // Why are we here?
                exit(EXIT_FAILURE); // INVALID CHARACTER
            }

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

// 1 and 2 related code are from my 368 PA2

void makeOutFile1(treeNode* root, char *argv[], int i)
{
    FILE *outputFile1 = fopen(argv[i], "w");

    if (outputFile1 == NULL)
    {
        exit(EXIT_FAILURE); // FAILED TO OPEN FIRST OUTPUT FILE
    }

    fprintf(outputFile1, "(%d,%d)\n", root->x[0], root->y[0]);

    fclose(outputFile1);
}

void makeOutFile2(treeNode* root, char *argv[], int i)
{
    FILE *outputFile2 = fopen(argv[i], "w");

    if (outputFile2 == NULL)
    {
        exit(EXIT_FAILURE); // FAILED TO OPEN SECOND OUTPUT FILE
    }

    outFile2Coords(root);

    writeOutFile2(root, outputFile2);

    fclose(outputFile2);
}

static void writeOutFile2(treeNode* node, FILE* outputFile2)
{
    if (!node) return;

    writeOutFile2(node->left, outputFile2);
    writeOutFile2(node->right, outputFile2);

    if (node->label > 0)
        fprintf(outputFile2, "%d((%d,%d)(%d,%d))\n", node->label, node->x[0], node->y[0], node->xCord, node->yCord);
}

static void outFile2Coords(treeNode* node)
{
    if (!node) return;

    if (node->label == H)
    {
        node->left->xCord = node->xCord;
        node->left->yCord = node->yCord + node->right->y[0];

        node->right->xCord = node->xCord;
        node->right->yCord = node->yCord;

        outFile2Coords(node->left);
        outFile2Coords(node->right);
    }
    else if (node->label == V)
    {
        node->right->yCord = node->yCord;
        node->right->xCord = node->xCord + node->left->x[0];

        node->left->xCord = node->xCord;
        node->left->yCord = node->yCord;

        outFile2Coords(node->left);
        outFile2Coords(node->right);
    }
}
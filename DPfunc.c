#include "DPfunc.h"

// Sorting the leaf nodes

static void processLeafNodes(treeNode *node);
static void processInternalNode(treeNode *node);

void DP(treeNode *node)
{
    if (!node)
        return;

    DP(node->left);
    DP(node->right);

    if (node->label > 0)
    {
        processLeafNodes(node);
    }
    else
    {
        processInternalNode(node);
    }
}

static void processLeafNodes(treeNode *node)
{
    // Sort based on Decreasing Height

    int n = node->size;
    int j, i;
    int tempX, tempY;
    for (i = 1; i < n; i++)
    {
        tempX = node->x[i];
        tempY = node->y[i];
        j = i - 1;

        while (j >= 0 && node->y[j] < tempY)
        {
            node->x[j + 1] = node->x[j];
            node->y[j + 1] = node->y[j];
            j--;
        }
        node->x[j + 1] = tempX;
        node->y[j + 1] = tempY;
    }

    // Prune dominated boxes
    int *keep = (int *)malloc(n * sizeof(int));
    int k = 0;
    for (i = 0; i < n; i++)
    {
        keep[i] = 1;

        for (j = i + 1; j < n; j++)
        {   
            
            if (node->x[j] <= node->x[i])
            {
                keep[i] = 0;
                
                break;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        if (keep[i] == 1)
        {
            node->x[k] = node->x[i];
            node->y[k] = node->y[i];
            k++;
        }
    }
    node->size = k;

    free(keep);

    // Tested, works fine.
}

static void processInternalNode(treeNode *node)
{

    // Clean the combinations I made for out file 1
    if (node->x || node->y)
    {
        free(node->x);
        free(node->y);
    }

    int j; // Optimal form other set index
    int i;
    int n = node->left->size;
    int m = node->right->size;

    int nm = n + m;

    node->x = (int *)malloc(nm * sizeof(int));
    node->y = (int *)malloc(nm * sizeof(int));

    nm = 0;

    int *leftX = node->left->x;
    int *leftY = node->left->y;
    int *rightX = node->right->x;
    int *rightY = node->right->y;

    int Threshold;

    if (node->label == H)
    {
        j = 0;

        while (j < m) // Skip leading Xs
        {
            if (rightX[j] <= leftX[0])
            {
                j++;
            }
            else
            {
                j--;
                break;
            }
        }

        if (j == m)
            j--;

        if (j < 0)
            j=0; 

        for (i = 0; i < n; i++)
        {
            if (j >= m) // I dont think this does anything, but im going to keep it.
                break;

            // Look Left Once
            if (rightX[j] <= leftX[i])
            {
                // Make Pair, we know i is max width
                node->x[nm] = leftX[i];
                node->y[nm] = leftY[i] + rightY[j];
                nm++;
            }

            // Either increase j or continue
            // Are we the last i ?
            Threshold = (i == n - 1) ? __INT_MAX__ : leftX[i + 1];

            while (rightX[j] < Threshold)
            {
                if (rightX[j] > leftX[i]) // Are we in between
                {
                    node->x[nm] = rightX[j];
                    node->y[nm] = rightY[j] + leftY[i];
                    nm++;
                }

                j++;

                if (j == m)
                {
                    j--;
                    break;
                }

                if (rightX[j] >= Threshold)
                {
                    j--;
                    break;
                }    
            }
        }
        node -> size = nm;
    }
    else if (node->label == V)
    {
        // Do nothing yet
        node -> size = 3;
        node -> x[0] = 10;
        node -> y[0] = 10;
        node -> x[1] = 20;
        node -> y[1] = 20;
        node -> x[2] = 100;
        node -> y[2] = 100;

        // cannot start with j = n -1 because then I would have to reverse my list at the end
        // big with j = 0
        // For all j with height > yi[0] generate combinations
        // for all i, generate 0-k combinations left
        // generate 1 combination to the right.
        // go to next node, repeat.
    }  
}
#ifndef __FILEMAN_H__
#define __FILEMAN_H__

#include <stdlib.h>
#include "pa2structs.h"
#include <stdio.h>

treeNode * readInputFile(int argc, char *argv[]);

void makeOutFile1(treeNode* root, char *argv[]);
void makeOutFile2(treeNode* root, char *argv[]);
void makeOutFile3(treeNode* root, char *argv[]);

#endif